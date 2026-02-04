#pragma once


//! @file
//! This file provides obsolete low-level helper macros used to define OCCT handles and types,
//! for compatibility with previous versions of OCCT.
//! Since OCCT 7.0, relevant macros are provided by Standard_Type.hpp and Standard_Handle.hpp.

#include <Standard_Type.hpp>

class Standard_Transient;
class Standard_Persistent;
class Standard_Type;

// Obsolete macros kept for compatibility
#define IMPLEMENT_DOWNCAST(C1, BC)
#define IMPLEMENT_STANDARD_HANDLE(C1, C2)
#define IMPLEMENT_STANDARD_PHANDLE(C1, C2)
#define IMPLEMENT_STANDARD_RTTI(C1)
#define IMPLEMENT_STANDARD_TYPE(C1)
#define IMPLEMENT_STANDARD_SUPERTYPE(Cn)
#define IMPLEMENT_STANDARD_SUPERTYPE_ARRAY()
#define IMPLEMENT_STANDARD_SUPERTYPE_ARRAY_END()
#define IMPLEMENT_STANDARD_TYPE_END(C1)

