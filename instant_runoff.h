#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int find_arr_min(int arr[], int length);
void find_winner(int arr[], int length);
void instant_runoff_method(int* matrix[], int rows, int cols, char* details);


int find_arr_min(int arr[], int length){

	int minimum = INT_MAX;
	// we want minimum that is nonzero only
	// NONZERO AND POSITIVE
	// this is because that signifies their votes aren't counted
	// and every candidate should get a nonzero borda count

	for (int i = 0; i < length; i++){

		if ( (arr[i] < minimum) && (arr[i] >= 0) ){
			minimum = arr[i];
		}
	}
	return minimum;
}


void find_winner(int arr[], int length){

	int maximum = INT_MIN;
	int max_index = -1;

	for (int i = 0; i < length; i++){

		if (arr[i] > maximum){
			maximum = arr[i];
			max_index = i;
		}
	}
	printf("Instant runoff winner is: Candidate %d\n\n", max_index);
}

void instant_runoff_method(int* matrix[], int rows, int cols, char* details){

	int r;
	int c;
	int candidate;
	int total_score[cols]; // number of first place rankings for each candidate
	float percent_score[cols];
	int i;

	int initial_score[cols];
	// initialize initial score
	for (c = 0; c < cols; c++){
		initial_score[c] = 0;
	}


	int num_with_majority = 0; // number of candidates with majority
	int minimum;


	while (num_with_majority != 1){


		// initialize scores to zero
		for (c = 0; c < cols; c++){
			total_score[c] = initial_score[c];
			percent_score[c] = 0;
		}

		// compute percents
		for (r = 0; r < rows; r++){
			for (c = 0; c < cols; c++){

				if (matrix[r][c] > 0){
					candidate = matrix[r][c] - 1;
					total_score[candidate] += 1;
					break;
				}
			}
		}

		if(strcmp(details, "d")==0){
			printf("Number of 1st place votes for each candidate:\n");
		}

		// print the scores
		for (c = 0; c < cols; c++){

			percent_score[c] = ( (float)total_score[c] / rows) * 100;
			// rows is number of ballots

			if(strcmp(details, "d")==0){
				if (total_score[c] >= 0){
					printf("Candidate %d: %d\n", c, total_score[c]);
				}
			}
		}

		// how many candidates hold the majority? >50%
		num_with_majority = 0;
		for (c = 0; c < cols; c++){
			if (percent_score[c] > 50.0){
				num_with_majority += 1;
			}
		}

		// if num_with_majority == 1, we are done! there is one winner
		// if num_with_majority != 1 (zero or 2+) we must loop again
		if ( num_with_majority != 1){

			// instant runoff
			// find the minimum using a function from borda
			minimum = find_arr_min(total_score, cols);

			for (i = 0; i < cols; i++){

				if (total_score[i] == minimum){
					// this is a candidate we will remove (all appearances on ballots)
					candidate = i + 1;
					initial_score[i] = -1; // candidate removed

					for (r = 0; r < rows; r++){
						for (c = 0; c < cols; c++){

							if (matrix[r][c] == candidate){
								matrix[r][c] = -1; // candidate removed
							}
						}
					} // done iterating  through elements of `matrix`
				} // end if-statement
			} // end for loop
		}
		else if (num_with_majority == 1){
			break;
		}


	} // END while loop
	find_winner(total_score, cols);

}
