#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_WitnessLine;
class IGESDimen_LeaderArrow;

class IGESDimen_OrdinateDimension : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_OrdinateDimension();

  Standard_EXPORT void Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                            const bool                                aType,
                            const occ::handle<IGESDimen_WitnessLine>& aLine,
                            const occ::handle<IGESDimen_LeaderArrow>& anArrow);

  Standard_EXPORT bool IsLine() const;

  Standard_EXPORT bool IsLeader() const;

  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  Standard_EXPORT occ::handle<IGESDimen_WitnessLine> WitnessLine() const;

  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> Leader() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_OrdinateDimension, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote> theNote;
  bool                               isItLine;
  occ::handle<IGESDimen_WitnessLine> theWitnessLine;
  occ::handle<IGESDimen_LeaderArrow> theLeader;
};
