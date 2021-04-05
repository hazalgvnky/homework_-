#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "the2.h"


/*
INPUT:
    int *row_count: vertical size of the matrix to be assigned (passed by reference from the main function)
    int *row_size: horizontal size of the matrix to be assigned (passed by reference from the main function)

OUTPUT:
    double **matrix: created data matrix

METHOD:
    This function creates the matrix streamed via stdin. 
    During this process, assigns row_count and row_size variables.
*/
int count(double *list, int s){
    int i,coun;
    for(i=0,coun=0;i<s;i++){
        if(list[i] == -1){
            if(list[i-1] != -1){
                coun++;
            }
            else{
                break;
            }
        }
    }
    return coun;
}

int size(double *list, int s){
    int i,siz;
    for(i=0,siz=0;i<s;i++){
        if(list[i] != -1){
            siz++;
        }
        else{
            break;
        }
    }
    return siz;
}

double **initialize_the_data(int *row_count, int *row_size) {
    double **matrix,*mtry,elem;
    int s,i,n,m,el=0;
    s=999999;
    mtry=(double*)malloc(s*sizeof(double));
    for(i=0;i<s;i++){
        scanf("%lf",&elem);
        mtry[i]=elem;
    }
    *row_count = count(mtry,s);
    *row_size = size(mtry,s);
    matrix = (double**)malloc(sizeof(double*)*(*row_count));
    for(n=0;n < *row_count;n++){
        matrix[n] = (double*)malloc(sizeof(double)*(*row_size));
        for(m=0;m < *row_size;m++){
            matrix[n][m] = mtry[el];
            el++;
        }
        el++;
    }
    return matrix;
}

/*
INPUT:
    double **matrix: data matrix
    int n: number of rows to be printed
    int row_size: horizontal size of the matrix

METHOD:
    This function prints first n row of the matrix.
*/
void print_first_n_row(double **matrix, int n, int row_size) {
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<row_size-1;j++){
            printf("%.4lf ",matrix[i][j]);
        }
        printf("%.4lf",matrix[i][row_size-1]);
        if(i < n-1){
            printf("\n");
        }
    }
}
/*
INPUT:
    double **matrix: data matrix
    int row_size: horizontal size of the data matrix
    int row1: index of the first row in the calculation
    int row2: index of the second row in the calculation

METHOD:
    This function calculates dot product of the row1 and the row2 and prints it in the following format:
        Dot product of rows <row1>, <row2>: <dot_product>
*/
void calculate_dot_product(double **matrix, int row_size, int row1, int row2) {
    double result=0,help;
    int i;
    for(i=0;i<row_size;i++){
        help = matrix[row1][i]*matrix[row2][i];
        result += help;
    }
    printf("Dot product of rows %d, %d: %.4lf",row1,row2,result);
}

/*
INPUT:
    double **matrix: data matrix
    int row_count: vertical size of the data matrix
    int row_size: horizontal size of the data matrix

OUTPUT:
    double **covariance_matrix: Created covariance matrix with size of row_size X row_size

METHOD:
    This function creates covariance matrix of the original data matrix and returns it.

*/
double helper_mean(double **matrix,int row_count,int column){
   int j;
   double result,sum=0;
      for(j=0;j<row_count;j++){
        sum += matrix[j][column];
    }
    result = sum/row_count;
    return result;
}


double **calculate_covariance_matrix(double **matrix, int row_count, int row_size) { 
    double x,y,sum,**covar;
    int i,j,n;
    covar = (double**)malloc(row_count*sizeof(double*));
    for(i=0;i<row_count;i++){
        covar[i]=(double*)malloc(row_size*sizeof(double));
        for(j=0;j<row_size;j++){
            x = helper_mean(matrix,row_count,i);
            y = helper_mean(matrix,row_count,j);
            sum=0;
            for(n=0;n<row_count;n++){
                sum+=(matrix[n][i]-x)*(matrix[n][j]-y);
            }
            sum = sum/(row_count-1);
            covar[i][j]=sum;
        }
    }
    return covar;
}

/*
INPUT:
    double **matrix: data matrix
    int row_count: vertical size of the data matrix
    int row_size: horizontal size of the data matrix

OUTPUT:
    double **result: Created result matrix with size of row_size X row_size

METHOD:
    This function calculates x^T * x. First finds the transpose of the original data matrix and apply matrix multiplication.
    At the end it returns the calculated matrix with size of row_size X row_size.

*/
double **helper_transpose(double **matrix, int row_count,int row_size){
   double **transpose;
    int i,j;
    transpose = (double**)malloc(row_size*sizeof(double*));
    for(i=0;i<row_size;i++){
        transpose[i]=(double*)malloc(row_count*sizeof(double));
        for(j=0;j<row_count;j++){
            transpose[i][j]=matrix[j][i];
        }
    }
    return transpose; 
}

double helper_sum(double **matrix,double **transpose,int row_count,int i,int j){
    double sum=0;
    int c;
    for(c=0;c<row_count;c++){
        sum += transpose[i][c]*matrix[c][j];
    }
    return sum;
}

double **calculate_x_transpose_times_x(double **matrix, int row_count, int row_size) { 
    double **times,**transpose,sum;
    int i,j;
    transpose = helper_transpose(matrix,row_count,row_size);
    times = (double**)malloc(row_size*sizeof(double*));
    for(i=0;i<row_size;i++){
        times[i]=(double*)malloc(row_size*sizeof(double));
        for(j=0;j<row_size;j++){
            sum = helper_sum(matrix,transpose,row_count,i,j);
            times[i][j]=sum;
        }
    }
    return times;
}

/*
INPUT:
    double **matrix: data matrix
    int *group_count: number of the groups to be assigned (passed by reference from the main function)
    int row_count: vertical size of the data matrix
    int row_size: horizontal size of the data matrix
    int group_column: index of the column to apply grouping over
    int operation: index of the operation to apply during grouping
        SUM -> 0
        AVG -> 1
        MAX -> 2
        MIN -> 3

OUTPUT:
    double **grouped_matrix: Created grouped matrix with size of group_count X row_size

METHOD:
    This function applies grouping over desired column index, creates a grouped matrix. It returns this grouped matrix.
    During this process it calculates group count and assigns to the variable.

*/

int elem(double *list,double el,int len){
    int i,n=0;
    for(i=0;i<len;i++){
        if(list[i]==el){
            n++;
            break;
        }
    }
    return n;
}

double *list_column(double **matrix,int row_count,int group_column,int *group_count){
    double *list;
    int i,j=0;
    list=(double*)malloc(row_count*sizeof(double));
    for(i=0;i<row_count;i++){
        if(elem(list,matrix[i][group_column],j)==0){
            list[j]=matrix[i][group_column];
            j++;
        }
    }
    list=(double*)realloc(list,j*sizeof(double));
    *group_count=j;
    return list;
}



double sum(double **matrix,double *list,int row_count,int group_column,int i,int j){
    double result=0,elem;
    int n;
    elem=list[i];
    for(n=0;n<row_count;n++){
        if(matrix[n][group_column]==elem){
            result+=matrix[n][j];
        }
    }
    return result;  
}

double avg(double **matrix,double *list,int row_count,int group_column,int i,int j){
    double result=0,elem;
    int n,d=0;
    elem=list[i];
    for(n=0;n<row_count;n++){
        if(matrix[n][group_column]==elem){
            result+=matrix[n][j];
            d++;
        }
    }
    result=result/d;
    return result;
}

double max(double **matrix,double *list,int row_count,int group_column,int i,int j){
    double result=0,elem;
    int n;
    elem=list[i];
    for(n=0;n<row_count;n++){
        if(matrix[n][group_column]==elem){
            if(matrix[n][j]>=result){
                result=matrix[n][j];
            }
        }
    }
    return result;
}

double min(double **matrix,double *list,int row_count,int group_column,int i,int j){
    double result=99999,elem;
    int n;
    elem=list[i];
    for(n=0;n<row_count;n++){
        if(matrix[n][group_column]==elem){
            if(matrix[n][j]<=result){
                result=matrix[n][j];
            }
        }
    }
    return result;
}

double **group_by(double **matrix, int *group_count, int row_count, int row_size, int group_column, int operation) {
    double **mgroup,ad,*list;
    int i,j;
    list=list_column(matrix,row_count,group_column,group_count);
    mgroup=(double**)malloc((*group_count)*sizeof(double*));
    for(i=0;i<(*group_count);i++){
        mgroup[i]=(double*)malloc(row_size*sizeof(double));
        for(j=0;j<row_size;j++){
            if(j==group_column){
                mgroup[i][j]=list[i];
            }
            else if(operation==0){
                ad=sum(matrix,list,row_count,group_column,i,j);
                mgroup[i][j]=ad;
            }
            else if(operation==1){
                ad=avg(matrix,list,row_count,group_column,i,j);
                mgroup[i][j]=ad;
            }
            else if(operation==2){
                ad=max(matrix,list,row_count,group_column,i,j);
                mgroup[i][j]=ad;
            }
            else if(operation==3){
                ad=min(matrix,list,row_count,group_column,i,j);
                mgroup[i][j]=ad;
            }
        }
    }
    return mgroup;
}

/*
INPUT:
    double **matrix: data matrix
    int row_count: vertical size of the data matrix
    int row_size: horizontal size of the data matrix
    double **kernel: kernel matrix
    int kernel_height: vertical size of the kernel matrix
    int kernel_width: horizontal size of the kernel matrix

OUTPUT:
    double **convoluted_matrix: Created convoluted matrix

METHOD:
    This function applies convolution over data matrix using kernel matrix and returns created matrix.

*/
double helper_convo(double **matrix,double **kernel,int kernel_height,int kernel_width,int i,int j){
    int n,m;
    double result=0;
    for(n=0;n<kernel_height;n++){
        for(m=0;m<kernel_width;m++){
            result += matrix[i+n][j+m]*kernel[n][m]; 
        }
    }
    return result;
}


double **convolution(double **matrix, int row_count, int row_size, double **kernel, int kernel_height, int kernel_width){ 
    double **convo,sum;
    int i,j;
    convo = (double**)malloc((row_count-kernel_height+1)*sizeof(double*));
    for(i=0;i<row_count-kernel_height+1;i++){
        convo[i]=(double*)malloc((row_size-kernel_width+1)*sizeof(double));
        for(j=0;j<row_size-kernel_width+1;j++){
            sum=helper_convo(matrix,kernel,kernel_height,kernel_width,i,j);
            convo[i][j]=sum;
        }
    }
    return convo;
}
    

    