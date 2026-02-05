#include <gp_Pnt.hpp>
#include <IGESSolid_VertexList.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_VertexList, IGESData_IGESEntity)

IGESSolid_VertexList::IGESSolid_VertexList() = default;

void IGESSolid_VertexList::Init(const occ::handle<NCollection_HArray1<gp_XYZ>>& Vertices)
{
  if (Vertices.IsNull() || Vertices->Lower() != 1)
    throw Standard_DimensionMismatch("IGESSolid_VertexList : Init");
  theVertices = Vertices;
  InitTypeAndForm(502, 1);
}

int IGESSolid_VertexList::NbVertices() const
{
  return (theVertices.IsNull() ? 0 : theVertices->Length());
}

gp_Pnt IGESSolid_VertexList::Vertex(const int Index) const
{
  return gp_Pnt(theVertices->Value(Index));
}
