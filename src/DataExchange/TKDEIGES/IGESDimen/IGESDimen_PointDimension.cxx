#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <IGESDimen_PointDimension.hpp>
#include <IGESGeom_CircularArc.hpp>
#include <IGESGeom_CompositeCurve.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_PointDimension, IGESData_IGESEntity)

IGESDimen_PointDimension::IGESDimen_PointDimension() = default;

void IGESDimen_PointDimension::Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                                    const occ::handle<IGESDimen_LeaderArrow>& anArrow,
                                    const occ::handle<IGESData_IGESEntity>&   aGeom)
{
  theNote   = aNote;
  theLeader = anArrow;
  theGeom   = aGeom;
  InitTypeAndForm(220, 0);
}

occ::handle<IGESDimen_GeneralNote> IGESDimen_PointDimension::Note() const
{
  return theNote;
}

occ::handle<IGESDimen_LeaderArrow> IGESDimen_PointDimension::LeaderArrow() const
{
  return theLeader;
}

occ::handle<IGESGeom_CircularArc> IGESDimen_PointDimension::CircularArc() const
{
  return GetCasted(IGESGeom_CircularArc, theGeom);
}

occ::handle<IGESGeom_CompositeCurve> IGESDimen_PointDimension::CompositeCurve() const
{
  return GetCasted(IGESGeom_CompositeCurve, theGeom);
}

occ::handle<IGESData_IGESEntity> IGESDimen_PointDimension::Geom() const
{
  return theGeom;
}

int IGESDimen_PointDimension::GeomCase() const
{
  if (theGeom.IsNull())
    return 0;
  else if (theGeom->TypeNumber() == 100)
    return 1;
  else if (theGeom->TypeNumber() == 102)
    return 2;
  else
    return 3;
}
