#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>
#include <TopOpeBRep_TypeLineCurve.hpp>

//! This package provides the topological operations
//! on the BRep data structure.
class TopOpeBRep
{
public:
  DEFINE_STANDARD_ALLOC

  //! Prints the name of <TLC> as a String on the
  //! Stream <S> and returns <S>.
  Standard_EXPORT static Standard_OStream& Print(const TopOpeBRep_TypeLineCurve TLC,
                                                 Standard_OStream&              OS);
};
