#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESBasic_SubfigureDef;
class gp_Pnt;

class IGESGeom_Point : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_Point();

  Standard_EXPORT void Init(const gp_XYZ&                              aPoint,
                            const occ::handle<IGESBasic_SubfigureDef>& aSymbol);

  Standard_EXPORT gp_Pnt Value() const;

  Standard_EXPORT gp_Pnt TransformedValue() const;

  Standard_EXPORT bool HasDisplaySymbol() const;

  Standard_EXPORT occ::handle<IGESBasic_SubfigureDef> DisplaySymbol() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_Point, IGESData_IGESEntity)

private:
  gp_XYZ                              thePoint;
  occ::handle<IGESBasic_SubfigureDef> theSymbol;
};
