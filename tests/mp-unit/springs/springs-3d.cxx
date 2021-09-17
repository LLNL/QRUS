#include <units/format.h>
#include <units/isq/si/international/length.h>
#include <units/isq/si/international/speed.h> // IWYU pragma: keep
#include <units/isq/si/length.h>
#include <units/isq/si/speed.h> // IWYU pragma: keep
#include <units/isq/si/time.h>
#include <units/isq/si/mass.h>
#include <units/isq/si/force.h>
#include <units/isq/si/electric_charge.h>
#include <units/isq/si/magnetic_induction.h>
#include <units/quantity_io.h>
#include <units/quantity.h>
#include <iostream>

#ifndef USE_IOSTREAM
#  define USE_IOSTREAM 1
#endif
#ifndef USE_CMATH
#  define USE_CMATH 1
#endif
#ifndef USE_ASM
#  define USE_ASM_ALTERNATIVES 0
#endif

#if USE_IOSTREAM
#  include <iostream>
#endif

#if USE_CMATH
#include <cmath>
#elif USE_ASM_ALTERNATIVES
double inline __declspec (naked) __fastcall sqrt(double n) {
	_asm fld qword ptr [esp+4]
	_asm fsqrt
	_asm ret 8
}
#else
double sqrt(const double fg) {
 double n = fg / 2.0;
 double lstX = 0.0; 
 while (n != lstX) { 
    lstX = n;
    n = (n + fg/n) / 2.0; 
  }
  return n;
}
#endif
using namespace units::isq;
using namespace units;
using namespace units::isq::si;
using namespace units::isq::si::references;
using namespace units::isq::si::magnetic_induction_references;

typedef double   Real;
typedef unsigned Index;

template <typename ProblemT>
struct System {
  quantity<si::dim_time, si::second, Real> time;                                                       ///< Current time

  quantity<si::dim_length, si::metre, Real> px [ProblemT::counts::mobiles + ProblemT::counts::anchors]; ///< Position along the X axis of the mobile nodes followed by the anchor nodes
  quantity<si::dim_length, si::metre, Real> py [ProblemT::counts::mobiles + ProblemT::counts::anchors]; ///< Position along the Y axis of the mobile nodes followed by the anchor nodes
  quantity<si::dim_length, si::metre, Real> pz [ProblemT::counts::mobiles + ProblemT::counts::anchors]; ///< Position along the Z axis of the mobile nodes followed by the anchor nodes

  quantity<si::dim_speed, si::metre_per_second, Real> vx [ProblemT::counts::mobiles];                             ///< Velocity along the X axis of the mobile nodes
  quantity<si::dim_speed, si::metre_per_second, Real> vy [ProblemT::counts::mobiles];                             ///< Velocity along the Y axis of the mobile nodes
  quantity<si::dim_speed, si::metre_per_second, Real> vz [ProblemT::counts::mobiles];                             ///< Velocity along the Z axis of the mobile nodes

  quantity<si::dim_force, si::newton, Real> fx [ProblemT::counts::mobiles + ProblemT::counts::anchors]; ///< Force exerted along the X axis on the mobile nodes then anchor nodes
  quantity<si::dim_force, si::newton, Real> fy [ProblemT::counts::mobiles + ProblemT::counts::anchors]; ///< Force exerted along the Y axis on the mobile nodes then anchor nodes
  quantity<si::dim_force, si::newton, Real> fz [ProblemT::counts::mobiles + ProblemT::counts::anchors]; ///< Force exerted along the Z axis on the mobile nodes then anchor nodes

  quantity<si::dim_mass, si::kilogram, Real> mass   [ProblemT::counts::mobiles];                         ///< Mass of the mobile nodes
  quantity<si::dim_electric_charge, si::coulomb, Real> charge [ProblemT::counts::mobiles];                         ///< Charge of the mobile nodes

  Index springs  [ProblemT::counts::springs * 2];                  ///< Springs between pairs of nodes
  quantity<si::dim_force, si::newton, Real>  tension  [ProblemT::counts::springs];                      ///< Tension coeficiant of the springs
  quantity<si::dim_force, si::newton, Real>  friction [ProblemT::counts::springs];                      ///< Friction coeficiant of the springs
  Real  length   [ProblemT::counts::springs];                      ///< Nominal length of the springs


  System() : time(0. * s) {
    ProblemT::initializers::anchors(px + ProblemT::counts::mobiles, py + ProblemT::counts::mobiles, pz + ProblemT::counts::mobiles);
    ProblemT::initializers::mobiles(px, py, pz, vx, vy, vz, mass, charge);
    ProblemT::initializers::springs(springs, tension, friction, length);
    compute_forces();
  }

  void compute_forces() {

    for (Index i = 0; i < ProblemT::counts::mobiles + ProblemT::counts::anchors; ++i) {
      auto const x = px[i];
      auto const y = py[i];
      auto const z = pz[i];

      // Compute effect of global force field (such as gravity)
      fx[i] = ProblemT::fields::force::x(time, x, y, z);
      fy[i] = ProblemT::fields::force::y(time, x, y, z);
      fz[i] = ProblemT::fields::force::z(time, x, y, z);

      // Electric and magnetic fields apply to mobile nodes only (anchor have no charge)
      if (i < ProblemT::counts::mobiles) {
        auto const C = charge[i];
        if (C != 0. * C) {
          auto const mx = ProblemT::fields::magnetic::x(time, x, y, z);
          auto const my = ProblemT::fields::magnetic::y(time, x, y, z);
          auto const mz = ProblemT::fields::magnetic::z(time, x, y, z);

          fx[i] += C * (my * vz[i] - mz * vy[i] + ProblemT::fields::electric::x(time, x, y, z));
          fy[i] += C * (mz * vx[i] - mx * vz[i] + ProblemT::fields::electric::y(time, x, y, z));
          fz[i] += C * (mx * vy[i] - my * vx[i] + ProblemT::fields::electric::z(time, x, y, z));
        }
      }
    }

    // Compute the forces generated by the springs

    for (Index i = 0; i < ProblemT::counts::springs; ++i) {
      Index const n0 = springs[2*i];
      Index const n1 = springs[2*i+1];

      // dp: delta-position
      Real const dpx = px[n0].number() - px[n1].number();
      Real const dpy = py[n0].number() - py[n1].number();
      Real const dpz = pz[n0].number() - pz[n1].number();

      // dv: delta-velocity
      Real const dvx = vx[n0].number() - vx[n1].number();
      Real const dvy = vy[n0].number() - vy[n1].number();
      Real const dvz = vz[n0].number() - vz[n1].number();

      Real const norm = sqrt(dpx*dpx+dpy*dpy+dpz*dpz);
      auto const dp_coef = tension[i]  * ( 1. - length[i] / norm );

      Real const dpdv_prod = dpx*dvx + dpy*dvy + dpz*dvz;
      Real const dpdv_prod_sqrt = dpdv_prod > 0 ? sqrt(dpdv_prod) : sqrt(-dpdv_prod);
      auto const dv_coef = friction[i] * (dpdv_prod_sqrt / norm);

      fx[n0] -= (dp_coef + dv_coef) * dpx; fx[n1] += (dp_coef + dv_coef) * dpx;
      fy[n0] -= (dp_coef + dv_coef) * dpy; fy[n1] += (dp_coef + dv_coef) * dpy;
      fz[n0] -= (dp_coef + dv_coef) * dpz; fz[n1] += (dp_coef + dv_coef) * dpz;
    }
  }

  void apply_forces(auto const & dt) {
    for (Index i = 0; i < ProblemT::counts::mobiles; i++) {
      vx[i] += fx[i] / mass[i] * dt;
      vy[i] += fy[i] / mass[i] * dt;
      vz[i] += fz[i] / mass[i] * dt;

      px[i] += vx[i] * dt;
      py[i] += vy[i] * dt;
      pz[i] += vz[i] * dt;
    }
  }

  auto step(auto const & dt) {
    compute_forces();
    apply_forces(dt);
    time += dt;
    return time;
  }

  void State2CSV() {
#if USE_IOSTREAM
    std::cout << time << ",";
    for (Index i = 0; i < ProblemT::counts::mobiles + ProblemT::counts::anchors; ++i) {
      std::cout << px[i] << "," << py[i] << "," << pz[i] << ",";
      std::cout << vx[i] << "," << vy[i] << "," << vz[i] << ",";
      std::cout << fx[i] << "," << fy[i] << "," << fz[i] << ",";
    }
    std::cout << std::endl;
#endif
  }
};

struct problem_0 {
  struct counts {
    static constexpr Index anchors { 1 };
    static constexpr Index mobiles { 4 };
    static constexpr Index springs { 8 };
  };

  struct initializers {
    static void anchors(
        auto * px, auto * py, auto * pz
    ) {
      px[0] = 0. * m; py[0] = 0. * m; pz[0] = 1. * m;
    }

    static void mobiles(
        auto * px, auto * py, auto * pz,
        auto * vx, auto * vy, auto * vz,
        auto * mass, auto * charge
    ) {
      px[0] =  1. * m; py[0] =  0. * m; pz[0] = 0. * m; vx[0] = 0. * (m/s); vy[0] = 0. * (m/s); vz[0] = 0. * (m/s); mass[0] = 1. * kg; charge[0] = 1. * C;
      px[1] =  0. * m; py[1] =  1. * m; pz[1] = 0. * m; vx[1] = 0. * (m/s); vy[1] = 0. * (m/s); vz[1] = 0. * (m/s); mass[1] = 1. * kg; charge[1] = 1. * C;
      px[2] = -1. * m; py[2] =  0. * m; pz[2] = 0. * m; vx[2] = 0. * (m/s); vy[2] = 0. * (m/s); vz[2] = 0. * (m/s); mass[2] = 1. * kg; charge[2] = 1. * C;
      px[3] =  0. * m; py[3] = -1. * m; pz[3] = 0. * m; vx[3] = 0. * (m/s); vy[3] = 0. * (m/s); vz[3] = 0. * (m/s); mass[3] = 1. * kg; charge[3] = 1. * C;      
    }

    static void springs(
        Index * springs,
        quantity<si::dim_force, si::newton, Real>  * tension,
        quantity<si::dim_force, si::newton, Real>  * friction,
        Real  * length 
    ) {
      springs[ 0] = 0; springs[ 1] = 1; tension[0] =   1. * N; friction[0] = 0. * N; length[0] = sqrt(2.);
      springs[ 2] = 1; springs[ 3] = 2; tension[1] =   1. * N; friction[1] = 0. * N; length[1] = sqrt(2.);
      springs[ 4] = 2; springs[ 5] = 3; tension[2] =   1. * N; friction[2] = 0. * N; length[2] = sqrt(2.);
      springs[ 6] = 3; springs[ 7] = 0; tension[3] =   1. * N; friction[3] = 0. * N; length[3] = sqrt(2.);

      springs[ 8] = 4; springs[ 9] = 0; tension[4] =   1. * N; friction[4] = 0. * N; length[4] = sqrt(2.);
      springs[10] = 4; springs[11] = 1; tension[5] =   1. * N; friction[5] = 0. * N; length[5] = sqrt(2.);
      springs[12] = 4; springs[13] = 2; tension[6] =   1. * N; friction[6] = 0. * N; length[6] = sqrt(2.);
      springs[14] = 4; springs[15] = 3; tension[7] =   1. * N; friction[7] = 0. * N; length[7] = sqrt(2.);
    }
  };

  struct fields {
    struct force {
      static auto x(auto t, auto x, auto y, auto z) { return 0. * N; }
      static auto y(auto t, auto x, auto y, auto z) { return 0. * N; }
      static auto z(auto t, auto x, auto y, auto z) { return -1. * N; }
    };
    struct electric {
      static auto x(auto t, auto x, auto y, auto z) { return 0. * (V/m); }
      static auto y(auto t, auto x, auto y, auto z) { return 0. * (V/m); }
      static auto z(auto t, auto x, auto y, auto z) { return 0. * (V/m); }
    };
    struct magnetic {
      static auto x(auto t, auto x, auto y, auto z) { return 0. * T; }
      static auto y(auto t, auto x, auto y, auto z) { return 0. * T; }
      static auto z(auto t, auto x, auto y, auto z) { return 1. * T; }
    };
  };
};

int main(int argc, char *argv[]) {
  auto tunit = 1. * s;
  auto dunit = 1. * m;
  auto vunit = 1. * (m / s);
  auto funit = 1. * N;
  auto munit = 1. * kg;
  auto cunit = 1. * C;

  System<problem_0> system;

  quantity<si::dim_time, si::second, Real> dt = .001 * s;
  quantity<si::dim_time, si::second, Real> stop = 100. * s;

  system.State2CSV();
  int cnt = 0;
  while (system.step(dt) < stop) {
    if (++cnt % 100 == 0)
      system.State2CSV();
  }

  return 0;
}

