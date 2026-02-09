#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class IGESBasic_HArray1OfHArray1OfIGESEntity;

class IGESGeom_Boundary : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_Boundary();

  Standard_EXPORT void Init(
    const int                                                                 aType,
    const int                                                                 aPreference,
    const occ::handle<IGESData_IGESEntity>&                                   aSurface,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allModelCurves,
    const occ::handle<NCollection_HArray1<int>>&                              allSenses,
    const occ::handle<IGESBasic_HArray1OfHArray1OfIGESEntity>&                allParameterCurves);

  Standard_EXPORT int BoundaryType() const;

  Standard_EXPORT int PreferenceType() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Surface() const;

  Standard_EXPORT int NbModelSpaceCurves() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> ModelSpaceCurve(const int Index) const;

  Standard_EXPORT int Sense(const int Index) const;

  Standard_EXPORT int NbParameterCurves(const int Index) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>
                  ParameterCurves(const int Index) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> ParameterCurve(const int Index,
                                                                  const int Num) const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_Boundary, IGESData_IGESEntity)

private:
  int                                                                theType;
  int                                                                thePreference;
  occ::handle<IGESData_IGESEntity>                                   theSurface;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theModelCurves;
  occ::handle<NCollection_HArray1<int>>                              theSenses;
  occ::handle<IGESBasic_HArray1OfHArray1OfIGESEntity>                theParameterCurves;
};
