
#ifndef __QRUS_FUNCTIONS_HPP__
# define __QRUS_FUNCTIONS_HPP__

#if !defined(__QRUS_HPP__)
#  error This file must not be included directly, instead include Qrus/qrus.hxx.
#endif

namespace Qrus {

  // Mathematical functions

  namespace promote {
    template <typename Q_, typename P>
    struct pow {
      using Q = Quantity<
                  typename Q_::R,
                  Unit<
                    std::ratio_multiply<typename Q_::U::M, P>,
                    std::ratio_multiply<typename Q_::U::L, P>,
                    std::ratio_multiply<typename Q_::U::T, P>,
                    std::ratio_multiply<typename Q_::U::A, P>
                  >,
                  std::ratio_multiply<typename Q_::S, P>
                >;
    };
  }

  template <typename Q_, typename P, typename Q=typename promote::pow<Q_, P>::Q >
  constexpr inline Q pow(Q_ const & op, P const & p) {
    return std::pow(op.repr,((long double)P::num)/((long double)P::den));
  }

  // Trigonometry functions

  template <typename R> Quantity<R, None> sin(Quantity<R, Angle> const & a) { return std::sin(a.repr); }
  template <typename R> Quantity<R, None> cos(Quantity<R, Angle> const & a) { return std::cos(a.repr); }
  template <typename R> Quantity<R, None> tan(Quantity<R, Angle> const & a) { return std::tan(a.repr); }

} // namespace Qrus

#endif /* __QRUS_FUNCTIONS_HPP__ */

