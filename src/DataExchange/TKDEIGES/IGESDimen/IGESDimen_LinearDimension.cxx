#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <IGESDimen_LinearDimension.hpp>
#include <IGESDimen_WitnessLine.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_LinearDimension, IGESData_IGESEntity)

IGESDimen_LinearDimension::IGESDimen_LinearDimension() = default;

void IGESDimen_LinearDimension::Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                                     const occ::handle<IGESDimen_LeaderArrow>& aLeader,
                                     const occ::handle<IGESDimen_LeaderArrow>& anotherLeader,
                                     const occ::handle<IGESDimen_WitnessLine>& aWitness,
                                     const occ::handle<IGESDimen_WitnessLine>& anotherWitness)
{
  theNote          = aNote;
  theFirstLeader   = aLeader;
  theSecondLeader  = anotherLeader;
  theFirstWitness  = aWitness;
  theSecondWitness = anotherWitness;
  InitTypeAndForm(216, FormNumber());
}

void IGESDimen_LinearDimension::SetFormNumber(const int fm)
{
  if (fm < 0 || fm > 2)
    throw Standard_OutOfRange("IGESDimen_LinearDimension : SetFormNumber");
  InitTypeAndForm(216, fm);
}

occ::handle<IGESDimen_GeneralNote> IGESDimen_LinearDimension::Note() const
{
  return theNote;
}

occ::handle<IGESDimen_LeaderArrow> IGESDimen_LinearDimension::FirstLeader() const
{
  return theFirstLeader;
}

occ::handle<IGESDimen_LeaderArrow> IGESDimen_LinearDimension::SecondLeader() const
{
  return theSecondLeader;
}

bool IGESDimen_LinearDimension::HasFirstWitness() const
{
  return (!theFirstWitness.IsNull());
}

occ::handle<IGESDimen_WitnessLine> IGESDimen_LinearDimension::FirstWitness() const
{
  return theFirstWitness;
}

bool IGESDimen_LinearDimension::HasSecondWitness() const
{
  return (!theSecondWitness.IsNull());
}

occ::handle<IGESDimen_WitnessLine> IGESDimen_LinearDimension::SecondWitness() const
{
  return theSecondWitness;
}
