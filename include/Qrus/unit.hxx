
#ifndef __QRUS_UNIT_HPP__
# define __QRUS_UNIT_HPP__

#if !defined(__QRUS_HPP__)
#  error This file must not be included directly, instead include Qrus/qrus.hxx.
#endif

namespace Qrus {

  // Qrus::Unit: uses 4 rationals (std::ratio) to represent any SI Unit (+ angles)

  template <typename M_, typename L_, typename T_, typename A_>
  struct Unit {
    using M = M_;
    using L = L_;
    using T = T_;
    using A = A_;

#if QRUS_HAS_IO
    static std::string __typename();
#endif
  };

  // Basic SI Units

  using None         = Unit< std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> >;
  using Mass         = Unit< std::ratio< 1>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> >;
  using Length       = Unit< std::ratio< 0>, std::ratio< 1>, std::ratio< 0>, std::ratio< 0> >;
  using Time         = Unit< std::ratio< 0>, std::ratio< 0>, std::ratio< 1>, std::ratio< 0> >;
  using Angle        = Unit< std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 1> >;
  using Speed        = Unit< std::ratio< 0>, std::ratio< 1>, std::ratio<-1>, std::ratio< 0> >;
  using Acceleration = Unit< std::ratio< 0>, std::ratio< 1>, std::ratio<-2>, std::ratio< 0> >;
  using Force        = Unit< std::ratio< 1>, std::ratio< 1>, std::ratio<-2>, std::ratio< 0> >;

} // namespace Qrus

#endif /* __QRUS_UNIT_HPP__ */

