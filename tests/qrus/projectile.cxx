
// Test 2: Projectile trajectory, Qrus version

#if !defined(OUTPUT_DATA)
#  define OUTPUT_DATA 1
#endif

#if OUTPUT_DATA
#  include <iostream>
#endif

#if !defined(K1)
#  define K1 0.
#endif

#if !defined(K2)
#  define K2 0.
#endif

#if !defined(N)
#  define N 10000
#endif

#if !defined(USE_MATH_FUNCTIONS)
#  define USE_MATH_FUNCTIONS 1
#endif

// QRUS header section

#include <Qrus/qrus.hxx>
#include <Qrus/litterals.hxx>

#if !defined(OUTPUT_INFO)
#  define OUTPUT_INFO QRUS_HAS_IO
#endif

#if OUTPUT_INFO && !QRUS_HAS_IO
#  error "Cannot display type-info without enabling I/O in Qrus (-DQRUS_HAS_IO=1)."
#endif

#if USE_MATH_FUNCTIONS
#  include <Qrus/functions.hxx>
#endif

int main() {

  // initial speed and angle, mass, gravitational constant, time step, starting position and starting speed

  auto   s = 10.000_mps;
  auto   a = 30.000_deg;
  auto   m = 80.000_kg;
  auto g_x =  0.000_mps2;
  auto g_y = -9.807_mps2;
  auto  dt = 10._us;
  auto   x = 0.000_m;
  auto   y = 0.000_m;
#if USE_MATH_FUNCTIONS
  auto v_x = s * Qrus::cos(a);
  auto v_y = s * Qrus::sin(a);
#else
  auto v_x = s * .86__;
  auto v_y = s * .50__;
#endif

  Qrus::Quantity< double, Qrus::Unit< std::ratio< 0> , std::ratio< 0> , std::ratio<-1> , std::ratio< 0> >, std::ratio< 1> > k_1(K1);
  Qrus::Quantity< double, Qrus::Unit< std::ratio< 0> , std::ratio<-1> , std::ratio< 0> , std::ratio< 0> >, std::ratio< 1> > k_2(K2);

#if OUTPUT_INFO
  std::cout << "initialize:" << std::endl;
  std::cout << "    s = " << std::scientific << std::showpos <<   s.repr << " " << decltype(  s)::__scale() << " " << decltype(  s)::__unit() << std::endl;
  std::cout << "    a = " << std::scientific << std::showpos <<   a.repr << " " << decltype(  a)::__scale() << " " << decltype(  a)::__unit() << std::endl;
  std::cout << "    m = " << std::scientific << std::showpos <<   m.repr << " " << decltype(  m)::__scale() << " " << decltype(  m)::__unit() << std::endl;
  std::cout << "  g_x = " << std::scientific << std::showpos << g_x.repr << " " << decltype(g_x)::__scale() << " " << decltype(g_x)::__unit() << std::endl;
  std::cout << "  g_y = " << std::scientific << std::showpos << g_y.repr << " " << decltype(g_y)::__scale() << " " << decltype(g_y)::__unit() << std::endl;
  std::cout << "  k_1 = " << std::scientific << std::showpos << k_1.repr << " " << decltype(k_1)::__scale() << " " << decltype(k_1)::__unit() << std::endl;
  std::cout << "  k_2 = " << std::scientific << std::showpos << k_2.repr << " " << decltype(k_2)::__scale() << " " << decltype(k_2)::__unit() << std::endl;
  std::cout << "   dt = " << std::scientific << std::showpos <<  dt.repr << " " << decltype( dt)::__scale() << " " << decltype( dt)::__unit() << std::endl;
  std::cout << "    x = " << std::scientific << std::showpos <<   x.repr << " " << decltype(  x)::__scale() << " " << decltype(  x)::__unit() << std::endl;
  std::cout << "    y = " << std::scientific << std::showpos <<   y.repr << " " << decltype(  y)::__scale() << " " << decltype(  y)::__unit() << std::endl;
  std::cout << "  v_x = " << std::scientific << std::showpos << v_x.repr << " " << decltype(v_x)::__scale() << " " << decltype(v_x)::__unit() << std::endl;
  std::cout << "  v_y = " << std::scientific << std::showpos << v_y.repr << " " << decltype(v_y)::__scale() << " " << decltype(v_y)::__unit() << std::endl;
#endif

  for ( int t = 0; t < N; ++t ) {

#if OUTPUT_INFO
    std::cout << "t=" << t << ":" << std::endl;
    std::cout << "    x[" << t << "] = " << std::scientific << std::showpos <<   x.repr << " " << decltype(  x)::__scale() << " " << decltype(  x)::__unit() << std::endl;
    std::cout << "    y[" << t << "] = " << std::scientific << std::showpos <<   y.repr << " " << decltype(  y)::__scale() << " " << decltype(  y)::__unit() << std::endl;
    std::cout << "  v_x[" << t << "] = " << std::scientific << std::showpos << v_x.repr << " " << decltype(v_x)::__scale() << " " << decltype(v_x)::__unit() << std::endl;
    std::cout << "  v_y[" << t << "] = " << std::scientific << std::showpos << v_y.repr << " " << decltype(v_y)::__scale() << " " << decltype(v_y)::__unit() << std::endl;
#endif

#if USE_MATH_FUNCTIONS
    auto a_x = g_x - k_1 * v_x + k_2 * (v_x.repr > 0. ? -1.__ : 1.__) * Qrus::pow(v_x,std::ratio<2>());
    auto a_y = g_y - k_1 * v_y + k_2 * (v_y.repr > 0. ? -1.__ : 1.__) * Qrus::pow(v_y,std::ratio<2>());
#else
    auto a_x = g_x - k_1 * v_x + k_2 * (v_x.repr > 0. ? -1.__ : 1.__) * v_x * v_x;
    auto a_y = g_y - k_1 * v_y + k_2 * (v_y.repr > 0. ? -1.__ : 1.__) * v_y * v_y;
#endif

#if OUTPUT_INFO
    std::cout << "  a_x[" << t << "] = " << std::scientific << std::showpos << a_x.repr << " " << decltype(a_x)::__scale() << " " << decltype(a_x)::__unit() << std::endl;
    std::cout << "  a_y[" << t << "] = " << std::scientific << std::showpos << a_y.repr << " " << decltype(a_y)::__scale() << " " << decltype(a_y)::__unit() << std::endl;
#endif

    v_x = v_x + a_x * dt;
    v_y = v_y + a_y * dt;
    x = x + v_x * dt;
    y = y + v_y * dt;

#if OUTPUT_DATA
    std::cout << "DATA[" << t << "] " << std::scientific << std::showpos << x.repr << " " << y.repr << " " << v_x.repr << " " << v_y.repr << " " << std::endl;
#endif
    
  }

#if OUTPUT_INFO
  std::cout << "t=" << N << ":" << std::endl;
  std::cout << "    x[" << N << "] = " << std::scientific <<   x.repr << " " << decltype(  x)::__scale() << " " << decltype(  x)::__unit() << std::endl;
  std::cout << "    y[" << N << "] = " << std::scientific <<   y.repr << " " << decltype(  y)::__scale() << " " << decltype(  y)::__unit() << std::endl;
  std::cout << "  v_x[" << N << "] = " << std::scientific << v_x.repr << " " << decltype(v_x)::__scale() << " " << decltype(v_x)::__unit() << std::endl;
  std::cout << "  v_y[" << N << "] = " << std::scientific << v_y.repr << " " << decltype(v_y)::__scale() << " " << decltype(v_y)::__unit() << std::endl;
#endif

  return 0;
}

