CC=gcc

wordle.out: bot.o entropy.o main.o occurence.o utils.o word.o
	$(CC) -o wordle.out -Wall bot.o entropy.o main.o occurence.o utils.o word.o -lm

bot.o: bot.c
	$(CC) -Wall -c bot.c

entropy.o: entropy.c
	$(CC) -Wall -c entropy.c

main.o: main.c 
	$(CC) -Wall -c main.c

occurence.o: occurence.c
	$(CC) -Wall -c occurence.c

utils.o: utils.c
	$(CC) -Wall -c utils.c

word.o: word.c
	$(CC) -Wall -c word.c

clean:
	rm -f *.o

clean_all: clean
	rm -f *.out