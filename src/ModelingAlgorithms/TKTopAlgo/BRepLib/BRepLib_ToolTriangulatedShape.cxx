

#include <BRepLib_ToolTriangulatedShape.hpp>

#include <BRep_Tool.hpp>
#include <GeomLib.hpp>
#include <Poly.hpp>
#include <Poly_Connect.hpp>
#include <Precision.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>

void BRepLib_ToolTriangulatedShape::ComputeNormals(const TopoDS_Face&                     theFace,
                                                   const occ::handle<Poly_Triangulation>& theTris,
                                                   Poly_Connect& thePolyConnect)
{
  if (theTris.IsNull() || theTris->HasNormals())
  {
    return;
  }

  const TopoDS_Face         aZeroFace = TopoDS::Face(theFace.Located(TopLoc_Location()));
  occ::handle<Geom_Surface> aSurf     = BRep_Tool::Surface(aZeroFace);
  if (!theTris->HasUVNodes() || aSurf.IsNull())
  {

    Poly::ComputeNormals(theTris);
    return;
  }

  constexpr double aTol = Precision::Confusion();
  int              aTri[3];
  gp_Dir           aNorm;
  theTris->AddNormals();
  for (int aNodeIter = 1; aNodeIter <= theTris->NbNodes(); ++aNodeIter)
  {

    if (GeomLib::NormEstim(aSurf, theTris->UVNode(aNodeIter), aTol, aNorm) > 1)
    {
      if (thePolyConnect.Triangulation() != theTris)
      {
        thePolyConnect.Load(theTris);
      }

      gp_XYZ eqPlan(0.0, 0.0, 0.0);
      for (thePolyConnect.Initialize(aNodeIter); thePolyConnect.More(); thePolyConnect.Next())
      {
        theTris->Triangle(thePolyConnect.Value()).Get(aTri[0], aTri[1], aTri[2]);
        const gp_XYZ v1(theTris->Node(aTri[1]).Coord() - theTris->Node(aTri[0]).Coord());
        const gp_XYZ v2(theTris->Node(aTri[2]).Coord() - theTris->Node(aTri[1]).Coord());
        const gp_XYZ vv   = v1 ^ v2;
        const double aMod = vv.Modulus();
        if (aMod >= aTol)
        {
          eqPlan += vv / aMod;
        }
      }
      const double aModMax = eqPlan.Modulus();
      aNorm                = (aModMax > aTol) ? gp_Dir(eqPlan) : gp::DZ();
    }

    theTris->SetNormal(aNodeIter, aNorm);
  }
}
