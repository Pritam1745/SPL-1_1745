#ifndef AUTH_H
#define AUTH_H

#define ROLE_ADMIN 1
#define ROLE_STAFF 2

struct User {
    char username[20];
    char password[20];
    int role;
};

int login_system();
void change_password(int role);
void load_users_from_file();
void save_users_to_file();

#endif