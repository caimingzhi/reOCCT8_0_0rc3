#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <Standard_Integer.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_LeaderArrow;

//! defines General Symbol, Type <228>, Form <0-3,5001-9999>
//! in package IGESDimen
//! Consists of zero or one (Form 0) or one (all other
//! forms), one or more geometry entities which define
//! a symbol, and zero, one or more associated leaders.
class IGESDimen_GeneralSymbol : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_GeneralSymbol();

  //! This method is used to set the fields of the class
  //! GeneralSymbol
  //! - aNote      : General Note, null for form 0
  //! - allGeoms   : Geometric Entities
  //! - allLeaders : Leader Arrows
  Standard_EXPORT void Init(
    const occ::handle<IGESDimen_GeneralNote>&                                   aNote,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&   allGeoms,
    const occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>>& allLeaders);

  //! Changes FormNumber (indicates the Nature of the Symbol)
  //! Error if not in ranges [0-3] or [> 5000]
  Standard_EXPORT void SetFormNumber(const int form);

  //! returns True if there is associated General Note Entity
  Standard_EXPORT bool HasNote() const;

  //! returns Null handle for form 0 only
  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  //! returns number of Geometry Entities
  Standard_EXPORT int NbGeomEntities() const;

  //! returns the Index'th Geometry Entity
  //! raises exception if Index <= 0 or Index > NbGeomEntities()
  Standard_EXPORT occ::handle<IGESData_IGESEntity> GeomEntity(const int Index) const;

  //! returns number of Leaders or zero if not specified
  Standard_EXPORT int NbLeaders() const;

  //! returns the Index'th Leader Arrow
  //! raises exception if Index <= 0 or Index > NbLeaders()
  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> LeaderArrow(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_GeneralSymbol, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote>                                   theNote;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>   theGeoms;
  occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>> theLeaders;
};
