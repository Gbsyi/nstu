#include <iostream>
#include <string>

using namespace std;

class Product
{
    string name;
    double mass;
    double temperature;
    double maxTemperature;
    double minTemperature;
    string state;
    double heatCapacity;

public:
    Product(string productName, double productMass, double productTemperature, double productMaxTemp,
            double productMinTemp, double productHeatCapacity)
        : name(std::move(productName)), mass(productMass), temperature(productTemperature),
          maxTemperature(productMaxTemp),
          minTemperature(productMinTemp), heatCapacity(productHeatCapacity)
    {
        state = "Нормальное";
    }

    string getName() const
    {
        return name;
    }

    double getMass() const
    {
        return mass;
    }

    double getTemperature() const
    {
        return temperature;
    }

    double getMaxTemperature() const
    {
        return maxTemperature;
    }

    double getMinTemperature() const
    {
        return minTemperature;
    }

    std::string getState() const
    {
        return state;
    }

    double getHeatCapacity() const
    {
        return heatCapacity;
    }

    void transferHeatEnergy(double heatEnergy)
    {
        temperature += heatEnergy / heatCapacity;

        if (temperature >= maxTemperature)
        {
            state = "Перегрет";
        }
        else if (temperature <= minTemperature)
        {
            state = "Переморожен";
        }
        else
        {
            state = "Нормальное";
        }
    }

    double getFinalTemperature(double heatEnergy) const
    {
        return temperature + heatEnergy / heatCapacity;
    }
};

int main()
{
    // Пример использования класса Product
    Product product("Молоко", 1.5, 20.0, 30.0, 0.0, 1.0);

    cout << "Название продукта: " << product.getName() << endl;
    cout << "Масса продукта: " << product.getMass() << " кг" << endl;
    cout << "Текущая температура продукта: " << product.getTemperature() << " °C" << endl;
    cout << "Максимально допустимая температура: " << product.getMaxTemperature() << " °C" << endl;
    cout << "Минимально допустимая температура: " << product.getMinTemperature() << " °C" << endl;
    cout << "Состояние продукта: " << product.getState() << endl;
    cout << "Теплоемкость продукта: " << product.getHeatCapacity() << " Дж/°C" << endl;

    double heatEnergy = 500.0;
    product.transferHeatEnergy(heatEnergy);
    cout << "Новая температура продукта после передачи " << heatEnergy << " Дж: " << product.getTemperature() << " °C"
        << endl;

    double additionalHeatEnergy = 200.0;
    double finalTemperature = product.getFinalTemperature(additionalHeatEnergy);
    cout << "Температура продукта при передаче дополнительной энергии " << additionalHeatEnergy << " Дж: " <<
        finalTemperature << " °C" << endl;

    return 0;
}
