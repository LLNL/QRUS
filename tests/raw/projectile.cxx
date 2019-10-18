
// Test 2: Projectile trajectory

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

#if USE_MATH_FUNCTIONS
#  include <cmath>
#endif

#if !defined(OUTPUT_INFO)
#  define OUTPUT_INFO 1
#endif

#if OUTPUT_INFO
#  include <iostream>
#endif

using real_t = double;

int main() {

  real_t   s = 10.000;
  real_t   a = 3.1415926535897932384626433832795 * 30.00 / 180.0;
  real_t   m = 80000;
  real_t g_x =  0.;
  real_t g_y = -9.807;
  real_t  dt = 10.e-6;
  real_t   x = 0.0;
  real_t   y = 0.0;
#if USE_MATH_FUNCTIONS
  real_t v_x = s * std::cos(a);
  real_t v_y = s * std::sin(a);
#else
  real_t v_x = s * .86;
  real_t v_y = s * .50;
#endif

  real_t k_1 = K1;
  real_t k_2 = K2;

#if OUTPUT_INFO
  std::cout << "initialize:" << std::endl;
  std::cout << "    s = " << std::scientific << std::showpos <<   s << std::endl;
  std::cout << "    a = " << std::scientific << std::showpos <<   a << std::endl;
  std::cout << "    m = " << std::scientific << std::showpos <<   m << std::endl;
  std::cout << "  g_x = " << std::scientific << std::showpos << g_x << std::endl;
  std::cout << "  g_y = " << std::scientific << std::showpos << g_y << std::endl;
  std::cout << "  k_1 = " << std::scientific << std::showpos << k_1 << std::endl;
  std::cout << "  k_2 = " << std::scientific << std::showpos << k_2 << std::endl;
  std::cout << "   dt = " << std::scientific << std::showpos <<  dt << std::endl;
  std::cout << "    x = " << std::scientific << std::showpos <<   x << std::endl;
  std::cout << "    y = " << std::scientific << std::showpos <<   y << std::endl;
  std::cout << "  v_x = " << std::scientific << std::showpos << v_x << std::endl;
  std::cout << "  v_y = " << std::scientific << std::showpos << v_y << std::endl;
#endif

  for ( int t = 0; t < N; ++t ) {

#if USE_MATH_FUNCTIONS
    real_t a_x = g_x - k_1 * v_x + k_2 * (v_x > 0. ? -1. : 1.) * std::pow(v_x,2);
    real_t a_y = g_y - k_1 * v_y + k_2 * (v_y > 0. ? -1. : 1.) * std::pow(v_y,2);
#else
    real_t a_x = g_x - k_1 * v_x + k_2 * (v_x > 0. ? -1. : 1.) * v_x * v_x;
    real_t a_y = g_y - k_1 * v_y + k_2 * (v_y > 0. ? -1. : 1.) * v_y * v_y;
#endif

    v_x = v_x + a_x * dt;
    v_y = v_y + a_y * dt;
    x = x + v_x * dt;
    y = y + v_y * dt;

#if OUTPUT_DATA
    std::cout << "DATA[" << t << "] " << std::scientific << std::showpos << x << " " << y << " " << v_x << " " << v_y << " " << std::endl;
#endif
    
  }

  return 0;
}

