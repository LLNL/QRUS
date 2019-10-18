
#ifndef __QRUS_QUANTITY_HPP__
# define __QRUS_QUANTITY_HPP__

#if !defined(__QRUS_HPP__)
#  error This file must not be included directly, instead include Qrus/qrus.hxx.
#endif

namespace Qrus {

  // Qrus::Quantity: a floating point representation, a Qrus::Unit, and a scale (std::ratio)

  template <typename R_, typename U_, typename S_=std::ratio<1>>
  struct Quantity {

    using R = R_;
    using U = U_;
    using S = S_;
    using Q = Quantity<R,U,S>;

    R repr;

    template <typename T>
    constexpr Quantity(T t) : repr(t) {};

    template <typename R_rhs, typename S_rhs>
    constexpr inline Q & operator = (const Quantity<R_rhs, U, S_rhs> & op) {
      repr = S::den * (R)( S_rhs::num * op.repr / S_rhs::den ) / S::num;
      return *this;
    }

#if QRUS_HAS_IO
    static std::string __typename();
    static std::string __unit();
    static std::string __scale();
#endif
  };

} // namespace Qrus

#endif /* __QRUS_QUANTITY_HPP__ */

