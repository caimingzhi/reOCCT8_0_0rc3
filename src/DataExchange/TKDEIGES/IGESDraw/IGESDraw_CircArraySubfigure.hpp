#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;

class IGESDraw_CircArraySubfigure : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDraw_CircArraySubfigure();

  Standard_EXPORT void Init(const occ::handle<IGESData_IGESEntity>&      aBase,
                            const int                                    aNumLocs,
                            const gp_XYZ&                                aCenter,
                            const double                                 aRadius,
                            const double                                 aStAngle,
                            const double                                 aDelAngle,
                            const int                                    aFlag,
                            const occ::handle<NCollection_HArray1<int>>& allNumPos);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> BaseEntity() const;

  Standard_EXPORT int NbLocations() const;

  Standard_EXPORT gp_Pnt CenterPoint() const;

  Standard_EXPORT gp_Pnt TransformedCenterPoint() const;

  Standard_EXPORT double CircleRadius() const;

  Standard_EXPORT double StartAngle() const;

  Standard_EXPORT double DeltaAngle() const;

  Standard_EXPORT int ListCount() const;

  Standard_EXPORT bool DisplayFlag() const;

  Standard_EXPORT bool DoDontFlag() const;

  Standard_EXPORT bool PositionNum(const int Index) const;

  Standard_EXPORT int ListPosition(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_CircArraySubfigure, IGESData_IGESEntity)

private:
  occ::handle<IGESData_IGESEntity>      theBaseEntity;
  int                                   theNbLocations;
  gp_XYZ                                theCenter;
  double                                theRadius;
  double                                theStartAngle;
  double                                theDeltaAngle;
  bool                                  theDoDontFlag;
  occ::handle<NCollection_HArray1<int>> thePositions;
};
