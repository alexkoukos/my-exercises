#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//test
    int sequentialSearch(int *arr,int size,int key){
        for(int i=0;i<size;i++){
            if(*(arr+i)==key){
                printf("The number was %d found\n",key);

                return i;
            }
        }
        return -1;
    }





    int partition(int *arr,int low,int high){
        int pivot=*(arr+high);
        int i =low-1;
        for(int j=low;j<high;j++){
            if(*(arr+j)<pivot){
                i++;
                int tmp=*(arr+i);
                *(arr+i)=*(arr+j);
                *(arr+j)=tmp;
            }
        }
        int tmp=*(arr+i+1);
        *(arr+i+1) =*(arr+high);
        *(arr+high)=tmp;
        return i+1;
            }


    void quickSort(int *arr,int low,int high){
        if(low<high){
            int mypar = partition(arr,low,high);
            quickSort(arr,low,mypar-1);
            quickSort(arr,mypar+1,high);
        }
    }


    int binarySearch(int *arr,int low,int high,int key){

        if(low>high){

            return -1;
        }
        int mid = low+(high-low)/2;

            if(*(arr+mid)==key){
            return mid;
            }
            if(key<*(arr+mid))
            {
                return binarySearch(arr,low,mid-1,key);
            }
            else{
                return binarySearch(arr,mid+1,high,key);
            }
        }





    int* mergeArrays(int* arr,int N){
        int* arr2=malloc(sizeof(int)*N);
        if(!arr2){
            fprintf(stderr,"Memory allocation failed\n");
            return NULL;
        }
        int* merged = malloc(sizeof(int)*(N+N));
          if(!merged){
            fprintf(stderr,"Memory allocation failed\n");
            return NULL;
        }
        int i;
        for(i=0;i<N;i++){
        *(arr2+i) = 30 + rand() % 21;
    }
    for(i=0;i<N;i++){
        *(merged+i) = *(arr2+i);
    }
            free(arr2);
         for(i=0;i<N;i++){
            *(merged+i+N)=*(arr+i);
        }

        return merged;
    }



    void printArrayContent(int* arr,int N){
        for(int i=0;i<N;i++){
            printf("%d  ",*(arr+i));
        }
        putchar('\n');
    }


    int saveArrayToFile(char* filename,int* arr,int N){
        FILE* file;

        file = fopen(filename,"w");
        if(!file){
            printf("There was an error opening the file\n");
            return -1;
        }
        for(int i=0;i<N;i++)
            fprintf(file,"%d\n",*(arr+i));
        fclose(file);
        return 0;
    }


    int* loadArrayFromFile(char* filename){
        FILE* file;

        file = fopen(filename,"r");
        if(!file){
            printf("There was an error opening the file\n");
            return NULL;
        }
        int cnt=0,tmp;

        while(fscanf(file,"%d",&tmp)==1)
            cnt++;
        rewind(file);
        int* filearr=malloc(sizeof(int)*cnt);
          if(!filearr){
            fprintf(stderr,"Memory allocation failed\n");
            return NULL;
        }
        for(int i=0;i<cnt;i++){
            fscanf(file,"%d",filearr+i);
        }
        fclose(file);
        return filearr;
    }



      int binarySearchcnt(int *arr,int low,int high,int key,int* BScnt){
        if(low>high){
            (*BScnt)++;
            return -1;
        }
        int mid = low+(high-low)/2;
            (*BScnt)++;
            if(*(arr+mid)==key){
            return mid;
            }
            if(key<*(arr+mid))
            {
                return binarySearchcnt(arr,low,mid-1,key,BScnt);
            }
            else{
                return binarySearchcnt(arr,mid+1,high,key,BScnt);
            }
        }

           int sequentialSearchcnt(int *arr,int size,int key,int* seqcnt){
        for(int i=0;i<size;i++){
            (*seqcnt)++;
            if(*(arr+i)==key){

                return i;
            }
        }
        return -1;
    }


    float binarySearchVSsequantialSearch(int* arr,int N){
        int BScnt=0;
        int seqcnt=0;
        for(int i=0;i<N;i++){
            sequentialSearchcnt(arr,N,*(arr+i),&seqcnt);
            binarySearchcnt(arr,0,N-1,*(arr+i),&BScnt);

        }
        printf("Total binary search reads: %d\n",BScnt);
        printf("Total sequential search reads: %d\n",seqcnt);
        return  ((float)seqcnt/(float)BScnt);
    }


    int main(int argc, char* argv[]){

    srand(time(NULL));
    int N,choice,key,BScnt,seqcnt;
    printf("Provide the wanted size of the array: \n");
    scanf("%d",&N);
    int *arr = malloc(sizeof(int)*N);
      if(!arr){
            fprintf(stderr,"Memory allocation failed\n");
            return -1;
        }
    for(int i=0;i<N;i++){
        *(arr+i) = 30 + rand() % 21;
    }




    do{
        printf("\n========================MENU==================================\n");
        printf("1.Sequential search for any given integer in any given array\n");
        printf("2.Quicksort for any given array\n");
        printf("3.Binary search in a sorted array for any given integer\n");
        printf("4.Merge any two given arrays\n");
        printf("5.Print any given array's content.\n");
        printf("6.Save (load) an array from(to) a given file\n");
        printf("7.Compare speed of binary and sequential search\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d",&choice);
        switch (choice){
        case 1:
            printf("Give the number you are looking for\n");
            scanf("%d",&key);
            int pos=sequentialSearch(arr,N,key);
            if(pos==-1){
                printf("The number was not found\n");
            }
            else{
                printf("The number was found in position: %d\n",pos);
            }
            break;
        case 2:
            printf("The array before being sorted\n");
            printArrayContent(arr,N);
            quickSort(arr,0,N-1);
            printf("The array after being sorted\n");
            printArrayContent(arr,N);
            break;
        case 3:
            printf("Give the number you are looking for\n");
            scanf("%d",&key);
            quickSort(arr,0,N-1);
            int pos1=binarySearch(arr,0,N-1,key);
             if(pos1==-1){
                printf("The number was not found\n");
            }
            else{
                printf("The number was found in position: %d\n",pos1);
            }
            break;
        case 4:
            printf("The array before being merged\n");
            printArrayContent(arr,N);
            int* merged=mergeArrays(arr,N);
            printf("The array after being merged\n");
            printArrayContent(merged,N+N);
            free(merged);
            break;
        case 5:
            printArrayContent(arr,N);
            break;
        case 6:
            saveArrayToFile("num.txt",arr,N);
            printf("The array that was saved to file is:\n");
            printArrayContent(arr,N);
            printf("The array that was loaded from file is:\n");
            int* filearr=loadArrayFromFile("num.txt");
            printArrayContent(filearr,N);
            free(filearr);
            break;
        case 7:{
            quickSort(arr,0,N-1);
            float k=binarySearchVSsequantialSearch(arr,N);
            printf("Binary search is %.2f times faster than sequential search for an array with %d elements.\n",k,N);
            break;
        }
        case 0:
            printf("Exit\n");
            break;
        default:
            printf("Invalid choice!\n");
        }

    }while(choice!=0);


    free(arr);
    return 0;
}



