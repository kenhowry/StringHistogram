#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//scans scores and adds them to an array
//count is how many integers are scanned in
char** readScores(int* pcount){
    char** parr = malloc(sizeof(char*) * 100);
    char score[100];
    int i = 0;
    while(scanf("%s", score) != EOF){
        parr[i] = malloc(strlen(score) + 1);
        strcpy(parr[i], score);
        i++;
    }
    *pcount = i;
    return parr;
}

//displays results for the test file
//format - score[place in array]: [score]
void displayScores(char** parr, int* count){
    for(int i = 0; i < *count; i++){
        printf("score %d: %s\n", i, parr[i]);
    }
}

//histogram struct
typedef struct freq{
    char* value;
    int frequency;
} Histogram;

//calulates the histogram for an array of integers
int* calcHistogram(char** parr, int* pcount, Histogram** phisto, int* phistCount){
    //variables
    Histogram* phist= malloc(sizeof(Histogram) * (*phistCount));
    int index = 0;
    int found = 0;

    //iterates through the array
    for(int i = 0; i < *pcount; i++){
        //iterates through the histogram
        for(int j = 0; j < index; j++){
            //if the value is found in the histogram
            if(strcmp(parr[i], phist[j].value) == 0){
                //increment the frequency
                phist[j].frequency++;
                found = 1;
                break;
            }
        }
        //if the value is not found in the histogram
        if(!found){
            //add the value to the histogram
            phist[index].value = parr[i];
            phist[index].frequency = 1;
            index++;
        }
        found = 0;
    }
    *phistCount = index;
    *phisto = phist;
    return phistCount;
}

//displays the results of the histogram
void displayHistogram(Histogram* phist, int* phistCount){
    for(int i = 0; i < *phistCount; i++){
        printf("value %s: freq %d\n", phist[i].value, phist[i].frequency);
    }
}

//sorts the histogram by highest -> lowest frequencies using selection sort
void sortHistogram(Histogram* phist, int* phistCount){
    //variables
    int maxIndex;
    Histogram temp;

    //iterates through the histogram
    for(int i = 0; i < *phistCount; i++){
        //sets the minimum index to the current index
        maxIndex = i;

        //iterates through the histogram
        for(int j = i + 1; j < *phistCount; j++){
            //if the frequency is less than the minimum frequency
            if(phist[j].frequency > phist[maxIndex].frequency){
                //set the minimum index to the current index
                maxIndex = j;
            }
        }
        //swap the current index with the minimum index
        temp = phist[i];
        phist[i] = phist[maxIndex];
        phist[maxIndex] = temp;
    }
}

int main(){
    //variables
    int count = 0;
    int* pcount = &count; //pointer

    //reading and displaying scores
    printf("Scores:\n");
    char** arr = readScores(pcount);
    displayScores(arr, pcount);

    //variables
    int histCount = 0;
    int* phistCount = &histCount; //pointer

    Histogram* phist = NULL;

    //calculating and displaying histogram
    printf("Histogram:\n");
    calcHistogram(arr, pcount, &phist, phistCount);
    displayHistogram(phist, phistCount);

    //sorting and displaying histogram
    printf("Histogram sorted by frequency:\n");
    sortHistogram(phist, phistCount);
    displayHistogram(phist, phistCount);

    //freeing memory
    free(phist);
    free(arr);

    return 0;
}