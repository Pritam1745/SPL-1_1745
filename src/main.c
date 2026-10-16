#include <stdio.h>
#include "../include/utils.h"

void display_main_menu() {
    printf("\n========================================\n");
    printf("       STOCKMATE INVENTORY SYSTEM       \n");
    printf("========================================\n");
    printf("1. Inventory Management\n");
    printf("2. Purchase Management\n");
    printf("3. Sales & Billing\n");
    printf("4. Business Reports\n");
    printf("5. Logout/Exit\n");
    printf("========================================\n");
    printf("Enter choice (1-5): ");
}

int main() {
    int choice = 0;
    char input_buffer[10];

    while (1) {
        display_main_menu();
        
        read_string(input_buffer, sizeof(input_buffer));
        
        choice = input_buffer[0] - '0';

        switch (choice) {
            case 1:
                printf("\n-> Opening Inventory Management module...\n");
                break;
            case 2:
                printf("\n-> Opening Purchase Management module...\n");
                break;
            case 3:
                printf("\n-> Opening Sales & Billing module...\n");
                break;
            case 4:
                printf("\n-> Opening Business Reports module...\n");
                break;
            case 5:
                printf("\nExiting StockMate. Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 5.\n");
        }
    }

    return 0;
}