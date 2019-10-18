
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

#if !defined(USE_STD_CMATH)
#  define USE_STD_CMATH 1
#endif

#if USE_STD_CMATH
#  include <cmath>
#endif

using real_t = double;

int main() {

  real_t   s = 10.000;
  real_t   a = 30.000 * 3.1415926535897932384626433832795;
  real_t   m = 80000;
  real_t g_x =  0.;
  real_t g_y = -9.807;
  real_t  dt = 10.e-6;
  real_t   x = 0.0;
  real_t   y = 0.0;
#if USE_STD_CMATH
  real_t v_x = s * std::cos(a);
  real_t v_y = s * std::sin(a);
#else
  real_t v_x = 8.6;
  real_t v_y = 5.0;
#endif

  real_t k_1 = .3;
  real_t k_2 = .1;

  int N = 150000;
  for ( int t = 0; t < N; ++t ) {

#if USE_STD_CMATH
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

