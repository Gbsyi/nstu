#include <iostream>
#include <string>

using namespace std;

const std::string PRODUCT_OVERHEATED = "Перегрет";
const std::string PRODUCT_FROZEN = "Переморожен";
const std::string PRODUCT_NORMAL = "Нормальное";

class Product
{
    int id_;
    std::string name_;
    double mass_;
    double temperature_;
    double max_temperature_;
    double min_temperature_;
    std::string state_;
    double heat_capacity_;

    void set_temperature(double temperature)
    {
        temperature_ = temperature;

        if (temperature_ >= max_temperature_)
        {
            state_ = PRODUCT_OVERHEATED;
        }
        else if (temperature_ <= min_temperature_)
        {
            state_ = PRODUCT_FROZEN;
        }
    }

public:
    Product(int id, std::string productName, double productMass, double productTemperature, double productMaxTemp,
            double productMinTemp, double productHeatCapacity)
        : id_(id), name_(std::move(productName)), mass_(productMass), temperature_(productTemperature),
          max_temperature_(productMaxTemp),
          min_temperature_(productMinTemp), heat_capacity_(productHeatCapacity)
    {
        state_ = PRODUCT_NORMAL;
    }

    int get_id() const
    {
        return id_;
    }

    std::string get_name() const
    {
        return name_;
    }

    double get_weight() const
    {
        return mass_;
    }

    double get_temperature() const
    {
        return temperature_;
    }

    double get_max_temperature() const
    {
        return max_temperature_;
    }

    double get_min_temperature() const
    {
        return min_temperature_;
    }

    std::string get_state() const
    {
        return state_;
    }

    double get_heat_capacity() const
    {
        return heat_capacity_;
    }

    void transfer_heat_energy(double heatEnergy)
    {
        const auto temperature = temperature_ + heatEnergy / heat_capacity_;
        set_temperature(temperature);
    }

    double get_final_temperature(double heatEnergy) const
    {
        return temperature_ + heatEnergy / heat_capacity_;
    }
};


int main()
{
    // Пример использования класса Product
    Product product(1, "Молоко", 1.5, 20.0, 30.0, 0.0, 1.0);

    cout << "Название продукта: " << product.get_name() << endl;
    cout << "Масса продукта: " << product.get_weight() << " кг" << endl;
    cout << "Текущая температура продукта: " << product.get_temperature() << " °C" << endl;
    cout << "Максимально допустимая температура: " << product.get_max_temperature() << " °C" << endl;
    cout << "Минимально допустимая температура: " << product.get_min_temperature() << " °C" << endl;
    cout << "Состояние продукта: " << product.get_state() << endl;
    cout << "Теплоемкость продукта: " << product.get_heat_capacity() << " Дж/°C" << endl;

    double heatEnergy = 500.0;
    product.transfer_heat_energy(heatEnergy);
    cout << "Новая температура продукта после передачи " << heatEnergy << " Дж: " << product.get_temperature() << " °C"
        << endl;

    double additionalHeatEnergy = 200.0;
    double finalTemperature = product.get_final_temperature(additionalHeatEnergy);
    cout << "Температура продукта при передаче дополнительной энергии " << additionalHeatEnergy << " Дж: " <<
        finalTemperature << " °C" << endl;

    return 0;
}
