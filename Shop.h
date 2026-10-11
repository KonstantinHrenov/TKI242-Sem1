#pragma once
#include <string>

class Shop {
public:
    Shop(std::string name, std::string address);

    const std::string& GetName() const;
    const std::string& GetAddress() const;
    std::string GetInfo() const;

private:
    std::string name_;
    std::string address_;
};
