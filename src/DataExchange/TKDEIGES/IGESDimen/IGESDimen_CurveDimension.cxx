#include <IGESDimen_CurveDimension.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <IGESDimen_WitnessLine.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_CurveDimension, IGESData_IGESEntity)

IGESDimen_CurveDimension::IGESDimen_CurveDimension() = default;

void IGESDimen_CurveDimension::Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                                    const occ::handle<IGESData_IGESEntity>&   aCurve,
                                    const occ::handle<IGESData_IGESEntity>&   anotherCurve,
                                    const occ::handle<IGESDimen_LeaderArrow>& aLeader,
                                    const occ::handle<IGESDimen_LeaderArrow>& anotherLeader,
                                    const occ::handle<IGESDimen_WitnessLine>& aLine,
                                    const occ::handle<IGESDimen_WitnessLine>& anotherLine)
{
  theNote              = aNote;
  theFirstCurve        = aCurve;
  theSecondCurve       = anotherCurve;
  theFirstLeader       = aLeader;
  theSecondLeader      = anotherLeader;
  theFirstWitnessLine  = aLine;
  theSecondWitnessLine = anotherLine;
  InitTypeAndForm(204, 0);
}

occ::handle<IGESDimen_GeneralNote> IGESDimen_CurveDimension::Note() const
{
  return theNote;
}

occ::handle<IGESData_IGESEntity> IGESDimen_CurveDimension::FirstCurve() const
{
  return theFirstCurve;
}

bool IGESDimen_CurveDimension::HasSecondCurve() const
{
  return (!theSecondCurve.IsNull());
}

occ::handle<IGESData_IGESEntity> IGESDimen_CurveDimension::SecondCurve() const
{
  return theSecondCurve;
}

occ::handle<IGESDimen_LeaderArrow> IGESDimen_CurveDimension::FirstLeader() const
{
  return theFirstLeader;
}

occ::handle<IGESDimen_LeaderArrow> IGESDimen_CurveDimension::SecondLeader() const
{
  return theSecondLeader;
}

bool IGESDimen_CurveDimension::HasFirstWitnessLine() const
{
  return (!theFirstWitnessLine.IsNull());
}

occ::handle<IGESDimen_WitnessLine> IGESDimen_CurveDimension::FirstWitnessLine() const
{
  return theFirstWitnessLine;
}

bool IGESDimen_CurveDimension::HasSecondWitnessLine() const
{
  return (!theSecondWitnessLine.IsNull());
}

occ::handle<IGESDimen_WitnessLine> IGESDimen_CurveDimension::SecondWitnessLine() const
{
  return theSecondWitnessLine;
}
