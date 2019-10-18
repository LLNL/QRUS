
#ifndef __QRUS_LITTERAL_HPP__
# define __QRUS_LITTERAL_HPP__

#include "Qrus/qrus.hxx"

namespace Qrus {
  constexpr Quantity<long double, None>               operator"" __     (long double x) { return Quantity<long double, None>(x); }
  constexpr Quantity<long double, Mass, std::kilo>    operator"" _kg    (long double x) { return Quantity<long double, Mass, std::kilo>(x); }
  constexpr Quantity<long double, Mass>               operator"" _g     (long double x) { return Quantity<long double, Mass>(x); }
  constexpr Quantity<long double, Mass, std::milli>   operator"" _mg    (long double x) { return Quantity<long double, Mass, std::milli>(x); }
  constexpr Quantity<long double, Length, std::kilo>  operator"" _km    (long double x) { return Quantity<long double, Length, std::kilo>(x); }
  constexpr Quantity<long double, Length>             operator"" _m     (long double x) { return Quantity<long double, Length>(x); }
  constexpr Quantity<long double, Length, std::milli> operator"" _mm    (long double x) { return Quantity<long double, Length, std::milli>(x); }
  constexpr Quantity<long double, Time>               operator"" _s     (long double x) { return Quantity<long double, Time>(x); }
  constexpr Quantity<long double, Time, std::milli>   operator"" _ms    (long double x) { return Quantity<long double, Time, std::milli>(x); }
  constexpr Quantity<long double, Time, std::micro>   operator"" _us    (long double x) { return Quantity<long double, Time, std::micro>(x); }
  constexpr Quantity<long double, Time, std::nano>    operator"" _ns    (long double x) { return Quantity<long double, Time, std::nano>(x); }
  constexpr Quantity<long double, Angle>              operator"" _rad   (long double x) { return Quantity<long double, Angle>(x); }
  constexpr Quantity<long double, Angle>              operator"" _deg   (long double x) { return Quantity<long double, Angle>(3.1415926535897932384626433832795 * x / 180.0); }
  constexpr Quantity<long double, Speed>              operator"" _mps   (long double x) { return Quantity<long double, Speed>(x); }
  constexpr Quantity<long double, Acceleration>       operator"" _mps2  (long double x) { return Quantity<long double, Acceleration>(x); }
  constexpr Quantity<long double, Force>              operator"" _N     (long double x) { return Quantity<long double, Force>(x); }

  constexpr Quantity<     double, None>               operator"" ___d   (long double x) { return Quantity<     double, None>(x); }
  constexpr Quantity<     double, Mass, std::kilo>    operator"" _kg_d  (long double x) { return Quantity<     double, Mass, std::kilo>(x); }
  constexpr Quantity<     double, Mass>               operator"" _g_d   (long double x) { return Quantity<     double, Mass>(x); }
  constexpr Quantity<     double, Mass, std::milli>   operator"" _mg_d  (long double x) { return Quantity<     double, Mass, std::milli>(x); }
  constexpr Quantity<     double, Length, std::kilo>  operator"" _km_d  (long double x) { return Quantity<     double, Length, std::kilo>(x); }
  constexpr Quantity<     double, Length>             operator"" _m_d   (long double x) { return Quantity<     double, Length>(x); }
  constexpr Quantity<     double, Length, std::milli> operator"" _mm_d  (long double x) { return Quantity<     double, Length, std::milli>(x); }
  constexpr Quantity<     double, Time>               operator"" _s_d   (long double x) { return Quantity<     double, Time>(x); }
  constexpr Quantity<     double, Time, std::milli>   operator"" _ms_d  (long double x) { return Quantity<     double, Time, std::milli>(x); }
  constexpr Quantity<     double, Time, std::micro>   operator"" _us_d  (long double x) { return Quantity<     double, Time, std::micro>(x); }
  constexpr Quantity<     double, Time, std::nano>    operator"" _ns_d  (long double x) { return Quantity<     double, Time, std::nano>(x); }
  constexpr Quantity<     double, Angle>              operator"" _rad_d (long double x) { return Quantity<     double, Angle>(x); }
  constexpr Quantity<     double, Angle>              operator"" _deg_d (long double x) { return Quantity<     double, Angle>(3.1415926535897932384626433832795 * x / 180.0); }
  constexpr Quantity<     double, Speed>              operator"" _mps_d (long double x) { return Quantity<     double, Speed>(x); }
  constexpr Quantity<     double, Acceleration>       operator"" _mps2_d(long double x) { return Quantity<     double, Acceleration>(x); }
  constexpr Quantity<     double, Force>              operator"" _N_d   (long double x) { return Quantity<     double, Force>(x); }

  constexpr Quantity<      float, None>               operator"" ___f   (long double x) { return Quantity<      float, None>(x); }
  constexpr Quantity<      float, Mass, std::kilo>    operator"" _kg_f  (long double x) { return Quantity<      float, Mass, std::kilo>(x); }
  constexpr Quantity<      float, Mass>               operator"" _g_f   (long double x) { return Quantity<      float, Mass>(x); }
  constexpr Quantity<      float, Mass, std::milli>   operator"" _mg_f  (long double x) { return Quantity<      float, Mass, std::milli>(x); }
  constexpr Quantity<      float, Length, std::kilo>  operator"" _km_f  (long double x) { return Quantity<      float, Length, std::kilo>(x); }
  constexpr Quantity<      float, Length>             operator"" _m_f   (long double x) { return Quantity<      float, Length>(x); }
  constexpr Quantity<      float, Length, std::milli> operator"" _mm_f  (long double x) { return Quantity<      float, Length, std::milli>(x); }
  constexpr Quantity<      float, Time>               operator"" _s_f   (long double x) { return Quantity<      float, Time>(x); }
  constexpr Quantity<      float, Time, std::milli>   operator"" _ms_f  (long double x) { return Quantity<      float, Time, std::milli>(x); }
  constexpr Quantity<      float, Time, std::micro>   operator"" _us_f  (long double x) { return Quantity<      float, Time, std::micro>(x); }
  constexpr Quantity<      float, Time, std::nano>    operator"" _ns_f  (long double x) { return Quantity<      float, Time, std::nano>(x); }
  constexpr Quantity<      float, Angle>              operator"" _rad_f (long double x) { return Quantity<      float, Angle>(x); }
  constexpr Quantity<      float, Angle>              operator"" _deg_f (long double x) { return Quantity<      float, Angle>(3.1415926535897932384626433832795 * x / 180.0); }
  constexpr Quantity<      float, Speed>              operator"" _mps_f (long double x) { return Quantity<      float, Speed>(x); }
  constexpr Quantity<      float, Acceleration>       operator"" _mps2_f(long double x) { return Quantity<      float, Acceleration>(x); }
  constexpr Quantity<      float, Force>              operator"" _N_f   (long double x) { return Quantity<      float, Force>(x); }
} // namespace Qrus

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

using Qrus::operator"" ___d;
using Qrus::operator"" _kg_d;
using Qrus::operator"" _g_d;
using Qrus::operator"" _mg_d;
using Qrus::operator"" _km_d;
using Qrus::operator"" _m_d;
using Qrus::operator"" _mm_d;
using Qrus::operator"" _s_d;
using Qrus::operator"" _ms_d;
using Qrus::operator"" _us_d;
using Qrus::operator"" _ns_d;
using Qrus::operator"" _rad_d;
using Qrus::operator"" _deg_d;
using Qrus::operator"" _mps_d;
using Qrus::operator"" _mps2_d;
using Qrus::operator"" _N_d;

using Qrus::operator"" ___f;
using Qrus::operator"" _kg_f;
using Qrus::operator"" _g_f;
using Qrus::operator"" _mg_f;
using Qrus::operator"" _km_f;
using Qrus::operator"" _m_f;
using Qrus::operator"" _mm_f;
using Qrus::operator"" _s_f;
using Qrus::operator"" _ms_f;
using Qrus::operator"" _us_f;
using Qrus::operator"" _ns_f;
using Qrus::operator"" _rad_f;
using Qrus::operator"" _deg_f;
using Qrus::operator"" _mps_f;
using Qrus::operator"" _mps2_f;
using Qrus::operator"" _N_f;

#endif /* __QRUS_LITTERAL_HPP__ */

