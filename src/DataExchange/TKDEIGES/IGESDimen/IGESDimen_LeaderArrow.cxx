#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_LeaderArrow, IGESData_IGESEntity)

IGESDimen_LeaderArrow::IGESDimen_LeaderArrow() = default;

void IGESDimen_LeaderArrow::Init(const double                                   height,
                                 const double                                   width,
                                 const double                                   depth,
                                 const gp_XY&                                   position,
                                 const occ::handle<NCollection_HArray1<gp_XY>>& segments)
{
  if (segments->Lower() != 1)
    throw Standard_DimensionMismatch("IGESDimen_LeaderArrow : Init");
  theArrowHeadHeight = height;
  theArrowHeadWidth  = width;
  theZDepth          = depth;
  theArrowHead       = position;
  theSegmentTails    = segments;
  InitTypeAndForm(214, FormNumber());
}

void IGESDimen_LeaderArrow::SetFormNumber(const int form)
{
  if (form < 1 || form > 12)
    throw Standard_OutOfRange("IGESDimen_LeaderArrow : SetFormNumber");
  InitTypeAndForm(214, form);
}

int IGESDimen_LeaderArrow::NbSegments() const
{
  return theSegmentTails->Length();
}

double IGESDimen_LeaderArrow::ArrowHeadHeight() const
{
  return theArrowHeadHeight;
}

double IGESDimen_LeaderArrow::ArrowHeadWidth() const
{
  return theArrowHeadWidth;
}

double IGESDimen_LeaderArrow::ZDepth() const
{
  return theZDepth;
}

gp_Pnt2d IGESDimen_LeaderArrow::ArrowHead() const
{
  gp_Pnt2d AHPnt2d(theArrowHead);
  return AHPnt2d;
}

gp_Pnt IGESDimen_LeaderArrow::TransformedArrowHead() const
{
  gp_XYZ point(theArrowHead.X(), theArrowHead.Y(), ZDepth());
  if (HasTransf())
    Location().Transforms(point);
  return gp_Pnt(point);
}

gp_Pnt2d IGESDimen_LeaderArrow::SegmentTail(const int Index) const
{
  gp_Pnt2d STPnt2d(theSegmentTails->Value(Index));
  return STPnt2d;
}

gp_Pnt IGESDimen_LeaderArrow::TransformedSegmentTail(const int Index) const
{
  gp_XY  point2d = theSegmentTails->Value(Index);
  gp_XYZ point(point2d.X(), point2d.Y(), ZDepth());
  if (HasTransf())
    Location().Transforms(point);
  return gp_Pnt(point);
}
