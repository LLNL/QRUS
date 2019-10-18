
#ifndef __QRUS_IO_HPP__
# define __QRUS_IO_HPP__

#if !defined(__QRUS_HPP__)
#  error This file must not be included directly, instead include Qrus/qrus.hxx.
#endif

#if !QRUS_HAS_IO
#  error This file should only be included when compiled with -DQRUS_HAS_IO=1.
#endif

namespace Qrus {

  template <typename M_, typename L_, typename T_, typename A_>
  std::string Unit<M_,L_,T_,A_>::__typename() {
    std::ostringstream oss;
    oss << "Unit< M=" << M::num << "/" << M::den << ", L=" << L::num << "/" << L::den << ", T=" << T::num << "/" << T::den << ", A=" << A::num << "/" << A::den << " >";
    return oss.str();
  }

  template <typename R_, typename U_, typename S_>
  std::string Quantity<R_,U_,S_>::__typename() {
    std::ostringstream oss;
    oss << "Quantity< R=" << typeid(R).name() << ", U=" << U::__typename() << ", S=" << S::num << "/" << S::den << " > >";
    return oss.str();
  }

  template <typename R_, typename U_, typename S_>
  std::string Quantity<R_,U_,S_>::__unit() {
    std::ostringstream oss;
    if (U::M::num != 0) {
      oss << "g";
      if (U::M::num != U::M::den) {
        if (U::M::den == 1)
          oss << "^" << U::M::num;
        else
          oss << "^(" << U::M::num << "/" << U::M::den << ")";
      }
    }
    if (U::L::num != 0) {
      if (U::M::num != 0)
        oss << ".";
      oss << "m";
      if (U::L::num != U::L::den) {
        if (U::L::den == 1)
          oss << "^" << U::L::num;
        else
          oss << "^(" << U::L::num << "/" << U::L::den << ")";
      }
    }
    if (U::T::num != 0) {
      if (U::M::num != 0 || U::L::num != 0)
        oss << ".";
      oss << "s";
      if (U::T::num != U::T::den) {
        if (U::T::den == 1)
          oss << "^" << U::T::num;
        else
          oss << "^(" << U::T::num << "/" << U::T::den << ")";
      }
    }
    if (U::A::num != 0) {
      if (U::M::num != 0 || U::L::num != 0 || U::T::num != 0)
        oss << ".";
      oss << "r";
      if (U::A::num != U::A::den) {
        if (U::A::den == 1)
          oss << "^" << U::A::num;
        else
          oss << "^(" << U::A::num << "/" << U::A::den << ")";
      }
    }
    return oss.str();
  }

  template <typename R_, typename U_, typename S_>
  std::string Quantity<R_,U_,S_>::__scale() {
    if (S::den == S::num) return "     ";
    if (S::num / S::den == 1000000)    return " mega";
    if (S::num / S::den == 1000)       return " kilo";
    if (S::den / S::num == 1000)       return "milli";
    if (S::den / S::num == 1000000)    return "micro";
    if (S::den / S::num == 1000000000) return " nano";

    std::ostringstream oss;
    oss << S::num << "/" << S::den;
    return oss.str();
  }
}

#endif /* __QRUS_IO_HPP__ */

