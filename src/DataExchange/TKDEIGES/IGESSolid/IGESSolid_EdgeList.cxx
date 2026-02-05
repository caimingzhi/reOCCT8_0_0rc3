#include <IGESSolid_EdgeList.hpp>
#include <IGESSolid_VertexList.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_EdgeList, IGESData_IGESEntity)

IGESSolid_EdgeList::IGESSolid_EdgeList() = default;

void IGESSolid_EdgeList::Init(
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&  Curves,
  const occ::handle<NCollection_HArray1<occ::handle<IGESSolid_VertexList>>>& startVertexList,
  const occ::handle<NCollection_HArray1<int>>&                               startVertexIndex,
  const occ::handle<NCollection_HArray1<occ::handle<IGESSolid_VertexList>>>& endVertexList,
  const occ::handle<NCollection_HArray1<int>>&                               endVertexIndex)
{
  int nb = (Curves.IsNull() ? 0 : Curves->Length());

  if (nb == 0 || Curves->Lower() != 1 || startVertexList->Lower() != 1
      || startVertexList->Length() != nb || startVertexIndex->Lower() != 1
      || startVertexIndex->Length() != nb || endVertexList->Lower() != 1
      || endVertexList->Length() != nb || endVertexIndex->Lower() != 1
      || endVertexIndex->Length() != nb)
    throw Standard_DimensionError("IGESSolid_EdgeList : Init");

  theCurves           = Curves;
  theStartVertexList  = startVertexList;
  theStartVertexIndex = startVertexIndex;
  theEndVertexList    = endVertexList;
  theEndVertexIndex   = endVertexIndex;

  InitTypeAndForm(504, 1);
}

int IGESSolid_EdgeList::NbEdges() const
{
  return (theCurves.IsNull() ? 0 : theCurves->Length());
}

occ::handle<IGESData_IGESEntity> IGESSolid_EdgeList::Curve(const int num) const
{
  return theCurves->Value(num);
}

occ::handle<IGESSolid_VertexList> IGESSolid_EdgeList::StartVertexList(const int num) const
{
  return theStartVertexList->Value(num);
}

int IGESSolid_EdgeList::StartVertexIndex(const int num) const
{
  return theStartVertexIndex->Value(num);
}

occ::handle<IGESSolid_VertexList> IGESSolid_EdgeList::EndVertexList(const int num) const
{
  return theEndVertexList->Value(num);
}

int IGESSolid_EdgeList::EndVertexIndex(const int num) const
{
  return theEndVertexIndex->Value(num);
}
