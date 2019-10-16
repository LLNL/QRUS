
#include "qrus.hxx"

#if !defined(OUTPUT_INFO)
#  define OUTPUT_INFO QRUS_HAS_IO
#endif

#if OUTPUT_INFO && !QRUS_HAS_IO
#  error "Cannot display type-info without enabling I/O in Qrus (-DQRUS_HAS_IO=1)."
#endif

int main() {

  auto a = 10._kg;
#if OUTPUT_INFO
  std::cout << "a = 10._kg = " << a.repr << " " << decltype(a)::__scale() << " " << decltype(a)::__unit() << std::endl;
#endif
  auto b = 4.7_km;
#if OUTPUT_INFO
  std::cout << "b = 4.7_km = " << b.repr << " " << decltype(b)::__scale() << " " << decltype(b)::__unit() << std::endl;
#endif
  auto c = a * b;
#if OUTPUT_INFO
  std::cout << "c =  a * b = " << c.repr << " " << decltype(c)::__scale() << " " << decltype(c)::__unit() << std::endl;
#endif
  auto d = 12._us;
#if OUTPUT_INFO
  std::cout << "d = 12._us = " << d.repr << " " << decltype(d)::__scale() << " " << decltype(d)::__unit() << std::endl;
#endif
  auto e = c * d;
#if OUTPUT_INFO
  std::cout << "e =  c * d = " << e.repr << " " << decltype(e)::__scale() << " " << decltype(e)::__unit() << std::endl;
#endif
  return e.repr != 564.;
}

