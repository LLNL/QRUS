
#ifndef __QRUS_HPP__
# define __QRUS_HPP__

#include <ratio>
#include <cmath>

#if !defined(QRUS_HAS_IO)
#  define QRUS_HAS_IO 1
#endif

#if QRUS_HAS_IO
#  include <sstream>
#  include <iostream>
#endif

namespace Qrus {

  using base_litt_t = long double;
  using qrus_litt_t = long double;

  // Qrus::Unit: uses 4 rationals (std::ratio) to represent any SI Unit (+ angles)

  template <typename M_, typename L_, typename T_, typename A_>
  struct Unit {
    using M = M_;
    using L = L_;
    using T = T_;
    using A = A_;

#if QRUS_HAS_IO
    static std::string __typename() {
      std::ostringstream oss;
      oss << "Unit< M=" << M::num << "/" << M::den << ", L=" << L::num << "/" << L::den << ", T=" << T::num << "/" << T::den << ", A=" << A::num << "/" << A::den << " >";
      return oss.str();
    }
#endif
  };

  namespace internal {

    template <typename R_lhs, typename R_rhs>
    struct ReprAssign {
      using R = R_lhs;
    };

    template <typename S_lhs, typename S_rhs>
    struct ScaleAssign {
      using S = S_lhs;
    };

    template <typename R_lhs, typename R_rhs>
    struct ReprAdd {
      using R = R_lhs;
    };

    template <typename S_lhs, typename S_rhs>
    struct ScaleAdd {
      using S = S_lhs;
    };

    template <typename R_lhs, typename R_rhs>
    struct ReprSub {
      using R = R_lhs;
    };

    template <typename S_lhs, typename S_rhs>
    struct ScaleSub {
      using S = S_lhs;
    };

    template <typename R_lhs, typename R_rhs>
    struct ReprMul {
      using R = R_lhs;
    };

    template <typename U_lhs, typename U_rhs>
    struct UnitMul {
      using U = Unit<
                  std::ratio_add<typename U_lhs::M, typename U_rhs::M>,
                  std::ratio_add<typename U_lhs::L, typename U_rhs::L>,
                  std::ratio_add<typename U_lhs::T, typename U_rhs::T>,
                  std::ratio_add<typename U_lhs::A, typename U_rhs::A>
                >;
    };

    template <typename S_lhs, typename S_rhs>
    struct ScaleMul {
      using S = std::ratio_multiply<S_lhs,S_rhs>;
    };

    template <typename R_lhs, typename R_rhs>
    struct ReprDiv {
      using R = R_lhs;
    };

    template <typename U_lhs, typename U_rhs>
    struct UnitDiv {
      using U = Unit<
                  std::ratio_subtract<typename U_lhs::M, typename U_rhs::M>,
                  std::ratio_subtract<typename U_lhs::L, typename U_rhs::L>,
                  std::ratio_subtract<typename U_lhs::T, typename U_rhs::T>,
                  std::ratio_subtract<typename U_lhs::A, typename U_rhs::A>
                >;
    };

    template <typename S_lhs, typename S_rhs>
    struct ScaleDiv {
      using S = std::ratio_divide<S_lhs,S_rhs>;
    };

    template <typename R_, typename P>
    struct PowRepr {
      using R = R_;
    };

    template <typename U_, typename P>
    struct PowUnit {
      using M = std::ratio_multiply<typename U_::M,P>;
      using L = std::ratio_multiply<typename U_::L,P>;
      using T = std::ratio_multiply<typename U_::T,P>;
      using A = std::ratio_multiply<typename U_::A,P>;

      using U = Unit<M,L,T,A>;
    };

    template <typename S_, typename P>
    struct PowScale {
      using S = std::ratio_multiply<S_,P>;
    };
  }

  // Qrus::Quantity: a floating point representation, a Qrus::Unit, and a scale (std::ratio)

  template <typename R_, typename U_, typename S_=std::ratio<1>>
  struct Quantity {

    using R = R_;
    using U = U_;
    using S = S_;
    using Q = Quantity<R,U,S>;

    R repr;

    constexpr Quantity(base_litt_t t) : repr(t) {};

    template <typename R_rhs, typename S_rhs>
    constexpr inline Q & operator = (const Quantity<R_rhs, U, S_rhs> & op) {
      repr = S::den * (R)( S_rhs::num * op.repr / S_rhs::den ) / S::num;
      return *this;
    }

#if QRUS_HAS_IO
    static std::string __typename() {
      std::ostringstream oss;
      oss << "Quantity< R=" << typeid(R).name() << ", U=" << U::__typename() << ", S=" << S::num << "/" << S::den << " > >";
      return oss.str();
    }

    static std::string __unit() {
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

    static std::string __scale() {
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
#endif
  };

  // Operators on Qrus::Quantity

  template <typename R_lhs, typename R_rhs, typename U, typename S_lhs, typename S_rhs>
  constexpr inline Quantity< typename internal::ReprAdd< R_lhs, R_rhs >::R, U, typename internal::ScaleAdd< S_lhs, S_rhs >::S > operator + (const Quantity<R_lhs, U, S_lhs> & lhs, const Quantity<R_rhs, U, S_rhs> & rhs) {
    using R = typename internal::ReprAdd< R_lhs, R_rhs >::R;
    using S = typename internal::ScaleAdd< S_lhs, S_rhs >::S;

    using Q = Quantity< R, U, S >;

    return Q(S::den * ( (R)( S_lhs::num * lhs.repr / S_lhs::den ) + (R)( S_rhs::num * rhs.repr / S_rhs::den ) ) / S::num);
  }

  template <typename R_lhs, typename R_rhs, typename U, typename S_lhs, typename S_rhs>
  constexpr inline Quantity< typename internal::ReprSub< R_lhs, R_rhs >::R, U, typename internal::ScaleSub< S_lhs, S_rhs >::S > operator - (const Quantity<R_lhs, U, S_lhs> & lhs, const Quantity<R_rhs, U, S_rhs> & rhs) {
    using R = typename internal::ReprSub< R_lhs, R_rhs >::R;
    using S = typename internal::ScaleSub< S_lhs, S_rhs >::S;

    using Q = Quantity< R, U, S >;

    return Q(S::den * ( (R)( S_lhs::num * lhs.repr / S_lhs::den ) - (R)( S_rhs::num * rhs.repr / S_rhs::den ) ) / S::num);
  }

  template <typename R_lhs, typename R_rhs, typename U_lhs, typename U_rhs, typename S_lhs, typename S_rhs>
  constexpr inline Quantity< typename internal::ReprMul< R_lhs, R_rhs >::R, typename internal::UnitMul< U_lhs, U_rhs>::U, typename internal::ScaleMul< S_lhs, S_rhs >::S > operator * (const Quantity<R_lhs, U_lhs, S_lhs> & lhs, const Quantity<R_rhs, U_rhs, S_rhs> & rhs) {
    using R = typename internal::ReprMul< R_lhs, R_rhs >::R;
    using U = typename internal::UnitMul< U_lhs, U_rhs>::U;
    using S = typename internal::ScaleMul< S_lhs, S_rhs >::S;

    using Q = Quantity< R, U, S >;

    return Q(S::den * ( (R)( S_lhs::num * lhs.repr / S_lhs::den ) * (R)( S_rhs::num * rhs.repr / S_rhs::den ) ) / S::num);
  }

  template <typename R_lhs, typename R_rhs, typename U_lhs, typename U_rhs, typename S_lhs, typename S_rhs>
  constexpr inline Quantity< typename internal::ReprDiv< R_lhs, R_rhs >::R, typename internal::UnitDiv< U_lhs, U_rhs>::U, typename internal::ScaleDiv< S_lhs, S_rhs >::S > operator / (const Quantity<R_lhs, U_lhs, S_lhs> & lhs, const Quantity<R_rhs, U_rhs, S_rhs> & rhs) {
    using R = typename internal::ReprDiv< R_lhs, R_rhs >::R;
    using U = typename internal::UnitDiv< U_lhs, U_rhs>::U;
    using S = typename internal::ScaleDiv< S_lhs, S_rhs >::S;

    using Q = Quantity< R, U, S >;

    return Q(S::den * ( (R)( S_lhs::num * lhs.repr / S_lhs::den ) / (R)( S_rhs::num * rhs.repr / S_rhs::den ) ) / S::num);
  }

  template <typename Q>
  constexpr inline Q operator - (const Q & op) {
    return Q(-op.repr);
  }

  // Special functions on Qrus::Quantity

  template <typename Q_, typename P>
  constexpr inline Quantity<
      typename internal::PowRepr <typename Q_::R,P>::R,
      typename internal::PowUnit <typename Q_::U,P>::U,
      typename internal::PowScale<typename Q_::S,P>::S
  > pow(Q_ const & op, P const & p) {
    using R = typename internal::PowRepr <typename Q_::R,P>::R;
    using U = typename internal::PowUnit <typename Q_::U,P>::U;
    using S = typename internal::PowScale<typename Q_::S,P>::S;
    using Q = Quantity<R,U,S>;

    return std::pow(op.repr,((R)P::num)/((R)P::den));
  }

  // Basic SI Units

  using None         = Unit< std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> >;
  using Mass         = Unit< std::ratio< 1>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> >;
  using Length       = Unit< std::ratio< 0>, std::ratio< 1>, std::ratio< 0>, std::ratio< 0> >;
  using Time         = Unit< std::ratio< 0>, std::ratio< 0>, std::ratio< 1>, std::ratio< 0> >;
  using Angle        = Unit< std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 1> >;
  using Speed        = Unit< std::ratio< 0>, std::ratio< 1>, std::ratio<-1>, std::ratio< 0> >;
  using Acceleration = Unit< std::ratio< 0>, std::ratio< 1>, std::ratio<-2>, std::ratio< 0> >;
  using Force        = Unit< std::ratio< 1>, std::ratio< 1>, std::ratio<-2>, std::ratio< 0> >;

  // Trigonometry functions

  template <typename R> Quantity<R, None> sin(Quantity<R, Angle> const & a) { return std::sin(a.repr); }
  template <typename R> Quantity<R, None> cos(Quantity<R, Angle> const & a) { return std::cos(a.repr); }
  template <typename R> Quantity<R, None> tan(Quantity<R, Angle> const & a) { return std::tan(a.repr); }

  // Literal operators

  constexpr Quantity<qrus_litt_t, None>               operator"" __   (base_litt_t x) { return Quantity<qrus_litt_t, None>(x); }
  constexpr Quantity<qrus_litt_t, Mass, std::kilo>    operator"" _kg  (base_litt_t x) { return Quantity<qrus_litt_t, Mass, std::kilo>(x); }
  constexpr Quantity<qrus_litt_t, Mass>               operator"" _g   (base_litt_t x) { return Quantity<qrus_litt_t, Mass>(x); }
  constexpr Quantity<qrus_litt_t, Mass, std::milli>   operator"" _mg  (base_litt_t x) { return Quantity<qrus_litt_t, Mass, std::milli>(x); }
  constexpr Quantity<qrus_litt_t, Length, std::kilo>  operator"" _km  (base_litt_t x) { return Quantity<qrus_litt_t, Length, std::kilo>(x); }
  constexpr Quantity<qrus_litt_t, Length>             operator"" _m   (base_litt_t x) { return Quantity<qrus_litt_t, Length>(x); }
  constexpr Quantity<qrus_litt_t, Length, std::milli> operator"" _mm  (base_litt_t x) { return Quantity<qrus_litt_t, Length, std::milli>(x); }
  constexpr Quantity<qrus_litt_t, Time>               operator"" _s   (base_litt_t x) { return Quantity<qrus_litt_t, Time>(x); }
  constexpr Quantity<qrus_litt_t, Time, std::milli>   operator"" _ms  (base_litt_t x) { return Quantity<qrus_litt_t, Time, std::milli>(x); }
  constexpr Quantity<qrus_litt_t, Time, std::micro>   operator"" _us  (base_litt_t x) { return Quantity<qrus_litt_t, Time, std::micro>(x); }
  constexpr Quantity<qrus_litt_t, Time, std::nano>    operator"" _ns  (base_litt_t x) { return Quantity<qrus_litt_t, Time, std::nano>(x); }
  constexpr Quantity<qrus_litt_t, Angle>              operator"" _rad (base_litt_t x) { return Quantity<qrus_litt_t, Angle>(x); }
  constexpr Quantity<qrus_litt_t, Angle>              operator"" _deg (base_litt_t x) { return Quantity<qrus_litt_t, Angle>(3.1415926535897932384626433832795 * x / 180.0); }
  constexpr Quantity<qrus_litt_t, Speed>              operator"" _mps (base_litt_t x) { return Quantity<qrus_litt_t, Speed>(x); }
  constexpr Quantity<qrus_litt_t, Acceleration>       operator"" _mps2(base_litt_t x) { return Quantity<qrus_litt_t, Acceleration>(x); }
  constexpr Quantity<qrus_litt_t, Force>              operator"" _N   (base_litt_t x) { return Quantity<qrus_litt_t, Force>(x); }

} // namespace Qrus

// Export literal operators into global scope

using Qrus::operator"" __;

using Qrus::operator"" _kg;
using Qrus::operator"" _g;
using Qrus::operator"" _mg;

using Qrus::operator"" _km;
using Qrus::operator"" _m;
using Qrus::operator"" _mm;

using Qrus::operator"" _s;
using Qrus::operator"" _ms;
using Qrus::operator"" _us;
using Qrus::operator"" _ns;

using Qrus::operator"" _rad;
using Qrus::operator"" _deg;

using Qrus::operator"" _mps;
using Qrus::operator"" _mps2;
using Qrus::operator"" _N;

#endif /* __QRUS_HPP__ */

