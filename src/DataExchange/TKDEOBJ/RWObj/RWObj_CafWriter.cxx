

#include <RWObj_CafWriter.hpp>

#include <Message.hpp>
#include <Message_LazyProgressScope.hpp>
#include <OSD_OpenFile.hpp>
#include <OSD_Path.hpp>
#include <RWMesh_FaceIterator.hpp>
#include <RWObj_ObjMaterialMap.hpp>
#include <RWObj_ObjWriterContext.hpp>
#include <Standard_CLocaleSentry.hpp>
#include <TDocStd_Document.hpp>
#include <TDataStd_Name.hpp>
#include <XCAFDoc_DocumentTool.hpp>
#include <XCAFDoc_ShapeTool.hpp>
#include <XCAFPrs_DocumentExplorer.hpp>

IMPLEMENT_STANDARD_RTTIEXT(RWObj_CafWriter, Standard_Transient)

namespace
{

  inline NCollection_Vec3<float> objXyzToVec(const gp_XYZ& thePnt)
  {
    return NCollection_Vec3<float>((float)thePnt.X(), (float)thePnt.Y(), (float)thePnt.Z());
  }

  inline NCollection_Vec2<float> objXyToVec(const gp_XY& thePnt)
  {
    return NCollection_Vec2<float>((float)thePnt.X(), (float)thePnt.Y());
  }

  static TCollection_AsciiString readNameAttribute(const TDF_Label& theRefLabel)
  {
    occ::handle<TDataStd_Name> aNodeName;
    if (!theRefLabel.FindAttribute(TDataStd_Name::GetID(), aNodeName))
    {
      return TCollection_AsciiString();
    }
    return TCollection_AsciiString(aNodeName->Get());
  }
} // namespace

RWObj_CafWriter::RWObj_CafWriter(const TCollection_AsciiString& theFile)
    : myFile(theFile)
{
}

RWObj_CafWriter::~RWObj_CafWriter() = default;

bool RWObj_CafWriter::toSkipFaceMesh(const RWMesh_FaceIterator& theFaceIter)
{
  return theFaceIter.IsEmptyMesh();
}

bool RWObj_CafWriter::Perform(
  const occ::handle<TDocStd_Document>&                                                theDocument,
  const NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theFileInfo,
  const Message_ProgressRange&                                                        theProgress)
{
  NCollection_Sequence<TDF_Label> aRoots;
  occ::handle<XCAFDoc_ShapeTool>  aShapeTool = XCAFDoc_DocumentTool::ShapeTool(theDocument->Main());
  aShapeTool->GetFreeShapes(aRoots);
  return Perform(theDocument, aRoots, nullptr, theFileInfo, theProgress);
}

bool RWObj_CafWriter::Perform(
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
    Message::SendFail("Nothing to export into OBJ file");
    return false;
  }

  int    aNbNodesAll = 0, aNbElemsAll = 0;
  double aNbPEntities    = 0;
  bool   toCreateMatFile = false;
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

      addFaceInfo(aFaceIter, aNbNodesAll, aNbElemsAll, aNbPEntities, toCreateMatFile);
    }
  }
  if (aNbNodesAll == 0 || aNbElemsAll == 0)
  {
    Message::SendFail("No mesh data to save");
    return false;
  }

  TCollection_AsciiString       aMatFileNameShort = aShortFileNameBase + ".mtl";
  const TCollection_AsciiString aMatFileNameFull =
    !aFolder.IsEmpty() ? aFolder + aMatFileNameShort : aMatFileNameShort;
  if (!toCreateMatFile)
  {
    aMatFileNameShort.Clear();
  }

  Standard_CLocaleSentry aLocaleSentry;
  RWObj_ObjWriterContext anObjFile(myFile);
  RWObj_ObjMaterialMap   aMatMgr(aMatFileNameFull);
  aMatMgr.SetDefaultStyle(myDefaultStyle);
  if (!anObjFile.IsOpened()
      || !anObjFile.WriteHeader(aNbNodesAll, aNbElemsAll, aMatFileNameShort, theFileInfo))
  {
    return false;
  }

  int aRootDepth = 0;
  if (theRootLabels.Size() == 1)
  {
    TDF_Label aRefLabel = theRootLabels.First();
    XCAFDoc_ShapeTool::GetReferredShape(theRootLabels.First(), aRefLabel);
    TCollection_AsciiString aRootName = readNameAttribute(aRefLabel);
    if (aRootName.EndsWith(".obj"))
    {

      aRootDepth = 1;
    }
  }

  const double              aPatchStep = 2048.0;
  Message_LazyProgressScope aPSentry(theProgress, "OBJ export", aNbPEntities, aPatchStep);

  bool isDone = true;
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

    TCollection_AsciiString aName = readNameAttribute(aDocNode.RefLabel);
    for (int aParentIter = aDocExplorer.CurrentDepth() - 1; aParentIter >= aRootDepth;
         --aParentIter)
    {
      const TCollection_AsciiString aParentName =
        readNameAttribute(aDocExplorer.Current(aParentIter).RefLabel);
      if (!aParentName.IsEmpty())
      {
        aName = aParentName + "/" + aName;
      }
    }

    if (!writeShape(anObjFile,
                    aMatMgr,
                    aPSentry,
                    aDocNode.RefLabel,
                    aDocNode.Location,
                    aDocNode.Style,
                    aName))
    {
      isDone = false;
      break;
    }
  }

  const bool isClosed = anObjFile.Close();
  if (isDone && !isClosed)
  {
    Message::SendFail(TCollection_AsciiString("Failed to write OBJ file\n") + myFile);
    return false;
  }
  return isDone && !aPSentry.IsAborted();
}

void RWObj_CafWriter::addFaceInfo(const RWMesh_FaceIterator& theFace,
                                  int&                       theNbNodes,
                                  int&                       theNbElems,
                                  double&                    theNbProgressSteps,
                                  bool&                      theToCreateMatFile)
{
  theNbNodes += theFace.NbNodes();
  theNbElems += theFace.NbTriangles();

  theNbProgressSteps += theFace.NbNodes();
  theNbProgressSteps += theFace.NbTriangles();
  if (theFace.HasNormals())
  {
    theNbProgressSteps += theFace.NbNodes();
  }
  if (theFace.HasTexCoords())
  {
    theNbProgressSteps += theFace.NbNodes();
  }

  theToCreateMatFile =
    theToCreateMatFile || theFace.HasFaceColor()
    || (!theFace.FaceStyle().BaseColorTexture().IsNull() && theFace.HasTexCoords());
}

bool RWObj_CafWriter::writeShape(RWObj_ObjWriterContext&        theWriter,
                                 RWObj_ObjMaterialMap&          theMatMgr,
                                 Message_LazyProgressScope&     thePSentry,
                                 const TDF_Label&               theLabel,
                                 const TopLoc_Location&         theParentTrsf,
                                 const XCAFPrs_Style&           theParentStyle,
                                 const TCollection_AsciiString& theName)
{
  bool toCreateGroup = true;
  for (RWMesh_FaceIterator aFaceIter(theLabel, theParentTrsf, true, theParentStyle);
       aFaceIter.More() && !thePSentry.IsAborted();
       aFaceIter.Next())
  {
    if (toSkipFaceMesh(aFaceIter))
    {
      continue;
    }

    ++theWriter.NbFaces;
    {
      const bool hasNormals = aFaceIter.HasNormals();

      const bool hasTexCoords = aFaceIter.HasTexCoords();

      if (theWriter.NbFaces != 1)
      {
        toCreateGroup = toCreateGroup || hasNormals != theWriter.HasNormals()
                        || hasTexCoords != theWriter.HasTexCoords();
      }
      theWriter.SetNormals(hasNormals);
      theWriter.SetTexCoords(hasTexCoords);
    }

    if (toCreateGroup && !theWriter.WriteGroup(theName))
    {
      return false;
    }
    toCreateGroup = false;

    TCollection_AsciiString aMatName;
    if (aFaceIter.HasFaceColor() || !aFaceIter.FaceStyle().BaseColorTexture().IsNull())
    {
      aMatName = theMatMgr.AddMaterial(aFaceIter.FaceStyle());
    }
    if (aMatName != theWriter.ActiveMaterial())
    {
      theWriter.WriteActiveMaterial(aMatName);
    }

    if (!writePositions(theWriter, thePSentry, aFaceIter))
    {
      return false;
    }

    if (theWriter.HasNormals() && !writeNormals(theWriter, thePSentry, aFaceIter))
    {
      return false;
    }

    if (theWriter.HasTexCoords() && !writeTextCoords(theWriter, thePSentry, aFaceIter))
    {
      return false;
    }

    if (!writeIndices(theWriter, thePSentry, aFaceIter))
    {
      return false;
    }
    theWriter.FlushFace(aFaceIter.NbNodes());
  }
  return true;
}

bool RWObj_CafWriter::writePositions(RWObj_ObjWriterContext&    theWriter,
                                     Message_LazyProgressScope& thePSentry,
                                     const RWMesh_FaceIterator& theFace)
{
  const int aNodeUpper = theFace.NodeUpper();
  for (int aNodeIter = theFace.NodeLower(); aNodeIter <= aNodeUpper && thePSentry.More();
       ++aNodeIter, thePSentry.Next())
  {
    gp_XYZ aNode = theFace.NodeTransformed(aNodeIter).XYZ();
    myCSTrsf.TransformPosition(aNode);
    if (!theWriter.WriteVertex(objXyzToVec(aNode)))
    {
      return false;
    }
  }
  return true;
}

bool RWObj_CafWriter::writeNormals(RWObj_ObjWriterContext&    theWriter,
                                   Message_LazyProgressScope& thePSentry,
                                   const RWMesh_FaceIterator& theFace)
{
  const int aNodeUpper = theFace.NodeUpper();
  for (int aNodeIter = theFace.NodeLower(); aNodeIter <= aNodeUpper && thePSentry.More();
       ++aNodeIter, thePSentry.Next())
  {
    const gp_Dir            aNormal   = theFace.NormalTransformed(aNodeIter);
    NCollection_Vec3<float> aNormVec3 = objXyzToVec(aNormal.XYZ());
    myCSTrsf.TransformNormal(aNormVec3);
    if (!theWriter.WriteNormal(aNormVec3))
    {
      return false;
    }
  }
  return true;
}

bool RWObj_CafWriter::writeTextCoords(RWObj_ObjWriterContext&    theWriter,
                                      Message_LazyProgressScope& thePSentry,
                                      const RWMesh_FaceIterator& theFace)
{
  const int aNodeUpper = theFace.NodeUpper();
  for (int aNodeIter = theFace.NodeLower(); aNodeIter <= aNodeUpper && thePSentry.More();
       ++aNodeIter, thePSentry.Next())
  {
    gp_Pnt2d aTexCoord = theFace.NodeTexCoord(aNodeIter);
    if (!theWriter.WriteTexCoord(objXyToVec(aTexCoord.XY())))
    {
      return false;
    }
  }
  return true;
}

bool RWObj_CafWriter::writeIndices(RWObj_ObjWriterContext&    theWriter,
                                   Message_LazyProgressScope& thePSentry,
                                   const RWMesh_FaceIterator& theFace)
{
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
  return true;
}
