#include <gp_GTrsf.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <gp_XYZ.hpp>
#include <IGESDimen_DiameterDimension.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_DiameterDimension, IGESData_IGESEntity)

IGESDimen_DiameterDimension::IGESDimen_DiameterDimension() = default;

void IGESDimen_DiameterDimension::Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                                       const occ::handle<IGESDimen_LeaderArrow>& aLeader,
                                       const occ::handle<IGESDimen_LeaderArrow>& anotherLeader,
                                       const gp_XY&                              aCenter)
{
  theNote         = aNote;
  theFirstLeader  = aLeader;
  theSecondLeader = anotherLeader;
  theCenter       = aCenter;
  InitTypeAndForm(206, 0);
}

occ::handle<IGESDimen_GeneralNote> IGESDimen_DiameterDimension::Note() const
{
  return theNote;
}

occ::handle<IGESDimen_LeaderArrow> IGESDimen_DiameterDimension::FirstLeader() const
{
  return theFirstLeader;
}

bool IGESDimen_DiameterDimension::HasSecondLeader() const
{
  return (!theSecondLeader.IsNull());
}

occ::handle<IGESDimen_LeaderArrow> IGESDimen_DiameterDimension::SecondLeader() const
{
  return theSecondLeader;
}

gp_Pnt2d IGESDimen_DiameterDimension::Center() const
{
  gp_Pnt2d center(theCenter);
  return center;
}

gp_Pnt2d IGESDimen_DiameterDimension::TransformedCenter() const
{
  gp_XYZ center(theCenter.X(), theCenter.Y(), 0);
  if (HasTransf())
    Location().Transforms(center);
  return gp_Pnt2d(center.X(), center.Y());
}
