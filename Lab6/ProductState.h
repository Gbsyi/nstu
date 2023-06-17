#pragma once
#include <string>

class ProductState
{
    std::string value_;

    explicit ProductState(std::string value);

public:
    operator std::string() const;

    bool operator!=(const ProductState& state) const;

    static ProductState Normal;
    static ProductState Frozen;
    static ProductState Overheated;
};
