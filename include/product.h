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

void save_products_to_file();
void load_products_from_file();
void search_product_by_id();
void search_product_by_name();

#endif