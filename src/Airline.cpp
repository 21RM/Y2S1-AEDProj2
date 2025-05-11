//
// Created by alexandre on 21-12-2023.
//

#include <iostream>
#include "Airline.h"

Airline::Airline(const std::string &code, const std::string &name, const std::string &callsign,
                 const std::string &country) {
    code_ = code;
    name_ = name;
    callsign_ = callsign;
    country_ = country;
    wcode_ = std::wstring(code_.begin(), code_.end());
    wname_ = std::wstring(name_.begin(), name_.end());
    wcallsign_ = std::wstring(callsign_.begin(), callsign_.end());
    wcountry_ = std::wstring(country_.begin(), country_.end());
}

const std::string &Airline::getCode() const {
    return code_;
}

const std::wstring &Airline::getWcode() const {
    return wcode_;
}
const std::wstring &Airline::getWname() const {
    return wname_;
}
const std::wstring &Airline::getWcallsign() const {
    return wcallsign_;
}
const std::wstring &Airline::getWcountry() const {
    return wcountry_;
}
bool Airline::operator==(const Airline &other) const{
    return other.getCode() == code_;
}

Airline::Airline() = default;
