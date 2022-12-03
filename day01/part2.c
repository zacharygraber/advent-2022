/******************************************************************
 * Advent of code 2022 day 1, part 2                              *
 * Author: Zach Graber (zegraber@iu.edu) (github: zacharygraber)  *
 * Date: 12/3/2022                                                *
 * Notes: This solution *should* generalize to any "top n" values *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define TOP_COUNT 3

int main(int argc, char* argv[]) {
	// Validate input and open the input file
	if (argc != 2) {
		fprintf(stderr, "Invalid no. of positional args: %d (Expected 1 input file)\n", argc);
		exit(1);
	}
	FILE* fp;
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "Error opening file %s!\n", argv[1]);
		exit(1);
	}

	// Read file line by line, exit when EOF (or some other problem)
	ssize_t charsRead;
	char* line;
	size_t n;

	int topCals[TOP_COUNT] = {0};
	int currCals = 0;
	int calsOnLine;
	while ((charsRead = getline(&line, &n, fp)) != -1) {
		// Only newline character (empty line)
		if (charsRead == 1) {
			for (int i = 0; i < TOP_COUNT; i++) {
				// if current Elf's cals are larger than `i`th cal count
				if (currCals > topCals[i]) {
					// Shift everything down and put currCals at index i
					for (int j = TOP_COUNT - 2; j >= i; j--) {
						// This is destructive, but it doesn't matter since 
						//  (a) we don't care about the last value since it's cast away anyway and
						//  (b) we're going in reverse order
						topCals[j+1] = topCals[j];
					}
					topCals[i] = currCals;
				}
			}
			currCals = 0;
		}
		else {
			if ((calsOnLine = atoi(line)) == 0) {
				fprintf(stderr, "Either something went terribly wrong reading a line or the input file is malformed.\n");
				fclose(fp);
				exit(1);
			}
			currCals += calsOnLine;
		}
	}
	fclose(fp);
	printf("Highest cal counts are:\n");
	int sum = 0;
	for (int i = 0; i < TOP_COUNT; i++) {
		printf("#%d: \t%d\n", i+1, topCals[i]);
		sum += topCals[i];
	}
	printf("Sum of top %d cal counts is %d\n", TOP_COUNT, sum);
	exit(0);
}
