#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XY.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class gp_Pnt2d;
class gp_Pnt;

class IGESGeom_Flash : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_Flash();

  Standard_EXPORT void Init(const gp_XY&                            aPoint,
                            const double                            aDim,
                            const double                            anotherDim,
                            const double                            aRotation,
                            const occ::handle<IGESData_IGESEntity>& aReference);

  Standard_EXPORT void SetFormNumber(const int form);

  Standard_EXPORT gp_Pnt2d ReferencePoint() const;

  Standard_EXPORT gp_Pnt TransformedReferencePoint() const;

  Standard_EXPORT double Dimension1() const;

  Standard_EXPORT double Dimension2() const;

  Standard_EXPORT double Rotation() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> ReferenceEntity() const;

  Standard_EXPORT bool HasReferenceEntity() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_Flash, IGESData_IGESEntity)

private:
  gp_XY                            thePoint;
  double                           theDim1;
  double                           theDim2;
  double                           theRotation;
  occ::handle<IGESData_IGESEntity> theReference;
};
