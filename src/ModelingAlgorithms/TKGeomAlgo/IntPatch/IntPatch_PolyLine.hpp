#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <IntPatch_IType.hpp>
#include <Standard_Boolean.hpp>
#include <IntPatch_Polygo.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
class IntPatch_WLine;
class IntPatch_RLine;

class IntPatch_PolyLine : public IntPatch_Polygo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPatch_PolyLine();

  Standard_EXPORT IntPatch_PolyLine(const double InitDefle);

  Standard_EXPORT void SetWLine(const bool OnFirst, const occ::handle<IntPatch_WLine>& Line);

  Standard_EXPORT void SetRLine(const bool OnFirst, const occ::handle<IntPatch_RLine>& Line);

  Standard_EXPORT void ResetError();

  Standard_EXPORT int NbPoints() const override;

  Standard_EXPORT gp_Pnt2d Point(const int Index) const override;

private:
  Standard_EXPORT void Prepare();

  gp_Pnt2d                    pnt;
  IntPatch_IType              typ;
  bool                        onfirst;
  occ::handle<IntPatch_WLine> wpoly;
  occ::handle<IntPatch_RLine> rpoly;
};

