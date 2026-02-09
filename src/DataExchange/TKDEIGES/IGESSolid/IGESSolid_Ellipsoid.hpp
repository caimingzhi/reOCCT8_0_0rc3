#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;
class gp_Dir;

class IGESSolid_Ellipsoid : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_Ellipsoid();

  Standard_EXPORT void Init(const gp_XYZ& aSize,
                            const gp_XYZ& aCenter,
                            const gp_XYZ& anXAxis,
                            const gp_XYZ& anZAxis);

  Standard_EXPORT gp_XYZ Size() const;

  Standard_EXPORT double XLength() const;

  Standard_EXPORT double YLength() const;

  Standard_EXPORT double ZLength() const;

  Standard_EXPORT gp_Pnt Center() const;

  Standard_EXPORT gp_Pnt TransformedCenter() const;

  Standard_EXPORT gp_Dir XAxis() const;

  Standard_EXPORT gp_Dir TransformedXAxis() const;

  Standard_EXPORT gp_Dir YAxis() const;

  Standard_EXPORT gp_Dir TransformedYAxis() const;

  Standard_EXPORT gp_Dir ZAxis() const;

  Standard_EXPORT gp_Dir TransformedZAxis() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_Ellipsoid, IGESData_IGESEntity)

private:
  gp_XYZ theSize;
  gp_XYZ theCenter;
  gp_XYZ theXAxis;
  gp_XYZ theZAxis;
};
