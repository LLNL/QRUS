
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

#include <Qrus/unit.hxx>
#include <Qrus/quantity.hxx>
#include <Qrus/operators.hxx>
#include <Qrus/functions.hxx>

#if QRUS_HAS_IO
#  include <Qrus/io.txx>
#endif

#endif /* __QRUS_HPP__ */

