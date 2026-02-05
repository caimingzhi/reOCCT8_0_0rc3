#include <IGESSolid_SolidAssembly.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_SolidAssembly, IGESData_IGESEntity)

IGESSolid_SolidAssembly::IGESSolid_SolidAssembly() = default;

void IGESSolid_SolidAssembly::Init(
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&           Items,
  const occ::handle<NCollection_HArray1<occ::handle<IGESGeom_TransformationMatrix>>>& Matrices)
{
  if (Items->Lower() != 1 || Matrices->Lower() != 1 || Items->Length() != Matrices->Length())
    throw Standard_DimensionError("IGESSolid_SolidAssembly : Init");

  theItems    = Items;
  theMatrices = Matrices;
  InitTypeAndForm(184, 0);
}

bool IGESSolid_SolidAssembly::HasBrep() const
{
  return (FormNumber() == 1);
}

void IGESSolid_SolidAssembly::SetBrep(const bool hasbrep)
{
  InitTypeAndForm(184, (hasbrep ? 1 : 0));
}

int IGESSolid_SolidAssembly::NbItems() const
{
  return theItems->Length();
}

occ::handle<IGESData_IGESEntity> IGESSolid_SolidAssembly::Item(const int Index) const
{
  return theItems->Value(Index);
}

occ::handle<IGESGeom_TransformationMatrix> IGESSolid_SolidAssembly::TransfMatrix(
  const int Index) const
{
  return theMatrices->Value(Index);
}
