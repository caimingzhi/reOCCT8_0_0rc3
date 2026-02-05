#include <IGESBasic_SubfigureDef.hpp>
#include <IGESGraph_LineFontDefTemplate.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGraph_LineFontDefTemplate, IGESData_LineFontEntity)

IGESGraph_LineFontDefTemplate::IGESGraph_LineFontDefTemplate() = default;

// This class inherits from IGESData_LineFontEntity

void IGESGraph_LineFontDefTemplate::Init(const int                                  anOrientation,
                                         const occ::handle<IGESBasic_SubfigureDef>& aTemplate,
                                         const double                               aDistance,
                                         const double                               aScale)
{
  theOrientation    = anOrientation;
  theTemplateEntity = aTemplate;
  theDistance       = aDistance;
  theScale          = aScale;
  InitTypeAndForm(304, 1);
}

int IGESGraph_LineFontDefTemplate::Orientation() const
{
  return theOrientation;
}

occ::handle<IGESBasic_SubfigureDef> IGESGraph_LineFontDefTemplate::TemplateEntity() const
{
  return theTemplateEntity;
}

double IGESGraph_LineFontDefTemplate::Distance() const
{
  return theDistance;
}

double IGESGraph_LineFontDefTemplate::Scale() const
{
  return theScale;
}
