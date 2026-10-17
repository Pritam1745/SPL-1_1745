#include <stdio.h>
#include "../include/auth.h"
#include "../include/utils.h"

struct User {
    char username[20];
    char password[20];
    int role; 
};

struct User users[2] = {
    {"admin", "admin123", ROLE_ADMIN},
    {"staff", "staff123", ROLE_STAFF}
};

int login_system() {
    char input_user[20];
    char input_pass[20];

    printf("\n========================================\n");
    printf("          STOCKMATE LOGIN               \n");
    printf("========================================\n");
    
    printf("Username: ");
    read_string(input_user, sizeof(input_user));
    
    printf("Password: ");
    read_string(input_pass, sizeof(input_pass));

    for (int i = 0; i < 2; i++) {
        if (my_strcmp(input_user, users[i].username) == 0 &&
            my_strcmp(input_pass, users[i].password) == 0) {
            
            if (users[i].role == ROLE_ADMIN) {
                printf("\nLogin Successful! Welcome, Admin.\n");
                return ROLE_ADMIN;
            } else {
                printf("\nLogin Successful! Welcome, Staff.\n");
                return ROLE_STAFF;
            }
        }
    }

    printf("\nInvalid username or password!\n");
    return 0;
}