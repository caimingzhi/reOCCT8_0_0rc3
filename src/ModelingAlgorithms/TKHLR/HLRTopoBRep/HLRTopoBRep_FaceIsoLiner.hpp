#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class TopoDS_Face;
class HLRTopoBRep_Data;
class TopoDS_Vertex;
class TopoDS_Edge;
class gp_Pnt;
class Geom2d_Line;

class HLRTopoBRep_FaceIsoLiner
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Perform(const int          FI,
                                      const TopoDS_Face& F,
                                      HLRTopoBRep_Data&  DS,
                                      const int          nbIsos);

  Standard_EXPORT static TopoDS_Vertex MakeVertex(const TopoDS_Edge& E,
                                                  const gp_Pnt&      P,
                                                  const double       Par,
                                                  const double       Tol,
                                                  HLRTopoBRep_Data&  DS);

  Standard_EXPORT static void MakeIsoLine(const TopoDS_Face&              F,
                                          const occ::handle<Geom2d_Line>& Iso,
                                          TopoDS_Vertex&                  V1,
                                          TopoDS_Vertex&                  V2,
                                          const double                    U1,
                                          const double                    U2,
                                          const double                    Tol,
                                          HLRTopoBRep_Data&               DS);
};
