#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESBasic_SubfigureDef;

class IGESBasic_SingularSubfigure : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_SingularSubfigure();

  Standard_EXPORT void Init(const occ::handle<IGESBasic_SubfigureDef>& aSubfigureDef,
                            const gp_XYZ&                              aTranslation,
                            const bool                                 hasScale,
                            const double                               aScale);

  Standard_EXPORT occ::handle<IGESBasic_SubfigureDef> Subfigure() const;

  Standard_EXPORT gp_XYZ Translation() const;

  Standard_EXPORT double ScaleFactor() const;

  Standard_EXPORT bool HasScaleFactor() const;

  Standard_EXPORT gp_XYZ TransformedTranslation() const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_SingularSubfigure, IGESData_IGESEntity)

private:
  occ::handle<IGESBasic_SubfigureDef> theSubfigureDef;
  gp_XYZ                              theTranslation;
  double                              theScaleFactor;
  bool                                hasScaleFactor;
};
