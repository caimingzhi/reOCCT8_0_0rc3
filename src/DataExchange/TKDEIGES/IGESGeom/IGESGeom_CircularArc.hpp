#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XY.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt2d;
class gp_Pnt;
class gp_Dir;

class IGESGeom_CircularArc : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_CircularArc();

  Standard_EXPORT void Init(const double aZT,
                            const gp_XY& aCenter,
                            const gp_XY& aStart,
                            const gp_XY& anEnd);

  Standard_EXPORT gp_Pnt2d Center() const;

  Standard_EXPORT gp_Pnt TransformedCenter() const;

  Standard_EXPORT gp_Pnt2d StartPoint() const;

  Standard_EXPORT gp_Pnt TransformedStartPoint() const;

  Standard_EXPORT double ZPlane() const;

  Standard_EXPORT gp_Pnt2d EndPoint() const;

  Standard_EXPORT gp_Pnt TransformedEndPoint() const;

  Standard_EXPORT double Radius() const;

  Standard_EXPORT double Angle() const;

  Standard_EXPORT gp_Dir Axis() const;

  Standard_EXPORT gp_Dir TransformedAxis() const;

  Standard_EXPORT bool IsClosed() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_CircularArc, IGESData_IGESEntity)

private:
  double theZT;
  gp_XY  theCenter;
  gp_XY  theStart;
  gp_XY  theEnd;
};
