#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "borda.h"
#include "instant_runoff.h"
#include "pairwise_comparison.h"
#include "schulze_beatpath.h"

int** createMatrix(FILE *fp, int* Matrix[], int rows, int cols);
int** transform_data(int* matrix[], int rows, int cols);
void printMatrix(int* Matrix[], int rows, int cols);
void freeMemory(int **data, int rows);


/*-------------------------------------MAIN---------------------------------------*/

int main(int argc, char* argv[]){

	/*INITIALIZE VARIABLES*/
	int cols; // number of candidates (columns)
	int rows; // number of ballots (rows)
	int r; // row indexing

	/*READ COMMAND INPUT*/
	char* detail = "g"; // don't display details
	if(argc==3 && strcmp(argv[2], "d")==0){
		detail = "d"; // display details
	}
    char* filename;

    if (argc > 1){
    	filename = argv[1];
    }
    else {
    	printf("Error occurred. Please provide a file name.");
    	return 0;
    }

	/*OPEN FILE*/
	FILE *fp = fopen(filename, "r"); // open in read mode
	if(!fp){
		printf("Error occurred. File not found.");
		return 0;
	}

	/*GET DATA DIMENSIONS*/
	fscanf(fp, "%d%d", &cols, &rows);

	/*ALLOCATE MEMORY FOR DATA*/
	int* Matrix[rows];
	for(r = 0; r < rows; r++){
		Matrix[r] = (int*)malloc(cols * sizeof(int));
	}

	/*GET DATA*/
	int** data = createMatrix(fp, Matrix, rows, cols);

	/*CLOSE FILE*/
	fclose(fp);
	printf("\n");

	/*VOTING METHODS: pairwise_comparison and shulze_beatpath*/
	pairwise_comparison(data, rows, cols, detail);
	shulze_beatpath(data, rows, cols, detail);

	/*VOTING METHODS: borda and instant_runoff*/
	int** new_data = transform_data(data, rows, cols); // specific to borda and runoff
	borda_count_method(new_data, rows, cols, detail);
	instant_runoff_method(new_data, rows, cols, detail);
	
	/*FREE DATA FROM MEMORY*/
	freeMemory(data, rows);
	freeMemory(new_data, rows);

	return 0;
}


/*--------------------------------FUNCTIONS-------------------------------------------*/

int** transform_data(int* matrix[], int rows, int cols){

	int r, c;

	int candidate_name;
	int candidate_rank;

	int new_matrix[rows][cols];

	// give values to new matrix
	for (r = 0; r < rows; r++){
		for (c = 0; c < cols; c++){

			candidate_name = c + 1;
			candidate_rank = matrix[r][c] - 1;

			new_matrix[r][candidate_rank] = candidate_name;
		}
	}

	// update the values of matrix!
	for (r = 0; r < rows; r++){
		for (c = 0; c < cols; c++){
			matrix[r][c] = new_matrix[r][c];
		}
	}

	return matrix;
}

void printMatrix(int* Matrix[], int rows, int cols){

	int i;
	int j;
	for (i = 0; i < rows; i++){
		for (j = 0; j < cols; j++){

			printf("%d ", Matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int** createMatrix(FILE *fp, int* Matrix[], int rows, int cols){

	char buff[rows];
	int row_count = 0;
	int col_count = 0;

	while(fgets(buff, rows, fp)){

		strtok(buff, "\n");
		char *line = strtok(buff, " "); // separates buff at space

		while( line != NULL){

			if (strcmp(line, "\n") != 0 && atoi(line) != 0){ // go through all numbers in the line of data

				Matrix[row_count][col_count] = atoi(line); // save individual number to matrix
				col_count++;

				if( col_count == cols){ // going to new row of data
					col_count = 0;
					row_count++;
				}
			}
			line = strtok(NULL, " ");
		}
		if (row_count >= rows){
			   break;
		}
	}

	return Matrix;
}


void freeMemory(int **data, int rows){

	for (int r = 0; r < rows; r++){
		free(data[r]);
	}
}

