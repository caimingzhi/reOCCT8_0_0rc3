

#include <Interface_Check.hpp>
#include "RWStepGeom_RWCartesianPoint.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <TCollection_HAsciiString.hpp>

RWStepGeom_RWCartesianPoint::RWStepGeom_RWCartesianPoint() = default;

void RWStepGeom_RWCartesianPoint::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<StepGeom_CartesianPoint>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "cartesian_point"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  if (!data->ReadString(num, 1, "name", ach, aName))
  {
    ach->Mend("Set to empty string");
    aName = new TCollection_HAsciiString;
  }

  double aCoordinatesItem;
  int    nsub2, nbcoord = 0;
  double XYZ[3] = {0., 0., 0.};
  if (data->ReadSubList(num, 2, "coordinates", ach, nsub2))
  {
    int nb2 = data->NbParams(nsub2);
    if (nb2 > 3)
    {
      ach->AddWarning("More than 3 coordinates, ignored");
    }
    nbcoord = std::min(nb2, 3);
    for (int i2 = 0; i2 < nbcoord; i2++)
    {
      if (data->ReadReal(nsub2, i2 + 1, "coordinates", ach, aCoordinatesItem))
      {
        XYZ[i2] = aCoordinatesItem;
      }
    }
  }

  if (nbcoord == 3)
    ent->Init3D(aName, XYZ[0], XYZ[1], XYZ[2]);
  else
    ent->Init2D(aName, XYZ[0], XYZ[1]);
}

void RWStepGeom_RWCartesianPoint::WriteStep(StepData_StepWriter&                        SW,
                                            const occ::handle<StepGeom_CartesianPoint>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbCoordinates(); i2++)
  {
    SW.Send(ent->CoordinatesValue(i2));
  }
  SW.CloseSub();
}
