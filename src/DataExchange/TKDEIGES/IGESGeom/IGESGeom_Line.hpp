#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class gp_Pnt;

class IGESGeom_Line : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_Line();

  Standard_EXPORT void Init(const gp_XYZ& aStart, const gp_XYZ& anEnd);

  Standard_EXPORT int Infinite() const;

  Standard_EXPORT void SetInfinite(const int status);

  Standard_EXPORT gp_Pnt StartPoint() const;

  Standard_EXPORT gp_Pnt TransformedStartPoint() const;

  Standard_EXPORT gp_Pnt EndPoint() const;

  Standard_EXPORT gp_Pnt TransformedEndPoint() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_Line, IGESData_IGESEntity)

private:
  gp_XYZ theStart;
  gp_XYZ theEnd;
};
