#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 50
#define STR_LEN 100

// Function Prototypes
int addBook(int ids[], char names[][STR_LEN], char authors[][STR_LEN], char categories[][STR_LEN], float prices[], int available[], int count);
void displayBooks(int ids[], char names[][STR_LEN], char authors[][STR_LEN], char categories[][STR_LEN], float prices[], int available[], int count);
void searchById(int ids[], char names[][STR_LEN], char authors[][STR_LEN], char categories[][STR_LEN], float prices[], int available[], int count);
void searchByName(int ids[], char names[][STR_LEN], char authors[][STR_LEN], char categories[][STR_LEN], float prices[], int available[], int count);
void issueBook(int ids[], int available[], int count);
void returnBook(int ids[], int available[], int count);
void updateBook(int ids[], char names[][STR_LEN], char authors[][STR_LEN], char categories[][STR_LEN], float prices[], int count);
void displayAvailable(int ids[], char names[][STR_LEN], char authors[][STR_LEN], char categories[][STR_LEN], float prices[], int available[], int count);
void clearInputBuffer();

int main() {
    int ids[MAX_BOOKS];
    char names[MAX_BOOKS][STR_LEN];
    char authors[MAX_BOOKS][STR_LEN];
    char categories[MAX_BOOKS][STR_LEN];
    float prices[MAX_BOOKS];
    int available[MAX_BOOKS]; // 1 = available, 0 = issued

    int count = 0;
    int choice;

    do {
        // Section 10: Exact Sample Menu Layout
        printf("\n========== LIBRARY MANAGEMENT SYSTEM ==========\n");
        printf("1. Add New Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book by ID\n");
        printf("4. Search Book by Name\n");
        printf("5. Issue Book\n");
        printf("6. Return Book\n");
        printf("7. Update Book Details\n");
        printf("8. Count Total Books\n");
        printf("9. Display Available Books\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice! Please enter a number between 1 and 10.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                count = addBook(ids, names, authors, categories, prices, available, count);
                break;
            case 2:
                displayBooks(ids, names, authors, categories, prices, available, count);
                break;
            case 3:
                searchById(ids, names, authors, categories, prices, available, count);
                break;
            case 4:
                searchByName(ids, names, authors, categories, prices, available, count);
                break;
            case 5:
                issueBook(ids, available, count);
                break;
            case 6:
                returnBook(ids, available, count);
                break;
            case 7:
                updateBook(ids, names, authors, categories, prices, count);
                break;
            case 8:
                printf("Total Books Stored: %d\n", count);
                break;
            case 9:
                displayAvailable(ids, names, authors, categories, prices, available, count);
                break;
            case 10:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please select 1 to 10.\n");
        }
    } while (choice != 10);

    return 0;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Section 11: Matches exact Add Book interaction
int addBook(int ids[], char names[][STR_LEN], char authors[][STR_LEN], char categories[][STR_LEN], float prices[], int available[], int count) {
    if (count >= MAX_BOOKS) {
        printf("Capacity warning: Library is full (50 books max)!\n");
        return count;
    }

    int newId;
    printf("Enter Book ID: ");
    if (scanf("%d", &newId) != 1) {
        printf("Invalid Book ID!\n");
        clearInputBuffer();
        return count;
    }

    for (int i = 0; i < count; i++) {
        if (ids[i] == newId) {
            printf("Duplicate ID rejected! Book ID %d already exists.\n", newId);
            return count;
        }
    }

    ids[count] = newId;

    printf("Enter Book Name: ");
    scanf(" %99[^\n]", names[count]);

    printf("Enter Author Name: ");
    scanf(" %99[^\n]", authors[count]);

    printf("Enter Category: ");
    scanf(" %99[^\n]", categories[count]);

    printf("Enter Price: ");
    while (scanf("%f", &prices[count]) != 1 || prices[count] < 0) {
        printf("Invalid price! Enter a valid price: ");
        clearInputBuffer();
    }

    available[count] = 1;
    printf("Book added successfully!\n");

    return count + 1;
}

void displayBooks(int ids[], char names[][STR_LEN], char authors[][STR_LEN], char categories[][STR_LEN], float prices[], int available[], int count) {
    if (count == 0) {
        printf("No books stored in the library.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Author: %s | Category: %s | Price: %.2f | Status: %s\n",
               ids[i], names[i], authors[i], categories[i], prices[i],
               available[i] == 1 ? "Available" : "Issued");
    }
}

void searchById(int ids[], char names[][STR_LEN], char authors[][STR_LEN], char categories[][STR_LEN], float prices[], int available[], int count) {
    int targetId;
    printf("Enter Book ID to search: ");
    scanf("%d", &targetId);

    for (int i = 0; i < count; i++) {
        if (ids[i] == targetId) {
            printf("ID: %d | Name: %s | Author: %s | Category: %s | Price: %.2f | Status: %s\n",
                   ids[i], names[i], authors[i], categories[i], prices[i],
                   available[i] == 1 ? "Available" : "Issued");
            return;
        }
    }
    printf("Book not found!\n");
}

void searchByName(int ids[], char names[][STR_LEN], char authors[][STR_LEN], char categories[][STR_LEN], float prices[], int available[], int count) {
    char targetName[STR_LEN];
    printf("Enter Book Name to search: ");
    scanf(" %99[^\n]", targetName);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(names[i], targetName) == 0) {
            printf("ID: %d | Name: %s | Author: %s | Category: %s | Price: %.2f | Status: %s\n",
                   ids[i], names[i], authors[i], categories[i], prices[i],
                   available[i] == 1 ? "Available" : "Issued");
            found = 1;
        }
    }
    if (!found) {
        printf("Book not found!\n");
    }
}

// Section 11: Matches exact Issue Book interaction & uses static storage class
void issueBook(int ids[], int available[], int count) {
    static int totalIssued = 0; // Retains issue count between function calls
    int targetId;

    printf("Enter Book ID to issue: ");
    scanf("%d", &targetId);

    for (int i = 0; i < count; i++) {
        if (ids[i] == targetId) {
            if (available[i] == 1) {
                available[i] = 0;
                totalIssued++;
                printf("Book issued successfully!\n");
            } else {
                printf("Operation rejected: Book is already issued!\n");
            }
            return;
        }
    }
    printf("Book not found!\n");
}

void returnBook(int ids[], int available[], int count) {
    int targetId;
    printf("Enter Book ID to return: ");
    scanf("%d", &targetId);

    for (int i = 0; i < count; i++) {
        if (ids[i] == targetId) {
            if (available[i] == 0) {
                available[i] = 1;
                printf("Book returned successfully!\n");
            } else {
                printf("Operation rejected: Book is already available!\n");
            }
            return;
        }
    }
    printf("Book not found!\n");
}

void updateBook(int ids[], char names[][STR_LEN], char authors[][STR_LEN], char categories[][STR_LEN], float prices[], int count) {
    int targetId;
    printf("Enter Book ID to update: ");
    scanf("%d", &targetId);

    for (int i = 0; i < count; i++) {
        if (ids[i] == targetId) {
            printf("Enter New Book Name: ");
            scanf(" %99[^\n]", names[i]);

            printf("Enter New Author Name: ");
            scanf(" %99[^\n]", authors[i]);

            printf("Enter New Category: ");
            scanf(" %99[^\n]", categories[i]);

            printf("Enter New Price: ");
            while (scanf("%f", &prices[i]) != 1 || prices[i] < 0) {
                printf("Invalid price! Enter a valid price: ");
                clearInputBuffer();
            }

            printf("Book updated successfully!\n");
            return;
        }
    }
    printf("Book not found!\n");
}

void displayAvailable(int ids[], char names[][STR_LEN], char authors[][STR_LEN], char categories[][STR_LEN], float prices[], int available[], int count) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (available[i] == 1) {
            printf("ID: %d | Name: %s | Author: %s | Category: %s | Price: %.2f\n",
                   ids[i], names[i], authors[i], categories[i], prices[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("No available books!\n");
    }
}