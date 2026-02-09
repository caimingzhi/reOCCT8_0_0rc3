#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_LineFontEntity.hpp>
class IGESBasic_SubfigureDef;

class IGESGraph_LineFontDefTemplate : public IGESData_LineFontEntity
{

public:
  Standard_EXPORT IGESGraph_LineFontDefTemplate();

  Standard_EXPORT void Init(const int                                  anOrientation,
                            const occ::handle<IGESBasic_SubfigureDef>& aTemplate,
                            const double                               aDistance,
                            const double                               aScale);

  Standard_EXPORT int Orientation() const;

  Standard_EXPORT occ::handle<IGESBasic_SubfigureDef> TemplateEntity() const;

  Standard_EXPORT double Distance() const;

  Standard_EXPORT double Scale() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_LineFontDefTemplate, IGESData_LineFontEntity)

private:
  int                                 theOrientation;
  occ::handle<IGESBasic_SubfigureDef> theTemplateEntity;
  double                              theDistance;
  double                              theScale;
};
