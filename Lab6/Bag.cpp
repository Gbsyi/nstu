#include "Bag.h"
#include <iostream>

Bag::Bag(double bag_max_weight): max_weight_(bag_max_weight)
{
}

std::vector<Product> Bag::get_products() const
{
    return products_;
}

double Bag::get_current_weight() const
{
    double total_weight = 0.0;
    for (const auto& product : products_)
    {
        total_weight += product.get_weight();
    }
    return total_weight;
}

double Bag::get_max_weight() const
{
    return max_weight_;
}

int Bag::get_product_count() const
{
    return products_.size();
}

int Bag::get_spoiled_product_count() const
{
    int spoiled_count = 0;
    for (const auto& product : products_)
    {
        if (product.get_state() != ProductState::Normal)
        {
            spoiled_count++;
        }
    }
    return spoiled_count;
}

int Bag::get_potential_spoilage_count(const std::vector<Product>& new_products) const
{
    int potential_spoilage_count = 0;
    for (const auto& product : new_products)
    {
        const double total_weight = get_current_weight() + product.get_weight();

        // Изменение температуры всех продуктов в сумке
        double total_heat_capacity = 0.0;
        double total_energy = 0.0;
        for (const auto& existing_product : products_)
        {
            total_heat_capacity += existing_product.get_heat_capacity();
            total_energy += existing_product.get_temperature() * existing_product.get_heat_capacity();
        }

        total_heat_capacity += product.get_heat_capacity();
        total_energy += product.get_temperature() * product.get_heat_capacity();

        const double average_temperature = total_energy / total_heat_capacity;
        for (const auto& existing_product : products_)
        {
            const double final_temperature = existing_product.get_final_temperature(
                existing_product.get_heat_capacity() * (average_temperature - existing_product.get_temperature()));
            if (final_temperature > existing_product.get_max_temperature() || final_temperature < existing_product.
                get_min_temperature())
            {
                potential_spoilage_count++;
            }
        }

        const double final_temperature = product.get_final_temperature(
            product.get_heat_capacity() * (average_temperature - product.get_temperature()));
        if (final_temperature > product.get_max_temperature() || final_temperature < product.get_min_temperature())
        {
            potential_spoilage_count++;
        }

        if (total_weight > max_weight_)
        {
            potential_spoilage_count++;
        }
    }
    return potential_spoilage_count;
}

void Bag::add_product(Product& product)
{
    const double total_weight = get_current_weight() + product.get_weight();
    // Мы не можем допустить переполнения сумки. Поэтому выбрасываем исключение
    if (total_weight > max_weight_)
    {
        throw std::overflow_error("Product can't be added. Not enough bag capacity");
    }
    
    // Изменение температуры всех продуктов в сумке
    double total_heat_capacity = 0.0;
    double total_energy = 0.0;
    for (auto& existing_product : products_)
    {
        total_heat_capacity += existing_product.get_heat_capacity();
        total_energy += existing_product.get_temperature() * existing_product.get_heat_capacity();
    }

    total_heat_capacity += product.get_heat_capacity();
    total_energy += product.get_temperature() * product.get_heat_capacity();

    const double average_temperature = total_energy / total_heat_capacity;
    for (auto& existing_product : products_)
    {
        existing_product.transfer_heat(
            existing_product.get_heat_capacity() * (average_temperature - existing_product.get_temperature()));
    }

    product.transfer_heat(product.get_heat_capacity() * (average_temperature - product.get_temperature()));

    products_.push_back(product);
}

void Bag::remove_product_by_index(int index)
{
    // Если нам передают невалидный индекс - выбрасываем исключение. Продолжение удаления невозможно (Иначе удалим не то)
    if (index < 0 || index >= products_.size())
    {
        throw std::out_of_range("Unavailable index");
    }
    
    products_.erase(products_.begin() + index);
}
