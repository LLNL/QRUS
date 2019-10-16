
//#include <cmath>

#if !defined(OUTPUT_DATA)
#  define OUTPUT_DATA 1
#endif

#if OUTPUT_DATA
#  include <iostream>
#endif

int main() {

  double   s = 10.000;
//double   a = 30.000 * 3.1415926535897932384626433832795;
  double   m = 80000;
  double g_x =  0.;
  double g_y = -9.807;
  double  dt = 10.e-6;
  double   x = 0.0;
  double   y = 0.0;
  double v_x = 8.6; // s * std::cos(a);
  double v_y = 5.0; // s * std::sin(a);

  double k_1 = .3;
  double k_2 = .1;

  int N = 150000;
  for ( int t = 0; t < N; ++t ) {

    double a_x = g_x - k_1 * v_x + k_2 * (v_x > 0. ? -1. : 1.) * v_x * v_x; // std::pow(v_x,2);
    double a_y = g_y - k_1 * v_y + k_2 * (v_y > 0. ? -1. : 1.) * v_y * v_y; // std::pow(v_y,2);

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

