#include <DBRep_Edge.hpp>
#include <Draw_Color.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Edge.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DBRep_Edge, Standard_Transient)

DBRep_Edge::DBRep_Edge(const TopoDS_Edge& E, const Draw_Color& C)
    : myEdge(E),
      myColor(C)
{
}
