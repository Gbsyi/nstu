#include <iostream>
#include <vector>
#include <io.h>
#include <fcntl.h>

#include "Bag.h"
#include "Product.h"
#include "ProductState.h"

using namespace std;

// Добавление продукта в сумку
void add_product(Bag& bag) {
    const auto bag_weight = bag.get_current_weight();
    const auto max_bag_weight = bag.get_max_weight();

    // Получаем от пользователя необходимую информацию
    cout << "Enter product name: ";
    string product_name;
    cin >> product_name;

    cout << "Enter product weight: ";
    double product_weight;
    cin >> product_weight;

    cout << "Enter product temperature: ";
    double product_temperature;
    cin >> product_temperature;

    cout << "Enter product max temperature: ";
    double product_max_temperature;
    cin >> product_max_temperature;

    cout << "Enter product min temperature: ";
    double product_min_temperature;
    cin >> product_min_temperature;

    cout << "Enter product heat capacity: ";
    double product_heat_capacity;
    cin >> product_heat_capacity;
    
    Product new_product(product_name, product_weight,product_temperature, product_max_temperature, product_min_temperature, product_heat_capacity);

    const int potential_spoilage_count = bag.get_potential_spoilage_count(vector<Product> {new_product});
    // Если в сумке после добавления могут испортиться продукты - предупреждаем
    if (potential_spoilage_count > 0)
    {
        const int spoiled_products = bag.get_spoiled_product_count();
        cout << "There is " << spoiled_products << "products in the bag" << endl
            << "After adding there will be " << potential_spoilage_count << " spoiled products" << endl
            << "If you still want to add product enter y ";
        string answer;
        cin >> answer;
        // Если пользователь не согласился - выходим
        if (answer != "y")
        {
            return;
        }
    }

    // Пытаемся добавить продукт
    try
    {
        bag.add_product(new_product);
    }
    // Ловим исключение - пишем причину ошибки
    catch (overflow_error& err)
    {
        cout << err.what() << endl;
    }
}

// Вывод информации о сумке
void get_bag_info(const Bag& bag)
{
    // Вес сумки {Текущий}/{Максимальный}
    cout << "Bag weight: " << bag.get_current_weight() << "/" << bag.get_max_weight() << endl;

    // Если есть испорченные - выводим их количество
    const auto spoiled_products_count = bag.get_spoiled_product_count();
    if (spoiled_products_count > 0)
    {
        cout << "Spoiled products: " << spoiled_products_count << endl;
    }

    // Выводим подробный список продуктов
    const auto products = bag.get_products();
    const auto products_count = products.size();
    cout << "Products count: " << products_count << endl;
    if (products_count == 0)
    {
        cout << "Bag is empty" << endl;
    }
    else
    {
        cout << "Products: " << endl;
    }
    
    for (auto i = 0; i < products.size(); i++)
    {
        cout << i << " - " << products[i].to_string();
    }
    cout << endl << endl;
}

// Удаление продукта из сумки
void remove_product_from_bag(Bag& bag)
{
    const auto products = bag.get_products();

    cout << "Products:" << endl;

    // Выводим список с продуктами в корзине с индексом для выбора
    for (auto i = 0; i < products.size(); i++)
    {
        cout << i << " - " << products[i].get_name() << endl;
    }
    cout << "Enter product index to remove: ";
    int choice;
    cin >> choice;

    // Пробуем удалить продукт по введённому индексу
    try
    {
        bag.remove_product_by_index(choice);
    }
    // Если пользователь ввёл некорректный индекс - выводим сообщение об этом
    catch (range_error& err)
    {
        cout << err.what();
    }
}

int main()
{
    cout << "Enter max basket weight: ";

    double bag_weight;
    cin >> bag_weight;
    Bag bag(bag_weight);

    while (true) {
        cout << "Menu: " << endl
            << "1 - Get bag info" << endl
            << "2 - Add new product" << endl
            << "3 - Remove product" << endl
            << "0 - Exit" << endl;
        int choice;
        cin >> choice;
        
        cout << endl;
        switch (choice)
        {
        case 1: 
            get_bag_info(bag);
            break;
        case 2:
            add_product(bag);
            break;
        case 3:
            remove_product_from_bag(bag);
            break;
        case 0:
            return 0;
        default:
            break;
        }
    }
}
