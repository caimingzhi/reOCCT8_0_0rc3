#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <gp_XY.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt2d;

class IGESDimen_BasicDimension : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_BasicDimension();

  Standard_EXPORT void Init(const int    nbPropVal,
                            const gp_XY& lowerLeft,
                            const gp_XY& lowerRight,
                            const gp_XY& upperRight,
                            const gp_XY& upperLeft);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT gp_Pnt2d LowerLeft() const;

  Standard_EXPORT gp_Pnt2d LowerRight() const;

  Standard_EXPORT gp_Pnt2d UpperRight() const;

  Standard_EXPORT gp_Pnt2d UpperLeft() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_BasicDimension, IGESData_IGESEntity)

private:
  int   theNbPropertyValues;
  gp_XY theLowerLeft;
  gp_XY theLowerRight;
  gp_XY theUpperRight;
  gp_XY theUpperLeft;
};
