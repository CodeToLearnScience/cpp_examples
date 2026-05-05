#include "6aDate_impl.h"
#include "6e_unique_ptr_Date.h"
#include <memory>

// Implemented using RAII
Date::Date(int day, int month, int year) {
  pImpl =
      std::make_unique<Date_impl>(day, month, year); // allocate in constructor
}

Date::~Date() = default;
Date::Date(Date &&) noexcept = default;
Date &Date::operator=(Date &&) noexcept = default;

void Date::set_day(int day) { pImpl->set_day(day); }

void Date::print() { pImpl->print(); }
