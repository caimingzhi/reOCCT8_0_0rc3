

#include <ShapePersistent_Poly.hpp>
#include <ShapePersistent_HArray1.hpp>

#include <Poly_Polygon2D.hpp>
#include <Poly_Polygon3D.hpp>
#include <Poly_PolygonOnTriangulation.hpp>
#include <Poly_Triangulation.hpp>

void ShapePersistent_Poly::pPolygon2D::PChildren(
  StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
{
  theChildren.Append(myNodes);
}

occ::handle<Poly_Polygon2D> ShapePersistent_Poly::pPolygon2D::Import() const
{
  if (myNodes.IsNull())
    return nullptr;

  occ::handle<Poly_Polygon2D> aPolygon = new Poly_Polygon2D(*myNodes->Array());
  aPolygon->Deflection(myDeflection);
  return aPolygon;
}

void ShapePersistent_Poly::pPolygon3D::PChildren(
  StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
{
  theChildren.Append(myNodes);
  theChildren.Append(myParameters);
}

occ::handle<Poly_Polygon3D> ShapePersistent_Poly::pPolygon3D::Import() const
{
  if (myNodes.IsNull() || myParameters.IsNull())
    return nullptr;

  occ::handle<Poly_Polygon3D> aPolygon =
    new Poly_Polygon3D(*myNodes->Array(), *myParameters->Array());
  aPolygon->Deflection(myDeflection);
  return aPolygon;
}

void ShapePersistent_Poly::pPolygonOnTriangulation::PChildren(
  StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
{
  theChildren.Append(myNodes);
  theChildren.Append(myParameters);
}

occ::handle<Poly_PolygonOnTriangulation> ShapePersistent_Poly::pPolygonOnTriangulation::Import()
  const
{
  occ::handle<Poly_PolygonOnTriangulation> aPolygon;

  if (myNodes)
  {
    if (myParameters)
      aPolygon = new Poly_PolygonOnTriangulation(*myNodes->Array(), *myParameters->Array());
    else
      aPolygon = new Poly_PolygonOnTriangulation(*myNodes->Array());

    aPolygon->Deflection(myDeflection);
  }

  return aPolygon;
}

void ShapePersistent_Poly::pTriangulation::PChildren(
  StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
{
  theChildren.Append(myNodes);
  theChildren.Append(myUVNodes);
  theChildren.Append(myTriangles);
}

occ::handle<Poly_Triangulation> ShapePersistent_Poly::pTriangulation::Import() const
{
  occ::handle<Poly_Triangulation> aTriangulation;

  if (myNodes && myTriangles)
  {
    if (myUVNodes)
      aTriangulation =
        new Poly_Triangulation(*myNodes->Array(), *myUVNodes->Array(), *myTriangles->Array());
    else
      aTriangulation = new Poly_Triangulation(*myNodes->Array(), *myTriangles->Array());

    aTriangulation->Deflection(myDeflection);
  }

  return aTriangulation;
}

Handle(ShapePersistent_Poly::Polygon2D) ShapePersistent_Poly::Translate(
  const occ::handle<Poly_Polygon2D>&                                                       thePoly,
  NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>& theMap)
{
  occ::handle<Polygon2D> aPP;
  if (!thePoly.IsNull())
  {
    if (theMap.IsBound(thePoly))
      aPP = occ::down_cast<Polygon2D>(theMap.Find(thePoly));
    else
    {
      aPP                             = new Polygon2D;
      aPP->myPersistent               = new pPolygon2D;
      aPP->myPersistent->myDeflection = thePoly->Deflection();
      aPP->myPersistent->myNodes =
        StdLPersistent_HArray1::Translate<NCollection_HArray1<gp_Pnt2d>>("PColgp_HArray1OfPnt2d",
                                                                         thePoly->Nodes());
      theMap.Bind(thePoly, aPP);
    }
  }
  return aPP;
}

Handle(ShapePersistent_Poly::Polygon3D) ShapePersistent_Poly::Translate(
  const occ::handle<Poly_Polygon3D>&                                                       thePoly,
  NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>& theMap)
{
  occ::handle<Polygon3D> aPP = new Polygon3D;
  if (!thePoly.IsNull())
  {
    if (theMap.IsBound(thePoly))
      aPP = occ::down_cast<Polygon3D>(theMap.Find(thePoly));
    else
    {
      aPP                             = new Polygon3D;
      aPP->myPersistent               = new pPolygon3D;
      aPP->myPersistent->myDeflection = thePoly->Deflection();
      aPP->myPersistent->myNodes =
        StdLPersistent_HArray1::Translate<NCollection_HArray1<gp_Pnt>>("PColgp_HArray1OfPnt",
                                                                       thePoly->Nodes());
      if (thePoly->HasParameters())
      {
        aPP->myPersistent->myParameters =
          StdLPersistent_HArray1::Translate<NCollection_HArray1<double>>(thePoly->Parameters());
      }
      theMap.Bind(thePoly, aPP);
    }
  }
  return aPP;
}

Handle(ShapePersistent_Poly::PolygonOnTriangulation) ShapePersistent_Poly::Translate(
  const occ::handle<Poly_PolygonOnTriangulation>& thePolyOnTriang,
  NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>& theMap)
{
  occ::handle<PolygonOnTriangulation> aPPonT;
  if (!thePolyOnTriang.IsNull())
  {
    if (theMap.IsBound(thePolyOnTriang))
      aPPonT = occ::down_cast<PolygonOnTriangulation>(theMap.Find(thePolyOnTriang));
    else
    {
      aPPonT                             = new PolygonOnTriangulation;
      aPPonT->myPersistent               = new pPolygonOnTriangulation;
      aPPonT->myPersistent->myDeflection = thePolyOnTriang->Deflection();
      aPPonT->myPersistent->myNodes =
        StdLPersistent_HArray1::Translate<NCollection_HArray1<int>>(thePolyOnTriang->Nodes());
      if (thePolyOnTriang->HasParameters())
      {
        aPPonT->myPersistent->myParameters =
          StdLPersistent_HArray1::Translate<NCollection_HArray1<double>>(
            thePolyOnTriang->Parameters()->Array1());
      }
      theMap.Bind(thePolyOnTriang, aPPonT);
    }
  }
  return aPPonT;
}

Handle(ShapePersistent_Poly::Triangulation) ShapePersistent_Poly::Translate(
  const occ::handle<Poly_Triangulation>& thePolyTriang,
  NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>& theMap)
{
  occ::handle<Triangulation> aPT;
  if (!thePolyTriang.IsNull())
  {
    if (theMap.IsBound(thePolyTriang))
      aPT = occ::down_cast<Triangulation>(theMap.Find(thePolyTriang));
    else
    {
      aPT               = new Triangulation;
      aPT->myPersistent = new pTriangulation;

      NCollection_Array1<gp_Pnt> pArrayOfNodes(1, thePolyTriang->NbNodes());
      for (int i = 1; i <= thePolyTriang->NbNodes(); i++)
      {
        pArrayOfNodes.SetValue(i, thePolyTriang->Node(i));
      }

      NCollection_Array1<Poly_Triangle> pArrayOfTriangles(1, thePolyTriang->NbTriangles());
      for (int i = 1; i <= thePolyTriang->NbTriangles(); i++)
      {
        pArrayOfTriangles.SetValue(i, thePolyTriang->Triangle(i));
      }

      aPT->myPersistent->myNodes =
        StdLPersistent_HArray1::Translate<NCollection_HArray1<gp_Pnt>>("PColgp_HArray1OfPnt",
                                                                       pArrayOfNodes);
      aPT->myPersistent->myTriangles =
        StdLPersistent_HArray1::Translate<NCollection_HArray1<Poly_Triangle>>(
          "PPoly_HArray1OfTriangle",
          pArrayOfTriangles);
      if (thePolyTriang->HasUVNodes())
      {

        NCollection_Array1<gp_Pnt2d> pArrayOfUVNodes(1, thePolyTriang->NbNodes());
        for (int i = 1; i <= thePolyTriang->NbNodes(); i++)
        {
          pArrayOfUVNodes.SetValue(i, thePolyTriang->UVNode(i));
        }

        aPT->myPersistent->myUVNodes =
          StdLPersistent_HArray1::Translate<NCollection_HArray1<gp_Pnt2d>>("PColgp_HArray1OfPnt2d",
                                                                           pArrayOfUVNodes);
      }
      theMap.Bind(thePolyTriang, aPT);
    }
  }
  return aPT;
}
