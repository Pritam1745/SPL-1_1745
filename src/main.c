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
    printf("5. Account Security (Change Password)\n");
    printf("6. Logout/Exit\n");
    printf("========================================\n");
    printf("Enter choice (1-6): ");
}

void inventory_menu(int current_role) {
    int choice = 0;
    char input_buffer[10];
    while(1) {
        printf("\n--- Inventory Management ---\n");
        printf("1. Add Product (Admin Only)\n");
        printf("2. View All Products\n");
        printf("3. Search Product by ID\n");
        printf("4. Search Product by Name\n");
        printf("5. Edit Product (Admin Only)\n");
        printf("6. Delete Product (Admin Only)\n");
        printf("7. View Low Stock Alerts\n");
        printf("8. Back to Main Menu\n");
        printf("Enter choice (1-8): ");
        
        read_string(input_buffer, sizeof(input_buffer));
        choice = input_buffer[0] - '0';

        if(choice == 1) {
            //staff check for Add Product
            if (current_role == ROLE_ADMIN) {
                add_product();
            } else {
                printf("\n-> Access Denied! Only Admin can add new products.\n");
            }
        } else if(choice == 2) {
            view_products();
        } else if(choice == 3) {
            search_product_by_id();
        } else if(choice == 4) {
            search_product_by_name();
        } else if(choice == 5) {
            //staff check for Edit
            if (current_role == ROLE_ADMIN) {
                edit_product();
            } else {
                printf("\n-> Access Denied! Only Admin can edit products.\n");
            }
        } else if(choice == 6) {
            //staff check for Delete
            if (current_role == ROLE_ADMIN) {
                delete_product();
            } else {
                printf("\n-> Access Denied! Only Admin can delete products.\n");
            }
        } else if(choice == 7) {
            view_low_stock_products();
        } else if(choice == 8) {
            break;
        } else {
            printf("Invalid choice!\n");
        }
    }
}

int main() {
    load_products_from_file();
    load_users_from_file();

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
                inventory_menu(current_role);
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
                change_password(current_role);
                break;
            case 6:
                printf("\nLogging out... Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 6.\n");
        }
    }
    return 0;
}