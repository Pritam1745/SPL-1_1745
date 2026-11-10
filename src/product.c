#include <stdio.h>
#include "../include/product.h"
#include "../include/utils.h"

struct Product inventory[100];
int product_count = 0;

int is_duplicate_id(int id) {
    for (int i = 0; i < product_count; i++) {
        if (inventory[i].id == id) {
            return 1;
        }
    }
    return 0;
}

void load_products_from_file() {
    FILE *fp = fopen("data/products.txt", "r");
    if (fp == NULL) {
        product_count = 0;
        return;
    }

    product_count = 0;
    while (fscanf(fp, "%d,%49[^,],%29[^,],%lf,%lf,%d,%d\n",
                  &inventory[product_count].id,
                  inventory[product_count].name,
                  inventory[product_count].category,
                  &inventory[product_count].purchase_cost,
                  &inventory[product_count].price,
                  &inventory[product_count].stock,
                  &inventory[product_count].min_stock) == 7) {
        product_count++;
    }
    fclose(fp);
}

void save_products_to_file() {
    FILE *fp = fopen("data/products.txt", "w");
    if (fp == NULL) {
        printf("Error: Unable to save product data to file!\n");
        return;
    }

    for (int i = 0; i < product_count; i++) {
        fprintf(fp, "%d,%s,%s,%.2f,%.2f,%d,%d\n",
                inventory[i].id,
                inventory[i].name,
                inventory[i].category,
                inventory[i].purchase_cost,
                inventory[i].price,
                inventory[i].stock,
                inventory[i].min_stock);
    }
    fclose(fp);
}

void add_product() {
    printf("\n--- Add New Product ---\n");
    
    struct Product new_product;
    char temp_buffer[30];
    
    printf("Enter Product ID: ");
    read_string(temp_buffer, sizeof(temp_buffer));
    
    int id = 0;
    for(int i = 0; temp_buffer[i] != '\0'; i++) {
        id = id * 10 + (temp_buffer[i] - '0');
    }

    if (is_duplicate_id(id)) {
        printf("Error: Product ID %d already exists! Please use a unique ID.\n", id);
        return;
    }
    new_product.id = id;

    printf("Enter Product Name: ");
    read_string(new_product.name, sizeof(new_product.name));

    printf("Enter Category: ");
    read_string(new_product.category, sizeof(new_product.category));

    printf("Enter Purchase Cost: ");
    read_string(temp_buffer, sizeof(temp_buffer));
    new_product.purchase_cost = string_to_double(temp_buffer);
    if (new_product.purchase_cost <= 0) {
        printf("Error: Purchase cost must be greater than zero!\n");
        return;
    }

    printf("Enter Selling Price: ");
    read_string(temp_buffer, sizeof(temp_buffer));
    new_product.price = string_to_double(temp_buffer);
    if (new_product.price <=0){
        printf("Error: Selling price must be greater than zero!\n");
        return;
    }

    printf("Enter Initial Stock Quantity: ");
    read_string(temp_buffer, sizeof(temp_buffer));
    int stock = 0;
    for(int i = 0; temp_buffer[i] != '\0'; i++){
         stock = stock * 10 + (temp_buffer[i] - '0');
    }
    if (stock < 0) {
        printf("Error: Stock quantity cannot be negative!\n");
        return;
    }
    new_product.stock = stock;

    printf("Enter Minimum Stock Threshold: ");
    read_string(temp_buffer, sizeof(temp_buffer));
    int min_s = 0;
    for(int i = 0; temp_buffer[i] != '\0'; i++){
        min_s = min_s * 10 + (temp_buffer[i] - '0');
    }
    if (min_s < 0) {
        printf("Error: Minimum stock threshold cannot be negative!\n");
        return;
    }
    new_product.min_stock = min_s;
    
    inventory[product_count] = new_product;
    product_count++;

    save_products_to_file();

    printf("Product added and saved to file successfully!\n");
}

void view_products() {
    printf("\n=============================================================================================\n");
    printf("%-8s | %-15s | %-12s | %-10s | %-10s | %-8s | %-12s\n", 
           "ID", "Name", "Category", "Cost", "Price", "Stock", "Status");
    printf("=============================================================================================\n");

    if (product_count == 0) {
        printf("No products available in inventory.\n");
        printf("=============================================================================================\n");
        return;
    }

    for (int i = 0; i < product_count; i++) {
        char *status = (inventory[i].stock <= inventory[i].min_stock) ? "[LOW STOCK]" : "OK";
        
        printf("%-8d | %-15s | %-12s | %-10.2f | %-10.2f | %-8d | %-12s\n", 
               inventory[i].id, 
               inventory[i].name, 
               inventory[i].category, 
               inventory[i].purchase_cost,
               inventory[i].price, 
               inventory[i].stock,
               status);
    }
    printf("=============================================================================================\n");
}

/*Searching for a product by its unique ID(linear search)*/

void search_product_by_id() {
    printf("\n--- Search Product by ID ---\n");
    if (product_count == 0) {
        printf("No products available to search.\n");
        return;
    }

    char temp_buffer[30];
    printf("Enter Product ID to search: ");
    read_string(temp_buffer, sizeof(temp_buffer));
    
    int search_id = 0;
    for(int i = 0; temp_buffer[i] != '\0'; i++) {
        search_id = search_id * 10 + (temp_buffer[i] - '0');
    }

    int found = 0;
    for (int i = 0; i < product_count; i++) {
        if (inventory[i].id == search_id) {
            char *status = (inventory[i].stock <= inventory[i].min_stock) ? "[LOW STOCK]" : "OK";
            
            printf("\nProduct Found Details:\n");
            printf("-----------------------------------\n");
            printf("ID           : %d\n", inventory[i].id);
            printf("Name         : %s\n", inventory[i].name);
            printf("Category     : %s\n", inventory[i].category);
            printf("Purchase Cost: %.2f\n", inventory[i].purchase_cost);
            printf("Selling Price: %.2f\n", inventory[i].price);
            printf("Stock Level  : %d\n", inventory[i].stock);
            printf("Min Threshold: %d\n", inventory[i].min_stock);
            printf("Status       : %s\n", status);
            printf("-----------------------------------\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Product with ID %d not found in inventory!\n", search_id);
    }
}

/* Searches for products by name (linear search) */

void search_product_by_name() {
    printf("\n--- Search Product by Name ---\n");
    if (product_count == 0) {
        printf("No products available to search.\n");
        return;
    }

    char search_name[50];
    printf("Enter Product Name to search: ");
    read_string(search_name, sizeof(search_name));

    int found = 0;
    for (int i = 0; i < product_count; i++) {
        
        if (my_strcmp(inventory[i].name, search_name) == 0) {
            char *status = (inventory[i].stock <= inventory[i].min_stock) ? "[LOW STOCK]" : "OK";
            
            printf("\nProduct Found Details:\n");
            printf("-----------------------------------\n");
            printf("ID           : %d\n", inventory[i].id);
            printf("Name         : %s\n", inventory[i].name);
            printf("Category     : %s\n", inventory[i].category);
            printf("Purchase Cost: %.2f\n", inventory[i].purchase_cost);
            printf("Selling Price: %.2f\n", inventory[i].price);
            printf("Stock Level  : %d\n", inventory[i].stock);
            printf("Min Threshold: %d\n", inventory[i].min_stock);
            printf("Status       : %s\n", status);
            printf("-----------------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("Product with name '%s' not found in inventory!\n", search_name);
    }
}