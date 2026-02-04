#pragma once


//! Type alias for curve pointer used in HLRBRep algorithms.
//! This provides a named type (void*) for curve pointers used in generic
//! algorithm interfaces, replacing the deprecated void*.
//! The void* type is required for compatibility with the generic template
//! instantiation system that uses const reference parameters.
typedef void* HLRBRep_CurvePtr;

//! Type alias for surface pointer used in HLRBRep algorithms.
//! This provides a named type (void*) for surface pointers used in generic
//! algorithm interfaces, replacing the deprecated void*.
typedef void* HLRBRep_SurfacePtr;

