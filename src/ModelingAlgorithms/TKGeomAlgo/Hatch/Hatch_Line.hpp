#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Lin2d.hpp>
#include <Hatch_LineForm.hpp>
#include <Hatch_Parameter.hpp>
#include <NCollection_Sequence.hpp>

class Hatch_Line
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Hatch_Line();

  Standard_EXPORT Hatch_Line(const gp_Lin2d& L, const Hatch_LineForm T);

  Standard_EXPORT void AddIntersection(const double Par1,
                                       const bool   Start,
                                       const int    Index,
                                       const double Par2,
                                       const double theToler);

  friend class Hatch_Hatcher;

private:
  gp_Lin2d                              myLin;
  Hatch_LineForm                        myForm;
  NCollection_Sequence<Hatch_Parameter> myInters;
};
