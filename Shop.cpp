#include "Shop.h"

Shop::Shop(const std::string& name, const std::string& address)
    : name_(name), address_(address) {}

const std::string& Shop::GetName() const noexcept { return name_; }
const std::string& Shop::GetAddress() const noexcept { return address_; }
