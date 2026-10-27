#include <stdio.h>
#include "../include/utils.h"
#include "../include/auth.h"
#include "../include/product.h"

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

void inventory_menu() {
    int choice = 0;
    char input_buffer[10];
    while(1) {
        printf("\n--- Inventory Management ---\n");
        printf("1. Add Product\n");
        printf("2. View Products\n");
        printf("3. Back to Main Menu\n");
        printf("Enter choice: ");
        
        read_string(input_buffer, sizeof(input_buffer));
        choice = input_buffer[0] - '0';

        if(choice == 1) {
            add_product();
        } else if(choice == 2) {
            view_products();
        } else if(choice == 3) {
            break;
        } else {
            printf("Invalid choice\n");
        }
    }
}

int main() {
    int current_role = 0;
    
    while (current_role == 0) {
        current_role = login_system();
        if (current_role == 0) {
            printf("Please try again.\n");
        }
    }

    int choice = 0;
    char input_buffer[10];

    while (1) {
        display_main_menu();
        
        read_string(input_buffer, sizeof(input_buffer));
        choice = input_buffer[0] - '0';

        switch (choice) {
            case 1:
                inventory_menu();
                break;
            case 2:
                if (current_role == ROLE_ADMIN) {
                    printf("\n-> Opening Purchase Management module...\n");
                } else {
                    printf("\n-> Access Denied! Only Admin can access Purchases.\n");
                }
                break;
            case 3:
                printf("\n-> Opening Sales & Billing module...\n");
                break;
            case 4:
                if (current_role == ROLE_ADMIN) {
                    printf("\n-> Opening Business Reports module...\n");
                } else {
                    printf("\n-> Access Denied! Only Admin can view Reports.\n");
                }
                break;
            case 5:
                printf("\nLogging out.... Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 5.\n");
        }
    }
    return 0;
}