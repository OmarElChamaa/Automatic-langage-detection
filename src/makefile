.PHONY: all clean


vpath %.c src
vpath %.h include



CC=gcc
CFLAGS += -g -Wall -Wextra

exe: main.o utils.o stack.o trie.o 
	$(CC) -o $@ $^ $(CFLAGS) 

main.o : main.c trie.h stack.h 
trie.o : trie.c trie.h stack.h utils.h
stack.o : stack.c stack.h trie.h
utils.o: utils.c utils.h stack.h trie.h 
dawg.o: dawg.c utils.h stack.h trie.h dawg.h

/%.o : %.c 
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f *.o exe 
		@echo Clean!
