

#include <RWPly_CafWriter.hpp>

#include <Message.hpp>
#include <Message_LazyProgressScope.hpp>
#include <OSD_Path.hpp>
#include <RWMesh_FaceIterator.hpp>
#include <RWMesh_MaterialMap.hpp>
#include <RWPly_PlyWriterContext.hpp>
#include <Standard_CLocaleSentry.hpp>
#include <TDocStd_Document.hpp>
#include <TDataStd_Name.hpp>
#include <XCAFDoc_DocumentTool.hpp>
#include <XCAFDoc_ShapeTool.hpp>
#include <XCAFPrs_DocumentExplorer.hpp>

IMPLEMENT_STANDARD_RTTIEXT(RWPly_CafWriter, Standard_Transient)

RWPly_CafWriter::RWPly_CafWriter(const TCollection_AsciiString& theFile)
    : myFile(theFile),
      myIsDoublePrec(false),
      myHasNormals(true),
      myHasColors(true),
      myHasTexCoords(false),
      myHasPartId(true),
      myHasFaceId(false)
{
}

RWPly_CafWriter::~RWPly_CafWriter() = default;

bool RWPly_CafWriter::toSkipFaceMesh(const RWMesh_FaceIterator& theFaceIter)
{
  return theFaceIter.IsEmptyMesh();
}

bool RWPly_CafWriter::Perform(
  const occ::handle<TDocStd_Document>&                                                theDocument,
  const NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theFileInfo,
  const Message_ProgressRange&                                                        theProgress)
{
  NCollection_Sequence<TDF_Label> aRoots;
  occ::handle<XCAFDoc_ShapeTool>  aShapeTool = XCAFDoc_DocumentTool::ShapeTool(theDocument->Main());
  aShapeTool->GetFreeShapes(aRoots);
  return Perform(theDocument, aRoots, nullptr, theFileInfo, theProgress);
}

bool RWPly_CafWriter::Perform(
  const occ::handle<TDocStd_Document>&            theDocument,
  const NCollection_Sequence<TDF_Label>&          theRootLabels,
  const NCollection_Map<TCollection_AsciiString>* theLabelFilter,
  const NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theFileInfo,
  const Message_ProgressRange&                                                        theProgress)
{
  TCollection_AsciiString aFolder, aFileName, aFullFileNameBase, aShortFileNameBase, aFileExt;
  OSD_Path::FolderAndFileFromPath(myFile, aFolder, aFileName);
  OSD_Path::FileNameAndExtension(aFileName, aShortFileNameBase, aFileExt);

  double aLengthUnit = 1.;
  if (XCAFDoc_DocumentTool::GetLengthUnit(theDocument, aLengthUnit))
  {
    myCSTrsf.SetInputLengthUnit(aLengthUnit);
  }

  if (theRootLabels.IsEmpty() || (theLabelFilter != nullptr && theLabelFilter->IsEmpty()))
  {
    Message::SendFail("Nothing to export into PLY file");
    return false;
  }

  int    aNbNodesAll = 0, aNbElemsAll = 0;
  double aNbPEntities = 0;
  for (XCAFPrs_DocumentExplorer aDocExplorer(theDocument,
                                             theRootLabels,
                                             XCAFPrs_DocumentExplorerFlags_OnlyLeafNodes);
       aDocExplorer.More();
       aDocExplorer.Next())
  {
    const XCAFPrs_DocumentNode& aDocNode = aDocExplorer.Current();
    if (theLabelFilter != nullptr && !theLabelFilter->Contains(aDocNode.Id))
    {
      continue;
    }

    for (RWMesh_FaceIterator aFaceIter(aDocNode.RefLabel, aDocNode.Location, true, aDocNode.Style);
         aFaceIter.More();
         aFaceIter.Next())
    {
      if (toSkipFaceMesh(aFaceIter))
      {
        continue;
      }

      addFaceInfo(aFaceIter, aNbNodesAll, aNbElemsAll);
      aNbPEntities += aNbNodesAll + aNbElemsAll;
    }
  }
  if (aNbNodesAll == 0)
  {
    Message::SendFail("No mesh data to save");
    return false;
  }

  Standard_CLocaleSentry aLocaleSentry;
  RWPly_PlyWriterContext aPlyCtx;
  aPlyCtx.SetDoublePrecision(myIsDoublePrec);
  aPlyCtx.SetNormals(myHasNormals);
  aPlyCtx.SetColors(myHasColors);
  aPlyCtx.SetTexCoords(myHasTexCoords);
  aPlyCtx.SetSurfaceId(myHasPartId || myHasFaceId);
  if (!aPlyCtx.Open(myFile) || !aPlyCtx.WriteHeader(aNbNodesAll, aNbElemsAll, theFileInfo))
  {
    return false;
  }

  const double              aPatchStep = 2048.0;
  Message_LazyProgressScope aPSentry(theProgress, "PLY export", aNbPEntities, aPatchStep);

  bool isDone = true;
  for (int aStepIter = 0; aStepIter < 2; ++aStepIter)
  {
    aPlyCtx.SetSurfaceId(0);
    for (XCAFPrs_DocumentExplorer aDocExplorer(theDocument,
                                               theRootLabels,
                                               XCAFPrs_DocumentExplorerFlags_OnlyLeafNodes);
         aDocExplorer.More() && !aPSentry.IsAborted();
         aDocExplorer.Next())
    {
      const XCAFPrs_DocumentNode& aDocNode = aDocExplorer.Current();
      if (theLabelFilter != nullptr && !theLabelFilter->Contains(aDocNode.Id))
      {
        continue;
      }

      if (myHasPartId)
      {
        aPlyCtx.SetSurfaceId(aPlyCtx.SurfaceId() + 1);
      }
      if (!writeShape(aPlyCtx,
                      aPSentry,
                      aStepIter,
                      aDocNode.RefLabel,
                      aDocNode.Location,
                      aDocNode.Style))
      {
        isDone = false;
        break;
      }
    }
  }

  const bool isClosed = aPlyCtx.Close();
  if (isDone && !isClosed)
  {
    Message::SendFail(TCollection_AsciiString("Failed to write PLY file\n") + myFile);
    return false;
  }
  return isDone && !aPSentry.IsAborted();
}

void RWPly_CafWriter::addFaceInfo(const RWMesh_FaceIterator& theFace,
                                  int&                       theNbNodes,
                                  int&                       theNbElems)
{
  theNbNodes += theFace.NbNodes();
  theNbElems += theFace.NbTriangles();
}

bool RWPly_CafWriter::writeShape(RWPly_PlyWriterContext&    theWriter,
                                 Message_LazyProgressScope& thePSentry,
                                 const int                  theWriteStep,
                                 const TDF_Label&           theLabel,
                                 const TopLoc_Location&     theParentTrsf,
                                 const XCAFPrs_Style&       theParentStyle)
{
  for (RWMesh_FaceIterator aFaceIter(theLabel, theParentTrsf, true, theParentStyle);
       aFaceIter.More() && !thePSentry.IsAborted();
       aFaceIter.Next())
  {
    if (toSkipFaceMesh(aFaceIter))
    {
      continue;
    }

    if (theWriteStep == 0 && !writeNodes(theWriter, thePSentry, aFaceIter))
    {
      return false;
    }
    if (theWriteStep == 1 && !writeIndices(theWriter, thePSentry, aFaceIter))
    {
      return false;
    }
  }
  return true;
}

bool RWPly_CafWriter::writeNodes(RWPly_PlyWriterContext&    theWriter,
                                 Message_LazyProgressScope& thePSentry,
                                 const RWMesh_FaceIterator& theFace)
{
  const int                 aNodeUpper = theFace.NodeUpper();
  NCollection_Vec3<float>   aNormVec;
  NCollection_Vec2<float>   aTexVec;
  NCollection_Vec4<uint8_t> aColorVec(255);
  if (theFace.HasFaceColor())
  {

    NCollection_Vec4<float> aColorF = theFace.FaceColor();
    aColorVec.SetValues((unsigned char)int(aColorF.r() * 255.0f),
                        (unsigned char)int(aColorF.g() * 255.0f),
                        (unsigned char)int(aColorF.b() * 255.0f),
                        (unsigned char)int(aColorF.a() * 255.0f));
  }
  for (int aNodeIter = theFace.NodeLower(); aNodeIter <= aNodeUpper && thePSentry.More();
       ++aNodeIter, thePSentry.Next())
  {
    gp_XYZ aNode = theFace.NodeTransformed(aNodeIter).XYZ();
    myCSTrsf.TransformPosition(aNode);
    if (theFace.HasNormals())
    {
      gp_Dir aNorm = theFace.NormalTransformed(aNodeIter);
      aNormVec.SetValues((float)aNorm.X(), (float)aNorm.Y(), (float)aNorm.Z());
      myCSTrsf.TransformNormal(aNormVec);
    }
    if (theFace.HasTexCoords())
    {
      const gp_Pnt2d aUV = theFace.NodeTexCoord(aNodeIter);
      aTexVec.SetValues((float)aUV.X(), (float)aUV.Y());
    }

    if (!theWriter.WriteVertex(aNode, aNormVec, aTexVec, aColorVec))
    {
      return false;
    }
  }
  return true;
}

bool RWPly_CafWriter::writeIndices(RWPly_PlyWriterContext&    theWriter,
                                   Message_LazyProgressScope& thePSentry,
                                   const RWMesh_FaceIterator& theFace)
{
  if (myHasFaceId)
  {
    theWriter.SetSurfaceId(theWriter.SurfaceId() + 1);
  }

  const int anElemLower = theFace.ElemLower();
  const int anElemUpper = theFace.ElemUpper();
  for (int anElemIter = anElemLower; anElemIter <= anElemUpper && thePSentry.More();
       ++anElemIter, thePSentry.Next())
  {
    const Poly_Triangle aTri = theFace.TriangleOriented(anElemIter);
    if (!theWriter.WriteTriangle(NCollection_Vec3<int>(aTri(1), aTri(2), aTri(3))
                                 - NCollection_Vec3<int>(anElemLower)))
    {
      return false;
    }
  }

  theWriter.SetVertexOffset(theWriter.VertexOffset() + theFace.NbNodes());
  return true;
}
