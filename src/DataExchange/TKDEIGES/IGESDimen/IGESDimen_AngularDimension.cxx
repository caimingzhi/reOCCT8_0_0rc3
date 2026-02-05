#include <gp_GTrsf.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <gp_XYZ.hpp>
#include <IGESDimen_AngularDimension.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <IGESDimen_WitnessLine.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_AngularDimension, IGESData_IGESEntity)

IGESDimen_AngularDimension::IGESDimen_AngularDimension() = default;

void IGESDimen_AngularDimension::Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                                      const occ::handle<IGESDimen_WitnessLine>& aLine,
                                      const occ::handle<IGESDimen_WitnessLine>& anotherLine,
                                      const gp_XY&                              aVertex,
                                      const double                              aRadius,
                                      const occ::handle<IGESDimen_LeaderArrow>& aLeader,
                                      const occ::handle<IGESDimen_LeaderArrow>& anotherLeader)
{
  theNote              = aNote;
  theFirstWitnessLine  = aLine;
  theSecondWitnessLine = anotherLine;
  theVertex            = aVertex;
  theRadius            = aRadius;
  theFirstLeader       = aLeader;
  theSecondLeader      = anotherLeader;
  InitTypeAndForm(202, 0);
}

occ::handle<IGESDimen_GeneralNote> IGESDimen_AngularDimension::Note() const
{
  return theNote;
}

bool IGESDimen_AngularDimension::HasFirstWitnessLine() const
{
  return (!theFirstWitnessLine.IsNull());
}

occ::handle<IGESDimen_WitnessLine> IGESDimen_AngularDimension::FirstWitnessLine() const
{
  return theFirstWitnessLine;
}

bool IGESDimen_AngularDimension::HasSecondWitnessLine() const
{
  return (!theSecondWitnessLine.IsNull());
}

occ::handle<IGESDimen_WitnessLine> IGESDimen_AngularDimension::SecondWitnessLine() const
{
  return theSecondWitnessLine;
}

gp_Pnt2d IGESDimen_AngularDimension::Vertex() const
{
  gp_Pnt2d vertex(theVertex);
  return vertex;
}

gp_Pnt2d IGESDimen_AngularDimension::TransformedVertex() const
{
  gp_XYZ point(theVertex.X(), theVertex.Y(), 0.0);
  if (HasTransf())
    Location().Transforms(point);
  return gp_Pnt2d(point.X(), point.Y());
}

double IGESDimen_AngularDimension::Radius() const
{
  return theRadius;
}

occ::handle<IGESDimen_LeaderArrow> IGESDimen_AngularDimension::FirstLeader() const
{
  return theFirstLeader;
}

occ::handle<IGESDimen_LeaderArrow> IGESDimen_AngularDimension::SecondLeader() const
{
  return theSecondLeader;
}
