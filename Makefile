all: RomanNumeralCalculator.c
	gcc -g -Wall -std=c99 -o calc RomanNumeralCalculator.c main.c
clear:
	rm clac
