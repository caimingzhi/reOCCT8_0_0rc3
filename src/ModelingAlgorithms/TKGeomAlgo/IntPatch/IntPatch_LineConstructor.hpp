#pragma once

#include <Adaptor3d_Surface.hpp>
#include <IntPatch_Line.hpp>
#include <NCollection_Sequence.hpp>

class Adaptor3d_TopolTool;

//! The intersections algorithms compute the intersection
//! on two surfaces and return the intersections lines as
//! IntPatch_Line.
class IntPatch_LineConstructor
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPatch_LineConstructor(const int mode);

  Standard_EXPORT void Perform(const NCollection_Sequence<occ::handle<IntPatch_Line>>& SL,
                               const occ::handle<IntPatch_Line>&                       L,
                               const occ::handle<Adaptor3d_Surface>&                   S1,
                               const occ::handle<Adaptor3d_TopolTool>&                 D1,
                               const occ::handle<Adaptor3d_Surface>&                   S2,
                               const occ::handle<Adaptor3d_TopolTool>&                 D2,
                               const double                                            Tol);

  Standard_EXPORT int NbLines() const;

  Standard_EXPORT occ::handle<IntPatch_Line> Line(const int index) const;

private:
  NCollection_Sequence<occ::handle<IntPatch_Line>> slin;
};
