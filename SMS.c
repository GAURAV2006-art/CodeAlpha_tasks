//Create a menu-driven C program to manage student records.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- 1. Structure Definition ---
typedef struct {
    int id;
    char name[50];
    char course[20];
    float gpa;
} Student;

// --- Function Prototypes ---
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void clearInputBuffer();

// Name of the file where data will be stored
const char *FILENAME = "students.dat";

int main() {
    int choice;

    while (1) {
        // --- Menu UI ---
        printf("\n=== STUDENT MANAGEMENT SYSTEM ===\n");
        printf("1. Add Student\n");
        printf("2. Display All Records\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            // Handle non-integer input to prevent infinite loops
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: 
                printf("Exiting program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// --- Helper to clear newline characters from buffer ---
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- 2. Feature: Add Student ---
void addStudent() {
    Student s;
    FILE *fp = fopen(FILENAME, "ab"); // "ab" = Append Binary
    
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n-- Add New Student --\n");
    printf("Enter ID: ");
    scanf("%d", &s.id);
    clearInputBuffer(); // Clear buffer before reading string

    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0; // Remove newline char

    printf("Enter Course: ");
    fgets(s.course, sizeof(s.course), stdin);
    s.course[strcspn(s.course, "\n")] = 0;

    printf("Enter GPA: ");
    scanf("%f", &s.gpa);

    // Write the struct to file
    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("Student added successfully!\n");
}

// --- 3. Feature: Display Records ---
void displayStudents() {
    Student s;
    FILE *fp = fopen(FILENAME, "rb"); // "rb" = Read Binary

    if (fp == NULL) {
        printf("\nNo records found (File does not exist yet).\n");
        return;
    }

    printf("\n%-10s %-25s %-15s %-10s\n", "ID", "Name", "Course", "GPA");
    printf("------------------------------------------------------------\n");

    // Read file one struct at a time
    while (fread(&s, sizeof(Student), 1, fp)) {
        printf("%-10d %-25s %-15s %-10.2f\n", s.id, s.name, s.course, s.gpa);
    }
    fclose(fp);
}

// --- 4. Feature: Search ---
void searchStudent() {
    int searchID, found = 0;
    Student s;
    FILE *fp = fopen(FILENAME, "rb");

    if (fp == NULL) {
        printf("\nNo records to search.\n");
        return;
    }

    printf("\nEnter Student ID to search: ");
    scanf("%d", &searchID);

    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == searchID) {
            printf("\nStudent Found:\n");
            printf("ID: %d\nName: %s\nCourse: %s\nGPA: %.2f\n", s.id, s.name, s.course, s.gpa);
            found = 1;
            break;
        }
    }

    if (!found) printf("Student with ID %d not found.\n", searchID);
    fclose(fp);
}

// --- 5. Feature: Update ---
void updateStudent() {
    int updateID, found = 0;
    Student s;
    FILE *fp = fopen(FILENAME, "rb");
    FILE *tempFp = fopen("temp.dat", "wb"); // Temporary file

    if (fp == NULL || tempFp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nEnter Student ID to update: ");
    scanf("%d", &updateID);

    // Logic: Copy all records to temp, but modify the specific one
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == updateID) {
            found = 1;
            printf("Enter New Name: ");
            clearInputBuffer();
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = 0;

            printf("Enter New Course: ");
            fgets(s.course, sizeof(s.course), stdin);
            s.course[strcspn(s.course, "\n")] = 0;

            printf("Enter New GPA: ");
            scanf("%f", &s.gpa);
        }
        fwrite(&s, sizeof(Student), 1, tempFp);
    }

    fclose(fp);
    fclose(tempFp);

    if (found) {
        remove(FILENAME);          // Delete old file
        rename("temp.dat", FILENAME); // Rename temp to original
        printf("Record updated successfully.\n");
    } else {
        remove("temp.dat");
        printf("Student ID not found.\n");
    }
}

// --- 6. Feature: Delete ---
void deleteStudent() {
    int deleteID, found = 0;
    Student s;
    FILE *fp = fopen(FILENAME, "rb");
    FILE *tempFp = fopen("temp.dat", "wb");

    if (fp == NULL || tempFp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nEnter Student ID to delete: ");
    scanf("%d", &deleteID);

    // Logic: Copy all records to temp EXCEPT the one to delete
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == deleteID) {
            found = 1; // Do not write this record to temp file
        } else {
            fwrite(&s, sizeof(Student), 1, tempFp);
        }
    }

    fclose(fp);
    fclose(tempFp);

    if (found) {
        remove(FILENAME);
        rename("temp.dat", FILENAME);
        printf("Record deleted successfully.\n");
    } else {
        remove("temp.dat");
        printf("Student ID not found.\n");
    }
}