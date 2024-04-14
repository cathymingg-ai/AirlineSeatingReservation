// Airline Seating Reservation System using C Program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROWS 5
#define SEATS_PER_ROW 4

// Structure to hold customer information for each seat
typedef struct {
    char seatID[3];
    int assignmentStatus;
    char firstName[7];
    char lastName[10];
} CustomerRec;

// Node structure for doubly linked list
typedef struct Node {
    CustomerRec data;
    struct Node* next;
    struct Node* prev;
} Node;

// Function prototypes
void displayMenu(CustomerRec *cr, int size);
void displayEmptySeats(CustomerRec *cr, int size);
void displayAssignedSeats(CustomerRec *cr, int size);
void displayAllSeats(CustomerRec *cr, int size);
void assignCustomer(CustomerRec *cr, int size);
void deleteAssignment(CustomerRec *cr, int size);
void freeMemory(Node* head);

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Array to hold customer records for each seat
    CustomerRec customers[ROWS * SEATS_PER_ROW];

    // Arrays for random first and last names
    char *firstNames[] = {"Emily", "Liam", "Sophia", "Noah", "Olivia", "Ethan", "Ava"};
    char *lastNames[] = {"Smith", "Patel", "Tremblay", "Singh", "Leblanc", "Chen"};

    // Populate customer information for each seat
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < SEATS_PER_ROW; j++) {
            int index = i * SEATS_PER_ROW + j;
            sprintf(customers[index].seatID, "%d%c", i+1, j == 0 ? 'A' : j == 1 ? 'D' : j == 2 ? 'G' : 'K');
            customers[index].assignmentStatus = rand() % 2;
            strcpy(customers[index].firstName, firstNames[rand() % 7]);
            strcpy(customers[index].lastName, lastNames[rand() % 6]);
        }
    }

    // Display the menu and interact with the system
    displayMenu(customers, ROWS * SEATS_PER_ROW);

    return 0;
}

// Function to display the menu and handle user input
void displayMenu(CustomerRec *cr, int size) {
    char choice;
    void (*displayFunction)(CustomerRec *cr, int size);

    do {
        // Display the menu options
        printf("\nMenu:\n");
        printf("a. Display empty seats\n");
        printf("b. Display assigned seats\n");
        printf("c. Display all seats\n");
        printf("d. Assign a customer to a seat\n");
        printf("e. Delete a seat assignment\n");
        printf("f. Quit\n");
        printf("Enter your choice (a-f): ");
        scanf(" %c", &choice);

        // Switch statement to handle user choice
        switch (choice) {
            case 'a':
                displayFunction = displayEmptySeats;
                break;
            case 'b':
                displayFunction = displayAssignedSeats;
                break;
            case 'c':
                displayFunction = displayAllSeats;
                break;
            case 'd':
                assignCustomer(cr, size);
                displayFunction = NULL;
                break;
            case 'e':
                deleteAssignment(cr, size);
                displayFunction = NULL;
                break;
            case 'f':
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                displayFunction = NULL;
        }

        // Call the appropriate display function based on user choice
        if (displayFunction) {
            displayFunction(cr, size);
        }
    } while (choice != 'f');
}

// Function to display empty seats
void displayEmptySeats(CustomerRec *cr, int size) {
    printf("Empty Seats:\n");
    for (int i = 0; i < size; i++) {
        if (cr[i].assignmentStatus == 0) {
            printf("Seat: %s\n", cr[i].seatID);
        }
    }
}

// Function to display assigned seats
void displayAssignedSeats(CustomerRec *cr, int size) {
    printf("Assigned Seats:\n");
    for (int i = 0; i < size; i++) {
        if (cr[i].assignmentStatus == 1) {
            printf("Seat: %s - Name: %s %s\n", cr[i].seatID, cr[i].firstName, cr[i].lastName);
        }
    }
}

// Function to display all seats
void displayAllSeats(CustomerRec *cr, int size) {
    printf("All Seats:\n");
    for (int i = 0; i < size; i++) {
        printf("Seat: %s - Assignment Status: %d\n", cr[i].seatID, cr[i].assignmentStatus);
    }
}

// Function to assign a customer to a seat
void assignCustomer(CustomerRec *cr, int size) {
    char seatID[3];
    printf("Enter the seat ID you want to assign a customer to: ");
    scanf("%s", seatID);
    for (int i = 0; i < size; i++) {
        if (strcmp(cr[i].seatID, seatID) == 0) {
            printf("Enter first name: ");
            scanf("%s", cr[i].firstName);
            printf("Enter last name: ");
            scanf("%s", cr[i].lastName);
            cr[i].assignmentStatus = 1;
            printf("Customer assigned to seat %s\n", seatID);
            return;
        }
    }
    printf("Invalid seat ID. Please try again.\n");
}

// Function to delete a seat assignment
void deleteAssignment(CustomerRec *cr, int size) {
    char seatID[3];
    printf("Enter the seat ID you want to delete the assignment for: ");
    scanf("%s", seatID);
    for (int i = 0; i < size; i++) {
        if (strcmp(cr[i].seatID, seatID) == 0) {
            cr[i].assignmentStatus = 0;
            strcpy(cr[i].firstName, "");
            strcpy(cr[i].lastName, "");
            printf("Assignment deleted for seat %s\n", seatID);
            return;
        }
    }
    printf("Invalid seat ID. Please try again.\n");
}

// Function to free up memory allocated for the linked list nodes
void freeMemory(Node* head) {
    Node* current = head;
    Node* temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
}