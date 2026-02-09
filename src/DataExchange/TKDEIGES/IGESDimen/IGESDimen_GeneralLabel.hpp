#pragma once

#include <Standard.hpp>

#include <IGESDimen_LeaderArrow.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_LeaderArrow;

class IGESDimen_GeneralLabel : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_GeneralLabel();

  Standard_EXPORT void Init(
    const occ::handle<IGESDimen_GeneralNote>&                                   aNote,
    const occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>>& someLeaders);

  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  Standard_EXPORT int NbLeaders() const;

  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> Leader(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_GeneralLabel, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote>                                   theNote;
  occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>> theLeaders;
};
