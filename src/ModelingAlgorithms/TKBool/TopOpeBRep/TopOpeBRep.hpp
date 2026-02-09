#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>
#include <TopOpeBRep_TypeLineCurve.hpp>

class TopOpeBRep
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static Standard_OStream& Print(const TopOpeBRep_TypeLineCurve TLC,
                                                 Standard_OStream&              OS);
};
