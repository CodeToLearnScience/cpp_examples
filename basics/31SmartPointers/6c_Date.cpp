#include "6aDate_impl.h"
#include "6b_Date.h"

// Implemented using RAII
Date::Date(int day, int month, int year) {
  pImpl = new Date_impl(day, month, year); // allocate in constructor
}

Date::~Date() { delete pImpl; }

void Date::set_day(int day) { pImpl->set_day(day); }
void Date::print() { pImpl->print(); }
