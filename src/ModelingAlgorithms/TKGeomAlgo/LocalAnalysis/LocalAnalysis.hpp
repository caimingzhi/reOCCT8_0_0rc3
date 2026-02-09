#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_OStream.hpp>

class LocalAnalysis_SurfaceContinuity;
class LocalAnalysis_CurveContinuity;

class LocalAnalysis
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Dump(const LocalAnalysis_SurfaceContinuity& surfconti,
                                   Standard_OStream&                      o);

  Standard_EXPORT static void Dump(const LocalAnalysis_CurveContinuity& curvconti,
                                   Standard_OStream&                    o);
};
