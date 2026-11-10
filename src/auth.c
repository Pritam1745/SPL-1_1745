#include <stdio.h>
#include "../include/auth.h"
#include "../include/utils.h"

struct User users[2] = {
    {"admin", "admin123", ROLE_ADMIN},
    {"staff", "staff123", ROLE_STAFF}
};

// Save updated user passwords to text file
void save_users_to_file() {
    FILE *fp = fopen("data/users.txt", "w");
    if (fp == NULL) {
        return;
    }
    for (int i = 0; i < 2; i++) {
        fprintf(fp, "%s,%s,%d\n", users[i].username, users[i].password, users[i].role);
    }
    fclose(fp);
}

void load_users_from_file() {
    FILE *fp = fopen("data/users.txt", "r");
    if (fp == NULL) {
        // First run:Create default file if not existing
        save_users_to_file();
        return;
    }

    int i = 0;
    while (i < 2 && fscanf(fp, "%19[^,],%19[^,],%d\n", 
                          users[i].username, 
                          users[i].password, 
                          &users[i].role) == 3) {
        i++;
    }
    fclose(fp);
}

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

void change_password(int role) {
    char old_pass[20];
    char new_pass[20];
    char confirm_pass[20];

    printf("\n--- Account Security: Change Password ---\n");

    int user_index = -1;
    for (int i = 0; i < 2; i++) {
        if (users[i].role == role) {
            user_index = i;
            break;
        }
    }

    if (user_index == -1) {
        printf("Error: Active user record not found!\n");
        return;
    }

    printf("Enter Current Password: ");
    read_string(old_pass, sizeof(old_pass));

    if (my_strcmp(old_pass, users[user_index].password) != 0) {
        printf("Error: Incorrect current password!\n");
        return;
    }

    printf("Enter New Password: ");
    read_string(new_pass, sizeof(new_pass));

    if (my_strlen(new_pass) < 4) {
        printf("Error: Password must be at least 4 characters long!\n");
        return;
    }

    printf("Confirm New Password: ");
    read_string(confirm_pass, sizeof(confirm_pass));

    if (my_strcmp(new_pass, confirm_pass) != 0) {
        printf("Error: New password and confirm password do not match!\n");
        return;
    }

    // Update memory array and write to file
    my_strcpy(users[user_index].password, new_pass);
    save_users_to_file();

    printf("Success: Password updated and saved to file for %s!\n", users[user_index].username);
}