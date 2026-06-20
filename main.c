#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Name: Bayda' Basim Rahhal , ID: 1250084 , lecture section: 9, lab section:17 , Doctor Ahmed Fahel.

// Global variables to store data for up to 100 students.
int studentIDs[100];    // Array to store 4-digit unique student IDs.
char studentNames[100][50]; //2D Array to store students names(max 50 characters each)
int ages[100];              //Array to store student ages
double gpas[100];           //Array to store student GPAs
int studentCount=0;         //Global counter keeping track of current number of students


//Function to implement Option 4 : Display all students in a tab-aligned format with statistics

void displayAllStudent(){
 if(studentCount==0){
    printf("No students in the system.\n");
    return;}

    printf("\n===ALL STUDENTS===\n");

//Tabbed columns header for consistent visual alignment
    printf("ID\tName\t\tAge\tGPA\n");
    printf("-----------------------------------------------\n");
    double gpaSum=0.0;//Accumulator variable to compute average GPA later
//Loop through all currently populated indices to display student details
    for(int i=0;i<studentCount;i++){
//Double -tab short names to maintain perfect column layout alignment
        if(strlen(studentNames[i])<8){
            printf("%d\t%s\t\t%d\t%.2f\n",studentIDs[i],studentNames[i],ages[i],gpas[i]);
        }else{
        printf("%d\t%s\t%d\t%.2f\n",studentIDs[i],studentNames[i],ages[i],gpas[i]);}
        gpaSum+=gpas[i];
    }
    printf("-------------------------------------------------\n");
//Calculate and print descriptive summary analytics
    double gpaAverage=gpaSum/studentCount;
    printf("Total Students:%d\n",studentCount);
    printf("Average GPA:%.2f\n",gpaAverage);
 }

 // Function to implement option 1 :Add a new student with data validation
void addStudent(){

// Check if the system has reached its maximum capacity(100 students)
if(studentCount>=100){
        printf("Error: System capacity reached. Cannot add more student.\n");
        return;
}
printf("\n===ADD NEW STUDENT===\n");

// Loop for reading and validating Student ID

int tempID;
while(1){
    printf("Enter 4-digit Student ID(1000-9999):");
// Ensure the input is  a valid integer to avoid infinite loops on invalid characters
    if(scanf("%d",&tempID)!=1){
        printf("Invalid input.Please enter a valid number.\n");
        while (getchar()!='\n');// clean input buffer
        continue;}
   if(tempID<1000|| tempID>9999){
    printf("Invalid ID.It should be 4 digits.\n");
    continue;}

//Check for duplicate ID by scanning existing records
int isDuplicate=0;
    for(int i=0;i<studentCount;i++){
        if(studentIDs[i]==tempID){
            isDuplicate=1;// Duplicate found
            break ;}}
    if(isDuplicate==1){
        printf("Error: Student ID already exists.Please enter a different ID.\n");
    }else{
    studentIDs[studentCount]=tempID;// Assign valid, unique ID
    break;//Exit ID validation loop
    }}

while(getchar()!='\n');// Clear the newline character left over from previous scanf
//loop for reading and validating Student Name
while(1){
    printf("Enter Student Name:");
    fgets(studentNames[studentCount],50,stdin);// Read name including spaces
    //Remove the trailing newline character'\n' captured by fgets
    studentNames[studentCount][strcspn(studentNames[studentCount],"\n")]='\0';
    //Check if the name string is completely empty
    if(strlen(studentNames[studentCount])==0){
       printf("Error:Name cannot be empty.\n");}
    else{break;//Valid name , exit loop
    }}

//Loop for reading and validating Student Age
int tempAge;
while(1){
    printf("Enter Student Age:");
    if(scanf("%d",&tempAge)!=1){
        printf("Invalid input. Please enter a valid number.\n");
        while(getchar()!='\n');
        continue;}
// Check if age is within the allowed academic range(6 to 50)
    if(tempAge<6|| tempAge>50){
        printf("Invalid Age.It should be between 6 and 50.\n");}
    else{
        ages[studentCount]=tempAge;// Assign valid age
        break;}
    }
//Loop for reading and validating Student GPA
    double tempGPA;
    while(1){
        printf("Enter GPA:");
        if(scanf("%lf",&tempGPA)!=1){
            printf("Invalid input. Please enter a valid number.\n");
            while(getchar()!='\n');
            continue;}
// Check if GPA is within the valid range (0.0 to 4.0)
        if(tempGPA<0.0|| tempGPA>4.0){
            printf("invalid GPA . It should be between 0.0 and 4.0\n");

        }else{gpas[studentCount]=tempGPA;// Assign valid GPA
        break;}
    }
// Successfully saved all fields , increment the total student counter
    printf("Student added successfully!\n");
    studentCount++;

}
//Function to implement Option 3: Search for a student by ID
void searchStudent(){
     if(studentCount==0){
        printf("No student in the system to search for.\n");
        return;
     }
     int searchID;
     printf("\n===SEARCH FOR STUDENTS===\n");
     printf("Enter Student ID to search: ");
     if(scanf("%d",&searchID)!=1){
        printf("Invalid input.ID must be a number.\n");
        while(getchar()!='\n');
        return;
     }
     int foundIndex= -1;
//Linear search loop to look for the matching ID
     for(int i=0;i<studentCount;i++){
        if(studentIDs[i]==searchID){
            foundIndex=i;//Match found, store the current index
            break;
        }
     }

//Print details if found , otherwise print error message
     if(foundIndex!= -1){
        printf("\nStudent Found:\n");
        printf("----------------------------\n");
        printf("ID:  %d\n",studentIDs[foundIndex]);
        printf("Name:  %s\n",studentNames[foundIndex]);
        printf("Age:  %d\n",ages[foundIndex]);
        printf("GPA:   %.2f\n",gpas[foundIndex]);
        printf("-----------------------------\n");
     }else{
        printf("Student with ID %d not found in the system.\n",searchID);}
}
//Function to implement Option 2: Remove a student by ID using array shifting

void removeStudent(){
// Check if the system is completely empty
    if(studentCount==0){
        printf("No students in the system to remove.\n");
        return;
    }
    int deleteID;
    printf("\n===REMOVE STUDENT===\n");
    printf("Enter Student ID to remove :");
    if(scanf("%d",&deleteID)!=1){
        printf("Invalid input. ID must be a number.\n");
        while(getchar()!='\n');
        return;
    }
    int foundIndex= -1;// -1 indicates the student has not been found yet
    // Search for target ID in the records
    for(int i=0;i<studentCount;i++){
        if(studentIDs[i]==deleteID){
            foundIndex=i;//Save the location index of the student
            break;
        }
    }
// If ID was not found , notify user and exit function
    if(foundIndex== -1){
        printf("Student with ID %d not found in the system.\n",deleteID);
        return;
    }
//Shift all subsequent student data one position to the left to overwrite deleted record
    for(int j=foundIndex;j<studentCount-1;j++){
        studentIDs[j]=studentIDs[j+1];
        strcpy(studentNames[j],studentNames[j+1]);//use strcpy for string arrays
        ages[j]=ages[j+1];
        gpas[j]=gpas[j+1];
    }
//Decrement the total student count to complete removal
    studentCount--;
    printf("Student with ID %d removed successfully!\n",deleteID);}

void initializeStudentRecords(){
printf("Student records loaded successfully.\n");} //Function to print a simulated loading / initialization message.


// Function to display the main operation menu to the user
void displayMainMenu(){
printf("\n===STUDENT RECORD MANAGEMENT SYSTEM===\n");
printf("Please Select an Operation(1-5):\n");
printf("1-Add New Student\n");
printf("2-Remove Student\n");
printf("3-Search for Student\n");
printf("4-Display All Students\n");
printf("5-Exit System\n");
printf("Enter your choice:");}

//Main driver function- coordinates system operations and controls application flow
int main()
{
int choice;

//Initialize the records once upon application startup
initializeStudentRecords();

//Infinite master loop to keep system running until user chooses Option 5(Exit)
while(1){
displayMainMenu();//Keep printing the menu  options on every cycle

//scan the operational choice from console
scanf("%d",&choice);
//Switch block acting as the control flow router for menu operations
switch(choice){
case 1:
    addStudent();//Route to add students routine
    break;
case 2:
    removeStudent();//Route to remove students routine
    break;
case 3:
    searchStudent();//Route to search students routine
    break;
case 4 :
    displayAllStudent();//Route to print all students routine
    break;
case 5:

//Mandatory mock data persistence save announcement before terminating
    printf("All students records saved to file.\n");
    printf("Exiting system. Goodbye!\n");
    return 0;
default:

//Handle arbitrary choices outside the expected range
    printf("Invalid operation. Please try again.\n");
    }
}


    return 0;
}
