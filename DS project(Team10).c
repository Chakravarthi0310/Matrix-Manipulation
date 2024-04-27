#include <stdio.h>
#include <stdlib.h>

	FILE *file1,*file2,*file3;
    const char* matrix1File = "matrix1.csv";
    const char* matrix2File = "matrix2.csv";
    const char* resultFile=   "result.csv";

void fprintMatrix(int **result,int rows,int cols)
{
	int i,j;
	file3=fopen(resultFile,"w");
	
	if(file3==NULL)
	{
		printf("error in opening file\n");
	}
	else
	{
		for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			fprintf(file3,"%d,",result[i][j]);
		}
		fprintf(file3,"\n");
	}
	fprintf(file3,"\n\n");
	fclose(file3);
	}
}
    
void readMatrix(const char* filename, int** matrix, int rows, int cols)  // Function to read a matrix from a CSV file
{
	int i,j;
    FILE* file = fopen(filename, "r");
    if (file == NULL) 
	{
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    for ( i = 0; i < rows; i++) 
	{
        for (j = 0; j < cols; j++) 
		{
            fscanf(file, "%d,", &matrix[i][j]);
        }
    }
    
    fclose(file);
}

void displayMatrix(int** matrix, int rows, int cols)    // Function to display matrix
{
	int i,j;
    for (i = 0; i < rows; i++) 
	{
        for (j = 0; j < cols; j++) 
		{
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void swapRows(int **matrix, int row1, int row2, int cols) {
    for (int i = 0; i < cols; i++) {
        int temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
}

int findRank(int **matrix, int rows, int cols) {
    int rank = cols;

    for (int row = 0; row < rank; row++) {
        // Check if matrix[row][row] is non-zero
        if (matrix[row][row]) {
            for (int col = 0; col < rows; col++) {
                if (col != row) {
                    int ratio = matrix[col][row] / matrix[row][row];
                    for (int i = 0; i < rank; i++)
                        matrix[col][i] -= ratio * matrix[row][i];
                }
            }
        } else {
            int reduce = 1;

            for (int i = row + 1; i < rows; i++) {
                if (matrix[i][row]) {
                    swapRows(matrix, row, i, cols);
                    reduce = 0;
                    break;
                }
            }

            if (reduce) {
                rank--;

                for (int i = 0; i < rows; i++)
                    matrix[i][row] = matrix[i][rank];
            }

            row--;
        }
    }

    return rank;
}
void addMatrices(int** matrix1, int** matrix2, int** result, int rows, int cols) 
{
    for (int i = 0; i < rows; i++) 
	{
        for (int j = 0; j < cols; j++) 
		{
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

void subtractMatrices(int** matrix1, int** matrix2, int** result, int rows, int cols) 
{
    for (int i = 0; i < rows; i++) 
	{
        for (int j = 0; j < cols; j++) 
		{
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
}

void multiplyMatrices(int** matrix1, int** matrix2, int*** result, int rows1, int cols1, int cols2)
 {
 	*result=(int **)malloc(rows1*sizeof(int *));
 	for(int i=0;i<rows1;i++)
 	{
 		(*result)[i]=(int *)malloc(cols2*sizeof(int ));
	 }
 	
    for (int i = 0; i < rows1; i++) 
	{
        for (int j = 0; j < cols2; j++) 
		{
            (*result)[i][j] = 0;
            for (int k = 0; k < cols1; k++) 
			{
                (*result)[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void powerOfMatrix(int** matrix, int size, int exp, int*** result) {
    // Create an identity matrix
    *result = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        (*result)[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            if (i == j) {
                (*result)[i][j] = 1;
            } else {
                (*result)[i][j] = 0;
            }
        }
    }

    int** temp;
    for (int i = 0; i < exp; i++) {
        multiplyMatrices(*result, matrix, &temp, size, size, size);
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                (*result)[j][k] = temp[j][k];
            }
        }
        // Free memory allocated for temp matrix
        for (int j = 0; j < size; j++) {
            free(temp[j]);
        }
        free(temp);
    }
}
int calculateDeterminant(int** matrix, int size) 
{
    if (size == 1) 
	{
        return matrix[0][0];
    }
    int determinant = 0;
    int sign = 1;

    for (int i = 0; i < size; i++) 
	{
        int** submatrix = (int**)malloc((size - 1) * sizeof(int*));    // Create submatrix
        for (int j = 0; j < size - 1; j++) 
		{
            submatrix[j] = (int*)malloc((size - 1) * sizeof(int));
        }

        for (int j = 1; j < size; j++)     // Fill submatrix with elements
		{
            int submatrixCol = 0;
            for (int k = 0; k < size; k++) 
			{
                if (k != i) 
				{
                    submatrix[j - 1][submatrixCol] = matrix[j][k];
                    submatrixCol++;
                }
            }
        }

        int submatrixDeterminant = calculateDeterminant(submatrix, size - 1);  // Compute submatrix determinant recursively
        determinant += sign * matrix[0][i] * submatrixDeterminant;    // Add current element to determinant
        sign *= -1;    // Update sign for next element

        for (int j = 0; j < size - 1; j++) 
		{
            free(submatrix[j]);
        }
        free(submatrix);
    }
    return determinant;
}

void changeMatrix(int ***matrix,int *rows,int *cols)
{
	int rows1,cols1;
	//printf("%d %d\n",*rows,*cols);
	 printf("Enter the number of rows of matrix1 : ");
     scanf("%d",&rows1);
     printf("Enter the number of coloumns of matrix1 : ");
     scanf("%d",&cols1);
    //printf("%d %d %d %d\n",rows1,cols1,*rows,*cols);
     if(rows1!=*rows)
     {
     	*rows=rows1;
     	*cols=cols1;
     	*matrix=(int **)malloc(rows1*sizeof(int *));
	    for(int i=0;i<rows1;i++)
	    {
		(*matrix)[i]=(int *)malloc(cols1*sizeof(int));
	    }
    }
	for(int i=0;i<rows1;i++)
	{
		for(int j=0;j<cols1;j++)
		{
			printf("Enter the value of the matrix at  %d th row %d th coloumn : ",i+1,j+1);
			scanf("%d",&(*matrix)[i][j]);
		}
	}
	
}

int calculateTrace(int** matrix, int size) {
    int trace = 0;
    for (int i = 0; i < size; i++) {
        trace += matrix[i][i];
    }
    return trace;
}

int main() {
	//taking input from csv file
    
    file1=fopen(matrix1File,"r");
    file2=fopen(matrix2File,"r");
    int rows1=0, cols1=1, rows2=0, cols2=1;
    char ch;
    int option;
    //determining the rows and coloumns of the matrices
    while((ch=fgetc(file1))!=EOF)
    {
    	if(rows1==0&&ch==',')
    	{
    		cols1++;
		}
		if(ch=='\n')
		{
			rows1++;
		}
	}
	while((ch=fgetc(file2))!=EOF)
	{
		if(rows2==0&&ch==',')
		{
			cols2++;
		}
		if(ch=='\n')
		{
			rows2++;
		}
	}
	fclose(file1);
	fclose(file2);
	
    int** matrix1 = (int**)malloc(rows1 * sizeof(int*));
    int** matrix2 = (int**)malloc(rows2 * sizeof(int*));   
   int** result = (int**)malloc(rows1 * sizeof(int*));

    for (int i = 0; i < rows1; i++) 
	{
        matrix1[i] = (int*)malloc(cols1 * sizeof(int));
        result[i] = (int*)malloc(cols2 * sizeof(int));
    }

    for (int i = 0; i < rows2; i++)
	{
        matrix2[i] = (int*)malloc(cols2 * sizeof(int));
    }
    //reading the matrices from CSV files
    readMatrix(matrix1File, matrix1, rows1, cols1);
    readMatrix(matrix2File, matrix2, rows2, cols2);
   // readMatrix(matrix2File, result, rows2, cols2);

    int choice;
    int determinant;

    for(int i=0;i<50;i++)
    {
    	if(i==25)
    	{
    		printf(" MATRIX POWER TOOL ");
		}
		else
		{
			printf("*_");
		}
	}
	printf("\n");
// instructing the user with menu
    while (1)
	 {
        printf("\nMatrix Operations Menu:\n\n");
        printf("1. Change the matrices in the CSV file\n");
        printf("2. Add Matrices\n");
        printf("3. Subtract Matrices\n");
        printf("4. Multiply Matrices\n");
        printf("5. Calculate Determinant of a Matrix\n");
        printf("6. Find the rank of the matrix\n");
        printf("7. Display Matrices\n");
        printf("8. Find power of the matrix\n");
        printf("9. Find the trace of the matrix\n");
        printf("10. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        	case 1:
        		//int option;
        		printf("\n\n\t1. Change matrix1\n\t2. Change matrix2\n");
				printf("\n\n\tChoose option : ");
				scanf("%d",&option);
				switch(option)
				{
        		    case 1:{
        		    	free(matrix1);
        		            changeMatrix(&matrix1,&rows1,&cols1);
        		            file1=fopen(matrix1File,"w");
        		            for(int i=0;i<rows1;i++)
        		            {
        		            	for(int j=0;j<cols1;j++)
        		            	{
        		            		if(j<cols1-1)
        		            		{
        		            			fprintf(file1,"%d,",matrix1[i][j]);
									}
									else
									{
										fprintf(file1,"%d",matrix1[i][j]);
									}
								}
								fprintf(file1,"\n");
							}
        		    	    fclose(file1);
						break;
					       }    
					case 2:{
						free(matrix2);
        		            changeMatrix(&matrix2,&rows2,&cols2);
        		            file2=fopen(matrix2File,"w");
        		             //printf("%d %d \n",rows2,cols2);
        		            for(int i=0;i<rows2;i++)
        		            {
        		            	for(int j=0;j<cols2;j++)
        		            	{
        		            		if(j<cols1-1)
        		            		{
        		            			fprintf(file2,"%d,",matrix2[i][j]);
									}
									else
									{
										fprintf(file2,"%d",matrix2[i][j]);
									}
								}
								fprintf(file2,"\n");
							}
							fclose(file2);
						break;
					}
					default:printf("Ivalid input\n");
					break;
			     }  		   
        	       break;
            case 2:
                if(rows1!=rows2||cols1!=cols2)
                {
                	printf("Matrix addition is not possible due to difference in the dimension of the matrices \n");
				}
				else
				{
					addMatrices(matrix1, matrix2, result, rows1, cols1);
                printf("Matrix Addition Result:\n");
                displayMatrix(result, rows1, cols1);
                fprintMatrix(result,rows1,cols1);
				}
                break;
            case 3:
                if(rows1!=rows2||cols1!=cols2)
                {
                	printf("Matrix subtraction is not possible due to difference in the dimension of the matrices \n");
				}
				else
				{
					printf("Choose option :\n1.A-B\n2.B-A\n Your option :");
					int k;
				    scanf("%d",&k);
				    if(k==1)
				    {
				    	subtractMatrices(matrix1, matrix2, result, rows1, cols1);
					}
					else
					{
						subtractMatrices(matrix2, matrix1, result, rows1, cols1);
                    }
                    printf("Matrix Subtraction Result:\n");
                    displayMatrix(result, rows1, cols1);
                    fprintMatrix(result,rows1,cols1);
				}
                break;
            case 4:
				
				    printf("Choose option :\n\n1. A x B\n2. B x A\n Your option : ");
				    int op;
				    scanf("%d",&op);
				    if(op==1)
				    {
				    		
							if(cols1!=rows2)
                           {
                            	printf("Matrix multiplication is not possible\n");
			               }
				            else
				            {
				            	
				            	multiplyMatrices(matrix1, matrix2, &result, rows1, cols1, cols2);
                            printf("Matrix Multiplication Result:\n");
                            displayMatrix(result, rows1, cols2);
                            fprintMatrix(result,rows1,cols2);
							}
							break;
					}
					else if (op == 2) {
                        if (cols2 != rows1) {
                          printf("Matrix multiplication is not possible\n");
                        } 
						else 
						 {
						 	printf("%d %d ",rows2,cols1);
                          multiplyMatrices(matrix2, matrix1, &result, rows2, cols2, cols1);
                          printf("Matrix Multiplication Result:\n");
                             displayMatrix(result, rows2, cols1);
                          fprintMatrix(result, rows2, cols1);
                          }
                          break;
						  }
            case 5:
            	printf("Choose matrix :\n");
            	printf("1.\n\n");
            	displayMatrix(matrix1,rows1,cols1);
            	printf("\n2.\n\n");
            	displayMatrix(matrix2,rows2,cols2);
            	printf("Choose your option : ");
            	int l;
            	scanf("%d",&l);
            	if(l==1)
            	{
            		 if(rows1==cols1)
            		 {
            		 	determinant = calculateDeterminant(matrix1, rows1);
                     printf("Determinant: %d\n", determinant);
					 }
					 else
					 {
					 	printf("\nThe matrix is not a square matrix \n");
					 }
                }   
				else
				{
					if(rows1==cols1)
					{
						 determinant = calculateDeterminant(matrix2, rows1);
                     printf("Determinant: %d\n", determinant);
					}
					else
					{
					 	printf("\nThe matrix is not a square matrix \n");
					}
		     	 }      
				  break;   	
            case 6:
            	printf("Select the matrix \nMatrix 1:\n");
            	displayMatrix(matrix1,rows1,cols1);
            	printf("Matrix 2:\n");
            	displayMatrix(matrix2,rows2,cols2);
            	int opt;
            	while(1)
            	{
            		printf("Choose Matrix (1 or 2) : ");
            		scanf("%d",&opt);
            		if(opt==1)
            		{
            			printf("The rank of the matrix 1 is %d \n",findRank(matrix1,rows1,cols1));
            			break;
					}
					else if(opt==2)
					{
						printf("The rank of the matrix 2 is %d \n",findRank(matrix2,rows2,cols2));
						break;
					}
					else
					{
						printf("Invalid option choose again \n");
					}
					
				}
				break;
            case 7:
            	printf("Matrix 1\n\n");
            	displayMatrix(matrix1,rows1,cols1);
            	printf("\n\nMatrix 2\n\n");
            	displayMatrix(matrix2,rows2, cols2);
            	break;
            case 8:
            	printf("\nChoose the matrix\n");
            	printf("Matrix1\n");
            	displayMatrix(matrix1,rows1,cols1);
            	printf("\nMatrix2\n");
            	displayMatrix(matrix2,rows2,cols2);
				printf("\nChoose the matrix : ");
				int o;
				scanf("%d",&o);
				if(o==1)
				{
					if(rows1!=cols1)
					{
						printf("The matrix is not a square matrix\n");
					}
					else
					{
						printf("Enter the exponent of the matrix : ");
						int ex;
						scanf("%d",&ex);
						powerOfMatrix(matrix1,rows1,ex,&result);
						printf("The power of A to %d is\n",ex);
						displayMatrix(result,rows1,cols1);
                        fprintMatrix(result,rows1,cols1);
					}
					break;
				}    
				else if(o==2)
				{
					if(rows2!=cols2)
					{
						printf("The matrix is not a square matrix\n");
					}
					else
					{
						printf("Enter the exponent of the matrix : ");
						int ex;
						scanf("%d",&ex);
						powerOfMatrix(matrix2,rows2,ex,&result);
						printf("The power of A to %d is\n",ex);
						displayMatrix(result,rows2,cols2);
                        fprintMatrix(result,rows2,cols2);
					}
					break;
				} 
				else
				{
					printf("Invalid choice \n");
					break;
				}   
			case 9:     	
			       printf("\nChoose the matrix\n");
            	printf("Matrix1\n");
            	displayMatrix(matrix1,rows1,cols1);
            	printf("\nMatrix2\n");
            	displayMatrix(matrix2,rows2,cols2);
				printf("\nChoose the matrix : ");
				int ko;
				scanf("%d",&ko);
				if(ko==1)
				{
					if(rows1!=cols1)
					{
						printf("It is not a square matrix \n");
					}
					else
					{
						printf("Trace of Matrix A is %d\n",calculateTrace(matrix1,rows1));
					}
				}
				else if(ko==2)
				{
					if(rows2!=cols2)
					{
						printf("It is not a square matrix \n");
					}
					else
					{
						printf("Trace of Matrix B is %d\n",calculateTrace(matrix2,rows2));
					}
				}
				else
				{
					printf("invalid choice\n");
				}
				break;
            case 10:
                printf("Exiting...\n");
                break;
            default:
                printf("INVALID CHOICE. Please try again.\n");
                break;
        }

        if (choice == 10) {
            break;
        }
    }

    for (int i = 0; i < rows1; i++) {
        free(matrix1[i]);
        free(result[i]);
    }
    for (int i = 0; i < rows2; i++) {
        free(matrix2[i]);
    }
    free(matrix1);
    free(matrix2);
    free(result);

    return 0;
}



