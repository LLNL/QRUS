#include <units/format.h>
#include <units/isq/si/international/length.h>
#include <units/isq/si/international/speed.h> // IWYU pragma: keep
#include <units/isq/si/length.h>
#include <units/isq/si/speed.h> // IWYU pragma: keep
#include <units/isq/si/time.h>
#include <units/isq/si/mass.h>
#include <units/quantity_io.h>
#include <units/quantity.h>
#include <units/generic/angle.h>
#include <iostream>

#if !defined(OUTPUT_INFO)
#  define OUTPUT_INFO QRUS_HAS_IO
#endif

#if !defined(N)
#  define N 100
#endif

using namespace units;
using namespace units::isq;
using namespace units::isq::si::references;
using namespace units::angle_references;

int main()
{

  auto ss = 10.000 * (m / s); 
  auto zerospeed = 0.0 * (m / s);
  auto unitspeed = 1.0 * (m / s);
  auto a = (30.000 * 2 * std::numbers::pi / 360.0) * (rad); 
  auto mpsx = 0.000 * (m / s); 
  auto mpsy = 9.807 * (m / s); 
  //auto a = 30.000 * deg ;
  auto mkg = 80.000 * kg; 
  auto unitsec = 1.0 * s;
  auto g_x = mpsx /  unitsec;
  auto g_y = mpsy /  unitsec;
  auto dt = 10.000 * us; 
  auto x = 0.000 * m; 
  auto y = 0.000 * m; 
  auto unitdist = 1.0 * m; 

  auto v_x = ss * 0.86;
  auto v_y = ss * 0.5;

  auto k1 = 1 / unitsec;
  auto k2 = 1 / unitdist;

#if OUTPUT_INFO
  std::cout << "initialize:" << std::endl;
  std::cout << "    s = " << ss << std::endl;
  std::cout << "    a = " << a << std::endl;
  std::cout << "    m = " << mkg << std::endl;
  std::cout << "  g_x = " << g_x << std::endl;
  std::cout << "  g_y = " << g_y << std::endl;
  std::cout << "  k_1 = " << k1 << std::endl;
  std::cout << "  k_2 = " << k2 << std::endl;
  std::cout << "   dt = " << dt << std::endl;
  std::cout << "    x = " << x << std::endl;
  std::cout << "    y = " << y << std::endl;
  std::cout << "  v_x = " << v_x << std::endl;
  std::cout << "  v_y = " << v_y << std::endl;
#endif
  for ( int t = 0; t < N; ++t ) {

#if OUTPUT_INFO
    std::cout << "t=" << t << ":" << std::endl;
    std::cout << "    x[" << t << "] = " << x << std::endl;
    std::cout << "    y[" << t << "] = " << y << std::endl;
    std::cout << "  v_x[" << t << "] = " << v_x << std::endl;
    std::cout << "  v_y[" << t << "] = " << v_y << std::endl;
#endif
    auto a_x = g_x - (k1 * v_x) + k2 * (v_x > zerospeed ? -1 : 1) * v_x * v_x;
    auto a_y = g_y - (k1 * v_y) + k2 * (v_y > zerospeed ? -1 : 1) * v_y * v_y;
#if OUTPUT_INFO
    std::cout << "  a_x[" << t << "] = " << a_x << std::endl;
    std::cout << "  a_y[" << t << "] = " << a_y << std::endl;
#endif

    v_x = v_x + a_x * dt;
    v_y = v_y + a_y * dt;
    x = x + v_x * dt;
    y = y + v_y * dt;

#if OUTPUT_DATA
    std::cout << "DATA[" << t << "] " << x << " " << y << " " << v_x << " " << v_y << " " << std::endl;
    std::cout << quantity{x} << std::endl;
#endif
  }

  return 0;
}
