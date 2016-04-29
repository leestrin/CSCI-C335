#Simon Lee
#C335 HW0

OBJECT=rpn
$(OBJECT): $(OBJECT).o
	@gcc -o $(OBJECT) $(OBJECT).o
	@rm $(OBJECT).o
$(OBJECT).o: $(OBJECT).c
	@gcc -c $(OBJECT).c

clean:
	@rm *.o
