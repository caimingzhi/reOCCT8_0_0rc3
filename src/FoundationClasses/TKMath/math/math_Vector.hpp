#pragma once

#include <math_VectorBase.hpp>

//! This class implements the real vector abstract data type.
//! Vectors can have an arbitrary range which must be defined at
//! the declaration and cannot be changed after this declaration.
//! @code
//!    math_Vector V1(-3, 5); // a vector with range [-3..5]
//! @endcode
//!
//! Vector are copied through assignment:
//! @code
//!    math_Vector V2( 1, 9);
//!    ....
//!    V2 = V1;
//!    V1(1) = 2.0; // the vector V2 will not be modified.
//! @endcode
//!
//! The Exception RangeError is raised when trying to access outside
//! the range of a vector :
//! @code
//!    V1(11) = 0.0 // --> will raise RangeError;
//! @endcode
//!
//! The Exception DimensionError is raised when the dimensions of two
//! vectors are not compatible :
//! @code
//!    math_Vector V3(1, 2);
//!    V3 = V1;    // --> will raise DimensionError;
//!    V1.Add(V3)  // --> will raise DimensionError;
//! @endcode
using math_Vector = math_VectorBase<double>;
