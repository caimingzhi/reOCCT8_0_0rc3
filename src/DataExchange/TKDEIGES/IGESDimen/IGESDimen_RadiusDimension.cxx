#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <IGESDimen_RadiusDimension.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_RadiusDimension, IGESData_IGESEntity)

IGESDimen_RadiusDimension::IGESDimen_RadiusDimension() = default;

void IGESDimen_RadiusDimension::Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                                     const occ::handle<IGESDimen_LeaderArrow>& anArrow,
                                     const gp_XY&                              arcCenter,
                                     const occ::handle<IGESDimen_LeaderArrow>& anotherArrow)
{
  theNote        = aNote;
  theLeaderArrow = anArrow;
  theCenter      = arcCenter;
  theLeader2     = anotherArrow;
  if (!anotherArrow.IsNull())
    InitTypeAndForm(222, 1);
  else
    InitTypeAndForm(222, FormNumber());
}

void IGESDimen_RadiusDimension::InitForm(const int form)
{
  InitTypeAndForm(222, form);
}

occ::handle<IGESDimen_GeneralNote> IGESDimen_RadiusDimension::Note() const
{
  return theNote;
}

occ::handle<IGESDimen_LeaderArrow> IGESDimen_RadiusDimension::Leader() const
{
  return theLeaderArrow;
}

bool IGESDimen_RadiusDimension::HasLeader2() const
{
  return (!theLeader2.IsNull());
}

gp_Pnt2d IGESDimen_RadiusDimension::Center() const
{
  gp_Pnt2d g(theCenter);
  return g;
}

gp_Pnt IGESDimen_RadiusDimension::TransformedCenter() const
{
  gp_XYZ tmpXYZ(theCenter.X(), theCenter.Y(), theLeaderArrow->ZDepth());
  if (HasTransf())
    Location().Transforms(tmpXYZ);
  return gp_Pnt(tmpXYZ);
}

occ::handle<IGESDimen_LeaderArrow> IGESDimen_RadiusDimension::Leader2() const
{
  return theLeader2;
}
