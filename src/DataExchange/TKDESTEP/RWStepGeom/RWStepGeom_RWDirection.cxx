

#include <Interface_Check.hpp>
#include <Interface_ShareTool.hpp>
#include "RWStepGeom_RWDirection.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Direction.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepGeom_RWDirection::RWStepGeom_RWDirection() = default;

void RWStepGeom_RWDirection::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                      const int                                   num,
                                      occ::handle<Interface_Check>&               ach,
                                      const occ::handle<StepGeom_Direction>&      ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "direction"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  double aCoordinatesItem;
  int    aNSub2, aNbCoord = 0;
  double aXYZ[3] = {0., 0., 0.};
  if (data->ReadSubList(num, 2, "direction_ratios", ach, aNSub2))
  {
    int aNbElements = data->NbParams(aNSub2);
    if (aNbElements > 3)
    {
      ach->AddWarning("More than 3 direction ratios, ignored");
    }
    aNbCoord = std::min(aNbElements, 3);
    for (int i2 = 0; i2 < aNbCoord; i2++)
    {
      if (data->ReadReal(aNSub2, i2 + 1, "direction_ratios", ach, aCoordinatesItem))
      {
        aXYZ[i2] = aCoordinatesItem;
      }
    }
  }

  if (aNbCoord == 3)
    ent->Init3D(aName, aXYZ[0], aXYZ[1], aXYZ[2]);
  else
    ent->Init2D(aName, aXYZ[0], aXYZ[1]);
}

void RWStepGeom_RWDirection::WriteStep(StepData_StepWriter&                   SW,
                                       const occ::handle<StepGeom_Direction>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbDirectionRatios(); i2++)
  {
    SW.Send(ent->DirectionRatiosValue(i2));
  }
  SW.CloseSub();
}

void RWStepGeom_RWDirection::Check(const occ::handle<StepGeom_Direction>& ent,
                                   const Interface_ShareTool&,
                                   occ::handle<Interface_Check>& ach) const
{
  int nbVal = ent->NbDirectionRatios();
  int i;
  for (i = 1; i <= nbVal; i++)
  {
    if (std::abs(ent->DirectionRatiosValue(i)) >= RealEpsilon())
      break;
  }
  if (i > nbVal)
    ach->AddFail("ERROR: DirectionRatios all 0.0");
}
