#pragma once


//! Status of surface normal computation.
//!
//! Describes the result of attempting to compute the normal N to a surface,
//! including cases involving derivatives of the normal (DN/du, DN/dv).
enum CSLib_NormalStatus
{
  CSLib_Singular,            //!< Surface is singular at the point (normal undefined).
  CSLib_Defined,             //!< Normal is well-defined and computed successfully.
  CSLib_InfinityOfSolutions, //!< Infinite normals possible.
  CSLib_D1NuIsNull,          //!< DN/du has null length: ||DN/du|| <= Resolution.
  CSLib_D1NvIsNull,          //!< DN/dv has null length: ||DN/dv|| <= Resolution.
  CSLib_D1NIsNull,           //!< Both normal derivatives are null.
  CSLib_D1NuNvRatioIsNull,   //!< DN/du is negligible compared to DN/dv.
  CSLib_D1NvNuRatioIsNull,   //!< DN/dv is negligible compared to DN/du.
  CSLib_D1NuIsParallelD1Nv   //!< DN/du and DN/dv are parallel.
};

