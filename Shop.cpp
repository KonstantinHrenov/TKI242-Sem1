#include "Shop.h"

Shop::Shop(std::string name, std::string address)
    : name_(std::move(name)),
    address_(std::move(address)) {
}

const std::string& Shop::GetName() const { return name_; }
const std::string& Shop::GetAddress() const { return address_; }

std::string Shop::GetInfo() const {
    return "Магазин: " + name_ + " | адрес: " + address_;
}