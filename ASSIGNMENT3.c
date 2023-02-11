/* COP 3502C Programming Assignment3
This program is written by: Vishal Choday */

#include <stdio.h>
#include <stdlib.h>


typedef struct ptr
{
    int x,y,distance;
} ptr;

//Global variables
int myloc_x, myloc_y;


void insertionSort(ptr arr[], int l, int r) ;
int compareTo(ptr *ptr1stpoint, ptr *ptr2ndpoint);
ptr* ReadData(FILE* fp, int nP,int nQ,int nT, int locx, int locy);

int main(void)
{
    //int radius;
    int nP; //number of People
    int nQ; //number of quries to search
    int nT; //threshold limit

    //opening the file for reading and writing
    FILE *output = fopen("out.txt", "w");
    FILE *input = fopen("assignment3input.txt","r");
    {
        //Want the points in an array
        ptr *points;

        // Read my location and reference locations from input file.
        fscanf(input, "%d%d%d%d%d", &myloc_x,&myloc_y,&nP,&nQ,&nT);

        points = ReadData(input,nP,nQ,nT,myloc_x, myloc_y);

        //Let's sort this data
        sort(points, nP, nT);

        //Let's write this data that we sorted to the out file.
        for(int i = 0; i <nP; i++)
        {
            fprintf(output, "%d %d\n", points[i].x, points[i].y);
        }

        printf("It Works!!!\n\n");

        //Let's use variable nQ to look for the number of points from our file.
        int gh;
        gh = 0;

        while(gh<nQ)
        {
            //Let us take the input from out user now.
            int x;
            int y;
            fscanf(input, "%d %d", &x, &y);

            ptr thequery;
            thequery.x = x;
            thequery.y = y;

            //Let's look for our point.
            int binarySearch(ptr arr[], ptr thequery, int n);
            int r = binarySearch(points, thequery, nP-1);
            if(r>=0)
                fprintf(output, "%d %d found at rank %d\n", x, y, r+1);
            else
                fprintf(output, "%d %d not found\n", x, y);

            gh++;
        }

        fclose(input);
        fclose(output);
        free(points);

    }
    return 0;
}

int Lets_calculate_the_distance(ptr FS, ptr SS)
{
    //This is used so that we won't perform the square root which won;t let us have a fraction.
    return (FS.x-SS.x)*(FS.x-SS.x) + (FS.y-SS.y)*(FS.y-SS.y);
}

//When looking, if we find it, we will show it's location and if we can't find it
//we will show a -1.
int binarySearch(ptr arr[], ptr thequery, int n)
{

    ptr referencePoint;
    referencePoint.x = myloc_x;
    referencePoint.y = myloc_y;
//let's find query point and the distance of it using the reference point and it's quuery point.
    thequery.distance = Lets_calculate_the_distance(thequery, referencePoint) ;

    int l = 0;
    int hmr = n;
    while(l <= hmr)
    {
        //This is the formula used to receive the middle value
        int m = (l + hmr)/2;


        if(compareTo(&arr[m], &thequery) == 0)
            return m;

        if(compareTo(&arr[m], &thequery) <0)
            l = m + 1;
        else if(compareTo(&arr[m], &thequery) >0)
            hmr = m - 1;
    }
    return -1;

}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(ptr arr[], int l, int m, int r)
{

    int FS, SS, MS;
    //These are sizes.
    int N1 = m-l + 1;
    int N2 = r - m;


    //Let's create arrays on the left and the right
    ptr *LFTARRAY = (ptr*)malloc(N1*sizeof(ptr));
    ptr *RGHTARRAY = (ptr*)malloc(N2*sizeof(ptr));

    //This creates the first array and the second array
    for(int i = 0; i < N1; i++)
        LFTARRAY[i] = arr[i + l];


    for(int i = 0; i < N2; i++)
        RGHTARRAY[i] = arr[i + m + 1];


    /* Merge the temp arrays back into arr[l..r]*/
    FS = 0; // Initial index of first subarray
    SS = 0; // Initial index of second subarray
    MS = l; // Initial index of merged subarray


    //We will check for the elements which are the smallest and we will put them in the array that's finished.
    while(FS < N1 && SS < N2)
    {
        if(compareTo(&LFTARRAY[FS], &RGHTARRAY[SS]) < 0)
        {
            arr[MS] = LFTARRAY[FS];
            FS++;

        }
        else
        {
            arr[MS] = RGHTARRAY[SS];
            SS++;
        }
        MS++;
    }

    //Let us copy the points which we have left over now.
    while(FS < N1)
    {
        arr[MS] = LFTARRAY[FS];
        FS++;
        MS++;
    }


//Let's copy the points left over into the final array
    while(SS < N2)
    {
        arr[MS] = RGHTARRAY[SS];
        SS++;
        MS++;
    }
//free LFTARRAY and RGHTARRAY now so program doesn't take up too much memory.
    free(LFTARRAY);
    free(RGHTARRAY);

}
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(ptr arr[], int l, int r, int AL)
{
    if(l<r)
    {
        // get the mid point
        int midpoint = (l+r)/2;
        mergeSort(arr,l,midpoint, AL);
        mergeSort(arr,midpoint+1,r, AL);
        merge(arr,l,midpoint,r);
    }
}

void sort(ptr arr[], int our_length, int our_threshold)
{
    mergeSort(arr, 0, our_length -1, our_threshold);
}

//Let's read the data from our input file and make it into an array.
ptr* ReadData(FILE *input, int nP,int nQ,int nT, int locx, int locy)
{
    ptr referencePoint = {locx, locy};

    //This is used in order to create and is used for the population of an array if you are
    //taking the ordered pairs from an input file.
    ptr* numP = malloc(sizeof(ptr) * nP);


    for (int i=0; i<nP; i++)
    {
        fscanf(input, "%d%d", &numP[i].x,&numP[i].y);
        numP[i].distance  =Lets_calculate_the_distance(numP[i], referencePoint);
    }

    return numP;

}


//Let's sort the array using insertion.
void insertionSort(ptr arr[], int l, int ROM)
{
    int n = ROM-l+1;
    int i, j;
    for (i = l+1; i <=ROM; i++)
    {
        ptr item;
        item = arr[i];
        /* Move elements of arr[0..i-1], that are
             greater than key, to one position ahead
             of their current position */
        for(j=i-1; j>=0; j--)
        {
            if(compareTo(&arr[j], &item)>0)
                //used to move our item.
                arr[j+1] = arr[j];
            else
                break;
        }
        arr[j+1] = item;
    }
}
// A utility function to print an array of size n
void printArray(ptr arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d\n", arr[i].x, arr[i].y);

}


//Let's take two points and compare it's distance.  We can use x and y and have the below function give a negative integer
//if the 1st point is not as big as the 2nd point.
int compareTo(ptr *ptr1stpoint, ptr *ptr2ndpoint)
{

    //Let's compare our distance
    if (((*ptr1stpoint).distance > (*ptr2ndpoint).distance) ||  ((*ptr1stpoint).distance < (*ptr2ndpoint).distance))
        return (*ptr1stpoint).distance - (*ptr2ndpoint).distance;


    //We must use x if our distance turns out being similar.
    if (((*ptr1stpoint).x > (*ptr2ndpoint).x) || ((*ptr1stpoint).x < (*ptr2ndpoint).x))
        return (*ptr1stpoint).x - (*ptr2ndpoint).x;


    //if our distance turns out looking similar and the x is similar, we must compare y now.
    if (((*ptr1stpoint).y > (*ptr2ndpoint).y) || ((*ptr1stpoint).y < (*ptr2ndpoint).y))
        return (*ptr1stpoint).y - (*ptr2ndpoint).y;

    return 0;
}
void selectionSort(int arr[], int n)
{
    int i, j, min_idx, temp;
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        printf("\nIteration# %d\n",i+1);
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        // Swap the found minimum element with the first element
        temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;

        printArray(arr, n);
    }
}

