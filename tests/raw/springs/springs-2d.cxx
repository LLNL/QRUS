
#ifndef USE_IOSTREAM
#  define USE_IOSTREAM 1
#endif

#if USE_IOSTREAM
#  include <iostream>
#endif

#include <cmath>

typedef float    Real;
typedef unsigned Index;
typedef int      Int;

template <typename ProblemT>
struct System {
  static constexpr Index N  { ProblemT::nx * ProblemT::ny };
  static constexpr Index Nb { (ProblemT::nx + 2) * (ProblemT::ny + 2) };
  Real time;
  Real length;

  Real px [Nb];
  Real py [Nb];
  Real vx [N];
  Real vy [N];
  Real fx [N];
  Real fy [N];

  System() : time(0.) {
    for (Index i = 0; i < ProblemT::nx + 2; ++i)
      for (Index j = 0; j < ProblemT::ny + 2; ++j) {
        px[i * (ProblemT::ny + 2) + j] = i * ProblemT::lx;
        py[i * (ProblemT::ny + 2) + j] = j * ProblemT::ly;
      }

    for (Index i = 0; i < ProblemT::nx; ++i)
      for (Index j = 0; j < ProblemT::ny; ++j) {
        vx[i * ProblemT::ny + j] = 0.;
        vy[i * ProblemT::ny + j] = 0.;
      }
        
    compute_forces();
  }

  void compute_force_single(
    Index i, Index j,
    Index i_, Index j_,
    Real k, Real d
  ) {
    Index p_idx = (i+1) * (ProblemT::ny + 2) + (j+1);
    Index __idx = i * ProblemT::ny + j;
    
    Index p_idx_ = (i+1+i_) * (ProblemT::ny + 2) + (j+1+j_);
    Index __idx_ = (i+i_) * ProblemT::ny + (j+j_);

    Real dx = px[p_idx_] - px[p_idx];
    Real dy = py[p_idx_] - py[p_idx];
    Real norm = sqrt(dx*dx+dy*dy);
    Real coef = k * ( 1. - d/norm );

    fx[__idx] += coef * dx;
    fy[__idx] += coef * dy;
  }

  void compute_forces() {
    for (Index i = 0; i < ProblemT::nx; ++i)
      for (Index j = 0; j < ProblemT::ny; ++j) {
        Index idx = i * ProblemT::ny + j;
        fx[idx] = 0.; fy[idx] = 0.;
        compute_force_single(i, j,  1,  0, ProblemT::kx, ProblemT::lx);
        compute_force_single(i, j, -1,  0, ProblemT::kx, ProblemT::lx);
        compute_force_single(i, j,  0,  1, ProblemT::ky, ProblemT::ly);
        compute_force_single(i, j,  0, -1, ProblemT::ky, ProblemT::ly);
      }
  }

  void apply_forces(Real const & dt) {
    for (Index i = 0; i < ProblemT::nx; ++i)
      for (Index j = 0; j < ProblemT::ny; ++j) {
        Index p_idx = (i+1) * (ProblemT::ny + 2) + (j+1);
        Index __idx = i * ProblemT::ny + j;

        vx[__idx] = vx[__idx] + fx[__idx] / ProblemT::mass * dt;
        vy[__idx] = vy[__idx] + fy[__idx] / ProblemT::mass * dt;
        px[p_idx] = px[p_idx] + vx[__idx] * dt;
        py[p_idx] = py[p_idx] + vy[__idx] * dt;
    }
  }

  Real step(Real const & dt) {
    compute_forces();
    apply_forces(dt);
    time += dt;
    return time;
  }

  void State2CSV() {
#if USE_IOSTREAM
    std::cout << time << ",";
    for (Index i = 0; i < ProblemT::nx; ++i)
      for (Index j = 0; j < ProblemT::ny; ++j) {
        Index p_idx = (i+1) * (ProblemT::ny + 2) + (j+1);
        Index __idx = i * ProblemT::ny + j;
        std::cout << px[p_idx] << "," << vx[__idx] << "," << fx[__idx] << "," << py[p_idx] << "," << vy[__idx] << "," << fy[__idx] << ",";
      }
    std::cout << std::endl;
#endif
  }
};

struct problem_0 {
  static constexpr Index nx { 3 };
  static constexpr Index ny { 3 };

  static constexpr Real mass{ 1. };

  static constexpr Real lx { 1. };
  static constexpr Real ly { 1. };

  static constexpr Real kx { 1. };
  static constexpr Real ky { 1. };
};

int main(int argc, char *argv[]) {
  System<problem_0> system;

  system.vx[2] = .5;

  Real dt = .01;
  Real stop = 100.;

  system.State2CSV();
  while (system.step(dt) < stop) {
    system.State2CSV();
  }

  return 0;
}

