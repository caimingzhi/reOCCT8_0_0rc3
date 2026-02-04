#pragma once


//! @file
//! Include this file to disable GCC warning -Wcast-function-type introduced in GCC 8.1.
//!
//! This diagnostic warns when a function pointer is cast to an incompatible function pointer.
//! Existing APIs loading function pointer from library (like dlsym() or wglGetProcAddress()) have
//! no possibility to return function of specified type nor to verify that exported symbol actually
//! matches the expected function signature, so that unsafe function cast is unavoidable.
//! There is no way to prevent this warning at OCCT level (until safer APIs is introduced), thus
//! suppressing it is the only feasible way to avoid it. As this warning still can point out broken
//! places, it should be suppressed only locally, where usage of function cast has been verified.
#if defined(__GNUC__) && !defined(__INTEL_COMPILER) && !defined(__clang__)
  #if (__GNUC__ > 8) || ((__GNUC__ == 8) && (__GNUC_MINOR__ >= 1))
    #pragma GCC diagnostic ignored "-Wcast-function-type"
  #endif
#endif

