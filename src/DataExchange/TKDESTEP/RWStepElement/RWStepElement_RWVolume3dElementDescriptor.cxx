#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepElement_RWVolume3dElementDescriptor.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepElement_Volume3dElementDescriptor.hpp>
#include <StepElement_VolumeElementPurposeMember.hpp>

RWStepElement_RWVolume3dElementDescriptor::RWStepElement_RWVolume3dElementDescriptor() = default;

void RWStepElement_RWVolume3dElementDescriptor::ReadStep(
  const occ::handle<StepData_StepReaderData>&               data,
  const int                                                 num,
  occ::handle<Interface_Check>&                             ach,
  const occ::handle<StepElement_Volume3dElementDescriptor>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "volume3d_element_descriptor"))
    return;

  StepElement_ElementOrder aElementDescriptor_TopologyOrder = StepElement_Linear;
  if (data->ParamType(num, 1) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 1);
    if (!strcmp(text, ".LINEAR."))
      aElementDescriptor_TopologyOrder = StepElement_Linear;
    else if (!strcmp(text, ".QUADRATIC."))
      aElementDescriptor_TopologyOrder = StepElement_Quadratic;
    else if (!strcmp(text, ".CUBIC."))
      aElementDescriptor_TopologyOrder = StepElement_Cubic;
    else
      ach->AddFail("Parameter #1 (element_descriptor.topology_order) has not allowed value");
  }
  else
    ach->AddFail("Parameter #1 (element_descriptor.topology_order) is not enumeration");

  occ::handle<TCollection_HAsciiString> aElementDescriptor_Description;
  data->ReadString(num, 2, "element_descriptor.description", ach, aElementDescriptor_Description);

  occ::handle<NCollection_HArray1<occ::handle<StepElement_VolumeElementPurposeMember>>> aPurpose;
  int                                                                                   sub3 = 0;
  if (data->ReadSubList(num, 3, "purpose", ach, sub3))
  {
    int nb0  = data->NbParams(sub3);
    aPurpose = new NCollection_HArray1<occ::handle<StepElement_VolumeElementPurposeMember>>(1, nb0);
    int num2 = sub3;
    for (int i0 = 1; i0 <= nb0; i0++)
    {

      occ::handle<StepElement_VolumeElementPurposeMember> aMember =
        new StepElement_VolumeElementPurposeMember;

      data->ReadMember(num2, i0, "volume_element_purpose", ach, aMember);
      aPurpose->SetValue(i0, aMember);
    }
  }

  StepElement_Volume3dElementShape aShape = StepElement_Hexahedron;
  if (data->ParamType(num, 4) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 4);
    if (!strcmp(text, ".HEXAHEDRON."))
      aShape = StepElement_Hexahedron;
    else if (!strcmp(text, ".WEDGE."))
      aShape = StepElement_Wedge;
    else if (!strcmp(text, ".TETRAHEDRON."))
      aShape = StepElement_Tetrahedron;
    else if (!strcmp(text, ".PYRAMID."))
      aShape = StepElement_Pyramid;
    else
      ach->AddFail("Parameter #4 (shape) has not allowed value");
  }
  else
    ach->AddFail("Parameter #4 (shape) is not enumeration");

  ent->Init(aElementDescriptor_TopologyOrder, aElementDescriptor_Description, aPurpose, aShape);
}

void RWStepElement_RWVolume3dElementDescriptor::WriteStep(
  StepData_StepWriter&                                      SW,
  const occ::handle<StepElement_Volume3dElementDescriptor>& ent) const
{

  switch (ent->StepElement_ElementDescriptor::TopologyOrder())
  {
    case StepElement_Linear:
      SW.SendEnum(".LINEAR.");
      break;
    case StepElement_Quadratic:
      SW.SendEnum(".QUADRATIC.");
      break;
    case StepElement_Cubic:
      SW.SendEnum(".CUBIC.");
      break;
  }

  SW.Send(ent->StepElement_ElementDescriptor::Description());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->Purpose()->Length(); i2++)
  {
    occ::handle<StepElement_VolumeElementPurposeMember> Var0 = ent->Purpose()->Value(i2);
    SW.Send(Var0);
  }
  SW.CloseSub();

  switch (ent->Shape())
  {
    case StepElement_Hexahedron:
      SW.SendEnum(".HEXAHEDRON.");
      break;
    case StepElement_Wedge:
      SW.SendEnum(".WEDGE.");
      break;
    case StepElement_Tetrahedron:
      SW.SendEnum(".TETRAHEDRON.");
      break;
    case StepElement_Pyramid:
      SW.SendEnum(".PYRAMID.");
      break;
  }
}

void RWStepElement_RWVolume3dElementDescriptor::Share(
  const occ::handle<StepElement_Volume3dElementDescriptor>&,
  Interface_EntityIterator&) const
{
}
