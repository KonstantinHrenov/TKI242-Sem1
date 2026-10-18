#include "Shop.h"

Shop::Shop(const std::string name, const std::string address)
    : name_(name), address_(address) {
}

const std::string& Shop::GetName() const { return name_; }
const std::string& Shop::GetAddress() const { return address_; }

std::string Shop::GetInfo() const {
    return "Магазин: " + name_ + " | адрес: " + address_;
}
