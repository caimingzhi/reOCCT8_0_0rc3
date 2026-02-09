

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepVisual_ExternallyDefinedTextFont.hpp>
#include <StepVisual_FontSelect.hpp>
#include <StepVisual_PreDefinedTextFont.hpp>

StepVisual_FontSelect::StepVisual_FontSelect() = default;

int StepVisual_FontSelect::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PreDefinedTextFont)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_ExternallyDefinedTextFont)))
    return 2;
  return 0;
}

occ::handle<StepVisual_PreDefinedTextFont> StepVisual_FontSelect::PreDefinedTextFont() const
{
  return GetCasted(StepVisual_PreDefinedTextFont, Value());
}

occ::handle<StepVisual_ExternallyDefinedTextFont> StepVisual_FontSelect::ExternallyDefinedTextFont()
  const
{
  return GetCasted(StepVisual_ExternallyDefinedTextFont, Value());
}
