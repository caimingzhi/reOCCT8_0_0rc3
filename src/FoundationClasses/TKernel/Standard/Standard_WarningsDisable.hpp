#if defined(__clang__)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wall"
  #pragma clang diagnostic ignored "-Wextra"
  #pragma clang diagnostic ignored "-Wshorten-64-to-32"
  #pragma clang diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
  #pragma warning(push, 0)
#elif defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))

  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
  #pragma GCC diagnostic ignored "-Wunused-variable"
  #pragma GCC diagnostic ignored "-Wunused-parameter"
  #pragma GCC diagnostic ignored "-Wenum-compare"
  #pragma GCC diagnostic ignored "-Wreorder"
  #if defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8))
    #pragma GCC diagnostic ignored "-Wunused-local-typedefs"
  #endif
#endif
