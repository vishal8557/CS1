#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define FSIZE 100
typedef struct student
{
    int id;
    char *lname; //stores last name of student
    float *scores; //stores scores of the student. Size is taken from num_scores array.
    float std_avg; //average score of the student (to be calculated)
} student;

typedef struct course
{
    char *course_name; //stores course name
    int num_sections; //number of sections
    student **sections; //stores array of student arrays(2D array). Size is num_sections;
    int *num_students; //stores array of number of students in each section. Size is num_sections;
    int *num_scores;
} course;

//declaring different methods for their functions.
course *read_courses(FILE *fp, int *num_courses);
student **read_sections(FILE *fp, int num_students[], int num_scores[], int num_sections);


int main(void)

{

    FILE *fp = fopen("assignment1input.txt", "r"); // opens the input file
    if (fp == NULL)
    {
        printf("Could not open file assignment1input.txt");//something went wrong opening the file
        exit(-1);
        return 0;
    }



    int number_of_test_cases;
    fscanf(fp, "%d", &number_of_test_cases); //reads the number of test cases.

    int v;
    for( v=0; v<number_of_test_cases; ++v)

    {
        printf("test case %d\n", v+1); //prints test case to output.

        course *courses = courses;                          //being used for the array of courses.

        int num_courses;

        courses = read_courses(fp,  &num_courses);          //reads the courses.

        process_courses(courses, num_courses);              //produces the array of courses and the amount.
        free_mem_courses(courses, num_courses);               //free all the memory that we allocated for courses, sections, students
    }
    fclose(fp);
};


course *read_courses(FILE *fp, int *num_courses)
{

    fscanf(fp, "%d", num_courses);//will scan the amount of courses.

    course *courses_list = (course *)malloc(*num_courses * sizeof(course));//dynamic memory allocation for all the courses listed.


    char my_course_name[100];//scans name from file up to 100 characters.

//for each course
//A pointer to an array of pointers storing all the words in.
//numcourses will be returned.
    int r;
    for( r=0; r < *num_courses; ++r)
    {

        fscanf(fp, "%s", my_course_name);//scans the name of the course.

        // length is equal to the string length of the course name.
        int length_of_course = strlen(my_course_name)+1;


        //This will store the course name.
        // Allocate the correct amount of memory for the arrays.

        fscanf(fp, "%d", &courses_list[r].num_sections); //scans the amount of sections.

        courses_list[r].num_students = malloc(sizeof(int) * courses_list[r].num_sections);//allocates memory for num_students and stores amount of students for each of the course sections.

        //This allocates memory for num_scores array. It's used to store the number of assignments for the section of courses.

        courses_list[r].num_scores =  malloc(sizeof(int) * courses_list[r].num_sections);

        //calling read_section for courses[c]. The arrays will be filled up by the function.

        courses_list[r].sections = read_sections(fp, courses_list[r].num_students,  courses_list[r].num_scores, courses_list[r].num_sections);
        //allocates memory for course_name.
        //   courses_list[r].course_name =  (char *)malloc( sizeof(char));
        courses_list[r].course_name =  malloc( length_of_course);

        strcpy(courses_list[r].course_name, my_course_name);  //This copies string.
    }

//return courses list which consists of the array of courses.
    return courses_list;
}



//reads data for the course sections.It also fills the amount of students and scores.

student **read_sections(FILE*fp, int num_students[], int num_scores[], int num_sections)

{

//stores array of student arrays(2D array). Size is num_sections;

    student **list_of_averages = (student**)malloc(num_sections * sizeof(student *)); //It's an array of the sections.

//for loop for the number of sections.
    int k;
    for( k = 0; k<num_sections; ++k)
    {

        //this will read the amount of students and the grades for this section.
        fscanf(fp, "%d", &num_students[k]);
        fscanf(fp, "%d", &num_scores[k]);

//This will make memory for the students in the array.

        list_of_averages[k] = (student*)malloc(num_students[k]*sizeof(student));  //This is an array of the student averages.

//for students in the section number k

        for(int x=0; x<num_students[k]; x++)

        {
            //last name can fit 100 characters.
            char lname[100];

            //This will read the last name of the student.
            fscanf(fp, "%d""%s", &list_of_averages[k][x].id,lname);

            //This makes memory and string copies the last name to the array

            int length_of_lname = strlen(lname) + 1;

            list_of_averages[k][x].lname =  (char*)malloc( length_of_lname);

//copies students.
            strcpy(list_of_averages[k][x].lname, lname);

            list_of_averages[k][x].scores = (float *)malloc  (sizeof(float) * num_scores[k]);//makes memory for scores.

            int m;
//used to find the average.
            float sum_scores = 0;
            for(m=0; m<num_scores[k]; ++m)
            {

                //used to read input and calculates the average based on list of students and the scores they received.
//scans scores of student from input file.

                fscanf(fp, "%f", &list_of_averages[k][x].scores[m]);

                //score average for student st of section s
                sum_scores += list_of_averages[k][x].scores[m];
                // Will calculate the average

                list_of_averages[k][x].std_avg = sum_scores/num_scores[k];
            }
        }

    }

//returns the section.
    return list_of_averages;

}

//This will show the courses in detail in the output.

void process_courses(course *courses, int num_courses)

{

//This is a forloop for each of the courses.
    int g;
    for ( g=0; g<num_courses; ++g)

    {

        //displays name of the course.  The "." is used when passing the actual
        //variable.

        printf("%s", courses[g].course_name);

//will show details in the course sections.
//The "." is used when passing the variables.
        show_section(courses[g].num_students, courses[g].num_scores, courses[g].num_sections, courses[g].sections );

    }

}

//print details for the sections of a course
//int ns, nus;

int show_section( int num_students[], int num_scores[], int num_sections, student **sections)

{

//stores test average for each section.

    float *avg_score = (float *) malloc(sizeof(num_sections) * sizeof(float));

//This is used to calculate the maximum for each section.
    float highest_average = 0;


    int highest_student_id = 0;


    int highest_section_id = 0;


    int pass_count = 0;



//This is for each section

    int ns;
    for( ns=0; ns <num_sections; ++ns)

    {

        //calculates the sum of averages in section.

        float section_added = 0;


        //for each student of section number s
        int x;
        for( x = 0; x<num_students[ns]; x++)

        {

            //calculates the passing number for each course which are the numbers next to them.  If their average is a 70 for all tests
            //then the student will pass.
            //The "." is used when passing the variable.

            if (sections[ns][x].std_avg >=70)


            {
//incrementing passing_number.
                pass_count++;

            }

            section_added += sections[ns][x].std_avg; //giving answer for the averages of
            //all of the students.
            //"The "." is used when passing the variable.
            //If statement to see which student has the highest average.

            if(sections[ns][x].std_avg>highest_average)

            {
//highest average is calculated using student average in the sections.
                highest_average = sections[ns][x].std_avg;
//This is used to take the id of the student with the highest average.
                highest_student_id = x;
//This takes the section of the student with the highest average.
                highest_section_id = ns;

            }

        }

//This is used for calculating the section averages.

        avg_score[ns] = section_added / num_students[ns];

    }
//This is used for calculatating passing number.  Students who passed.
    printf("%d ", pass_count);
//fThis is a forloop for the sections.
    int i;
    for(i = 0; i<num_sections; ++i)
    {
//This will print section averages
        printf("%.2lf ", avg_score[i]);
    }
// This is used to print results.
    printf("%d %s %.2lf \n",
//This is used to take the id of the highest student.
           sections[highest_section_id][highest_student_id].id,
//This is used used to get last name of the highest student.
           sections[highest_section_id][highest_student_id].lname,
//This is used to get average of highest student using section id.
           sections[highest_section_id][highest_student_id].std_avg

          );


    //This is used to free the memory that was allocated for avg_score.
    free(avg_score);
}

//This will be used to free the memory for the courses.

void free_mem_courses( course *courses, int num_courses)

{



//forloop for the number of courses.

    for (int kh = 0; kh<num_courses; ++kh)

    {
        //Freeing the array memory.  If you don't free the memory, the program will crash.
        //free the course name, num_students and num_scores
        //The "." is used when passing the variable.

        // lets free memory for all the sections for each course
        free_mem_sections( courses[kh].num_sections, courses[kh].num_students, courses[kh].num_scores, courses[kh].sections);
        free(courses[kh].num_students);
        free(courses[kh].course_name);

        free(courses[kh].num_scores);



    }

}

void free_mem_sections( int num_sections, int *num_students, int *num_scores, student **sections)
{
//forloop for  each of the sections



for(int i = 0; i<num_sections; i++)

{

    //forloop used for each of the students.

    for(int j= 0; j<num_students[i]; j++)

    {

      //free the last name and their scores

      free(sections[i][j].lname);

      free(sections[i][j].scores);

    }

    //freeing the section

    free(sections[i]);

}

//lets  free the sections now

free(sections);

}

