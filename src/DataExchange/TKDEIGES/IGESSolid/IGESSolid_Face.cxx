#include <IGESSolid_Face.hpp>
#include <IGESSolid_Loop.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_Face, IGESData_IGESEntity)

IGESSolid_Face::IGESSolid_Face() = default;

void IGESSolid_Face::Init(
  const occ::handle<IGESData_IGESEntity>&                              aSurface,
  const bool                                                           OuterLoopFlag,
  const occ::handle<NCollection_HArray1<occ::handle<IGESSolid_Loop>>>& Loops)
{
  if (Loops->Lower() != 1)
    throw Standard_DimensionMismatch("IGESSolid_Face : Init");
  theSurface   = aSurface;
  hasOuterLoop = OuterLoopFlag;
  theLoops     = Loops;
  InitTypeAndForm(510, 1);
}

occ::handle<IGESData_IGESEntity> IGESSolid_Face::Surface() const
{
  return theSurface;
}

int IGESSolid_Face::NbLoops() const
{
  return theLoops->Length();
}

bool IGESSolid_Face::HasOuterLoop() const
{
  return hasOuterLoop;
}

occ::handle<IGESSolid_Loop> IGESSolid_Face::Loop(const int Index) const
{
  return theLoops->Value(Index);
}
