#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;
class gp_Dir;

class IGESSolid_Cylinder : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_Cylinder();

  Standard_EXPORT void Init(const double  aHeight,
                            const double  aRadius,
                            const gp_XYZ& aCenter,
                            const gp_XYZ& anAxis);

  Standard_EXPORT double Height() const;

  Standard_EXPORT double Radius() const;

  Standard_EXPORT gp_Pnt FaceCenter() const;

  Standard_EXPORT gp_Pnt TransformedFaceCenter() const;

  Standard_EXPORT gp_Dir Axis() const;

  Standard_EXPORT gp_Dir TransformedAxis() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_Cylinder, IGESData_IGESEntity)

private:
  double theHeight;
  double theRadius;
  gp_XYZ theFaceCenter;
  gp_XYZ theAxis;
};
