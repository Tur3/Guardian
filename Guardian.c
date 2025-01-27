#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Menu();     // Declaration of the menu function
void Calc();     // Function that calculates the ping on each IP 
void AddIP();    // Function to add an IP address
void LookIP();   // Function to display IP addresses 
void Removeip(); // Function to remove IP addresses 
void Clear();    // Function that clears the screen based on the operating system

int main() {

    int ch; // choice
    while (1) {
        clear();
        menu();  // Display the menu
        scanf("%d", &ch);  // Read the user's option

        switch (ch) {
            case 1: // calculate ping
                clear();
                calc();               
                break;
            case 2: // add IP
                clear();
                AddIP();
                break;
            case 3: // remove IP
                clear();
                removeip();
                break;
            case 4: // print IP from txt file
                clear();
                LookIP();
                break;
            case 5: // exit
                printf("Powered by T.\n");
                exit(0); 
            default:
                printf("Invalid option! Please try again.\n");
                clear();
                break;
        }
    }

    return 0;
}

// Function to clear the screen
void Clear() {
    #if defined(_WIN32) || defined(_WIN64)
        // Command for Windows
        system("cls");
    #elif defined(__linux__) || defined(__APPLE__) || defined(__unix__)
        // Linux/macOS/Unix
        system("clear");
    #else
        // error
        printf("Unable to clear the screen.\n");
    #endif
}

// Function that returns the menu
void Menu() {
    // printf("\033[48;5;0m\033[32m");  // black background and green text
    printf("\n");
    printf("**************************************************\n");  
    printf("*                                                *\n");
    printf("*                     GUARDIAN                   *\n");  
    printf("*                                                *\n");
    printf("**************************************************\n");
    printf("* 1. Calculate Ping on an IP address             *\n");
    printf("* 2. Add an IP address                           *\n");
    printf("* 3. Remove an IP address                        *\n");
    printf("* 4. Display saved IP addresses                  *\n");
    printf("* 5. Exit                                        *\n");
    printf("**************************************************\n");
    printf("Choose an option (1-5):                          \n"); 
}

// Function that calculates the ping on the list of addresses
void Calc(){
  FILE *file;
    char nome[100], ip[16];
    char command[200];

    // Open the ip.txt file in read mode
    file = fopen("ip.txt", "r");
    if (file == NULL) {
        printf("Error opening the file ip.txt\n");
        exit(1);
    }

    // Perform the ping on each IP address in the file
    while (fscanf(file, "%s %s", nome, ip) != EOF) {
        // Create the ping command based on the operating system
        #if defined(_WIN32) || defined(_WIN64)
            // Command for Windows
            snprintf(command, sizeof(command), "ping -n 1 %s", ip);
        #elif defined(__linux__) || defined(__APPLE__) || defined(__unix__)
            // Command for Linux/macOS/Unix
            snprintf(command, sizeof(command), "ping -c 1 %s", ip);
        #else
            printf("Unsupported operating system for ping.\n");
            fclose(file);
            return;
        #endif

        printf("Pinging %s - %s...\n", nome, ip);
        int result = system(command); // Execute the ping command

        if (result == 0) {
            printf("Ping successful for %s - %s\n", nome, ip);
        } else {
            printf("\033[31m Error pinging %s - %s\n \033[0m", nome, ip);
        }
    }

    fclose(file);
    printf("\n\nPress any key to return to the main menu\n");
    while(getchar() != '\n');
    getchar();
}

// Function to add an IP address to the file
void AddIP() {
    FILE *file;
    char nome[100];
    char ip[16];

    printf("Enter the name: ");
    scanf("%s", nome);
    printf("Enter the IP address: ");
    scanf("%s", ip);

    // Open the ip.txt file in append mode (to add without overwriting)
    file = fopen("ip.txt", "a");

    if (file == NULL) {
        printf("Error opening the file ip.txt\n");
        exit(1);
    }

    // Perform a check for the correct IP format
    fprintf(file, "%s %s\n", nome, ip);
    fclose(file);
}

// Function to display the IP addresses
void LookIP() {
    FILE *file;
    char nome[100], ip[16];

    // Open the ip.txt file in read mode
    file = fopen("ip.txt", "r");
    if (file == NULL) {
        printf("Error opening the file ip.txt\n");
        exit(1);
    }
    printf("IP Addresses:\n");
    for (int i = 0; fscanf(file, "%s %s", nome, ip) != EOF; i++) {
        // print name in blue and IP in yellow
        printf("\033[34m%s\033[0m ", nome );
        printf(" - \033[33m%s\033[0m\n", ip);  
    }
    

    while(getchar() != '\n');
    getchar();
    fclose(file);
}

// Function to remove IP
void Removeip() {
    FILE *file, *tempFile;
    char nome[100], ip[16];
    char nomeDaEliminare[100], ipDaEliminare[16];
    int count = 1, select;
    
    // Open the ip.txt file in read mode
    file = fopen("ip.txt", "r");
    if (file == NULL) {
        printf("Error opening the file ip.txt\n");
        exit(1);
    }

    // Create a temporary file to save the IPs that were not deleted
    // ideal solution for a large number of addresses
    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening the temporary file.\n");
        fclose(file);
        exit(1);
    }
    printf("IP Addresses:\n");
    while (fscanf(file, "%s %s", nome, ip) != EOF) {
        printf("\033[34m [%d] %s\033[0m ",count++ , nome );
        printf(" - \033[33m%s\033[0m\n", ip);  
    }

    // Ask the user which IP to delete
    printf("Enter the number of the IP address to delete: ");
    scanf("%d", &select);

    if (select < 1 || select >= count) {
        printf("Invalid number.\n");
        fclose(file);
        fclose(tempFile);
        return;
    }

    // Rewind the file to reread the IPs
    rewind(file);
    count = 1;

    // Copy all IPs except the selected one to the temporary file
    while (fscanf(file, "%s %s", nome, ip) != EOF) {
        if (count != select) {
            // Write the IPs that are not to be deleted into the temporary file
            fprintf(tempFile, "%s %s\n", nome, ip);
        }
        count++;
    }

    fclose(file);
    fclose(tempFile);

    // Remove the original file and rename the temporary file
    remove("ip.txt");
    rename("temp.txt", "ip.txt");

    printf("IP address removed successfully.\n");
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');  // Wait for the user to press Enter
    getchar();
}
