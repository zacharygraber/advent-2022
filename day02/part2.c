/********************************************************************
 * Advent of code 2022 day 2, part 2                                *
 * Author: Zach Graber (zegraber@iu.edu) (github: zacharygraber)    *
 * Date: 12/3/2022                                                  *
 * Notes: Fairly resilient, gives stderr message if input malformed *
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef enum {
	ROCK,
	PAPER,
	SCISSORS
} rps_choice_t;

typedef enum {
	WIN,
	LOSE,
	DRAW
} rps_outcome_t;

int scoreRound(rps_choice_t myChoice, rps_choice_t oppChoice);
rps_choice_t decodeOppChoice(char oppChoice);
rps_outcome_t decodeIdealOutcome(char outcome);
rps_choice_t chooseForOutcome(rps_choice_t oppChoice, rps_outcome_t outcome);

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
	char* line = NULL;
	size_t n;

	int totalScore = 0;
	int roundScore;
	rps_choice_t oppChoice;
	while ((charsRead = getline(&line, &n, fp)) != -1) {
		// We expect line to be "_ _\n", or 4 chars total, including newline [or carriage return... blah blah blah]
		if (charsRead != 4) {
			if (charsRead == 1) {
				// empty line--ignore
				fprintf(stderr, "WARN: empty line in input file! Skipping.\n");
				continue;
			}
			fprintf(stderr, "Input differed from expected... malformed?\n");
			fprintf(stderr, "Received %d characters (expected 4)\n", (int) charsRead);
			fprintf(stderr, "Actual line received: %s\n", line);
			fclose(fp);
			exit(1);
		}
		else {
			oppChoice = decodeOppChoice(line[0]);
			roundScore = scoreRound(oppChoice, chooseForOutcome(oppChoice, decodeIdealOutcome(line[2])));
			if (roundScore == -1) {
				fprintf(stderr, "Something went wrong while scoring a round\n");
				fclose(fp);
				exit(1);
			}
			totalScore += roundScore;
		}
	}
	fclose(fp);
	printf("Total Score: %d\n", totalScore);

	exit(0);
}

rps_choice_t decodeOppChoice(char oppChoice) {
	switch (oppChoice) {
		case 'A':
			return(ROCK);
			break;
		case 'B':
			return(PAPER);
			break;
		case 'C':
			return(SCISSORS);
			break;
		default:
			fprintf(stderr, "Invalid opponent choice '%c'!\n", oppChoice);
			exit(-1);
			break;
	}

}

rps_outcome_t decodeIdealOutcome(char outcome) {
	switch (outcome) {
		case 'X':
			return(LOSE);
			break;
		case 'Y':
			return(DRAW);
			break;
		case 'Z':
			return(WIN);
			break;
		default:
			fprintf(stderr, "Invalid outcom code '%c'!\n", outcome);
			exit(-1);
			break;
	}
}

rps_choice_t chooseForOutcome(rps_choice_t oppChoice, rps_outcome_t outcome) {
	if (outcome == DRAW) {
		// Choose same as opponent to draw
		return oppChoice;
	}
	else {
		// Choose the correct output to win/lose
		switch (oppChoice) {
			case ROCK:
				return outcome == WIN ? PAPER : SCISSORS;
				break;
			case PAPER:
				return outcome == WIN ? SCISSORS : ROCK;
				break;
			case SCISSORS:
				return outcome == WIN ? ROCK : PAPER;
				break;
		}
	}
}

// Returns the score for a round, or -1 if a problem was encountered.
int scoreRound(rps_choice_t myChoice, rps_choice_t oppChoice) {
	int choiceScore;
	int outcomeScore;

	// Score our choice
	switch (myChoice) {
		case ROCK:
			choiceScore = 1;
			break;
		case PAPER:
			choiceScore = 2;
			break;
		case SCISSORS:
			choiceScore = 3;
			break;
		default:
			fprintf(stderr, "Invalid player choice in scoreRound(...)!\n");
			return -1;
			break;
	}

	// Score the outcome of the round (did we win?)
	if (myChoice == oppChoice) {
		// Draw
		outcomeScore = 3;
	}
	else if ((myChoice == ROCK && oppChoice == SCISSORS) || (myChoice == SCISSORS && oppChoice == PAPER) || (myChoice == PAPER && oppChoice == ROCK)) {
		// Win
		outcomeScore = 6;
	}
	else {
		// Loss
		outcomeScore = 0;
	}

	return choiceScore + outcomeScore;
}
