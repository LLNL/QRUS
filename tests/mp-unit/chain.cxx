#include <units/format.h>
#include <units/isq/si/international/length.h>
#include <units/isq/si/international/speed.h> // IWYU pragma: keep
#include <units/isq/si/length.h>
#include <units/isq/si/speed.h> // IWYU pragma: keep
#include <units/isq/si/time.h>
#include <units/isq/si/mass.h>
#include <units/quantity_io.h>
#include <units/quantity.h>
#include <iostream>

#if !defined(OUTPUT_INFO)
#  define OUTPUT_INFO QRUS_HAS_IO
#endif

using namespace units::isq;
using namespace units;
using namespace units::isq::si::references;

int main()
{
  auto a = 10 * kg; 
#if OUTPUT_INFO
  std::cout << "a = 10.kg = " << a  << std::endl;
#endif
  auto b = 4.7 * km; 
#if OUTPUT_INFO
  std::cout << "b = 4.7 km = " << b  << std::endl;
#endif
  auto c = a * b; 
#if OUTPUT_INFO
  std::cout << "c = a * b = " << c  << std::endl;
#endif
  auto d = 12. * us;
#if OUTPUT_INFO
  std::cout << "d = 12. us = " << d  << std::endl;
#endif
  auto e = c * d; 
#if OUTPUT_INFO
  std::cout << "e = c * d = " << e  << std::endl;
#endif
}
