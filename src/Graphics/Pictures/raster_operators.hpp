
/******************************************************************************
* MODULE     : raster_operators.hpp
* DESCRIPTION: Templates for several raster operations
* COPYRIGHT  : (C) 2013  Joris van der Hoeven
*******************************************************************************
* This software falls under the GNU general public license version 3 or later.
* It comes WITHOUT ANY WARRANTY WHATSOEVER. For details, see the file LICENSE
* in the root directory or <http://www.gnu.org/licenses/gpl-3.0.html>.
******************************************************************************/

#ifndef RASTER_OPERATORS_HPP
#define RASTER_OPERATORS_HPP
#include "picture.hpp"
#include "operators.hpp"

/******************************************************************************
* Default implementations
******************************************************************************/

template<typename C> void clear (C& x) { x= 0.0; }
template<typename C> C mul_alpha (C& x) { return x; }
template<typename C> C div_alpha (C& x) { return x; }

/******************************************************************************
* Unary operators
******************************************************************************/

template<typename Op, typename C>
struct unary_return_type_helper {
  typedef C RET;
};

#define Unary_return_type(Op,C) \
  typename unary_return_type_helper<Op,C>::RET

struct mul_alpha_op {
  template<typename C> static inline C
  op (const C& x) { return mul_alpha (x); }
};

struct div_alpha_op {
  template<typename C> static inline C
  op (const C& x) { return div_alpha (x); }
};

struct normalize_op {
  template<typename C> static inline C
  op (const C& x) { return normalize (x); }
};

struct get_alpha_op {
  template<typename C> static inline typename C::scalar_type
  op (const C& x) { return get_alpha (x); }
};

template<typename C>
struct unary_return_type_helper<get_alpha_op,C> {
  typedef typename C::scalar_type RET;
};

/******************************************************************************
* Binary operators
******************************************************************************/

struct hypot_op {
  template<typename C> static inline C
  op (const C& x, const C& y) { return hypot (x, y); }
};

/******************************************************************************
* Composition operators
******************************************************************************/

template<composition_mode M>
struct composition_op {
  template<typename C, typename S> static inline C
  op (const C& x, const S& y) { (void) y; return x; }
  template<typename C, typename S> static inline void
  set_op (C& x, const S& y) { (void) x; (void) y; }
};

template<>
struct composition_op<compose_source> {
  template<typename C, typename S> static inline C
  op (const C& x, const S& y) { (void) x; return y; }
  template<typename C, typename S> static inline void
  set_op (C& x, const S& y) { x= y; }
};

template<>
struct composition_op<compose_source_over> {
  template<typename C, typename S> static inline C
  op (const C& x, const S& y) { return source_over (x, y); }
  template<typename C, typename S> static inline void
  set_op (C& x, const S& y) { x= source_over (x, y); }
};

template<>
struct composition_op<compose_towards_source> {
  template<typename C, typename S> static inline C
  op (const C& x, const S& y) { return towards_source (x, y); }
  template<typename C, typename S> static inline void
  set_op (C& x, const S& y) { x= towards_source (x, y); }
};

typedef composition_op<compose_source> source_op;
typedef composition_op<compose_source_over> source_over_op;
typedef composition_op<compose_towards_source> towards_source_op;

#endif // RASTER_OPERATORS_H