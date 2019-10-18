
#ifndef __QRUS_OPERATORS_HPP__
# define __QRUS_OPERATORS_HPP__

#if !defined(__QRUS_HPP__)
#  error This file must not be included directly, instead include Qrus/qrus.hxx.
#endif

namespace Qrus {

  // Basic operators for Qrus::Quantity

  template <typename Q>
  constexpr inline Q operator + (const Q & op) {
    return Q(+op.repr);
  }

  template <typename Q>
  constexpr inline Q operator - (const Q & op) {
    return Q(-op.repr);
  }

  namespace promote {
    template <typename Q_lhs, typename Q_rhs>
    struct add;

    template <typename R_lhs, typename R_rhs, typename U, typename S_lhs, typename S_rhs>
    struct add< Quantity<R_lhs, U, S_lhs>, Quantity<R_rhs, U, S_rhs> > {
      using Q = Quantity<R_rhs, U, S_rhs>;
    };
  }

  template < typename Q_lhs, typename Q_rhs, typename Q=typename promote::add< Q_lhs, Q_rhs >::Q >
  constexpr inline Q operator + (Q_lhs const & lhs, Q_rhs const & rhs) {
//  return Q(Q::S::den * ( (typename Q::R)( Q_lhs::S::num * lhs.repr / Q_lhs::S::den ) + (typename Q::R)( Q_rhs::S::num * rhs.repr / Q_rhs::S::den ) ) / Q::S::num);

    const long double nl = Q::S::den * Q_lhs::S::num * Q_rhs::S::den;
    const long double nr = Q::S::den * Q_lhs::S::den * Q_rhs::S::num;
    const long double  d = Q::S::num * Q_lhs::S::den * Q_rhs::S::den;

    return Q( ( (typename Q::R)(nl / d) * lhs.repr ) + ( (typename Q::R)(nr / d) * rhs.repr ) );
  }

  namespace promote {
    template <typename Q_lhs, typename Q_rhs>
    struct subtract;

    template <typename R_lhs, typename R_rhs, typename U, typename S_lhs, typename S_rhs>
    struct subtract< Quantity<R_lhs, U, S_lhs>, Quantity<R_rhs, U, S_rhs> > {
      using Q = Quantity<R_rhs, U, S_rhs>;
    };
  }

  template < typename Q_lhs, typename Q_rhs, typename Q=typename promote::subtract< Q_lhs, Q_rhs >::Q >
  constexpr inline Q operator - (Q_lhs const & lhs, Q_rhs const & rhs) {
//  return Q(Q::S::den * ( (typename Q::R)( Q_lhs::S::num * lhs.repr / Q_lhs::S::den ) - (typename Q::R)( Q_rhs::S::num * rhs.repr / Q_rhs::S::den ) ) / Q::S::num);

    const long double nl = Q::S::den * Q_lhs::S::num * Q_rhs::S::den;
    const long double nr = Q::S::den * Q_lhs::S::den * Q_rhs::S::num;
    const long double  d = Q::S::num * Q_lhs::S::den * Q_rhs::S::den;

    return Q( ( (typename Q::R)(nl / d) * lhs.repr ) - ( (typename Q::R)(nr / d) * rhs.repr ) );
  }

  namespace promote {
    template <typename Q_lhs, typename Q_rhs>
    struct multiply {
      using Q = Quantity<
                  typename Q_lhs::R,
                  Unit<
                    std::ratio_add<typename Q_lhs::U::M, typename Q_rhs::U::M>,
                    std::ratio_add<typename Q_lhs::U::L, typename Q_rhs::U::L>,
                    std::ratio_add<typename Q_lhs::U::T, typename Q_rhs::U::T>,
                    std::ratio_add<typename Q_lhs::U::A, typename Q_rhs::U::A>
                  >,
                  std::ratio_multiply<typename Q_lhs::S, typename Q_rhs::S>
                >;
    };
  }

  template < typename Q_lhs, typename Q_rhs, typename Q=typename promote::multiply< Q_lhs, Q_rhs >::Q >
  constexpr inline Q operator * (Q_lhs const & lhs, Q_rhs const & rhs) {
//  return Q(Q::S::den * ( (typename Q::R)( Q_lhs::S::num * lhs.repr / Q_lhs::S::den ) * (typename Q::R)( Q_rhs::S::num * rhs.repr / Q_rhs::S::den ) ) / Q::S::num);

    const long double n = Q::S::den * Q_lhs::S::num * Q_rhs::S::num;
    const long double d = Q::S::num * Q_lhs::S::den * Q_rhs::S::den;
    return Q( (typename Q::R)(n/d) * ( rhs.repr * lhs.repr ) );
  }

  namespace promote {
    template <typename Q_lhs, typename Q_rhs>
    struct divide {
      using Q = Quantity<
                  typename Q_lhs::R,
                  Unit<
                    std::ratio_subtract<typename Q_lhs::U::M, typename Q_rhs::U::M>,
                    std::ratio_subtract<typename Q_lhs::U::L, typename Q_rhs::U::L>,
                    std::ratio_subtract<typename Q_lhs::U::T, typename Q_rhs::U::T>,
                    std::ratio_subtract<typename Q_lhs::U::A, typename Q_rhs::U::A>
                  >,
                  std::ratio_divide<typename Q_lhs::S, typename Q_rhs::S>
                >;
    };
  }

  template < typename Q_lhs, typename Q_rhs, typename Q=typename promote::divide< Q_lhs, Q_rhs >::Q >
  constexpr inline Q operator / (Q_lhs const & lhs, Q_rhs const & rhs) {
//  return Q(Q::S::den * ( (typename Q::R)( Q_lhs::S::num * lhs.repr / Q_lhs::S::den ) / (typename Q::R)( Q_rhs::S::num * rhs.repr / Q_rhs::S::den ) ) / Q::S::num);

    const long double n = Q::S::den * Q_lhs::S::num * Q_rhs::S::den;
    const long double d = Q::S::num * Q_lhs::S::den * Q_rhs::S::num;
    return Q( (typename Q::R)(n/d) * (lhs.repr / rhs.repr) );
  }

} // namespace Qrus

#endif /* __QRUS_OPERATORS_HPP__ */

