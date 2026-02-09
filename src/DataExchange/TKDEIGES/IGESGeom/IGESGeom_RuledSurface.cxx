#include <IGESGeom_RuledSurface.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGeom_RuledSurface, IGESData_IGESEntity)

IGESGeom_RuledSurface::IGESGeom_RuledSurface() = default;

void IGESGeom_RuledSurface::Init(const occ::handle<IGESData_IGESEntity>& aCurve,
                                 const occ::handle<IGESData_IGESEntity>& anotherCurve,
                                 const int                               aDirFlag,
                                 const int                               aDevFlag)
{
  theCurve1  = aCurve;
  theCurve2  = anotherCurve;
  theDirFlag = aDirFlag;
  theDevFlag = aDevFlag;
  InitTypeAndForm(118, FormNumber());
}

void IGESGeom_RuledSurface::SetRuledByParameter(const bool F)
{
  InitTypeAndForm(118, (F ? 1 : 0));
}

occ::handle<IGESData_IGESEntity> IGESGeom_RuledSurface::FirstCurve() const
{
  return theCurve1;
}

occ::handle<IGESData_IGESEntity> IGESGeom_RuledSurface::SecondCurve() const
{
  return theCurve2;
}

int IGESGeom_RuledSurface::DirectionFlag() const
{
  return theDirFlag;
}

bool IGESGeom_RuledSurface::IsDevelopable() const
{
  return (theDevFlag == 1);
}

bool IGESGeom_RuledSurface::IsRuledByParameter() const
{
  return (FormNumber() != 0);
}
