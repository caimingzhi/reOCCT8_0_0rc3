#include <IGESBasic_HArray1OfHArray1OfIGESEntity.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESGeom_Boundary.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGeom_Boundary, IGESData_IGESEntity)

IGESGeom_Boundary::IGESGeom_Boundary() = default;

void IGESGeom_Boundary::Init(
  const int                                                                 aType,
  const int                                                                 aPreference,
  const occ::handle<IGESData_IGESEntity>&                                   aSurface,
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allModelCurves,
  const occ::handle<NCollection_HArray1<int>>&                              allSenses,
  const occ::handle<IGESBasic_HArray1OfHArray1OfIGESEntity>&                allParameterCurves)
{
  int num1 = allSenses->Length();
  if (allSenses->Lower() != 1 || (allModelCurves->Lower() != 1 || allModelCurves->Length() != num1)
      || (allParameterCurves->Lower() != 1 || allParameterCurves->Length() != num1))
    throw Standard_DimensionMismatch("IGESGeom_Boundary: Init");

  theType            = aType;
  thePreference      = aPreference;
  theSurface         = aSurface;
  theModelCurves     = allModelCurves;
  theSenses          = allSenses;
  theParameterCurves = allParameterCurves;
  InitTypeAndForm(141, 0);
}

int IGESGeom_Boundary::BoundaryType() const
{
  return theType;
}

int IGESGeom_Boundary::PreferenceType() const
{
  return thePreference;
}

occ::handle<IGESData_IGESEntity> IGESGeom_Boundary::Surface() const
{
  return theSurface;
}

int IGESGeom_Boundary::NbModelSpaceCurves() const
{
  return theModelCurves->Length();
}

int IGESGeom_Boundary::Sense(const int Index) const
{
  return theSenses->Value(Index);
}

occ::handle<IGESData_IGESEntity> IGESGeom_Boundary::ModelSpaceCurve(const int Index) const
{
  return theModelCurves->Value(Index);
}

int IGESGeom_Boundary::NbParameterCurves(const int Index) const
{
  if (theParameterCurves->Value(Index).IsNull())
    return 0;
  return theParameterCurves->Value(Index)->Length();
}

occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> IGESGeom_Boundary::
  ParameterCurves(const int Index) const
{
  return theParameterCurves->Value(Index);
}

occ::handle<IGESData_IGESEntity> IGESGeom_Boundary::ParameterCurve(const int Index,
                                                                   const int Num) const
{
  return theParameterCurves->Value(Index)->Value(Num);
}
