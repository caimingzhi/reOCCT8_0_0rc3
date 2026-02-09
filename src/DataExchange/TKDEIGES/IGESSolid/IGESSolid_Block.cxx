#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESSolid_Block.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_Block, IGESData_IGESEntity)

IGESSolid_Block::IGESSolid_Block() = default;

void IGESSolid_Block::Init(const gp_XYZ& aSize,
                           const gp_XYZ& aCorner,
                           const gp_XYZ& aXAxis,
                           const gp_XYZ& aZAxis)
{
  theSize   = aSize;
  theCorner = aCorner;
  theXAxis  = aXAxis;
  theZAxis  = aZAxis;
  InitTypeAndForm(150, 0);
}

gp_XYZ IGESSolid_Block::Size() const
{
  return theSize;
}

double IGESSolid_Block::XLength() const
{
  return theSize.X();
}

double IGESSolid_Block::YLength() const
{
  return theSize.Y();
}

double IGESSolid_Block::ZLength() const
{
  return theSize.Z();
}

gp_Pnt IGESSolid_Block::Corner() const
{
  return gp_Pnt(theCorner);
}

gp_Pnt IGESSolid_Block::TransformedCorner() const
{
  if (!HasTransf())
    return gp_Pnt(theCorner);
  else
  {
    gp_XYZ tmp = theCorner;
    Location().Transforms(tmp);
    return gp_Pnt(tmp);
  }
}

gp_Dir IGESSolid_Block::XAxis() const
{
  return gp_Dir(theXAxis);
}

gp_Dir IGESSolid_Block::TransformedXAxis() const
{
  if (!HasTransf())
    return gp_Dir(theXAxis);
  else
  {
    gp_XYZ   xyz = theXAxis;
    gp_GTrsf loc = Location();
    loc.SetTranslationPart(gp_XYZ(0., 0., 0.));
    loc.Transforms(xyz);
    return gp_Dir(xyz);
  }
}

gp_Dir IGESSolid_Block::YAxis() const
{
  return gp_Dir(theXAxis ^ theZAxis);
}

gp_Dir IGESSolid_Block::TransformedYAxis() const
{
  if (!HasTransf())
    return gp_Dir(theXAxis ^ theZAxis);
  else
  {
    gp_XYZ   xyz = theXAxis ^ theZAxis;
    gp_GTrsf loc = Location();
    loc.SetTranslationPart(gp_XYZ(0., 0., 0.));
    loc.Transforms(xyz);
    return gp_Dir(xyz);
  }
}

gp_Dir IGESSolid_Block::ZAxis() const
{
  return gp_Dir(theZAxis);
}

gp_Dir IGESSolid_Block::TransformedZAxis() const
{
  if (!HasTransf())
    return gp_Dir(theZAxis);
  else
  {
    gp_XYZ   xyz(theZAxis);
    gp_GTrsf loc = Location();
    loc.SetTranslationPart(gp_XYZ(0., 0., 0.));
    loc.Transforms(xyz);
    return gp_Dir(xyz);
  }
}
