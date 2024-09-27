/*
    Program description: this program holds information about 4 production lines within an aeronautical company including product IDs, issue codes, descriptions,
    resolution codes, descriptions and employee IDs. The program displays the given production lines and then in the following 4 tasks we sort the production lines by
    product ID issue code and date/time (task1), we then combine all of this into one single list (task2), then in task 3 we provide a feature to search for the earliest
    occurence of a product ID and its given issue code and then finally task 4 reports the amount of issues reported throughout the production lines for each product ID

    Author: Justin McGarr

    Date: 25th March 2024
*/

//header files
#include <stdio.h>
#include <stdlib.h>

//symbolic names
#define DESCRIPTION 100
#define SIZE 12
#define UNIQUE_LINES 7

//structure declarations
struct batch_date
{
    int day;
    int hour;
    int minute;
};
struct issue_code
{
    int iss_code;
    char iss_description[DESCRIPTION];    
};
struct resolution_code
{
    int res_code;
    char res_description[DESCRIPTION];
};
struct production_line
{
    int line_code;
    int batch_code;
    struct batch_date batch_date;
    int product_ID;
    struct issue_code issue_code;
    struct resolution_code resolution_code;
    int employee_ID;
};
struct node
{
    struct production_line linklist;
    struct node *link;
};

//Function Signatures

//task 1
//Sorting product ID
void prodIDsort(struct production_line[], int, int);
void prodIDmerge(struct production_line[], int, int, int);

//Sorting issue code
void issuecodeSort(struct production_line[]);
void issuecodeMergeSort(struct production_line line[], int, int);
void issuecodeMerge(struct production_line line[],int,int,int);

//Sorting date and time
void datetimeSort(struct production_line[]);
void datetimeMergeSort(struct production_line[],int,int);
void datetimeMerge(struct production_line[],int,int,int);

//displaying task 1
void printProductionLine(struct production_line[],int);
void sorted_productionline(struct production_line[],struct production_line[],struct production_line[],struct production_line[]);

//task2
//Creating single-list
struct node* linked_list(struct production_line[],struct production_line[],struct production_line[],struct production_line[], struct node*);
//printing single-list 
void printlinklist(struct node *first);

//task 3
//Searching
void productsearch(struct production_line[],struct production_line[],struct production_line[],struct production_line[]);
int binarysearch(struct production_line[],int,int,int,int);

//task 4
//Searching
void task4(struct production_line[],struct production_line[],struct production_line[],struct production_line[]);
int* linearSearch(struct production_line[],struct production_line[],struct production_line[],struct production_line[],int,int,int[]);


int main()
{
    //initialising the single list for task2
    struct node *first = NULL;
    struct node *result = NULL;
    //intialising production line data, format = {linecode,batchcode,time,productID,{issuecode,issudesc},{resolutioncode,resolutiondesc},employeeID}
    //line1
    struct production_line line1[SIZE] =
    {
        {1, 10789, {10, 8, 10}, 503456, {334501, "Cockpit instrument lighting not working."}, {392135, "Repair or replace malfunctioning cockpit instrument lighting."}, 20235},
        {1, 18123, {15, 4, 54}, 544567, {303456, "Engine experiences intermittent sputtering."}, {309876, "clean fuel filters or adjust ignition timing."}, 20867},
        {1, 11456, {15, 6, 12}, 559876, {332135, "Cabin wi bbyhgndow cracked or shattered."}, {335678, "Replace the broken window pane with a new one."}, 20453},
        {1, 13678, {19, 9, 13}, 515678, {334501, "Cockpit instrument lighting not working."}, {392135, "Repair or replace malfunctioning cockpit instrument lighting."}, 20576},
        {1, 10987, {12, 9, 47}, 592135, {301890, "Flap control mechanism stuck."}, {328901, "Inspect and lubricate flap control mechanisms."}, 20198},
        {1, 17345, {11, 10, 15}, 508901, {335678, "Radio transmit button unresponsive."}, {377654, "Repair or replace the radio transmit button or associated wiring."}, 20312},
        {1, 18567, {27, 4, 16}, 537654, {308901, "Oxygen mask deployment system malfunctioning."}, {301890, "Inspect and repair the oxygen mask deployment system."}, 20734},
        {1, 10789, {13, 11, 17}, 503456, {301234, "Indicator light for landing gear malfunctioning."}, {314567, "Inspect and replace the indicator light bulb"}, 20904},
        {1, 18123, {5, 11, 29}, 544567, {335678, "Radio transmit button unresponsive."}, {377654, "Repair or replace the radio transmit button or associated wiring."}, 20658},
        {1, 11456, {30, 5, 19}, 559876, {301234, "Indicator light for landing gear malfunctioning."}, {314567, "Inspect and replace the indicator light bulb"}, 20134},
        {1, 13678, {19, 16, 20}, 515678, {301890, "Flap control mechanism stuck."}, {392135, "Repair or replace malfunctioning cockpit instrument lighting."}, 20890},
        {1, 10987, {12, 13, 44}, 592135, {303456, "Engine experiences intermittent sputtering."}, {309876, "clean fuel filters or adjust ignition timing."}, 20765},
    };
    //line2
    struct production_line line2[SIZE] =
    {
        {2, 13678, {23, 15, 32}, 515678, {334501, "Cockpit instrument lighting not working."}, {392135, "Repair or replace malfunctioning cockpit instrument lighting."}, 20755},
        {2, 10789, {8, 12, 5}, 503456, {303456, "Engine experiences intermittent sputtering."}, {309876, "clean fuel filters or adjust ignition timing."}, 20976},
        {2, 10987, {14, 7, 19}, 592135, {301890, "Flap control mechanism stuck."}, {328901, "Inspect and lubricate flap control mechanisms."}, 20432},
        {2, 18123, {11, 18, 46}, 544567, {303456, "Engine experiences intermittent sputtering."}, {309876, "clean fuel filters or adjust ignition timing."}, 20194},
        {2, 11456, {5, 6, 57}, 559876, {334501, "Cockpit instrument lighting not working."}, {392135, "Repair or replace malfunctioning cockpit instrument lighting."}, 20842},
        {2, 13678, {16, 11, 28}, 515678, {308901, "Oxygen mask deployment system malfunctioning."}, {301890, "Inspect and repair the oxygen mask deployment system."}, 20680},
        {2, 10789, {19, 8, 14}, 503456, {301234, "Indicator light for landing gear malfunctioning."}, {314567, "Inspect and replace the indicator light bulb."}, 20237},
        {2, 18567, {27, 3, 22}, 537654, {308901, "Oxygen mask deployment system malfunctioning."}, {301890, "Inspect and repair the oxygen mask deployment system."}, 20908},
        {2, 17345, {10, 9, 33}, 508901, {335678, "Radio transmit button unresponsive."}, {377654, "Repair or replace the radio transmit button or associated wiring."}, 20572},
        {2, 11456, {18, 15, 48}, 559876, {332135, "Cabin window cracked or shattered."}, {335678, "Replace the broken window pane with a new one."}, 20321},
        {2, 10987, {21, 7, 9}, 592135, {301890, "Flap control mechanism stuck."}, {328901, "Inspect and lubricate flap control mechanisms."}, 20763},
        {2, 18123, {13, 4, 35}, 544567, {303456, "Engine experiences intermittent sputtering."}, {309876, "clean fuel filters or adjust ignition timing."}, 20849},
    };
    //line3
    struct production_line line3[SIZE] =
    {
        {3, 18123, {9, 17, 42}, 544567, {335678, "Radio transmit button unresponsive."}, {377654, "Repair or replace the radio transmit button or associated wiring."}, 20876},
        {3, 10987, {20, 11, 28}, 592135, {301890, "Flap control mechanism stuck."}, {328901, "Inspect and lubricate flap control mechanisms."}, 20342},
        {3, 10789, {14, 6, 19}, 503456, {303456, "Engine experiences intermittent sputtering."}, {309876, "clean fuel filters or adjust ignition timing."}, 20987},
        {3, 13678, {22, 10, 57}, 515678, {335678, "Radio transmit button unresponsive."}, {377654, "Repair or replace the radio transmit button or associated wiring."}, 22563},
        {3, 11456, {18, 14, 33}, 559876, {335678, "Radio transmit button unresponsive."}, {377654, "Repair or replace the radio transmit button or associated wiring."}, 27756},
        {3, 10789, {16, 9, 24}, 503456, {301234, "Indicator light for landing gear malfunctioning."}, {314567, "Inspect and replace the indicator light bulb."}, 28198},
        {3, 13678, {12, 8, 17}, 515678, {334501, "Cockpit instrument lighting not working."}, {392135, "Repair or replace malfunctioning cockpit instrument lighting."}, 26454},
        {3, 10987, {11, 7, 46}, 592135, {301890, "Flap control mechanism stuck."}, {328901, "Inspect and lubricate flap control mechanisms."}, 20875},
        {3, 18567, {25, 5, 38}, 537654, {308901, "Oxygen mask deployment system malfunctioning."}, {301890, "Inspect and repair the oxygen mask deployment system."}, 24429},
        {3, 11456, {17, 12, 52}, 559876, {332135, "Cabin window cracked or shattered."}, {335678, "Replace the broken window pane with a new one."}, 22632},
        {3, 18123, {8, 15, 21}, 544567, {303456, "Engine experiences intermittent sputtering."}, {309876, "clean fuel filters or adjust ignition timing."}, 29384},
        {3, 17345, {19, 13, 14}, 508901, {335678, "Radio transmit button unresponsive."}, {377654, "Repair or replace the radio transmit button or associated wiring."}, 21237},
    };
    //line4
    struct production_line line4[SIZE] =
    {
        {4, 13678, {13, 8, 35}, 515678, {308901, "Oxygen mask deployment system malfunctioning."}, {301890, "Inspect and repair the oxygen mask deployment system."}, 20842},
        {4, 10789, {17, 10, 28}, 503456, {335678, "Radio transmit button unresponsive."}, {377654, "Repair or replace the radio transmit button or associated wiring."}, 20755},
        {4, 10987, {21, 12, 47}, 592135, {334501, "Cockpit instrument lighting not working."}, {392135, "Repair or replace malfunctioning cockpit instrument lighting."}, 21543},
        {4, 18123, {10, 7, 19}, 544567, {308901, "Oxygen mask deployment system malfunctioning."}, {301890, "Inspect and repair the oxygen mask deployment system."}, 20698},
        {4, 11456, {16, 9, 52}, 559876, {332135, "Cabin window cracked or shattered."}, {335678, "Replace the broken window pane with a new one."}, 20123},
        {4, 10789, {14, 6, 37}, 503456, {301234, "Indicator light for landing gear malfunctioning."}, {314567, "Inspect and replace the indicator light bulb."}, 21784},
        {4, 13678, {18, 11, 44}, 515678, {334501, "Cockpit instrument lighting not working."}, {392135, "Repair or replace malfunctioning cockpit instrument lighting."}, 20987},
        {4, 10987, {12, 8, 51}, 592135, {301890, "Flap control mechanism stuck."}, {328901, "Inspect and lubricate flap control mechanisms."}, 22876},
        {4, 18567, {26, 4, 28}, 537654, {308901, "Oxygen mask deployment system malfunctioning."}, {301890, "Inspect and repair the oxygen mask deployment system."}, 20349},
        {4, 11456, {15, 12, 39}, 559876, {301234, "Indicator light for landing gear malfunctioning."}, {314567, "Inspect and replace the indicator light bulb."}, 21056},
        {4, 18123, {9, 13, 17}, 544567, {303456, "Engine experiences intermittent sputtering."}, {309876, "clean fuel filters or adjust ignition timing."}, 23567},
        {4, 17345, {20, 15, 22}, 508901, {335678, "Radio transmit button unresponsive."}, {377654, "Repair or replace the radio transmit button or associated wiring."}, 21654},
    };
    //functions to display the unordered , original data
    printf("\nprinting original data before sorting\n");
    printproduction_line(line1, 1);
    printproduction_line(line2, 2);
    printproduction_line(line3, 3);
    printproduction_line(line4, 4);
    //sorting and printing the linens by product ID , issue code and time
    sorted_productionline(line1,line2,line3,line4);
    
    //creating and printing the linked list frr task 2
    first = linked_list(line1,line2,line3,line4,first);
    printlinklist(first);
    
    //searching for the earliest occurence of a product ID
    productsearch(line1,line2,line3,line4);
    
    //reporting the amount of issue codes within the code
    task4(line1,line2,line3,line4);
    
}   
//divides prodIDS to merge sort them
void prodIDsort(struct production_line line[], int low, int high)
{
    int mid = 0;
    //dividing elements till they get to one
    if(low >= high)
    {
        //causes the pop
        return;
    }
    else
    {
        mid = (low+high)/2;
        //divide struct into left and right
        prodIDsort(line, low, mid);
        prodIDsort(line, mid +1, high);
        //using merge rejoins them back into one
        prodIDmerge(line, low, mid, high);
    }
}//end prodIDsort

//merge prodID separated structure and sort them
void prodIDmerge(struct production_line line[], int low, int mid, int high)
{
    struct production_line tempstruct[SIZE];
    int i, j, t;
    i = low; // i is left
    j = mid + 1; // j is right
    t = i; // t is temp variable
    
    //using every single element
    while(i <= mid && j <= high)
    {
        //if i is bigger than j then line[j] is put into the temporary structure and t and i are incremented to continue sorting
        if(line[i].product_ID<=line[j].product_ID)
        {
            tempstruct[t++] = line[i++];
        }
        else
        {
            tempstruct[t++] = line[j++];
        }
    }
    //any leftover elements to be used
    if(i > mid)
    {
        while(j <= high)
        {
            tempstruct[t++] = line[j++];
        }
    }
    else
    {
        while(i <= mid)
        {
            tempstruct[t++] = line[i++];
        }
    }
    //placing all sorted elements into the original structure now 
    for(i = low ; i<= high; i++)
    {
        line[i] = tempstruct[i];
    }
}//end prodIDmerge

//sorting issue codes with the product IDs that correspond to them and deal with duplicates
void issuecodeSort(struct production_line line[])
{
    int start = 0;
    int end = 0;
    int curr = 0;
    int i;
    for(i=0;i<SIZE;i++)
    {
        start = i; //beginning
        curr = i; //current produt ID
        
        //find first index of a product ID
        while(line[curr].product_ID == line[i].product_ID)
        {
            //continue looking for duplicates
            i++;
        }
        //stop once all have been found by decrementing
        i--;
        end = i;
        
        //as long as beginning and end are different , call merge sort
        if (end > start)
        {
            issuecodeMergeSort(line, start, end);
        }
    }
}//end issuecodeSort

//merge sort for issue codes
void issuecodeMergeSort(struct production_line line[], int low, int high)
{
    int mid = 0;
    
    //divides array until elements are only one
    if(low >= high)
    {
        //causes the pop
        return;
    }
    else
    {
        mid = (low+high)/2;
        
        //divides into left and right sections
        issuecodeMergeSort(line, low, mid);
        issuecodeMergeSort(line, mid +1, high);
        
        //rejoins the substructures back into the original 
        issuecodeMerge(line, low, mid, high);
    }
}//end issuecodeMergeSort
void issuecodeMerge(struct production_line line[], int low, int mid, int high)
{
    struct production_line tempstruct[SIZE];
    int i, j, t;
    i = low; // i is left
    j = mid + 1; // j is right
    t = i; // t is temp variable
    while (i <= mid && j <= high)
    {
        //if i is bigger than j then line[j] is put into the temporary structure and t and i are incremented to continue sorting
        if (line[i].issue_code.iss_code<= line[j].issue_code.iss_code)
        {
            tempstruct[t++] = line[i++];
        }
        else
        {
            tempstruct[t++] = line[j++];
        }
    }
    if (i > mid)
    {
        //use leftover elements
        while (j <= high)
        {
            tempstruct[t++] = line[j++];
        }
    }
    else
    {
        while (i <= mid)
        {
            tempstruct[t++] = line[i++];
        }
    }
    
    //place sorted elements back into original structure only sorted elements
    for (i = low; i <= high; i++)
    {
        line[i] = tempstruct[i];
    }
}//issuecodeMerge

//sort times within duplicate time values or such for IDs
void datetimeSort(struct production_line line[])
{
    int start = 0;
    int end = 0;
    int curr = 0;
    int i;
    for(i=0;i<SIZE;i++)
    {
        start = i; //start
        curr = i; //current product ID
        
        //finds the start and the end of specific product ID indexes
        while(line[curr].product_ID == line[i].product_ID)
        {
            i++;
            //continue looking
        }
        //stop looking for duplicates once found by decrementing
        i--;
        end = i; // i becomes the finall o
        
        //if start and end are different , call mergesort
        if (end > start)
        {
            datetimeMergeSort(line, start, end);
        }
    } 
}//end datetimeSort
void datetimeMergeSort(struct production_line line[], int low, int high)
{
    int mid = 0;
    //divides array until elements are one
    if(low >= high)
    {
        //causes the pop
        return;
    }
    else
    {
        mid = (low+high)/2;
        //splits structure into left and rigth section
        datetimeMergeSort(line, low, mid);
        datetimeMergeSort(line, mid +1, high);
        
        //rejoins back into one structure
        datetimeMerge(line, low, mid, high);
    }
}//end datetimeMergeSort
void datetimeMerge(struct production_line line[], int low, int mid, int high)
{
     struct production_line tempstruct[SIZE];
    int i, j, t;
    i = low; // i is left
    j = mid + 1; // j is right
    t = i; // t is temp variable
   
    //use all elements
    while (i <= mid && j <= high)
    {
         //if i is bigger than j then line[j] is put into the temporary structure and t and i are incremented to continue sorting
        if (line[i].batch_date.day<= line[j].batch_date.day)
        {
            tempstruct[t++] = line[i++];
        }
        //if the other way around also place j into the temporary structure
        else if(line[i].batch_date.day>= line[j].batch_date.day)
        {
            tempstruct[t++] = line[j++];
        }
        else
        {
            //else ifs do the same as the original but now measure for the hour as opposed to day
            if (line[i].batch_date.hour<= line[j].batch_date.hour)
            {
                tempstruct[t++] = line[i++];
            }
            else if(line[i].batch_date.hour>= line[j].batch_date.hour)
            {
                tempstruct[t++] = line[j++];
            }
            else
            {
            
                //sorting minutes into th eemporart structure
                if (line[i].batch_date.minute<= line[j].batch_date.minute)
                {
                    tempstruct[t++] = line[i++];
                }
                else if(line[i].batch_date.minute>= line[j].batch_date.minute)
                {
                    tempstruct[t++] = line[j++];
                }
            }
        }
    }
    //dealing with any elements that are leftover
    if (i > mid)
    {
        while (j <= high)
        {
            tempstruct[t++] = line[j++];
        }
    }
    else
    {
        while (i <= mid)
        {
            tempstruct[t++] = line[i++];
        }
    }
    //transfer all the sorted elements back into the original structure
    for (i = low; i <= high; i++)
    {
        line[i] = tempstruct[i];
    }
}//end datetimeMerge

//function to print the unordered QA lines
void printproduction_line(struct production_line line[], int lineNum) 
{
    printf("\n\n\nProduction Line %d:\n\n", lineNum);
    printf("Batch Code:\tDate:  Time:\tProduct ID:\tIssue Code:\tIssue Description:\t\t\t\tResolution Code:\tResolution Description:\t\t\t\t\t     Employee ID:");
    printf("\n----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < SIZE; i++) 
    {
        printf("    %d    ", line[i].batch_code);
        printf("    %d    %d:%d   ", line[i].batch_date.day, line[i].batch_date.hour, line[i].batch_date.minute);
        printf("   %d    ", line[i].product_ID);
        printf("   \t%d    ", line[i].issue_code.iss_code);
        printf(" \t%-50s", line[i].issue_code.iss_description);
        printf("   %d", line[i].resolution_code.res_code);
        printf("     %-65s   ", line[i].resolution_code.res_description);
        printf("%d\n", line[i].employee_ID);
    }
}//end printproductionline

//task 1 function to print the production lines sorted by product ID , issue code and date/time
void sorted_productionline(struct production_line line1[], struct production_line line2[], struct production_line line3[], struct production_line line4[])
{
    int i;
    //line 1 sorting
    prodIDsort(line1, 0, SIZE - 1); //product merge sort and merge
    datetimeSort(line1); //date sort , merge sort and merge
    issuecodeSort(line1); //issuecode sort , merge sort and merge

    //line 2 sorting
    prodIDsort(line2, 0, SIZE - 1); //product merge sort and merge
    datetimeSort(line2); //date sort , date merge sort and merge
    issuecodeSort(line2); //issue sort , issue merge sort amd merge

    //line 3 sorting
    prodIDsort(line3, 0, SIZE - 1); //product merge sort and merge
    datetimeSort(line3); //date sort, date merge sort and merge
    issuecodeSort(line3); //issuecode sort , issue merge sort and merge

    //line 4 sorting
    prodIDsort(line4, 0, SIZE - 1); //product merge sort and merge
    datetimeSort(line4); //date sort, date merge sort and merge
    issuecodeSort(line4); //issuecode sort, issue merge sort and merge

    //print task 2 and the sorted lines
    printf("\nTask 1");
    
    printf("\n\033[4mLine1\033[0m");
    printf("\nProduct ID\tIssue Code\tDay\tHour\tMin\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d\t\t%d\t\t%d\t%d\t%d\n", line1[i].product_ID, line1[i].issue_code.iss_code,line1[i].batch_date.day,line1[i].batch_date.hour,line1[i].batch_date.minute);
    }

    printf("\n\033[4mLine2\033[0m");
    printf("\nProduct ID\tIssue Code\tDay\tHour\tMin\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d\t\t%d\t\t%d\t%d\t%d\n", line2[i].product_ID, line2[i].issue_code.iss_code,line2[i].batch_date.day,line2[i].batch_date.hour,line2[i].batch_date.minute);
    }

    printf("\n\033[4mLine3\033[0m");
    printf("\nProduct ID\tIssue Code\tDay\tHour\tMin\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d\t\t%d\t\t%d\t%d\t%d\n",line3[i].product_ID, line3[i].issue_code.iss_code,line3[i].batch_date.day,line3[i].batch_date.hour,line3[i].batch_date.minute);
    }

    printf("\n\033[4mLine4\033[0m");
    printf("\nProduct ID\tIssue Code\tDay\tHour\tMin\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d\t\t%d\t\t%d\t%d\t%d\n", line4[i].product_ID, line4[i].issue_code.iss_code,line4[i].batch_date.day,line4[i].batch_date.hour,line4[i].batch_date.minute);
    }
}//end sorted_productionline


struct node* linked_list(struct production_line line1[],struct production_line line2[],struct production_line line3[],struct production_line line4[], struct node *first)
{
    int i;
    
    //node used to cycle through and add each time
    struct node *temp;
    struct node *ptr;
    
    //node 1 of the list
    first = (struct node *)malloc(sizeof(struct node));
    first->linklist = line1[0];
    first->link = NULL;
    ptr = first;

    //adding line 1 to list
    for(i = 1; i<SIZE;i++)
    {
        //create new node
        temp = (struct node *)malloc(sizeof(struct node));
        temp->linklist = line1[i];
        temp->link = NULL;
        //ptr pointing to the new node and assigning to temp
        ptr->link = temp;
        ptr = temp;      
    }
    //line 2
    for(i = 0; i<SIZE;i++)
    {
        // new node
        temp = (struct node *)malloc(sizeof(struct node));
        temp->linklist = line2[i];
        temp->link = NULL;
        //ptr pointing to the new node and assigning to temp
        ptr->link = temp;
        ptr = temp;      
    }
    //line 3
    for(i = 0; i<SIZE;i++)
    {
        //new node
        temp = (struct node *)malloc(sizeof(struct node));
        temp->linklist = line3[i];
        temp->link = NULL;
        //ptr pointing to the new node and assigning to temp
        ptr->link = temp;
        ptr = temp;      
    }
    
    //line 4
    for(i = 0; i<SIZE;i++)
    {
        //new node
        temp = (struct node *)malloc(sizeof(struct node));
        temp->linklist = line4[i];
        temp->link = NULL;
        //ptr pointing to the new node and assigning to temp
        ptr->link = temp;
        ptr = temp;      
    }
    //return to main so i can print
    return first;
}//end linked_list

//function to print the linked list for task 2
void printlinklist(struct node *first)
{
    //if list is empty tell user so
    if(first == NULL)
    {
        printf("\nlinked list is empty\n");
    }
    struct node *ptr = NULL;
    //ptr = head and will cycle through the rest of the list
    ptr = first; 
    printf("\n\n\n\nTask 2 - Copying the data structures from all 4 Production Lines into a Single Linked-List");
    printf("\n\nLine ID | Product ID | Issue Code");
    printf("\n----------------------------------");
    //ptr cycles list until it finds NULL aka linked list is done
    while(ptr != NULL)
    {
        printf("\n%d\t   %d\t %d", ptr->linklist.line_code,ptr->linklist.product_ID,ptr->linklist.issue_code.iss_code);
        //point to the next node and continue looking
        ptr = ptr->link;
    }
}//end printlinklist

//function to look for a given product ID and issue code at its earliest occurence for task 3
void productsearch(struct production_line line1[],struct production_line line2[],struct production_line line3[],struct production_line line4[])
{
    struct production_line tempstruct[4]; //stores the earliest occurence in each line
    int l = 0;
    int r = SIZE - 1;
    int result = 0;
    int searchID = 0;
    int searchissue = 0;
    int occurence = 0;

    printf("\nProduct IDS are:503456,544567,559876,515678,592135,508901,537654\n");
    printf("\n\nEnter your target productID:");
    scanf("%d", &searchID);
    printf("\nIssue codes are:334501,303456,332135,301890,335678,308901,301234\n");
    printf("\n\nEnter your target issue code:");
    scanf("%d", &searchissue);

    //line 1 search  
    result = binarysearch(line1,l,r,searchID,searchissue);

    if(result !=  -1)
    {
        tempstruct[occurence] = line1[result];
        occurence++;
    } 

    //line 2 search
    result = binarysearch(line2,l,r,searchID,searchissue);
    //if the result is found
    if(result != -1)
    {
        tempstruct[occurence] = line2[result];
        occurence++;
    } 

    //line 3 search
    result = binarysearch(line3,l,r,searchID,searchissue);
    //if the result is found
    if(result != -1)
    {
        tempstruct[occurence] = line3[result];
        occurence++;
    }
    
    //line 4 search
    //if the result is found
    result = binarysearch(line4,l,r,searchID,searchissue);
    if(result != -1)
    {
        tempstruct[occurence] = line4[result];
        occurence++;
    }
    
    //searching the temporary structure aka all 4 lines
    result = binarysearch(tempstruct,l,r,searchID,searchissue);
    
    //if the given product ID and issue code does not exist then tell the user
    if (result == -1)
    {
        printf("\nthis pair does not exist in the production lines.\n");
    }
    else
    {
        //binary search the temporary structure containing all the searched lines
        binarysearch(tempstruct,l,r,searchID,searchissue);
        printf("\nProduction Line | Product ID | Issue Code  | Date Time (Hr:Min)");
        printf("\n-----------------------------------------------------------------------------");
        printf("\n%d\t\t| %d     |%d\t   |  %d  %d:%d", tempstruct->line_code, tempstruct->product_ID, tempstruct->issue_code.iss_code, tempstruct->batch_date.day, tempstruct->batch_date.hour, tempstruct->batch_date.minute);
    }
}//end productsearch

//function to use binary search to find the earliest occurence of given product ID and issuecode pairs
int binarysearch(struct production_line tempstruct[],int l,int r,int searchID,int searchissue)
{
    int mid = 0;
    if(l > r)
    {
        return -1;
    }
    else
    {
        mid = (l+r)/2;
        //if the middle is the target ID and the target issue code already then return the middle
        if(tempstruct[mid].product_ID == searchID && tempstruct[mid].issue_code.iss_code == searchissue)
        {
            return mid;
        }
        //if the target ID is less than the middle or its the right ID but less than the right issue code, then we binary search the left side of the temporrary structure
        else if(searchID < tempstruct[mid].product_ID || (tempstruct[mid].product_ID == searchID && searchissue < tempstruct[mid].issue_code.iss_code))
        {
            return binarysearch(tempstruct,l, mid -1, searchID,searchissue);
        }
        //otherwise we search the right side of the temporary structure
        else
        {
            return binarysearch(tempstruct, mid + 1,r,searchID,searchissue);
        }
    }
}//end binarysearch

//task 4
void task4(struct production_line line1[], struct production_line line2[], struct production_line line3[], struct production_line line4[])
{
    int arr_503456[UNIQUE_LINES];
    int arr_544567[UNIQUE_LINES];
    int arr_559876[UNIQUE_LINES];
    int arr_515678[UNIQUE_LINES];
    int arr_592135[UNIQUE_LINES];
    int arr_508901[UNIQUE_LINES];
    int arr_537654[UNIQUE_LINES];


    int* counts[UNIQUE_LINES] = {arr_503456, arr_544567, arr_559876, arr_515678, arr_592135, arr_508901, arr_537654};


    //intialise arrays of the numbers we will be looking for
    int arrOfProdIDs[] = {503456,544567,559876,515678,592135,508901,537654};
    int issueCodeIndexMap[UNIQUE_LINES] = {334501,303456,332135,301890,335678,308901,301234};




    //count is the amount of times we find the productIDs and issue codes in the lines using linear search
    for (int i = 0; i < UNIQUE_LINES; i++){
        counts[i] = linearSearch(line1, line2, line3, line4, arrOfProdIDs[i], SIZE, issueCodeIndexMap);
    }


    //printing task 4
    printf("\n\n\nTask 4\n");
    printf("\nIssues reported on products over all production lines:\n");
    printf("\nIssue Codes     |\t3032\t3147\t3210\t3276\t3428\t3856\t3965\n");
    printf("-----------------------------------------------------------------------------\n");


    for (int i = 0; i < UNIQUE_LINES; i++) {
        printf("Product ID %d: ", arrOfProdIDs[i]);
        for (int j = 0; j < UNIQUE_LINES; j++) {
            printf("\t%d ", counts[i][j]);
        }
        printf("\n");
    }
}//end task4
int* linearSearch(struct production_line line1[], struct production_line line2[], struct production_line line3[], struct production_line line4[], int prodID, int N, int issueCodeIndexMap[])
{


    //the amount of time each issue code is reported throughout the code
    int* issueCodesPresence = (int *)calloc(UNIQUE_LINES, sizeof(int));




    //line 1
    for (int i = 0; i < N; i++) {
        if (line1[i].product_ID == prodID) {
            for (int j = 0; j < 7; j++) {
                if (line1[i].issue_code.iss_code == issueCodeIndexMap[j]) {
                    //if the issue code is found increment the counter
                    issueCodesPresence[j]++;
                    break;
                }
            }
        }
    }




    //line 2
    for (int i = 0; i < N; i++) {
        if (line2[i].product_ID == prodID) {
            for (int j = 0; j < 7; j++) {
                if (line2[i].issue_code.iss_code == issueCodeIndexMap[j]) {
                    //if the issue code is found increment the counter
                    issueCodesPresence[j]++;
                    break;
                }
            }
        }
    }




    //line 3
    for (int i = 0; i < N; i++) {
        if (line3[i].product_ID == prodID) {
            for (int j = 0; j < 7; j++) {
                if (line3[i].issue_code.iss_code == issueCodeIndexMap[j]) {
                    //if the issue code is found increment the counter
                    issueCodesPresence[j]++;
                    break;
                }
            }
        }
    }




    //line 4
    for (int i = 0; i < N; i++) {
        if (line4[i].product_ID == prodID) {
            for (int j = 0; j < 7; j++) {
                if (line4[i].issue_code.iss_code == issueCodeIndexMap[j]) {
                    //if the issue code is found increment the counter
                    issueCodesPresence[j]++;
                    break;
                }
            }
        }
    }




    return issueCodesPresence;
}//end linear search
