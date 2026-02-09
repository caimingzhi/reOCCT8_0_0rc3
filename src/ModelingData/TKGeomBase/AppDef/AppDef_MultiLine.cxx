

#include <AppDef_MultiPointConstraint.hpp>
#include <NCollection_Array1.hpp>
#include <AppDef_MultiLine.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_OutOfRange.hpp>

AppDef_MultiLine::AppDef_MultiLine() = default;

AppDef_MultiLine::AppDef_MultiLine(const int NbMult)
{
  if (NbMult < 0)
    throw Standard_ConstructionError();

  tabMult = new NCollection_HArray1<AppDef_MultiPointConstraint>(1, NbMult);
}

AppDef_MultiLine::AppDef_MultiLine(const NCollection_Array1<AppDef_MultiPointConstraint>& tabMultiP)
{
  tabMult = new NCollection_HArray1<AppDef_MultiPointConstraint>(1, tabMultiP.Length());
  int i, Lower = tabMultiP.Lower();
  for (i = 1; i <= tabMultiP.Length(); i++)
  {
    tabMult->SetValue(i, tabMultiP.Value(Lower + i - 1));
  }
}

AppDef_MultiLine::AppDef_MultiLine(const NCollection_Array1<gp_Pnt>& tabP3d)
{
  tabMult = new NCollection_HArray1<AppDef_MultiPointConstraint>(1, tabP3d.Length());
  int i, Lower = tabP3d.Lower();
  for (i = 1; i <= tabP3d.Length(); i++)
  {
    AppDef_MultiPointConstraint MP(1, 0);
    MP.SetPoint(1, tabP3d(Lower + i - 1));
    tabMult->SetValue(i, MP);
  }
}

AppDef_MultiLine::AppDef_MultiLine(const NCollection_Array1<gp_Pnt2d>& tabP2d)
{
  tabMult = new NCollection_HArray1<AppDef_MultiPointConstraint>(1, tabP2d.Length());
  int i, Lower = tabP2d.Lower();
  for (i = 1; i <= tabP2d.Length(); i++)
  {
    AppDef_MultiPointConstraint MP(0, 1);
    MP.SetPoint2d(1, tabP2d(Lower + i - 1));
    tabMult->SetValue(i, MP);
  }
}

int AppDef_MultiLine::NbMultiPoints() const
{
  return tabMult->Length();
}

int AppDef_MultiLine::NbPoints() const
{
  return tabMult->Value(1).NbPoints() + tabMult->Value(1).NbPoints2d();
}

void AppDef_MultiLine::SetValue(const int Index, const AppDef_MultiPointConstraint& MPoint)
{
  if ((Index <= 0) || (Index > tabMult->Length()))
  {
    throw Standard_OutOfRange();
  }
  tabMult->SetValue(Index, MPoint);
}

AppDef_MultiPointConstraint AppDef_MultiLine::Value(const int Index) const
{
  if ((Index <= 0) || (Index > tabMult->Length()))
  {
    throw Standard_OutOfRange();
  }
  return tabMult->Value(Index);
}

void AppDef_MultiLine::Dump(Standard_OStream& o) const
{
  o << "AppDef_MultiLine dump:" << std::endl;

  o << "It contains " << tabMult->Length() << " MultiPointConstraint" << std::endl;
}
