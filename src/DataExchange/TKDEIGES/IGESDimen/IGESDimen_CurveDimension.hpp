#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_LeaderArrow;
class IGESDimen_WitnessLine;

class IGESDimen_CurveDimension : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_CurveDimension();

  Standard_EXPORT void Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                            const occ::handle<IGESData_IGESEntity>&   aCurve,
                            const occ::handle<IGESData_IGESEntity>&   anotherCurve,
                            const occ::handle<IGESDimen_LeaderArrow>& aLeader,
                            const occ::handle<IGESDimen_LeaderArrow>& anotherLeader,
                            const occ::handle<IGESDimen_WitnessLine>& aLine,
                            const occ::handle<IGESDimen_WitnessLine>& anotherLine);

  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> FirstCurve() const;

  Standard_EXPORT bool HasSecondCurve() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> SecondCurve() const;

  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> FirstLeader() const;

  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> SecondLeader() const;

  Standard_EXPORT bool HasFirstWitnessLine() const;

  Standard_EXPORT occ::handle<IGESDimen_WitnessLine> FirstWitnessLine() const;

  Standard_EXPORT bool HasSecondWitnessLine() const;

  Standard_EXPORT occ::handle<IGESDimen_WitnessLine> SecondWitnessLine() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_CurveDimension, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote> theNote;
  occ::handle<IGESData_IGESEntity>   theFirstCurve;
  occ::handle<IGESData_IGESEntity>   theSecondCurve;
  occ::handle<IGESDimen_LeaderArrow> theFirstLeader;
  occ::handle<IGESDimen_LeaderArrow> theSecondLeader;
  occ::handle<IGESDimen_WitnessLine> theFirstWitnessLine;
  occ::handle<IGESDimen_WitnessLine> theSecondWitnessLine;
};
