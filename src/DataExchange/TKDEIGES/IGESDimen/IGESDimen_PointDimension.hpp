#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_LeaderArrow;
class IGESGeom_CircularArc;
class IGESGeom_CompositeCurve;

class IGESDimen_PointDimension : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_PointDimension();

  Standard_EXPORT void Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                            const occ::handle<IGESDimen_LeaderArrow>& anArrow,
                            const occ::handle<IGESData_IGESEntity>&   aGeom);

  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> LeaderArrow() const;

  Standard_EXPORT int GeomCase() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Geom() const;

  Standard_EXPORT occ::handle<IGESGeom_CircularArc> CircularArc() const;

  Standard_EXPORT occ::handle<IGESGeom_CompositeCurve> CompositeCurve() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_PointDimension, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote> theNote;
  occ::handle<IGESDimen_LeaderArrow> theLeader;
  occ::handle<IGESData_IGESEntity>   theGeom;
};
