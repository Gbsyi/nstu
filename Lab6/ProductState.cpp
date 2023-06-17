#include "ProductState.h"

ProductState::ProductState(std::string value) : value_(std::move(value))
{
}

ProductState::operator std::string() const
{
    return value_;
}

bool ProductState::operator!=(const ProductState& state) const
{
    return this->value_ != state.value_;
}

// Нормальное состояние продукта
ProductState ProductState::Normal = ProductState("Normal");
// Перемороженное состояние продукта
ProductState ProductState::Frozen = ProductState("Frozen");
// Перегретое состояние продукта
ProductState ProductState::Overheated = ProductState("Overheated");
