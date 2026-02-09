

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <gp_Pnt.hpp>
#include <ShapeBuild_Vertex.hpp>
#include <TopoDS_Vertex.hpp>

TopoDS_Vertex ShapeBuild_Vertex::CombineVertex(const TopoDS_Vertex& V1,
                                               const TopoDS_Vertex& V2,
                                               const double         tolFactor) const
{
  return CombineVertex(BRep_Tool::Pnt(V1),
                       BRep_Tool::Pnt(V2),
                       BRep_Tool::Tolerance(V1),
                       BRep_Tool::Tolerance(V2),
                       tolFactor);
}

TopoDS_Vertex ShapeBuild_Vertex::CombineVertex(const gp_Pnt& pnt1,
                                               const gp_Pnt& pnt2,
                                               const double  tol1,
                                               const double  tol2,
                                               const double  tolFactor) const
{
  gp_Pnt pos;
  double tol;

  gp_Vec v    = pnt2.XYZ() - pnt1.XYZ();
  double dist = v.Magnitude();

  if (dist + tol2 <= tol1)
  {
    pos = pnt1;
    tol = tol1;
  }
  else if (dist + tol1 <= tol2)
  {
    pos = pnt2;
    tol = tol2;
  }
  else
  {
    tol      = 0.5 * (dist + tol1 + tol2);
    double s = (dist > 0.) ? (tol2 - tol1) / dist : 0.;
    pos      = 0.5 * ((1 - s) * pnt1.XYZ() + (1 + s) * pnt2.XYZ());
  }

  TopoDS_Vertex V;
  BRep_Builder  B;
  B.MakeVertex(V, pos, tolFactor * tol);
  return V;
}
