

#include <RWObj_CafReader.hpp>

IMPLEMENT_STANDARD_RTTIEXT(RWObj_CafReader, RWMesh_CafReader)

RWObj_CafReader::RWObj_CafReader()
    : myIsSinglePrecision(false)
{

  myCoordSysConverter.SetInputCoordinateSystem(RWMesh_CoordinateSystem_glTF);
}

void RWObj_CafReader::BindNamedShape(const TopoDS_Shape&            theShape,
                                     const TCollection_AsciiString& theName,
                                     const RWObj_Material*          theMaterial,
                                     const bool                     theIsRootShape)
{
  if (theShape.IsNull())
  {
    return;
  }

  RWMesh_NodeAttributes aShapeAttribs;
  aShapeAttribs.Name = theName;
  if (theMaterial != nullptr)
  {

    occ::handle<XCAFDoc_VisMaterial> aMat = new XCAFDoc_VisMaterial();
    if (!myObjMaterialMap.Find(theMaterial->Name, aMat))
    {
      XCAFDoc_VisMaterialCommon aMatXde;
      aMatXde.IsDefined     = true;
      aMatXde.AmbientColor  = theMaterial->AmbientColor;
      aMatXde.DiffuseColor  = theMaterial->DiffuseColor;
      aMatXde.SpecularColor = theMaterial->SpecularColor;
      aMatXde.Shininess     = theMaterial->Shininess;
      aMatXde.Transparency  = theMaterial->Transparency;
      if (!theMaterial->DiffuseTexture.IsEmpty())
      {
        aMatXde.DiffuseTexture = new Image_Texture(theMaterial->DiffuseTexture);
      }

      aMat = new XCAFDoc_VisMaterial();
      aMat->SetCommonMaterial(aMatXde);
      aMat->SetRawName(new TCollection_HAsciiString(theMaterial->Name));
      myObjMaterialMap.Bind(theMaterial->Name, aMat);
    }
    aShapeAttribs.Style.SetMaterial(aMat);
  }
  myAttribMap.Bind(theShape, aShapeAttribs);

  if (theIsRootShape)
  {
    myRootShapes.Append(theShape);
  }
}

occ::handle<RWObj_TriangulationReader> RWObj_CafReader::createReaderContext()
{
  occ::handle<RWObj_TriangulationReader> aReader = new RWObj_TriangulationReader();
  return aReader;
}

bool RWObj_CafReader::performMesh(std::istream&                  theStream,
                                  const TCollection_AsciiString& theFile,
                                  const Message_ProgressRange&   theProgress,
                                  const bool                     theToProbe)
{
  occ::handle<RWObj_TriangulationReader> aCtx = createReaderContext();
  aCtx->SetSinglePrecision(myIsSinglePrecision);
  aCtx->SetCreateShapes(true);
  aCtx->SetShapeReceiver(this);
  aCtx->SetTransformation(myCoordSysConverter);
  aCtx->SetMemoryLimit(myMemoryLimitMiB == -1 ? size_t(-1)
                                              : size_t(myMemoryLimitMiB * 1024 * 1024));
  bool isDone = false;
  if (theToProbe)
  {
    isDone = aCtx->Probe(theStream, theFile, theProgress);
  }
  else
  {
    isDone = aCtx->Read(theStream, theFile, theProgress);
  }
  if (!aCtx->FileComments().IsEmpty())
  {
    myMetadata.Add("Comments", aCtx->FileComments());
  }
  for (NCollection_IndexedMap<TCollection_AsciiString>::Iterator aFileIter(aCtx->ExternalFiles());
       aFileIter.More();
       aFileIter.Next())
  {
    myExternalFiles.Add(aFileIter.Value());
  }
  return isDone;
}
