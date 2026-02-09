#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_DefType.hpp>
class Interface_Check;
class IGESData_IGESEntity;

class IGESData_DirChecker
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESData_DirChecker();

  Standard_EXPORT IGESData_DirChecker(const int atype);

  Standard_EXPORT IGESData_DirChecker(const int atype, const int aform);

  Standard_EXPORT IGESData_DirChecker(const int atype, const int aform1, const int aform2);

  Standard_EXPORT bool IsSet() const;

  Standard_EXPORT void SetDefault();

  Standard_EXPORT void Structure(const IGESData_DefType crit);

  Standard_EXPORT void LineFont(const IGESData_DefType crit);

  Standard_EXPORT void LineWeight(const IGESData_DefType crit);

  Standard_EXPORT void Color(const IGESData_DefType crit);

  Standard_EXPORT void GraphicsIgnored(const int hierarchy = -1);

  Standard_EXPORT void BlankStatusIgnored();

  Standard_EXPORT void BlankStatusRequired(const int val);

  Standard_EXPORT void SubordinateStatusIgnored();

  Standard_EXPORT void SubordinateStatusRequired(const int val);

  Standard_EXPORT void UseFlagIgnored();

  Standard_EXPORT void UseFlagRequired(const int val);

  Standard_EXPORT void HierarchyStatusIgnored();

  Standard_EXPORT void HierarchyStatusRequired(const int val);

  Standard_EXPORT void Check(occ::handle<Interface_Check>&           ach,
                             const occ::handle<IGESData_IGESEntity>& ent) const;

  Standard_EXPORT void CheckTypeAndForm(occ::handle<Interface_Check>&           ach,
                                        const occ::handle<IGESData_IGESEntity>& ent) const;

  Standard_EXPORT bool Correct(const occ::handle<IGESData_IGESEntity>& ent) const;

private:
  bool             isitset;
  int              thetype;
  int              theform1;
  int              theform2;
  IGESData_DefType thestructure;
  IGESData_DefType thelinefont;
  IGESData_DefType thelineweig;
  IGESData_DefType thecolor;
  int              thegraphier;
  int              theblankst;
  int              thesubordst;
  int              theuseflag;
  int              thehierst;
};
