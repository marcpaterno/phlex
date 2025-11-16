#ifndef PHLEX_MODULE_HPP
#define PHLEX_MODULE_HPP

#include "phlex_int_export.hpp"
#include "phlex/concurrency.hpp"
#include "phlex/configuration.hpp"
#include "phlex/core/graph_proxy.hpp"

#include "boost/preprocessor.hpp"

namespace phlex::experimental::detail {
  using module_creator_t = void(graph_proxy<void_tag>&, configuration const&);
}

#define NARGS(...) BOOST_PP_DEC(BOOST_PP_VARIADIC_SIZE(__VA_OPT__(, ) __VA_ARGS__))

#define CREATE_1ARG(m)                                                                             \
  void create(phlex::experimental::graph_proxy<phlex::experimental::void_tag>& m,                  \
              phlex::experimental::configuration const&)
#define CREATE_2ARGS(m, pset)                                                                      \
  void create(phlex::experimental::graph_proxy<phlex::experimental::void_tag>& m,                  \
              phlex::experimental::configuration const& config)

#define SELECT_SIGNATURE(...)                                                                      \
  BOOST_PP_IF(BOOST_PP_EQUAL(NARGS(__VA_ARGS__), 1), CREATE_1ARG, CREATE_2ARGS)(__VA_ARGS__)

#define PHLEX_EXPERIMENTAL_REGISTER_ALGORITHMS(...)                                                \
  extern "C" {                                                                                     \
  phlex_int_EXPORT void create_module(phlex::experimental::graph_proxy<phlex::experimental::void_tag>&, \
                                   phlex::experimental::configuration const&);                     \
  }                                                                                                \
  static SELECT_SIGNATURE(__VA_ARGS__);                                                            \
  void create_module(phlex::experimental::graph_proxy<phlex::experimental::void_tag>& proxy,       \
                     phlex::experimental::configuration const& config)                                 \
  {                                                                                                \
    create(proxy, config);                                                                         \
  }

#endif // PHLEX_MODULE_HPP
