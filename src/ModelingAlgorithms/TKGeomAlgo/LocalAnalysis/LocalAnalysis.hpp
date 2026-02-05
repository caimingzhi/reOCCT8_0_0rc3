#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_OStream.hpp>

class LocalAnalysis_SurfaceContinuity;
class LocalAnalysis_CurveContinuity;

//! This package gives tools to check the local continuity
//! between two points situated on two curves or two surfaces.
class LocalAnalysis
{
public:
  DEFINE_STANDARD_ALLOC

  //! This class computes and gives tools to check the local
  //! continuity between two points situated on 2 curves.
  //!
  //! This function gives information about a variable CurveContinuity
  Standard_EXPORT static void Dump(const LocalAnalysis_SurfaceContinuity& surfconti,
                                   Standard_OStream&                      o);

  //! This function gives information about a variable SurfaceContinuity
  Standard_EXPORT static void Dump(const LocalAnalysis_CurveContinuity& curvconti,
                                   Standard_OStream&                    o);
};
