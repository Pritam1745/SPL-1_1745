#include <stdio.h>
#include "../include/product.h"
#include "../include/utils.h"

struct Product inventory[100];
int product_count = 0;

void add_product() {
    printf("\n--- Add New Product ---\n");
    
    struct Product new_product;
    char temp_buffer[20];
    
    printf("Enter Product ID: ");
    read_string(temp_buffer, sizeof(temp_buffer));
    
    int id = 0;
    for(int i = 0; temp_buffer[i] != '\0'; i++) {
        id = id * 10 + (temp_buffer[i] - '0');
    }
    new_product.id = id;

    printf("Enter Product Name: ");
    read_string(new_product.name, sizeof(new_product.name));

    printf("Enter Category: ");
    read_string(new_product.category, sizeof(new_product.category));

    new_product.price = 500.00; 
    new_product.stock = 50;

    inventory[product_count] = new_product;
    product_count++;

    printf("Product added successfully\n");
}

void view_products() {
    printf("\n--- Product List ---\n");
    if (product_count == 0) {
        printf("No products available in inventory.\n");
        return;
    }
    
    printf("ID\tName\t\tCategory\tCost\tPrice\tStock\tMin Stock\n");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < product_count; i++) {
        printf("%d\t%s\t\t%s\t\t%.2f\t%.2f\t%d\t%d\n", 
               inventory[i].id, 
               inventory[i].name, 
               inventory[i].category, 
               inventory[i].purchase_cost,
               inventory[i].price, 
               inventory[i].stock,
               inventory[i].min_stock);
    }
}