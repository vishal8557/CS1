#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #define is used to define the constants used.
#define MAX_ITEMS 100
#define NUM_LINES 12
const int MAXTIME = 100000;

// Defining the sturct so the information of the customers can be stored.
typedef struct customer {
//storing name with up to 10 characters in the structure.
    char name [10];
//declaring time_that_was_taken_inline  to store in structure.
    int time_that_was_taken_inline;
//declaring the_line_number for the line number they are in, in the structure.
    int the_line_number;
//declaring num_Of_the_items_here in the structure.
    int num_Of_the_items_here;
} customer;

// defining making listnode as a structure so it can be used in the linked list.
typedef struct listnode {
//using value of customer and customer_Ptr_here in the struct.
    customer* customer_Ptr_here;
//defining struct and stores the value of listnode and next in the structure.
    struct listnode* next;
} listnode;

// Defining struct so the data of the queue can be stores
typedef struct queue {
//value of listnode and front and back in the queue because in queue the first person in is the first person out.
    listnode* front;
    listnode* back;
} queue;

//  Let's define the queue that's is pointed to by the pointer using the variable "q".
void lets_init_the_Queue(queue *q) {
//you use arrows when you are referencing the data.  If you're passing
//the actual variable, then you use "."
//q references to front which equals null.
    q->front = NULL;
//q references to the back which equals to null.
    q->back = NULL;
}

//You have to return the value if queue is being pointed to by the pointer of
//q and has no value.
int queue_empty(queue *q) {
    return q->front == NULL;
}
//An enqueue is adding pieces of data that is being processed to the queue containing the items.
//The following will enqueue list node that is being pointed to by the newnode that's to the queue
//that is being pointed to by pointer of q.
void enqueue(queue *q, listnode* Node) {

    // This if statement assigns a queue that's empty for the
    //people in the front and back of the line.
    if (queue_empty(q)) {
        q->front = Node;
        q->back = Node;
    }
//will be used to do a link back to the newer nodes and will move them
//back.
    else {
        q->back->next = Node;
        q->back = Node;
    }
}



// Null will be returned to the function if it is found
// that the queue is found to be empty and is used as
// a precaution.
listnode* dequeue(queue* qbb_Ptr) {

    if (queue_empty(qbb_Ptr)) return NULL;

    // This will store the node and references qPtr to
    //the front.
    listnode* reterVale = qbb_Ptr->front;

    // qPtr referencing to front is equal to qbb_Ptr referencing to front referencing
    // to the next.
    qbb_Ptr->front = qbb_Ptr->front->next;

    // This is basically verifying the queue in the program.
    if (qbb_Ptr->front == NULL)
        qbb_Ptr->back = NULL;

    // We want to return the reterVale so we get Val.
    return reterVale;
}

//  This frees the dynamic memory allocation in the struct.
// We do this because we do not want it taking up to much memory.
//If it takes up too much memory then the program will crash and won't work.
//You have to free every time you use malloc to prevent the program from crashing.
void freeNode(listnode* ptr_this_Node) {
    free(ptr_this_Node->customer_Ptr_here);
    free(ptr_this_Node);
}

//This is being used to calculate how much time it takes for a customer
//to checkout.
customer* The_customer_in_the_front(queue* qbb_Ptr)
        {
            if (queue_empty(qbb_Ptr)) return NULL;
            return qbb_Ptr->front->customer_Ptr_here;
        }


int main(void) {
//This will read the data in the input file that is given.
    customer *scan_customer(FILE *fp,int *test_cases);

//Will open file in reading mode.
    FILE*fp = (fopen("assignment2input.txt","r"));
//if fp contains a garbage value, it will print
//"error opening file, please confirm your input file now!"
    if (fp == NULL)
    {
        printf("Error opening file , please confirm your input file now! ");
        // exit(1) means exit failure which means that there was an
        //error that occurred.
        exit(1);
    }

//To make an array, you must declare it for the lines you are
//using queue for.
    queue queues_lines_Array[NUM_LINES];
    //Initializing the test cases and setting it equal to zero.
    int test_cases=0;
//We use fscanf here because we want to read the test cases provided in
//the file.
    fscanf(fp,"%d",&test_cases);
  //The first line contains a single positive integer, c(c< 25)
  //which represents the number of test cases that will be processed.
    if(test_cases > 0 && test_cases <= 25)
    {
     // initializing these variables so it can store the customer name
     //the line , the time ,and the items.
        int num_of_Customerz = 0,  curline = 0, time = 0, totalItems=0;

        // initializing variables so we can store the first customer in line and the duration.
        int firstCustomerLine = 0,  totalduration=0;

//This for loop is being used for all test cases and stops at
//the last one.
    for (int loop=0; loop<test_cases; ++loop)
    {

//This is a for loop that is storing the number of lines for each
//customer.
        for (int q=0; q<NUM_LINES; ++q)
            {
            lets_init_the_Queue(&queues_lines_Array[q]);
            }
//This will read the number of customers in the file and will store the amount of
//customers for each of the test cases.
       customer **customer_details(FILE *fp, int num_of_Customerz[], int curline[], int totalItems);
        fscanf(fp,"%d", &num_of_Customerz);
//if 0 is greater than num_of_Customerz then you return 0;
        if(num_of_Customerz <0 ){
            return 0;
        }

        //Loop and read through each customer data
        for (int c=0; c<num_of_Customerz; ++c)
        {
//scans total duration, curline, name and total items in the file.
            char name[10];
        fscanf(fp,"%d",&totalduration);
        fscanf(fp,"%d",&curline);
//using s because name is a string and holds 10 characters.
        fscanf(fp,"%10s",name);
        fscanf(fp,"%d",&totalItems);
// storing variables in the structure.
       customer* makeCustNode(char* name, int time, int line, int numitems)
        {
//You must dynamically allocate memory for the customer.
            customer* tmp = malloc(sizeof(customer));
            strcpy(tmp->name, name);
//tmp referencing time_that_was_taken_inline quals time.
            tmp->time_that_was_taken_inline = time;
//tmp referencing to the_line_number equals line.
            tmp->the_line_number = line;
//tmp referencing numitems equals numitems.
            tmp->num_Of_the_items_here = numitems;
            //return tmp the the memory.
            return tmp;
        }

            customer* tmp_this_Ptr = makeCustNode(name,totalduration, curline, totalItems);
// Make a temporary list node with customer info stored in struct.
            listnode* tmp_this_Node_now = malloc(sizeof(listnode));
            tmp_this_Node_now->customer_Ptr_here = tmp_this_Ptr;
            tmp_this_Node_now->next = NULL;

//This is used so you can add to the back of the line.
            enqueue(&queues_lines_Array[curline-1], tmp_this_Node_now);
        }
        //initializing the checkout time.
       int Checkouttime = 0;
//Forloop used for number of customers.
        for (int l=0; l<num_of_Customerz; ++l) {
//This will Caluclate the wait time per customer in the queue we're doing,
//if the line appears to not contain anything you should try to skip it and go to
//the other line.
int Caluclate_line(queue lines[], int Checkouttime) {

    //This is being used to store the current line number.
    int current_line = -1, min_of_the_items = MAX_ITEMS+1;

    // This for loop is being used to see if
    //there is a customer that's in line by
    //following the order.
    for (int i=0; i<NUM_LINES; i++) {

        //if the queue is empty, then go to a different line.
        if (queue_empty(&lines[i])) continue;

        // This looks for people in the front of the queue.
        customer* tmp = The_customer_in_the_front(&lines[i]);

        //We will skip if these specific conditions below are not being done.
        if (tmp->time_that_was_taken_inline > Checkouttime) continue;

        //This will look at the items each customer has.
        if (tmp->num_Of_the_items_here < min_of_the_items) {
            current_line = i;
            min_of_the_items = tmp->num_Of_the_items_here;
        }
    }

    //Checks if there is a customer and who is in the front.
    // != means not equal in c.
    if (current_line != -1) return current_line;


    int Totaltime = MAXTIME + 1;

   //This forloop is being used to do a calculation of the time of
   //the line that is currently active.
    for (int i=0; i<NUM_LINES; i++) {

        //if queue is empty, let's skip.
       if (queue_empty(&lines[i])) continue;

        // This will grab the details of the person in
        //front of the line.
        customer* tmp = The_customer_in_the_front(&lines[i]);

//This if statement is used to verify the total time the customer is using.
        if (tmp->time_that_was_taken_inline < Totaltime) {
            current_line = i;
            Totaltime = tmp->time_that_was_taken_inline;
        }
    }

    // This returns current line and gives an answer.
    return current_line;
//This will close the file.
    fclose(fp);
}



//This is used to locate the line that's needed to be calculated.
            int Findline = Caluclate_line(queues_lines_Array, Checkouttime);

            // This is used to Dequeue the item.
            //Dequeue stands for double ended queue which lets you insert
            //and remove elements from the front or rear.
            listnode* tmp_this_Node_now = dequeue(&queues_lines_Array[Findline]);


            //Grabs details of customer from the value of the customer.
            customer* tmp_this_Ptr = tmp_this_Node_now->customer_Ptr_here;

            // This is being used to update the time starting.
            // looking at where the  customer is at in the queue.
            if (Checkouttime < tmp_this_Ptr->time_that_was_taken_inline)
                Checkouttime = tmp_this_Ptr->time_that_was_taken_inline;

            // This is used to look at the current customer.
            const int DUR_PERCUSTOMER = 30;
            //Defining the constant.
            #define DUR_PERITEM 5;
            int time_being_Used_right_now(customer* custPtr)
            {
            return DUR_PERCUSTOMER + custPtr->num_Of_the_items_here*DUR_PERITEM;
            }
            Checkouttime += time_being_Used_right_now(tmp_this_Ptr);

            // This is going to print the customer's standing.
            printf("%s from line %d checks out at time %d.\n", tmp_this_Ptr->name, tmp_this_Ptr->the_line_number, Checkouttime);

            // Releases the memory of tmpNode so it doesn't take up
            //too much memory.
            freeNode(tmp_this_Node_now);
        }
    }
}
    return 0;
}
