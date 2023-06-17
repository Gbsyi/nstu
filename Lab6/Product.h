#pragma once
#include <vector>

#include "ProductState.h"

class Product
{
    std::string name_;
    double weight_;
    double temperature_;
    double max_temperature_;
    double min_temperature_;
    ProductState state_;
    double heat_capacity_;

public:
    Product(std::string product_name, double product_weight, double product_temperature,
            double product_max_temperature, double product_min_temperature, double product_heat_capacity);

    // Получение имени
    std::string get_name() const;

    // Получение веса
    double get_weight() const;

    // Получение температуры
    double get_temperature() const;

    // Получение максимально допустимой температуры
    double get_max_temperature() const;

    // Получение минимально допустимой температуры
    double get_min_temperature() const;

    // Получение текущего состояния продукта
    ProductState get_state() const;

    // Получение теплоёмкости
    double get_heat_capacity() const;

    // Передать продукту энергию
    void transfer_heat(double energy);

    // Получение итоговой температуры, после передачи энергии
    double get_final_temperature(double energy) const;

    // Формирование строки для вывода продукта
    std::string to_string() const;
};
