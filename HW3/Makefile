######################################
# Makefile
# 
# Author: Simon Lee (sijlee)
# Date Created: Mar 01, 2016
# Date Last Modified: Mar 01, 2016
# Assignment HW3
# Part of: C335 assignment
#

OBJECT=hw3
$(OBJECT): $(OBJECT).o
	@gcc -o $(OBJECT) $(OBJECT).o
	@rm $(OBJECT).o
$(OBJECT).o: $(OBJECT).c
	@gcc -c $(OBJECT).c

clean:
	@rm *.o
