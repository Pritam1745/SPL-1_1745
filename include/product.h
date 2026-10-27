#ifndef PRODUCT_H
#define PRODUCT_H

struct Product {
    int id;
    char name[50];
    char category[30];
    double purchase_cost;
    double price;
    int stock;
    int min_stock;
};

void add_product();
void view_products();

#endif