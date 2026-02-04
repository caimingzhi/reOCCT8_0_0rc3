#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_LeaderArrow;
class IGESGeom_CircularArc;
class IGESGeom_CompositeCurve;

//! defines IGES Point Dimension, Type <220> Form <0>,
//! in package IGESDimen
//! A Point Dimension Entity consists of a leader, text, and
//! an optional circle or hexagon enclosing the text
//! IGES specs for this entity mention SimpleClosedPlanarCurve
//! Entity(106/63)which is not listed in LIST.Text In the sequel
//! we have ignored this & considered only the other two entity
//! for representing the hexagon or circle enclosing the text.
class IGESDimen_PointDimension : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_PointDimension();

  Standard_EXPORT void Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                            const occ::handle<IGESDimen_LeaderArrow>& anArrow,
                            const occ::handle<IGESData_IGESEntity>&   aGeom);

  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> LeaderArrow() const;

  //! returns the type of geometric entity.
  //! 0 if no hexagon or circle encloses the text
  //! 1 if CircularArc
  //! 2 if CompositeCurve
  //! 3 otherwise
  Standard_EXPORT int GeomCase() const;

  //! returns the Geometry Entity, Null handle if GeomCase(me) .eq. 0
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Geom() const;

  //! returns Null handle if GeomCase(me) .ne. 1
  Standard_EXPORT occ::handle<IGESGeom_CircularArc> CircularArc() const;

  //! returns Null handle if GeomCase(me) .ne. 2
  Standard_EXPORT occ::handle<IGESGeom_CompositeCurve> CompositeCurve() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_PointDimension, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote> theNote;
  occ::handle<IGESDimen_LeaderArrow> theLeader;
  occ::handle<IGESData_IGESEntity>   theGeom;
};

