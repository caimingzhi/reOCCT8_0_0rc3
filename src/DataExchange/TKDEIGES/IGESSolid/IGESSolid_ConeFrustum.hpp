#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;
class gp_Dir;

class IGESSolid_ConeFrustum : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_ConeFrustum();

  Standard_EXPORT void Init(const double  Ht,
                            const double  R1,
                            const double  R2,
                            const gp_XYZ& Center,
                            const gp_XYZ& anAxis);

  Standard_EXPORT double Height() const;

  Standard_EXPORT double LargerRadius() const;

  Standard_EXPORT double SmallerRadius() const;

  Standard_EXPORT gp_Pnt FaceCenter() const;

  Standard_EXPORT gp_Pnt TransformedFaceCenter() const;

  Standard_EXPORT gp_Dir Axis() const;

  Standard_EXPORT gp_Dir TransformedAxis() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_ConeFrustum, IGESData_IGESEntity)

private:
  double theHeight;
  double theR1;
  double theR2;
  gp_XYZ theFaceCenter;
  gp_XYZ theAxis;
};
