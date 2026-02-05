#include <BRep_Tool.hpp>
#include <gp_Pnt.hpp>
#include <StdPrs_ToolVertex.hpp>
#include <TopoDS_Vertex.hpp>

void StdPrs_ToolVertex::Coord(const TopoDS_Vertex& aVertex, double& X, double& Y, double& Z)
{
  gp_Pnt P = BRep_Tool::Pnt(aVertex);
  X        = P.X();
  Y        = P.Y();
  Z        = P.Z();
}
