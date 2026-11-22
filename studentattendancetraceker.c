#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_DAYS 31

struct Student
{
    int id;
    char name[50];
    int attendance[MAX_DAYS];
};

struct Student students[MAX_STUDENTS];
int numStudents = 0;
int totalDays = 0;

// Enter student details
void enterStudents()
{
    printf("Enter number of students: ");
    scanf("%d", &numStudents);

    for(int i = 0; i < numStudents; i++)
    {
        printf("\nStudent %d\n", i + 1);

        printf("Enter ID: ");
        scanf("%d", &students[i].id);

        printf("Enter Name: ");
        scanf(" %[^\n]", students[i].name);

        for(int j = 0; j < MAX_DAYS; j++)
            students[i].attendance[j] = 0;
    }
}

// Record attendance
void recordAttendance()
{
    int day;

    printf("Enter day number (1-%d): ", MAX_DAYS);
    scanf("%d", &day);

    if(day > totalDays)
        totalDays = day;

    printf("\nEnter Attendance (1 = Present, 0 = Absent)\n");

    for(int i = 0; i < numStudents; i++)
    {
        printf("%s: ", students[i].name);
        scanf("%d", &students[i].attendance[day - 1]);
    }
}

// Display attendance
void displayAttendance()
{
    printf("\nAttendance Record\n");

    printf("ID\tName\t");

    for(int d = 0; d < totalDays; d++)
        printf("D%d ", d + 1);

    printf("\n");

    for(int i = 0; i < numStudents; i++)
    {
        printf("%d\t%s\t", students[i].id, students[i].name);

        for(int d = 0; d < totalDays; d++)
            printf("%d  ", students[i].attendance[d]);

        printf("\n");
    }
}

// Total classes attended
int totalAttended(int index)
{
    int total = 0;

    for(int d = 0; d < totalDays; d++)
        total += students[index].attendance[d];

    return total;
}

// Attendance percentage
float attendancePercentage(int index)
{
    if(totalDays == 0)
        return 0;

    return ((float)totalAttended(index)*100.0f)/(float)totalDays;
}

// Display percentages
void showPercentages()
{
    printf("\nAttendance Percentage\n");

    for(int i = 0; i < numStudents; i++)
    {
        printf("%d\t%s\t%.2f%%\n",
               students[i].id,
               students[i].name,
               attendancePercentage(i));
    }
}

// Low attendance students
void lowAttendance()
{
    float limit;

    printf("Enter minimum attendance percentage: ");
    scanf("%f",&limit);

    printf("\nStudents Below %.2f%% Attendance\n", limit);

    for(int i = 0; i < numStudents; i++)
    {
        if(attendancePercentage(i) < limit)
        {
            printf("%d\t%s\t%.2f%%\n",
                   students[i].id,
                   students[i].name,
                   attendancePercentage(i));
        }
    }
}

// Highest attendance
void highestAttendance()
{
    float max = 0;

    for(int i = 0; i < numStudents; i++)
    {
        float per = attendancePercentage(i);

        if(per > max)
            max = per;
    }

    printf("\nHighest Attendance Students\n");

    for(int i = 0; i < numStudents; i++)
    {
        if(attendancePercentage(i) == max)
        {
            printf("%d\t%s\t%.2f%%\n",
                   students[i].id,
                   students[i].name,
                   max);
        }
    }
}

// Search student by ID
void searchStudent()
{
    int id;
    printf("Enter Student ID: ");
    scanf("%d", &id);

    for(int i = 0; i < numStudents; i++)
    {
        if(students[i].id == id)
        {
            printf("\nStudent Found\n");
            printf("ID : %d\n", students[i].id);
            printf("Name : %s\n", students[i].name);
            printf("Attendance : %d/%d\n",
                    totalAttended(i),
                    totalDays);
            printf("Percentage : %.2f%%\n",
                    attendancePercentage(i));
            return;
        }
    }

    printf("Student Not Found!\n");
}

// Save data to file
void saveToFile()
{
    FILE *fp = fopen("attendance.txt", "w");

    if(fp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    fprintf(fp, "Monthly Attendance Report\n\n");

    for(int i = 0; i < numStudents; i++)
    {
        fprintf(fp,
                "ID: %d\nName: %s\nClasses Attended: %d\nAttendance: %.2f%%\n\n",
                students[i].id,
                students[i].name,
                totalAttended(i),
                attendancePercentage(i));
    }

    fclose(fp);

    printf("Attendance saved to attendance.txt\n");
}

// Monthly report
void monthlyReport()
{
    printf("\n===== MONTHLY ATTENDANCE REPORT =====\n");

    for(int i = 0; i < numStudents; i++)
    {
        printf("\nID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Classes Attended: %d out of %d\n",
               totalAttended(i),
               totalDays);

        printf("Attendance Percentage: %.2f%%\n",
               attendancePercentage(i));
    }
}

int main()
{
    int choice;

    while(1)
    {
        printf("\n\n===== STUDENT ATTENDANCE TRACKER =====\n");
        printf("1. Enter Student Details\n");
        printf("2. Record Attendance\n");
        printf("3. Display Attendance Records\n");
        printf("4. Show Attendance Percentage\n");
        printf("5. Students Below Required Attendance\n");
        printf("6. Highest Attendance Student\n");
        printf("7. Search Student by ID\n");
        printf("8. Save Attendance to File\n");
        printf("9. Generate Monthly Report\n");
        printf("10. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                enterStudents();
                break;

            case 2:
                recordAttendance();
                break;

            case 3:
                displayAttendance();
                break;

            case 4:
                showPercentages();
                break;

            case 5:
                lowAttendance();
                break;

            case 6:
                highestAttendance();
                break;

            case 7:
                searchStudent();
                break;

            case 8:
                saveToFile();
                break;

            case 9:
                monthlyReport();
                break;

            case 10:
                printf("Exiting Program...\n");
                exit(0);

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}
