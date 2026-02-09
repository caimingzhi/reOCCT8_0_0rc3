

#include <BRep_TEdge.hpp>
#include <BRep_TFace.hpp>
#include <BRep_Tool.hpp>
#include <BRep_TVertex.hpp>
#include <ShapeFix_ShapeTolerance.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>

ShapeFix_ShapeTolerance::ShapeFix_ShapeTolerance() = default;

bool ShapeFix_ShapeTolerance::LimitTolerance(const TopoDS_Shape&    shape,
                                             const double           tmin,
                                             const double           tmax,
                                             const TopAbs_ShapeEnum styp) const
{
  if (shape.IsNull() || tmin < 0)
    return false;
  bool   iamax = (tmax >= tmin);
  double prec;
  bool   fait = false;
  if (styp == TopAbs_VERTEX || styp == TopAbs_EDGE || styp == TopAbs_FACE)
  {
    for (TopExp_Explorer ex(shape, styp); ex.More(); ex.Next())
    {
      TopoDS_Shape sh     = ex.Current();
      int          newtol = 0;
      if (styp == TopAbs_VERTEX)
      {
        TopoDS_Vertex V = TopoDS::Vertex(sh);
        prec            = BRep_Tool::Tolerance(V);
        if (iamax && prec > tmax)
          newtol = 1;
        else if (prec < tmin)
          newtol = -1;
        if (newtol)
        {
          const occ::handle<BRep_TVertex>& TV = *((occ::handle<BRep_TVertex>*)&V.TShape());
          TV->Tolerance((newtol > 0 ? tmax : tmin));
          fait = true;
        }
      }
      else if (styp == TopAbs_EDGE)
      {
        TopoDS_Edge E = TopoDS::Edge(sh);
        prec          = BRep_Tool::Tolerance(E);
        if (iamax && prec > tmax)
          newtol = 1;
        else if (prec < tmin)
          newtol = -1;
        if (newtol)
        {
          const occ::handle<BRep_TEdge>& TE = *((occ::handle<BRep_TEdge>*)&E.TShape());
          TE->Tolerance((newtol > 0 ? tmax : tmin));
          fait = true;
        }
      }
      else if (styp == TopAbs_FACE)
      {
        TopoDS_Face F = TopoDS::Face(sh);
        prec          = BRep_Tool::Tolerance(F);
        if (iamax && prec > tmax)
          newtol = 1;
        else if (prec < tmin)
          newtol = -1;
        if (newtol)
        {
          const occ::handle<BRep_TFace>& TF = *((occ::handle<BRep_TFace>*)&F.TShape());
          TF->Tolerance((newtol > 0 ? tmax : tmin));
          fait = true;
        }
      }
    }
  }
  else if (styp == TopAbs_WIRE)
  {
    for (TopExp_Explorer ex(shape, TopAbs_EDGE); ex.More(); ex.Next())
    {
      TopoDS_Shape sh = ex.Current();
      TopoDS_Edge  E  = TopoDS::Edge(sh);
      LimitTolerance(E, tmin, tmax, TopAbs_EDGE);
      TopoDS_Vertex V1, V2;
      TopExp::Vertices(E, V1, V2);
      if (!V1.IsNull())
        fait |= LimitTolerance(V1, tmin, tmax, TopAbs_VERTEX);
      if (!V2.IsNull())
        fait |= LimitTolerance(V2, tmin, tmax, TopAbs_VERTEX);
    }
  }
  else
  {
    fait |= LimitTolerance(shape, tmin, tmax, TopAbs_VERTEX);
    fait |= LimitTolerance(shape, tmin, tmax, TopAbs_EDGE);
    fait |= LimitTolerance(shape, tmin, tmax, TopAbs_FACE);
  }
  return fait;
}

void ShapeFix_ShapeTolerance::SetTolerance(const TopoDS_Shape&    shape,
                                           const double           preci,
                                           const TopAbs_ShapeEnum styp) const
{

  if (shape.IsNull() || preci <= 0)
    return;
  if (styp == TopAbs_VERTEX || styp == TopAbs_EDGE || styp == TopAbs_FACE)
  {
    for (TopExp_Explorer ex(shape, styp); ex.More(); ex.Next())
    {
      TopoDS_Shape sh = ex.Current();
      if (styp == TopAbs_VERTEX)
      {
        TopoDS_Vertex V = TopoDS::Vertex(sh);

        const occ::handle<BRep_TVertex>& TV = *((occ::handle<BRep_TVertex>*)&V.TShape());
        TV->Tolerance(preci);
      }
      else if (styp == TopAbs_EDGE)
      {
        TopoDS_Edge E = TopoDS::Edge(sh);

        const occ::handle<BRep_TEdge>& TE = *((occ::handle<BRep_TEdge>*)&E.TShape());
        TE->Tolerance(preci);
      }
      else if (styp == TopAbs_FACE)
      {
        TopoDS_Face F = TopoDS::Face(sh);

        const occ::handle<BRep_TFace>& TF = *((occ::handle<BRep_TFace>*)&F.TShape());
        TF->Tolerance(preci);
      }
    }
  }
  else if (styp == TopAbs_WIRE)
  {
    for (TopExp_Explorer ex(shape, TopAbs_EDGE); ex.More(); ex.Next())
    {
      TopoDS_Shape sh = ex.Current();
      TopoDS_Edge  E  = TopoDS::Edge(sh);

      const occ::handle<BRep_TEdge>& TE = *((occ::handle<BRep_TEdge>*)&E.TShape());
      TE->Tolerance(preci);
      TopoDS_Vertex V1, V2;
      TopExp::Vertices(E, V1, V2);
      if (!V1.IsNull())
      {

        const occ::handle<BRep_TVertex>& TV = *((occ::handle<BRep_TVertex>*)&V1.TShape());
        TV->Tolerance(preci);
      }
      if (!V2.IsNull())
      {

        const occ::handle<BRep_TVertex>& TV = *((occ::handle<BRep_TVertex>*)&V2.TShape());
        TV->Tolerance(preci);
      }
    }
  }
  else
  {
    SetTolerance(shape, preci, TopAbs_VERTEX);
    SetTolerance(shape, preci, TopAbs_EDGE);
    SetTolerance(shape, preci, TopAbs_FACE);
  }
}
