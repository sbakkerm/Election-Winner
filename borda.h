#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

void borda_count_method(int* matrix[], int rows, int cols, char* details);
int* find_borda_counts(int total_score[], int* matrix[], int rows, int cols, int points_matrix[rows][cols]);
int find_maximum_of_array(int arr[], int length);
int has_multiple_maxima(int arr[], int length, int maximum);
int find_minimum_of_array(int arr[], int length);
void find_borda_winner(int arr[], int length, int maximum);


int* find_borda_counts(int total_score[], int* matrix[], int rows, int cols, int points_matrix[rows][cols]){

	int i; // row iterator
	int j; // column iterator

	// initialize total scores as zero
	for (j = 0; j < cols; j++){
		total_score[j] = 0;
	}

	int candidate; // temporary variable to represent candidate at i,j
	int score; // temporary variable to represent borda count

	for (i = 0; i < rows; i++){

		for (j = 0; j < cols; j++){

			candidate = matrix[i][j] - 1;
			score = points_matrix[i][j];
			total_score[candidate] += score;
		}
	}

	return total_score;
}

int find_maximum_of_array(int arr[], int length){

	int maximum = INT_MIN;

	for (int i = 0; i < length; i++){

		if (arr[i] > maximum){
			maximum = arr[i];
		}
	}
	return maximum;
}

int find_minimum_of_array(int arr[], int length){

	int minimum = INT_MAX;
	// we want minimum that is nonzero only
	// this is because that signifies their votes aren't counted
	// and every candidate should get a nonzero borda count

	for (int i = 0; i < length; i++){

		if ( (arr[i] < minimum) && (arr[i] != 0) ){
			minimum = arr[i];
		}
	}
	return minimum;
}


int has_multiple_maxima(int arr[], int length, int maximum){

	int maxima = 0; // number of values equl to maximum

	for (int i = 0; i < length; i++){

		if (arr[i] == maximum){
			maxima += 1;
		}
	}

	if (maxima == 1){
		// returns 0 (false) if there is only one maximum in the array
		return 0;
	}
	else {
		// returns 1 (true) if there are more than one maximum in the array
		return 1;
	}
}


void find_borda_winner(int arr[], int length, int maximum){

	for (int i = 0; i < length; i++){

		if (arr[i] == maximum){
			printf("Borda count winner is: Candidate %d\n", i);
			break;
		}
	}
}


void borda_count_method(int* matrix[], int rows, int cols, char* details){

	int total_score[cols]; // total borda points for each candidate 0, 1, ...., N-1
	int n_dropped = 0; // number of candidates dropped from ballot
	int points_matrix[rows][cols]; // borda points matrix
	int maximum, minimum; // maximum and minimum scores
	int multi_max = 1; // boolean for while loop
	int* sp; // score pointer
	int i, r, c; // indexing

	// create matrix of borda points that candidates can receive
	for (r = 0; r < rows; r++){
		for (c = 0; c < cols; c++){
			points_matrix[r][c] = cols - c;
		}
	}

	while (multi_max != 0){

		// get borda counts
		sp = find_borda_counts(total_score, matrix, rows, cols, points_matrix);

		if(strcmp(details, "d")==0){

			printf("\nBorda points for each candidate:\n");
			for (i = 0; i < cols; i++){
				printf("Candidate %d: %d\n", i, sp[i]);
			}
		}

		// find the maximum
		maximum = find_maximum_of_array(sp, cols);

		// is there more than one maximum?
		multi_max = has_multiple_maxima(sp, cols, maximum);
		if (multi_max == 1) {
			// case that there is more than one maximum

			minimum = find_minimum_of_array(sp, cols);

			for (i = 0; i < cols; i++){

				// find the candidates with minimum scores
				// "remove" these candidates from the ballot
				if (sp[i] == minimum){

					n_dropped += 1; // dropping a candidate from ballot

					// update the points matrix
					for (r = 0; r < rows; r++){
						for (c = 0; c < cols; c++){

							if(matrix[r][c] == i + 1){
								points_matrix[r][c] = 0;
								break;
							}
							else{
								if (points_matrix[r][c] != 0){
									points_matrix[r][c] -= 1;
								}
							}
						}
					}// done updating points matrix
				}
			}
		} // outside if-else statement

		// break statement if no more candidates
		if (n_dropped == cols){
			// all candidates have dropped
			printf("Borda count winners are: All candidates\n");
			break;
		}
	}

	if (n_dropped != cols){
		// find the winner
		find_borda_winner(sp, cols, maximum);
	}

	printf("\n");
}

