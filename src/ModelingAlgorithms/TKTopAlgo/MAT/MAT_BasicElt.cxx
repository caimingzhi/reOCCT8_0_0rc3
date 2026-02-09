#include <MAT_Arc.hpp>
#include <MAT_BasicElt.hpp>
#include <MAT_Node.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MAT_BasicElt, Standard_Transient)

MAT_BasicElt::MAT_BasicElt(const int anInteger)
    : startLeftArc(nullptr),
      endLeftArc(nullptr),
      index(anInteger),
      geomIndex(0)
{
}

occ::handle<MAT_Arc> MAT_BasicElt::StartArc() const
{
  return (MAT_Arc*)startLeftArc;
}

occ::handle<MAT_Arc> MAT_BasicElt::EndArc() const
{
  return (MAT_Arc*)endLeftArc;
}

int MAT_BasicElt::Index() const
{
  return index;
}

int MAT_BasicElt::GeomIndex() const
{
  return geomIndex;
}

void MAT_BasicElt::SetStartArc(const occ::handle<MAT_Arc>& anArc)
{
  startLeftArc = anArc.get();
}

void MAT_BasicElt::SetEndArc(const occ::handle<MAT_Arc>& anArc)
{
  endLeftArc = anArc.get();
}

void MAT_BasicElt::SetIndex(const int anInteger)
{
  index = anInteger;
}

void MAT_BasicElt::SetGeomIndex(const int anInteger)
{
  geomIndex = anInteger;
}
