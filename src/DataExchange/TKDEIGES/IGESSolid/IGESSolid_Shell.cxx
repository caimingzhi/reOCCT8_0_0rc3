#include <IGESSolid_Shell.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_Shell, IGESData_IGESEntity)

IGESSolid_Shell::IGESSolid_Shell() = default;

void IGESSolid_Shell::Init(
  const occ::handle<NCollection_HArray1<occ::handle<IGESSolid_Face>>>& Faces,
  const occ::handle<NCollection_HArray1<int>>&                         Orient)
{
  if (Faces->Lower() != 1 || Orient->Lower() != 1 || Faces->Length() != Orient->Length())
    throw Standard_DimensionError("IGESSolid_Shell : Init");

  theFaces       = Faces;
  theOrientation = Orient;
  InitTypeAndForm(514, 1);
}

bool IGESSolid_Shell::IsClosed() const
{
  return (FormNumber() == 1);
}

void IGESSolid_Shell::SetClosed(const bool closed)
{
  InitTypeAndForm(514, (closed ? 1 : 2));
}

int IGESSolid_Shell::NbFaces() const
{
  return theFaces->Length();
}

occ::handle<IGESSolid_Face> IGESSolid_Shell::Face(const int Index) const
{
  return theFaces->Value(Index);
}

bool IGESSolid_Shell::Orientation(const int Index) const
{
  return (theOrientation->Value(Index) != 0);
}
