#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XY.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_LeaderArrow;
class gp_Pnt2d;
class gp_Pnt;

//! Defines IGES Radius Dimension, type <222> Form <0, 1>,
//! in package IGESDimen.
//! A Radius Dimension Entity consists of a General Note, a
//! leader, and an arc center point. A second form of this
//! entity accounts for the occasional need to have two
//! leader entities referenced.
class IGESDimen_RadiusDimension : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_RadiusDimension();

  Standard_EXPORT void Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                            const occ::handle<IGESDimen_LeaderArrow>& anArrow,
                            const gp_XY&                              arcCenter,
                            const occ::handle<IGESDimen_LeaderArrow>& anotherArrow);

  //! Allows to change Form Number
  //! (1 admits null arrow)
  Standard_EXPORT void InitForm(const int form);

  //! returns the General Note entity
  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  //! returns the Leader Arrow entity
  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> Leader() const;

  //! returns the coordinates of the Arc Center
  Standard_EXPORT gp_Pnt2d Center() const;

  //! returns the coordinates of the Arc Center after Transformation
  //! (Z coord taken from ZDepth of Leader Entity)
  Standard_EXPORT gp_Pnt TransformedCenter() const;

  //! returns True if form is 1, False if 0
  Standard_EXPORT bool HasLeader2() const;

  //! returns Null handle if Form is 0
  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> Leader2() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_RadiusDimension, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote> theNote;
  occ::handle<IGESDimen_LeaderArrow> theLeaderArrow;
  gp_XY                              theCenter;
  occ::handle<IGESDimen_LeaderArrow> theLeader2;
};
