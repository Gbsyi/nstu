#include "Product.h"

Product::Product(std::string product_name, const double product_weight, const double product_temperature, const double product_max_temperature,
                 const double product_min_temperature, const double product_heat_capacity)
    : name_(std::move(product_name)),
      weight_(product_weight),
      temperature_(product_temperature),
      max_temperature_(product_max_temperature),
      min_temperature_(product_min_temperature),
      state_(ProductState::Normal),
      heat_capacity_(product_heat_capacity)
{
}

std::string Product::get_name() const
{
    return name_;
}

double Product::get_weight() const
{
    return weight_;
}

double Product::get_temperature() const
{
    return temperature_;
}

double Product::get_max_temperature() const
{
    return max_temperature_;
}

double Product::get_min_temperature() const
{
    return min_temperature_;
}

ProductState Product::get_state() const
{
    return state_;
}

double Product::get_heat_capacity() const
{
    return heat_capacity_;
}

void Product::transfer_heat(double energy)
{
    temperature_ += energy / heat_capacity_;
    
    // Если перегрели или переохладили - меняем состояние.
    // Обратно вернуть в нормальное уже невозможно
    if (temperature_ > max_temperature_)
    {
        state_ = ProductState::Overheated;
    }
    else if (temperature_ < min_temperature_)
    {
        state_ = ProductState::Frozen;
    }
}

double Product::get_final_temperature(double energy) const
{
    return temperature_ + energy / heat_capacity_;
}

std::string Product::to_string() const
{
    return name_ + ": \n"
        + "\tWeight: " + std::to_string(weight_) + "\n"
        + "\tTemperature: " + std::to_string(temperature_) + "\n"
        + "\tMax temperature: " + std::to_string(max_temperature_) + "\n"
        + "\tMin temperature: " + std::to_string(min_temperature_) + "\n"
        + "\tState: " + std::string(state_) + "\n"
        + "\tHeat capacity: " + std::to_string(heat_capacity_) + "\n";
    
}
