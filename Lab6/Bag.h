#pragma once
#include <vector>

#include "Product.h"

class Bag
{
    double max_weight_;
    std::vector<Product> products_;

public:
    Bag(double bag_max_weight);

    // Получение списка продуктов
    std::vector<Product> get_products() const;

    // Получение текущего веса сумки
    double get_current_weight() const;

    // Получение максимально допустимого веса сумки
    double get_max_weight() const;

    // Получение количества продуктов
    int get_product_count() const;

    // Получение количества уже испорченных продуктов
    int get_spoiled_product_count() const;

    // Получение количества потенциально испорченных продуктов после удаления
    int get_potential_spoilage_count(const std::vector<Product>& new_products) const;

    // Добавление продукта в сумку
    void add_product(Product& product);
    
    // Удаление продукта из сумки по индексу
    void remove_product_by_index(int index);
};
