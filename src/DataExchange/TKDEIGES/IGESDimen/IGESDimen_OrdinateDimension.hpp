#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_WitnessLine;
class IGESDimen_LeaderArrow;

//! defines IGES Ordinate Dimension, Type <218> Form <0, 1>,
//! in package IGESDimen
//! Note: The ordinate dimension entity is used to
//! indicate dimensions from a common base line.
//! Dimensioning is only permitted along the XT
//! or YT axis.
class IGESDimen_OrdinateDimension : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_OrdinateDimension();

  Standard_EXPORT void Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                            const bool                                aType,
                            const occ::handle<IGESDimen_WitnessLine>& aLine,
                            const occ::handle<IGESDimen_LeaderArrow>& anArrow);

  //! returns True if Witness Line and False if Leader (only for Form 0)
  Standard_EXPORT bool IsLine() const;

  //! returns True if Leader and False if Witness Line (only for Form 0)
  Standard_EXPORT bool IsLeader() const;

  //! returns the General Note entity associated.
  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  //! returns the Witness Line associated or Null handle
  Standard_EXPORT occ::handle<IGESDimen_WitnessLine> WitnessLine() const;

  //! returns the Leader associated or Null handle
  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> Leader() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_OrdinateDimension, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote> theNote;
  bool                               isItLine;
  occ::handle<IGESDimen_WitnessLine> theWitnessLine;
  occ::handle<IGESDimen_LeaderArrow> theLeader;
};

