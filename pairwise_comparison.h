#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>


void pairwise_comparison(int* matrix[], int rows, int cols, char* details){
	
	// pairwise comparison
	int comparisons[cols][cols]; // comparison matrix
	int points[cols]; // points matrix
	
	// initialize comparison matrix (setting duplicate comparisons = 0, the rest = 1 for visualization purposes)
	for(int i = 0; i < cols; i++){
		for(int j = 0; j < cols; j++){
			if(j == i){
				comparisons[i][j] = 0;
			}
			else{
				comparisons[i][j] = 1;
			}
		}
	}
		
	// create and fill a comparison matrix  
	int comp1 = 0;
	int comp2 = 0;
	for(int a = 0; a < cols; a++){
		for(int b = a+1; b < cols; b++){
			for(int c = 0; c < rows; c++){
				if(matrix[c][a] < matrix[c][b]){
					comp1++;
				}
				else if(matrix[c][a] > matrix[c][b]){
					comp2++;
				}
			}
		comparisons[a][b] = comp1;
		comparisons[b][a] = comp2; 
		comp1 = 0;
		comp2 = 0;
		}
	}
	
	
	// filling 'points' array that shows points for all candidates
	int numPoints = 0;
	for(int x = 0; x < cols; x++){
		for(int y = 0; y < cols; y++){
			if(comparisons[x][y] > rows/2){
				numPoints++;
			}
		}
		points[x] = numPoints;
		numPoints = 0;
	}

    if(strcmp(details, "d")==0){
        printf("Comparison matrix for pairwise comparison:\n");
        for (int k = 0; k < cols; k++){
            for (int l = 0; l < cols; l++){
                printf("%d ", comparisons[k][l]);
            }
            printf("\n");
        }
        for(int z = 0; z < cols; z++){
            printf("Candidate %d points: ", z);
            printf("%d \n", points[z]);
        }
    }
    
    
	printf("Pairwise comparison winner(s) is/are: ");
	int max = -1;
	for(int g = 0; g < cols; g++){
		if(points[g] > max){
			max = points[g];
		}
	}
	for(int h = 0; h < cols; h++){
		if(points[h] == max){
			printf("Candidate %d ", h);
		}
	}

	printf("\n\n");
		
}
