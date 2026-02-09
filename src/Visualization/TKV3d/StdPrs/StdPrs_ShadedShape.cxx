#include <StdPrs_ShadedShape.hpp>

#include <BRepTools.hpp>
#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <Graphic3d_ArrayOfSegments.hpp>
#include <Graphic3d_ArrayOfTriangles.hpp>
#include <Graphic3d_Group.hpp>
#include <gp_Dir.hpp>
#include <gp_Vec.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_IncAllocator.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Shared.hpp>
#include <Precision.hpp>
#include <Prs3d_Drawer.hpp>
#include <Prs3d_IsoAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_ShadingAspect.hpp>
#include <Poly_PolygonOnTriangulation.hpp>
#include <Poly_Triangulation.hpp>
#include <StdPrs_ToolTriangulatedShape.hpp>
#include <StdPrs_WFShape.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Array1.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>

namespace
{

  void wireframeFromShape(const occ::handle<Prs3d_Presentation>& thePrs,
                          const TopoDS_Shape&                    theShape,
                          const occ::handle<Prs3d_Drawer>&       theDrawer)
  {
    TopExp_Explorer aShapeIter(theShape, TopAbs_FACE);
    if (!aShapeIter.More())
    {
      StdPrs_WFShape::Add(thePrs, theShape, theDrawer);
      return;
    }

    const bool aDrawAllVerticesFlag = (theDrawer->VertexDrawMode() == Prs3d_VDM_All);
    if (!aDrawAllVerticesFlag && theShape.ShapeType() != TopAbs_COMPOUND)
    {
      return;
    }

    TopoDS_Compound aCompoundWF;
    BRep_Builder    aBuilder;
    aBuilder.MakeCompound(aCompoundWF);
    bool hasElement = false;

    for (aShapeIter.Init(theShape, TopAbs_EDGE, TopAbs_FACE); aShapeIter.More(); aShapeIter.Next())
    {
      hasElement = true;
      aBuilder.Add(aCompoundWF, aShapeIter.Current());
    }

    aShapeIter.Init(theShape, TopAbs_VERTEX, aDrawAllVerticesFlag ? TopAbs_SHAPE : TopAbs_EDGE);
    for (; aShapeIter.More(); aShapeIter.Next())
    {
      hasElement = true;
      aBuilder.Add(aCompoundWF, aShapeIter.Current());
    }
    if (hasElement)
    {
      StdPrs_WFShape::Add(thePrs, aCompoundWF, theDrawer);
    }
  }

  void wireframeNoTriangFacesFromShape(const occ::handle<Prs3d_Presentation>& thePrs,
                                       const TopoDS_Shape&                    theShape,
                                       const occ::handle<Prs3d_Drawer>&       theDrawer)
  {
    TopoDS_Compound aCompoundWF;
    BRep_Builder    aBuilder;
    aBuilder.MakeCompound(aCompoundWF);
    TopLoc_Location aLoc;
    bool            hasElement = false;

    for (TopExp_Explorer aShapeIter(theShape, TopAbs_FACE); aShapeIter.More(); aShapeIter.Next())
    {
      const TopoDS_Face&                    aFace   = TopoDS::Face(aShapeIter.Current());
      const occ::handle<Poly_Triangulation> aTriang = BRep_Tool::Triangulation(aFace, aLoc);
      if (aTriang.IsNull())
      {
        hasElement = true;
        aBuilder.Add(aCompoundWF, aFace);
      }
    }

    if (hasElement)
    {
      int aPrevUIsoNb = theDrawer->UIsoAspect()->Number();
      int aPrevVIsoNb = theDrawer->VIsoAspect()->Number();
      theDrawer->UIsoAspect()->SetNumber(5);
      theDrawer->VIsoAspect()->SetNumber(5);

      StdPrs_WFShape::Add(thePrs, aCompoundWF, theDrawer);

      theDrawer->UIsoAspect()->SetNumber(aPrevUIsoNb);
      theDrawer->VIsoAspect()->SetNumber(aPrevVIsoNb);
    }
  }

  static occ::handle<Graphic3d_ArrayOfTriangles> fillTriangles(const TopoDS_Shape& theShape,
                                                               const bool          theHasTexels,
                                                               const gp_Pnt2d&     theUVOrigin,
                                                               const gp_Pnt2d&     theUVRepeat,
                                                               const gp_Pnt2d&     theUVScale)
  {
    occ::handle<Poly_Triangulation> aT;
    TopLoc_Location                 aLoc;
    gp_Pnt                          aPoint;
    int                             aNbTriangles = 0;
    int                             aNbVertices  = 0;

    constexpr double aPreci = Precision::SquareConfusion();

    TopExp_Explorer aFaceIt(theShape, TopAbs_FACE);
    for (; aFaceIt.More(); aFaceIt.Next())
    {
      const TopoDS_Face& aFace = TopoDS::Face(aFaceIt.Current());
      aT                       = BRep_Tool::Triangulation(aFace, aLoc);
      if (!aT.IsNull())
      {
        aNbTriangles += aT->NbTriangles();
        aNbVertices += aT->NbNodes();
      }
    }
    if (aNbVertices < 3 || aNbTriangles <= 0)
    {
      return occ::handle<Graphic3d_ArrayOfTriangles>();
    }

    occ::handle<Graphic3d_ArrayOfTriangles> anArray =
      new Graphic3d_ArrayOfTriangles(aNbVertices, 3 * aNbTriangles, true, false, theHasTexels);
    double aUmin(0.0), aUmax(0.0), aVmin(0.0), aVmax(0.0), dUmax(0.0), dVmax(0.0);
    for (aFaceIt.Init(theShape, TopAbs_FACE); aFaceIt.More(); aFaceIt.Next())
    {
      const TopoDS_Face& aFace = TopoDS::Face(aFaceIt.Current());
      aT                       = BRep_Tool::Triangulation(aFace, aLoc);
      if (aT.IsNull() || !aT->HasGeometry())
      {
        continue;
      }
      const gp_Trsf& aTrsf = aLoc.Transformation();

      bool isMirrored = aTrsf.VectorialPart().Determinant() < 0;

      StdPrs_ToolTriangulatedShape::ComputeNormals(aFace, aT);

      if (theHasTexels)
      {
        BRepTools::UVBounds(aFace, aUmin, aUmax, aVmin, aVmax);
        dUmax = (aUmax - aUmin);
        dVmax = (aVmax - aVmin);
      }

      const int aDecal = anArray->VertexNumber();
      for (int aNodeIter = 1; aNodeIter <= aT->NbNodes(); ++aNodeIter)
      {
        aPoint       = aT->Node(aNodeIter);
        gp_Dir aNorm = aT->Normal(aNodeIter);
        if ((aFace.Orientation() == TopAbs_REVERSED) ^ isMirrored)
        {
          aNorm.Reverse();
        }
        if (!aLoc.IsIdentity())
        {
          aPoint.Transform(aTrsf);
          aNorm.Transform(aTrsf);
        }

        if (theHasTexels && aT->HasUVNodes())
        {
          const gp_Pnt2d aNode2d = aT->UVNode(aNodeIter);
          const gp_Pnt2d aTexel =
            (dUmax == 0.0 || dVmax == 0.0)
              ? aNode2d
              : gp_Pnt2d((-theUVOrigin.X() + (theUVRepeat.X() * (aNode2d.X() - aUmin)) / dUmax)
                           / theUVScale.X(),
                         (-theUVOrigin.Y() + (theUVRepeat.Y() * (aNode2d.Y() - aVmin)) / dVmax)
                           / theUVScale.Y());
          anArray->AddVertex(aPoint, aNorm, aTexel);
        }
        else
        {
          anArray->AddVertex(aPoint, aNorm);
        }
      }

      int anIndex[3];
      for (int aTriIter = 1; aTriIter <= aT->NbTriangles(); ++aTriIter)
      {
        if ((aFace.Orientation() == TopAbs_REVERSED))
        {
          aT->Triangle(aTriIter).Get(anIndex[0], anIndex[2], anIndex[1]);
        }
        else
        {
          aT->Triangle(aTriIter).Get(anIndex[0], anIndex[1], anIndex[2]);
        }

        const gp_Pnt aP1 = aT->Node(anIndex[0]);
        const gp_Pnt aP2 = aT->Node(anIndex[1]);
        const gp_Pnt aP3 = aT->Node(anIndex[2]);

        gp_Vec aV1(aP1, aP2);
        if (aV1.SquareMagnitude() <= aPreci)
        {
          continue;
        }
        gp_Vec aV2(aP2, aP3);
        if (aV2.SquareMagnitude() <= aPreci)
        {
          continue;
        }
        gp_Vec aV3(aP3, aP1);
        if (aV3.SquareMagnitude() <= aPreci)
        {
          continue;
        }
        aV1.Normalize();
        aV2.Normalize();
        aV1.Cross(aV2);
        if (aV1.SquareMagnitude() > aPreci)
        {
          anArray->AddEdges(anIndex[0] + aDecal, anIndex[1] + aDecal, anIndex[2] + aDecal);
        }
      }
    }
    return anArray;
  }

  static bool shadeFromShape(const TopoDS_Shape&                    theShape,
                             const occ::handle<Prs3d_Presentation>& thePrs,
                             const occ::handle<Prs3d_Drawer>&       theDrawer,
                             const bool                             theHasTexels,
                             const gp_Pnt2d&                        theUVOrigin,
                             const gp_Pnt2d&                        theUVRepeat,
                             const gp_Pnt2d&                        theUVScale,
                             const bool                             theIsClosed,
                             const occ::handle<Graphic3d_Group>&    theGroup = nullptr)
  {
    occ::handle<Graphic3d_ArrayOfTriangles> aPArray =
      fillTriangles(theShape, theHasTexels, theUVOrigin, theUVRepeat, theUVScale);
    if (aPArray.IsNull())
    {
      return false;
    }

    occ::handle<Graphic3d_Group> aGroup = !theGroup.IsNull() ? theGroup : thePrs->NewGroup();
    aGroup->SetClosed(theIsClosed);
    aGroup->SetGroupPrimitivesAspect(theDrawer->ShadingAspect()->Aspect());
    aGroup->AddPrimitiveArray(aPArray);
    return true;
  }

  static occ::handle<Graphic3d_ArrayOfSegments> fillFaceBoundaries(const TopoDS_Shape& theShape,
                                                                   GeomAbs_Shape theUpperContinuity)
  {

    int aNodeNumber  = 0;
    int aNbPolylines = 0;

    TopLoc_Location aTrsf;

    Handle(NCollection_Shared<NCollection_Sequence<gp_Pnt>>) aSeqPntsExtra;
    for (TopExp_Explorer aFaceIter(theShape, TopAbs_FACE); aFaceIter.More(); aFaceIter.Next())
    {
      const TopoDS_Face& aFace = TopoDS::Face(aFaceIter.Current());
      if (aFace.NbChildren() == 0)
      {

        if (aSeqPntsExtra.IsNull())
        {
          occ::handle<NCollection_IncAllocator> anIncAlloc = new NCollection_IncAllocator();
          aSeqPntsExtra = new NCollection_Shared<NCollection_Sequence<gp_Pnt>>(anIncAlloc);
        }
        StdPrs_WFShape::AddEdgesOnTriangulation(*aSeqPntsExtra, aFace, false);
      }
    }

    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>
      anEdgesMap;
    TopExp::MapShapesAndAncestors(theShape, TopAbs_EDGE, TopAbs_FACE, anEdgesMap);
    for (NCollection_IndexedDataMap<TopoDS_Shape,
                                    NCollection_List<TopoDS_Shape>,
                                    TopTools_ShapeMapHasher>::Iterator anEdgeIter(anEdgesMap);
         anEdgeIter.More();
         anEdgeIter.Next())
    {

      if (anEdgeIter.Value().Extent() == 0)
      {
        continue;
      }

      const TopoDS_Face&              aFace          = TopoDS::Face(anEdgeIter.Value().First());
      occ::handle<Poly_Triangulation> aTriangulation = BRep_Tool::Triangulation(aFace, aTrsf);
      if (aTriangulation.IsNull())
      {
        continue;
      }

      const TopoDS_Edge& anEdge = TopoDS::Edge(anEdgeIter.Key());
      if (theUpperContinuity < GeomAbs_CN && anEdgeIter.Value().Extent() >= 2
          && BRep_Tool::MaxContinuity(anEdge) > theUpperContinuity)
      {
        continue;
      }

      occ::handle<Poly_PolygonOnTriangulation> anEdgePoly =
        BRep_Tool::PolygonOnTriangulation(anEdge, aTriangulation, aTrsf);
      if (!anEdgePoly.IsNull() && anEdgePoly->Nodes().Length() >= 2)
      {
        aNodeNumber += anEdgePoly->Nodes().Length();
        ++aNbPolylines;
      }
    }
    const int aNbExtra = !aSeqPntsExtra.IsNull() ? aSeqPntsExtra->Size() : 0;
    if (aNodeNumber == 0)
    {
      if (aNbExtra < 2)
      {
        return occ::handle<Graphic3d_ArrayOfSegments>();
      }

      occ::handle<Graphic3d_ArrayOfSegments> aSegments = new Graphic3d_ArrayOfSegments(aNbExtra);
      for (NCollection_Sequence<gp_Pnt>::Iterator aPntIter(*aSeqPntsExtra); aPntIter.More();
           aPntIter.Next())
      {
        aSegments->AddVertex(aPntIter.Value());
      }
      return aSegments;
    }

    const int                              aSegmentEdgeNb = (aNodeNumber - aNbPolylines) * 2;
    occ::handle<Graphic3d_ArrayOfSegments> aSegments =
      new Graphic3d_ArrayOfSegments(aNodeNumber + aNbExtra, aSegmentEdgeNb + aNbExtra);
    for (NCollection_IndexedDataMap<TopoDS_Shape,
                                    NCollection_List<TopoDS_Shape>,
                                    TopTools_ShapeMapHasher>::Iterator anEdgeIter(anEdgesMap);
         anEdgeIter.More();
         anEdgeIter.Next())
    {
      if (anEdgeIter.Value().Extent() == 0)
      {
        continue;
      }

      const TopoDS_Face&              aFace          = TopoDS::Face(anEdgeIter.Value().First());
      occ::handle<Poly_Triangulation> aTriangulation = BRep_Tool::Triangulation(aFace, aTrsf);
      if (aTriangulation.IsNull())
      {
        continue;
      }

      const TopoDS_Edge& anEdge = TopoDS::Edge(anEdgeIter.Key());
      if (theUpperContinuity < GeomAbs_CN && anEdgeIter.Value().Extent() >= 2
          && BRep_Tool::MaxContinuity(anEdge) > theUpperContinuity)
      {
        continue;
      }

      occ::handle<Poly_PolygonOnTriangulation> anEdgePoly =
        BRep_Tool::PolygonOnTriangulation(anEdge, aTriangulation, aTrsf);
      if (anEdgePoly.IsNull() || anEdgePoly->Nodes().Length() < 2)
      {
        continue;
      }

      const NCollection_Array1<int>& anEdgeNodes = anEdgePoly->Nodes();

      int aSegmentEdge = aSegments->VertexNumber() + 1;
      for (int aNodeIdx = anEdgeNodes.Lower(); aNodeIdx <= anEdgeNodes.Upper(); ++aNodeIdx)
      {

        const int aTriIndex = anEdgeNodes.Value(aNodeIdx);
        gp_Pnt    aTriNode  = aTriangulation->Node(aTriIndex);
        if (!aTrsf.IsIdentity())
        {
          aTriNode.Transform(aTrsf);
        }

        aSegments->AddVertex(aTriNode);
        if (aNodeIdx != anEdgeNodes.Lower())
        {
          aSegments->AddEdge(aSegmentEdge);
          aSegments->AddEdge(++aSegmentEdge);
        }
      }
    }

    if (!aSeqPntsExtra.IsNull())
    {
      int aSegmentEdge = aSegments->VertexNumber();
      for (NCollection_Sequence<gp_Pnt>::Iterator aPntIter(*aSeqPntsExtra); aPntIter.More();
           aPntIter.Next())
      {
        aSegments->AddVertex(aPntIter.Value());
        aSegments->AddEdge(++aSegmentEdge);
      }
    }

    return aSegments;
  }

} // namespace

void StdPrs_ShadedShape::ExploreSolids(const TopoDS_Shape& theShape,
                                       const BRep_Builder& theBuilder,
                                       TopoDS_Compound&    theClosed,
                                       TopoDS_Compound&    theOpened,
                                       const bool          theIgnore1DSubShape)
{
  if (theShape.IsNull())
  {
    return;
  }

  switch (theShape.ShapeType())
  {
    case TopAbs_COMPOUND:
    case TopAbs_COMPSOLID:
    {
      for (TopoDS_Iterator anIter(theShape); anIter.More(); anIter.Next())
      {
        ExploreSolids(anIter.Value(), theBuilder, theClosed, theOpened, theIgnore1DSubShape);
      }
      return;
    }
    case TopAbs_SOLID:
    {
      for (TopoDS_Iterator anIter(theShape); anIter.More(); anIter.Next())
      {
        const TopoDS_Shape& aSubShape = anIter.Value();
        const bool          isClosed  = aSubShape.ShapeType() == TopAbs_SHELL
                              && BRep_Tool::IsClosed(aSubShape)
                              && StdPrs_ToolTriangulatedShape::IsTriangulated(aSubShape);
        theBuilder.Add(isClosed ? theClosed : theOpened, aSubShape);
      }
      return;
    }
    case TopAbs_SHELL:
    case TopAbs_FACE:
    {
      theBuilder.Add(theOpened, theShape);
      return;
    }
    case TopAbs_WIRE:
    case TopAbs_EDGE:
    case TopAbs_VERTEX:
    {
      if (!theIgnore1DSubShape)
      {
        theBuilder.Add(theOpened, theShape);
      }
      return;
    }
    case TopAbs_SHAPE:
    default:
      return;
  }
}

void StdPrs_ShadedShape::Add(const occ::handle<Prs3d_Presentation>& thePrs,
                             const TopoDS_Shape&                    theShape,
                             const occ::handle<Prs3d_Drawer>&       theDrawer,
                             const StdPrs_Volume                    theVolume,
                             const occ::handle<Graphic3d_Group>&    theGroup)
{
  gp_Pnt2d aDummy;
  StdPrs_ShadedShape::Add(thePrs,
                          theShape,
                          theDrawer,
                          false,
                          aDummy,
                          aDummy,
                          aDummy,
                          theVolume,
                          theGroup);
}

void StdPrs_ShadedShape::Add(const occ::handle<Prs3d_Presentation>& thePrs,
                             const TopoDS_Shape&                    theShape,
                             const occ::handle<Prs3d_Drawer>&       theDrawer,
                             const bool                             theHasTexels,
                             const gp_Pnt2d&                        theUVOrigin,
                             const gp_Pnt2d&                        theUVRepeat,
                             const gp_Pnt2d&                        theUVScale,
                             const StdPrs_Volume                    theVolume,
                             const occ::handle<Graphic3d_Group>&    theGroup)
{
  if (theShape.IsNull())
  {
    return;
  }

  if (theDrawer->IsAutoTriangulation())
  {

    StdPrs_ToolTriangulatedShape::Tessellate(theShape, theDrawer);
  }

  wireframeFromShape(thePrs, theShape, theDrawer);

  wireframeNoTriangFacesFromShape(thePrs, theShape, theDrawer);

  if ((theShape.ShapeType() == TopAbs_COMPOUND || theShape.ShapeType() == TopAbs_COMPSOLID
       || theShape.ShapeType() == TopAbs_SOLID)
      && theVolume == StdPrs_Volume_Autodetection)
  {

    TopoDS_Compound anOpened, aClosed;
    BRep_Builder    aBuilder;
    aBuilder.MakeCompound(aClosed);
    aBuilder.MakeCompound(anOpened);
    ExploreSolids(theShape, aBuilder, aClosed, anOpened, true);

    if (aClosed.NbChildren() > 0)
    {
      shadeFromShape(aClosed,
                     thePrs,
                     theDrawer,
                     theHasTexels,
                     theUVOrigin,
                     theUVRepeat,
                     theUVScale,
                     true,
                     theGroup);
    }

    if (anOpened.NbChildren() > 0)
    {
      shadeFromShape(anOpened,
                     thePrs,
                     theDrawer,
                     theHasTexels,
                     theUVOrigin,
                     theUVRepeat,
                     theUVScale,
                     false,
                     theGroup);
    }
  }
  else
  {

    shadeFromShape(theShape,
                   thePrs,
                   theDrawer,
                   theHasTexels,
                   theUVOrigin,
                   theUVRepeat,
                   theUVScale,
                   theVolume == StdPrs_Volume_Closed,
                   theGroup);
  }

  if (theDrawer->FaceBoundaryDraw())
  {
    if (occ::handle<Graphic3d_ArrayOfSegments> aBndSegments =
          fillFaceBoundaries(theShape, theDrawer->FaceBoundaryUpperContinuity()))
    {
      occ::handle<Graphic3d_Group> aPrsGrp = !theGroup.IsNull() ? theGroup : thePrs->NewGroup();
      aPrsGrp->SetGroupPrimitivesAspect(theDrawer->FaceBoundaryAspect()->Aspect());
      aPrsGrp->AddPrimitiveArray(aBndSegments);
    }
  }
}

occ::handle<Graphic3d_ArrayOfTriangles> StdPrs_ShadedShape::FillTriangles(
  const TopoDS_Shape& theShape,
  const bool          theHasTexels,
  const gp_Pnt2d&     theUVOrigin,
  const gp_Pnt2d&     theUVRepeat,
  const gp_Pnt2d&     theUVScale)
{
  return fillTriangles(theShape, theHasTexels, theUVOrigin, theUVRepeat, theUVScale);
}

occ::handle<Graphic3d_ArrayOfSegments> StdPrs_ShadedShape::FillFaceBoundaries(
  const TopoDS_Shape& theShape,
  GeomAbs_Shape       theUpperContinuity)
{
  return fillFaceBoundaries(theShape, theUpperContinuity);
}

void StdPrs_ShadedShape::AddWireframeForFreeElements(const occ::handle<Prs3d_Presentation>& thePrs,
                                                     const TopoDS_Shape&              theShape,
                                                     const occ::handle<Prs3d_Drawer>& theDrawer)
{
  wireframeFromShape(thePrs, theShape, theDrawer);
}

void StdPrs_ShadedShape::AddWireframeForFacesWithoutTriangles(
  const occ::handle<Prs3d_Presentation>& thePrs,
  const TopoDS_Shape&                    theShape,
  const occ::handle<Prs3d_Drawer>&       theDrawer)
{
  wireframeNoTriangFacesFromShape(thePrs, theShape, theDrawer);
}
