#pragma once

#include <Standard.hpp>

#include <IGESDimen_LeaderArrow.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_LeaderArrow;

//! defines GeneralLabel, Type <210> Form <0>
//! in package IGESDimen
//! Used for general labeling with leaders
class IGESDimen_GeneralLabel : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_GeneralLabel();

  //! This method is used to set the fields of the class
  //! GeneralLabel
  //! - aNote       : General Note Entity
  //! - someLeaders : Associated Leader Entities
  Standard_EXPORT void Init(
    const occ::handle<IGESDimen_GeneralNote>&                                   aNote,
    const occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>>& someLeaders);

  //! returns General Note Entity
  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  //! returns Number of Leaders
  Standard_EXPORT int NbLeaders() const;

  //! returns Leader Entity
  //! raises exception if Index <= 0 or Index > NbLeaders()
  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> Leader(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_GeneralLabel, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote>                                   theNote;
  occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>> theLeaders;
};
