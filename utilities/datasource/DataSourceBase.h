#pragma once

#include <vector>
#include <cstdint>
#include <iostream>

template <typename Derived>
class DataSource
{
public:

    void read(std::vector<uint8_t>& buffer)
    {
        derived().readImpl(buffer);
    }

    bool configure()
    {
        return derived().configureImpl();
    }

private:
    Derived& derived() { return static_cast<Derived&>(*this); }
    const Derived& derived() const { return static_cast<const Derived&>(*this); }
};