// vim:filetype=cpp:textwidth=80:shiftwidth=2:softtabstop=2:expandtab
// Copyright 2014 schwering@kbsg.rwth-aachen.de

#ifndef SRC_MAYBE_H_
#define SRC_MAYBE_H_

#include <cassert>
#include <utility>

namespace esbl {

template<typename... T>
struct Maybe {
};

template<typename T>
struct Maybe<T> {
  Maybe()                                           : succ(false) {}
  explicit Maybe(T&& val)                           : succ(true), val(val) {}  // NOLINT
  template<typename U> explicit Maybe(const U& val) : succ(true), val(val) {}
  Maybe(bool succ, T&& val)                         : succ(succ), val(val) {}  // NOLINT

  Maybe(const Maybe&) = default;
  Maybe(Maybe&&) = default;
  Maybe& operator=(Maybe&) = default;
  Maybe& operator=(Maybe&&) = default;

  template<typename U> Maybe(const Maybe<U>& m)            : succ(m.succ), val(m.val) {}  // NOLINT
  template<typename U> Maybe(Maybe<U>&& m)                 : succ(m.succ), val(m.val) {}  // NOLINT
  template<typename U> Maybe& operator=(const Maybe<U>& m) { succ = m.succ; val = m.val; }  // NOLINT
  template<typename U> Maybe& operator=(Maybe<U>&& m)      { succ = m.succ; val = m.val; }  // NOLINT

  operator bool() const { return succ; }

  bool succ;
  T val;
};

template<typename T1, typename T2>
struct Maybe<T1, T2> {
  Maybe()                                                                           : succ(false) {}
  explicit Maybe(T1&& val1, T2&& val2)                                              : succ(true), val1(val1), val2(val2) {}  // NOLINT
  template<typename U1, typename U2> explicit Maybe(const U1& val1, const U2& val2) : succ(true), val1(val1), val2(val2) {}  // NOLINT
  Maybe(bool succ, T1&& val1, T2&& val2)                                            : succ(succ), val1(val1), val2(val2) {}  // NOLINT

  Maybe(const Maybe&) = default;
  Maybe(Maybe&&) = default;
  Maybe& operator=(Maybe&) = default;
  Maybe& operator=(Maybe&&) = default;

  template<typename U1, typename U2> Maybe(const Maybe<U1, U2>& m)       : succ(m.succ), val1(m.val1), val2(m.val2) {}  // NOLINT
  template<typename U1, typename U2> Maybe(Maybe<U1, U2>&& m)            : succ(m.succ), val1(m.val1), val2(m.val2) {}  // NOLINT
  template<typename U1, typename U2> Maybe& operator=(Maybe<U1, U2>& m)  { succ = m.succ; val1 = m.val1; val2 = m.val2; }  // NOLINT
  template<typename U1, typename U2> Maybe& operator=(Maybe<U1, U2>&& m) { succ = m.succ; val1 = m.val1; val2 = m.val2; }  // NOLINT

  operator bool() const { return succ; }

  bool succ;
  T1 val1;
  T2 val2;
};

struct NothingType {
  template<typename... Types>
  operator Maybe<Types...>() const {
    return Maybe<Types...>();
  }
};

constexpr NothingType Nothing = NothingType();

template<typename... Types>
Maybe<Types...> Just(Types&&... val) {  // NOLINT
  return Maybe<Types...>(val...);
}

template<typename... Types>
Maybe<Types...> Perhaps(bool succ, Types&&... val) {  // NOLINT
  return Maybe<Types...>(succ, val...);
}

}  // namespace esbl

#endif  // SRC_MAYBE_H_
