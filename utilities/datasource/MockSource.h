#pragma once
#include <iostream>

class MockSource : public DataSource<MockSource>
{
public:
    bool openImpl()
    {
        std::cout << "Mock open\n";
        return true;
    }

    bool readImpl(std::vector<uint8_t>& buffer)
    {
        buffer = {42, 42, 42};
        std::cout << "Mock read\n";
        return true;
    }

    void closeImpl()
    {
        std::cout << "Mock close\n";
    }
};