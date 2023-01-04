#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>


int findMax(int a, int b){
	if(a > b){
		return a;
	}
	else if(b > a){
		return b;
	}
	else{
		return a;
	}
}

int findMin(int a, int b){
	if(a < b){
		return a;
	}
	else if(b < a){
		return b;
	}
	else{
		return a;
	}
}

void shulze_beatpath(int* matrix[], int rows, int cols, char* details){
	
	int comparisons[cols][cols]; // comparison matrix
	int points1[cols];
	
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
	
	
	// initializing output matrix
	int p[cols][cols];
	for(int i = 0; i < cols; i++){
		for(int j = 0; j < cols; j++){
			if(j == i){
				p[i][j] = 0;
			}
			else{
				p[i][j] = 1;
			}
		}
	}
	
	// filling strongest path matrix
	for(int q = 0; q < cols; q++){
		for(int r = 0; r < cols; r++){
			if(q != r){
				if(comparisons[q][r] > comparisons[r][q]){
					p[q][r] = comparisons[q][r];
				}
				else{
					p[q][r] = 0;
				}
			}
		}
	}

	// stongest paths
	for(int q = 0; q < cols; q++){
		for(int r = 0; r < cols; r++){
			if(q != r){
				for(int s = 0; s < cols; s++){
					if(q != s && r != s){
						p[r][s] = findMax(p[r][s], findMin(p[r][q], p[q][s]));
					}
				}
			}
		}
	}

	// int points1[cols];
	for(int u = 0; u < cols; u++){
		points1[u] = 0;
	}
	for(int d = 0; d < cols; d++){
		for(int e = 0; e < cols; e++){
			if(d != e){
				if(p[d][e] > p[e][d]){
					points1[d] = points1[d] + 1;
				}
				else if(p[d][e] < p[e][d]){
					points1[e] = points1[e] + 1;
				}
			}
		}
	}

    if(strcmp(details, "d")==0){
        printf("Shortest path matrix for Schulze beatpath:\n");
        for (int k = 0; k < cols; k++){
            for (int l = 0; l < cols; l++){
                printf("%d ", comparisons[k][l]);
            }
            printf("\n");
        }
        for(int z = 0; z < cols; z++){
            printf("Candidate %d points: ", z);
            printf("%d \n", points1[z]);
        }
    }
    
	printf("Schulze beatpath winner(s) is/are: ");
	int max1 = -1;
	for(int g = 0; g < cols; g++){
		if(points1[g] > max1){
			max1 = points1[g];
		}
	}
	for(int h = 0; h < cols; h++){
		if(points1[h] == max1){
			printf("Candidate %d ", h);
		}
	}
	printf("\n\n");
	
}
