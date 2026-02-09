#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_LeaderArrow;
class IGESDimen_WitnessLine;

class IGESDimen_LinearDimension : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_LinearDimension();

  Standard_EXPORT void Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                            const occ::handle<IGESDimen_LeaderArrow>& aLeader,
                            const occ::handle<IGESDimen_LeaderArrow>& anotherLeader,
                            const occ::handle<IGESDimen_WitnessLine>& aWitness,
                            const occ::handle<IGESDimen_WitnessLine>& anotherWitness);

  Standard_EXPORT void SetFormNumber(const int form);

  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> FirstLeader() const;

  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> SecondLeader() const;

  Standard_EXPORT bool HasFirstWitness() const;

  Standard_EXPORT occ::handle<IGESDimen_WitnessLine> FirstWitness() const;

  Standard_EXPORT bool HasSecondWitness() const;

  Standard_EXPORT occ::handle<IGESDimen_WitnessLine> SecondWitness() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_LinearDimension, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote> theNote;
  occ::handle<IGESDimen_LeaderArrow> theFirstLeader;
  occ::handle<IGESDimen_LeaderArrow> theSecondLeader;
  occ::handle<IGESDimen_WitnessLine> theFirstWitness;
  occ::handle<IGESDimen_WitnessLine> theSecondWitness;
};
