/* audio.c ---
 *
 * Filename: audio.c
 * Description: Main logic of audio
 * Author:
 * Maintainer:
 * Created: Thu April 15, 2016
 * Last-Updated: Sunday April 24, 2016
 *           By: Brandon Burzon, Simon Lee
 *     Update #: 30
 * Keywords:
 * Compatibility: Backward complatible
 *
 */

/* Commentary: nO comments
 *
 *
 *
 */

/* Change log: lots
 *
 *
 */
/* Code: */

#include "audio.h"

void readckhd(FIL *fid, struct ckhd *hd, uint32_t ckID) {
  f_read(fid, hd, sizeof(struct ckhd), &ret);
  if (ret != sizeof(struct ckhd)) {
    printf("po, exiting\n");
    exit(-1);
  }
  if (ckID && (ckID != hd->ckID)) {
    printf("ckID && (ckID != hd->ckID)\n");
    exit(-1);
  }
}

void die (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  while (1);
}

int play_selected_file(char *filename) {
  FRESULT rc;			/* Result code */
  DIR dir;			/* Directory object */
  FILINFO fno;			/* File information object */
  UINT bw, br;
  unsigned int retval;
  int bytesread;

  printf("\nOpen %s\n", filename);
  rc = f_open(&fid, filename, FA_READ);

  printf("opened file with rc: %d\n", rc);

  if (!rc) {
    printf("Success opening file\n");
    struct ckhd hd;
    uint32_t  waveid;
    struct fmtck fck;

    readckhd(&fid, &hd, 'FFIR');

    f_read(&fid, &waveid, sizeof(waveid), &ret);
    if ((ret != sizeof(waveid)) || (waveid != 'EVAW'))
      return -1;

    readckhd(&fid, &hd, ' tmf');

    f_read(&fid, &fck, sizeof(fck), &ret);

    // skip over extra info

    if (hd.cksize != 16) {
      printf("extra header info %d\n", hd.cksize - 16);
      f_lseek(&fid, hd.cksize - 16);
    }

    printf("audio format 0x%x\n", fck.wFormatTag);
    printf("channels %d\n", fck.nChannels);
    printf("sample rate %d\n", fck.nSamplesPerSec);
    printf("data rate %d\n", fck.nAvgBytesPerSec);
    printf("block alignment %d\n", fck.nBlockAlign);
    printf("bits per sample %d\n", fck.wBitsPerSample);

    // now skip all non-data chunks !

    while(1){
      printf("skipping all non-data chunks\n");
      readckhd(&fid, &hd, 0);
      if (hd.ckID == 'atad')
        break;
      f_lseek(&fid, hd.cksize);
    }

    printf("Samples %d\n", hd.cksize);

    f_read(&fid, Audiobuf, AUDIOBUFSIZE, &ret);
    hd.cksize -= ret;
    audioplayerStart();
    while (hd.cksize) {
      int next = hd.cksize > AUDIOBUFSIZE/2 ? AUDIOBUFSIZE/2 : hd.cksize;
      if (audioplayerHalf) {
        if (next < AUDIOBUFSIZE/2)
          bzero(Audiobuf, AUDIOBUFSIZE/2);
        f_read(&fid, Audiobuf, next, &ret);
        hd.cksize -= ret;
        audioplayerHalf = 0;
      }
      if (audioplayerWhole) {
        if (next < AUDIOBUFSIZE/2)
          bzero(&Audiobuf[AUDIOBUFSIZE/2], AUDIOBUFSIZE/2);
        f_read(&fid, &Audiobuf[AUDIOBUFSIZE/2], next, &ret);
        hd.cksize -= ret;
        audioplayerWhole = 0;
      }
    }
    audioplayerStop();
  }

  printf("\nClose the file.\n");
  rc = f_close(&fid);

  if (rc) die(rc);
  return 0;
}

/* end of audio.c */
