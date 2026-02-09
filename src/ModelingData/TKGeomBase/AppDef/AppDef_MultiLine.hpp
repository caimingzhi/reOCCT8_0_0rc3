#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <AppDef_MultiPointConstraint.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_OStream.hpp>
class AppDef_MultiPointConstraint;

class AppDef_MultiLine
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AppDef_MultiLine();

  Standard_EXPORT AppDef_MultiLine(const int NbMult);

  Standard_EXPORT AppDef_MultiLine(
    const NCollection_Array1<AppDef_MultiPointConstraint>& tabMultiP);

  Standard_EXPORT AppDef_MultiLine(const NCollection_Array1<gp_Pnt>& tabP3d);

  Standard_EXPORT AppDef_MultiLine(const NCollection_Array1<gp_Pnt2d>& tabP2d);

  Standard_EXPORT int NbMultiPoints() const;

  Standard_EXPORT int NbPoints() const;

  Standard_EXPORT void SetParameter(const int Index, const double U);

  Standard_EXPORT void SetValue(const int Index, const AppDef_MultiPointConstraint& MPoint);

  Standard_EXPORT AppDef_MultiPointConstraint Value(const int Index) const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

protected:
  occ::handle<NCollection_HArray1<AppDef_MultiPointConstraint>> tabMult;
};
