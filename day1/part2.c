/******************************************************************
 * Advent of code 2022 day 1, part 2                              *
 * Author: Zach Graber (zegraber@iu.edu) (github: zacharygraber)  *
 * Date: 12/3/2022                                                *
 * Notes: This assumes the input file is well-formed.             *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>

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

	int highestCals = 0;
	int currCals = 0;
	int calsOnLine;
	while ((charsRead = getline(&line, &n, fp)) != -1) {
		// Only newline character (empty line)
		if (charsRead == 1) {
			if (currCals > highestCals) {
				highestCals = currCals;
			}
			currCals = 0;
		}
		else {
			if ((calsOnLine = atoi(line)) == 0) {
				fprintf(stderr, "Either something went terribly wrong reading a line or the input file is malformed.\n");
				exit(1);
			}
			currCals += calsOnLine;
		}
	}
	printf("Highest cal count: %d\n", highestCals);

	exit(0);
}
