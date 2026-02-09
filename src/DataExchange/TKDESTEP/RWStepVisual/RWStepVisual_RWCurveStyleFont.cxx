

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWCurveStyleFont.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_CurveStyleFont.hpp>
#include <StepVisual_CurveStyleFontPattern.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepVisual_RWCurveStyleFont::RWStepVisual_RWCurveStyleFont() = default;

void RWStepVisual_RWCurveStyleFont::ReadStep(
  const occ::handle<StepData_StepReaderData>&   data,
  const int                                     num,
  occ::handle<Interface_Check>&                 ach,
  const occ::handle<StepVisual_CurveStyleFont>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "curve_style_font"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<occ::handle<StepVisual_CurveStyleFontPattern>>> aPatternList;
  occ::handle<StepVisual_CurveStyleFontPattern>                                   anent2;
  int                                                                             nsub2;
  if (data->ReadSubList(num, 2, "pattern_list", ach, nsub2))
  {
    int nb2      = data->NbParams(nsub2);
    aPatternList = new NCollection_HArray1<occ::handle<StepVisual_CurveStyleFontPattern>>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {

      if (data->ReadEntity(nsub2,
                           i2,
                           "curve_style_font_pattern",
                           ach,
                           STANDARD_TYPE(StepVisual_CurveStyleFontPattern),
                           anent2))
        aPatternList->SetValue(i2, anent2);
    }
  }

  ent->Init(aName, aPatternList);
}

void RWStepVisual_RWCurveStyleFont::WriteStep(
  StepData_StepWriter&                          SW,
  const occ::handle<StepVisual_CurveStyleFont>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbPatternList(); i2++)
  {
    SW.Send(ent->PatternListValue(i2));
  }
  SW.CloseSub();
}

void RWStepVisual_RWCurveStyleFont::Share(const occ::handle<StepVisual_CurveStyleFont>& ent,
                                          Interface_EntityIterator&                     iter) const
{

  int nbElem1 = ent->NbPatternList();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->PatternListValue(is1));
  }
}
