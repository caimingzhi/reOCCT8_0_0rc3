

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWPresentationStyleByContext.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_NullStyleMember.hpp>
#include <StepVisual_PresentationStyleByContext.hpp>
#include <StepVisual_PresentationStyleSelect.hpp>
#include <StepVisual_StyleContextSelect.hpp>

RWStepVisual_RWPresentationStyleByContext::RWStepVisual_RWPresentationStyleByContext() = default;

void RWStepVisual_RWPresentationStyleByContext::ReadStep(
  const occ::handle<StepData_StepReaderData>&               data,
  const int                                                 num,
  occ::handle<Interface_Check>&                             ach,
  const occ::handle<StepVisual_PresentationStyleByContext>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "presentation_style_by_context"))
    return;

  occ::handle<NCollection_HArray1<StepVisual_PresentationStyleSelect>> aStyles;
  StepVisual_PresentationStyleSelect                                   aStylesItem;
  int                                                                  nsub1;
  if (data->ReadSubList(num, 1, "styles", ach, nsub1))
  {
    int nb1 = data->NbParams(nsub1);
    aStyles = new NCollection_HArray1<StepVisual_PresentationStyleSelect>(1, nb1);
    for (int i1 = 1; i1 <= nb1; i1++)
    {
      Interface_ParamType aType = data->ParamType(nsub1, i1);
      if (aType == Interface_ParamIdent)
      {
        data->ReadEntity(nsub1, i1, "styles", ach, aStylesItem);
      }
      else
      {
        occ::handle<StepData_SelectMember> aMember;
        data->ReadMember(nsub1, i1, "null_style", ach, aMember);
        const char*                             anEnumText = aMember->EnumText();
        occ::handle<StepVisual_NullStyleMember> aNullStyle = new StepVisual_NullStyleMember();
        aNullStyle->SetEnumText(0, anEnumText);
        aStylesItem.SetValue(aNullStyle);
      }
      aStyles->SetValue(i1, aStylesItem);
    }
  }

  StepVisual_StyleContextSelect aStyleContext;

  data->ReadEntity(num, 2, "style_context", ach, aStyleContext);

  ent->Init(aStyles, aStyleContext);
}

void RWStepVisual_RWPresentationStyleByContext::WriteStep(
  StepData_StepWriter&                                      SW,
  const occ::handle<StepVisual_PresentationStyleByContext>& ent) const
{

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->NbStyles(); i1++)
  {
    StepVisual_PresentationStyleSelect aStyle = ent->StylesValue(i1);
    if (aStyle.Value()->IsKind(STANDARD_TYPE(StepVisual_NullStyleMember)))
    {
      SW.OpenTypedSub("NULL_STYLE");
      SW.SendEnum(".NULL.");
      SW.CloseSub();
    }
    else
      SW.Send(aStyle.Value());
  }
  SW.CloseSub();

  SW.Send(ent->StyleContext().Value());
}

void RWStepVisual_RWPresentationStyleByContext::Share(
  const occ::handle<StepVisual_PresentationStyleByContext>& ent,
  Interface_EntityIterator&                                 iter) const
{

  int nbElem1 = ent->NbStyles();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->StylesValue(is1).Value());
  }

  iter.GetOneItem(ent->StyleContext().Value());
}
