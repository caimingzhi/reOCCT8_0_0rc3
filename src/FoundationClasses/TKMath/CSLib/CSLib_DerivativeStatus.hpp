#pragma once

//! Status of surface derivatives computation for normal calculation.
//!
//! Describes the result of attempting to compute a surface normal
//! from the first derivatives D1U and D1V at a point on a surface.
enum CSLib_DerivativeStatus
{
  CSLib_Done,              //!< Normal computed successfully.
  CSLib_D1uIsNull,         //!< D1U has null length: ||D1U|| <= Resolution.
  CSLib_D1vIsNull,         //!< D1V has null length: ||D1V|| <= Resolution.
  CSLib_D1IsNull,          //!< Both derivatives are null.
  CSLib_D1uD1vRatioIsNull, //!< D1U is negligible: ||D1U|| / ||D1V|| <= RealEpsilon.
  CSLib_D1vD1uRatioIsNull, //!< D1V is negligible: ||D1V|| / ||D1U|| <= RealEpsilon.
  CSLib_D1uIsParallelD1v   //!< D1U and D1V are parallel.
};
