

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWSurfaceStyleParameterLine.hpp"
#include <Standard_Integer.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_CurveStyle.hpp>
#include <StepVisual_SurfaceStyleParameterLine.hpp>

RWStepVisual_RWSurfaceStyleParameterLine::RWStepVisual_RWSurfaceStyleParameterLine() = default;

void RWStepVisual_RWSurfaceStyleParameterLine::ReadStep(
  const occ::handle<StepData_StepReaderData>&              data,
  const int                                                num,
  occ::handle<Interface_Check>&                            ach,
  const occ::handle<StepVisual_SurfaceStyleParameterLine>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "surface_style_parameter_line"))
    return;

  occ::handle<StepVisual_CurveStyle> aStyleOfParameterLines;

  data->ReadEntity(num,
                   1,
                   "style_of_parameter_lines",
                   ach,
                   STANDARD_TYPE(StepVisual_CurveStyle),
                   aStyleOfParameterLines);

  int                     numr, numpr;
  TCollection_AsciiString UType("U_DIRECTION_COUNT");
  TCollection_AsciiString VType("V_DIRECTION_COUNT");
  TCollection_AsciiString TrueType;

  occ::handle<NCollection_HArray1<StepVisual_DirectionCountSelect>> aDirectionCounts;
  int                                                               aDirectionCountsItem;
  StepVisual_DirectionCountSelect                                   aDirectionCountSelect;

  int nsub2;
  if (data->ReadSubList(num, 2, "direction_counts", ach, nsub2))
  {
    int nb2          = data->NbParams(nsub2);
    aDirectionCounts = new NCollection_HArray1<StepVisual_DirectionCountSelect>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {

      if (data->ReadTypedParam(nsub2, i2, true, "direction_count", ach, numr, numpr, TrueType))
      {

        if (data->ReadInteger(numr, numpr, "direction_counts", ach, aDirectionCountsItem))
        {
          if (TrueType == UType)
          {
            aDirectionCountSelect.SetUDirectionCount(aDirectionCountsItem);
            aDirectionCounts->SetValue(i2, aDirectionCountSelect);
          }
          else if (TrueType == VType)
          {
            aDirectionCountSelect.SetVDirectionCount(aDirectionCountsItem);
            aDirectionCounts->SetValue(i2, aDirectionCountSelect);
          }
          else
          {
            ach->AddFail("Parameter #2 (direction_counts) item has illegal TYPE");
          }
        }
        else
        {
          ach->AddFail("Parameter #2 (direction_counts) item is not an INTEGER");
        }
      }
      else
      {
        ach->AddFail("Parameter #2 (direction_counts) item is not TYPED");
      }
    }
  }

  ent->Init(aStyleOfParameterLines, aDirectionCounts);
}

void RWStepVisual_RWSurfaceStyleParameterLine::WriteStep(
  StepData_StepWriter&                                     SW,
  const occ::handle<StepVisual_SurfaceStyleParameterLine>& ent) const
{

  SW.Send(ent->StyleOfParameterLines());

  SW.Send(ent->DirectionCounts());
}

void RWStepVisual_RWSurfaceStyleParameterLine::Share(
  const occ::handle<StepVisual_SurfaceStyleParameterLine>& ent,
  Interface_EntityIterator&                                iter) const
{

  iter.GetOneItem(ent->StyleOfParameterLines());
}
