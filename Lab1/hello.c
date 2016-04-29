/* Simon Lee
   CSCI-C335 Lab1
 */

#include<stdio.h>
#include<unistd.h>

int main(void) {
  //variables for counters  
  int timeCounter = 0;
  int printCounter = 0;
  //while true (infinite loop)
  while(1){
    //keep making file stream
    FILE *input;
    //called helloInfo.txt
    input = fopen("helloInfo.txt", "w");
    //add time counter by 3 since this will loop every 3 seconds
    timeCounter += 3;
    //add printer counter by 1 for every loop it takes
    printCounter += 1;
    //record information on file stream
    fprintf(input, "%d seconds has been passed after execution.", timeCounter);
    fprintf(input, " Printed \"Hello, World!\" %d times.", printCounter);
    //close the file (it will overewrite when loop restarts)
    fclose(input);
   
    //prints Hello, World!
    printf("Hello, World!\n");
    //wait for 3 seconds
    sleep(3);
  }

  return 0;
}
