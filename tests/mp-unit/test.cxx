#include <units/format.h>
#include <units/isq/si/international/length.h>
#include <units/isq/si/international/speed.h> // IWYU pragma: keep
#include <units/isq/si/length.h>
#include <units/isq/si/speed.h> // IWYU pragma: keep
#include <units/isq/si/time.h>
#include <units/quantity_io.h>
#include <units/quantity.h>
#include <iostream>

using namespace units::isq;
using namespace units;
using namespace units::isq::si::references;


template<typename U1, typename R1, typename U2, typename R2>
constexpr Speed auto si_avg_speed(si::length<U1, R1> d,
                                  si::time<U2, R2> t)
{
  return d / t;
}

constexpr Speed auto avg_speed(Length auto d, Time auto t)
{
  return d / t;
}

int main()
{
  using namespace units::isq::si::literals;
  using namespace units::isq::si::references;
  using namespace units::aliases::isq::si::international;

  constexpr auto distance = 240 * cm;
  constexpr auto duration = 2 * min;

quantity<si::dim_length, si::kilometre, double> d1(123.);
si::length<si::kilometre,int> d2(123);
auto d3 = 123. * km; 
d3 *= 10;

  constexpr Speed auto v1 = 110 * (km / h);
  constexpr Speed auto v2 = mi_per_h<>(70.);
  constexpr Speed auto v3 = avg_speed(220_q_km, 2_q_h);
  constexpr Speed auto v4 = avg_speed(si::length<si::international::mile>(140), si::time<si::hour>(2));
#if UNITS_DOWNCAST_MODE == 0
  constexpr Speed auto v5 = quantity_cast<si::speed<si::metre_per_second>>(v3);
  constexpr Speed auto v6 = quantity_cast<si::dim_speed, si::metre_per_second>(v4);
#else
  constexpr Speed auto v5 = quantity_cast<si::speed<si::metre_per_second>>(v3);
  constexpr Speed auto v6 = quantity_cast<si::metre_per_second>(v4);
#endif
  constexpr Speed auto v7 = quantity_cast<int>(v6);

  std::cout << d1 << '\n';                                  // 110 km/h
  std::cout << d2 << '\n';                                  // 110 km/h
  std::cout << d3 << '\n';                                  // 110 km/h
  std::cout << v1 << '\n';                                  // 110 km/h
  std::cout << v2 << '\n';                                  // 70 mi/h
  std::cout << v3 << '\n';                                  // 70 mi/h
  std::cout << distance * distance << '\n';                                  // 70 mi/h
  std::cout << avg_speed(distance, duration) << '\n'; 
  std::cout << si_avg_speed(distance, duration) * 2 << '\n'; 
/*
  std::cout << fmt::format("{}", v3) << '\n';               // 110 km/h
  std::cout << fmt::format("{:*^14}", v4) << '\n';          // ***70 mi/h****
  std::cout << fmt::format("{:%Q in %q}", v5) << '\n';      // 30.5556 in m/s
  std::cout << fmt::format("{0:%Q} in {0:%q}", v6) << '\n'; // 31.2928 in m/s
  std::cout << fmt::format("{:%Q}", v7) << '\n';            // 31
*/
}
