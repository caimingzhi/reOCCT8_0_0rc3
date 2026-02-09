

#include <StlAPI_Writer.hpp>

#include <Bnd_Box.hpp>
#include <Message.hpp>
#include <OSD_OpenFile.hpp>
#include <RWStl.hpp>
#include <BRep_Tool.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopExp_Explorer.hpp>
#include <Poly_Triangulation.hpp>
#include <fstream>

StlAPI_Writer::StlAPI_Writer()
    : myASCIIMode(true)
{
}

bool StlAPI_Writer::Write(const TopoDS_Shape&          theShape,
                          const char*                  theFileName,
                          const Message_ProgressRange& theProgress)
{
  std::ofstream aStream(theFileName, myASCIIMode ? std::ios::out : std::ios::binary);
  if (!aStream.is_open())
  {
    return false;
  }

  return Write(theShape, aStream, theProgress);
}

bool StlAPI_Writer::Write(const TopoDS_Shape&          theShape,
                          Standard_OStream&            theStream,
                          const Message_ProgressRange& theProgress)
{
  int aNbNodes     = 0;
  int aNbTriangles = 0;

  for (TopExp_Explorer anExpSF(theShape, TopAbs_FACE); anExpSF.More(); anExpSF.Next())
  {
    TopLoc_Location                 aLoc;
    occ::handle<Poly_Triangulation> aTriangulation =
      BRep_Tool::Triangulation(TopoDS::Face(anExpSF.Current()), aLoc);
    if (!aTriangulation.IsNull())
    {
      aNbNodes += aTriangulation->NbNodes();
      aNbTriangles += aTriangulation->NbTriangles();
    }
  }

  if (aNbTriangles == 0)
  {

    return false;
  }

  occ::handle<Poly_Triangulation> aMesh = new Poly_Triangulation(aNbNodes, aNbTriangles, false);

  int aNbFacesNoTri = 0;

  int aNodeOffset    = 0;
  int aTriangleOffet = 0;
  for (TopExp_Explorer anExpSF(theShape, TopAbs_FACE); anExpSF.More(); anExpSF.Next())
  {
    const TopoDS_Shape&             aFace = anExpSF.Current();
    TopLoc_Location                 aLoc;
    occ::handle<Poly_Triangulation> aTriangulation =
      BRep_Tool::Triangulation(TopoDS::Face(aFace), aLoc);
    if (aTriangulation.IsNull())
    {
      ++aNbFacesNoTri;
      continue;
    }

    gp_Trsf aTrsf = aLoc.Transformation();
    for (int aNodeIter = 1; aNodeIter <= aTriangulation->NbNodes(); ++aNodeIter)
    {
      gp_Pnt aPnt = aTriangulation->Node(aNodeIter);
      aPnt.Transform(aTrsf);
      aMesh->SetNode(aNodeIter + aNodeOffset, aPnt);
    }

    const TopAbs_Orientation anOrientation = anExpSF.Current().Orientation();
    for (int aTriIter = 1; aTriIter <= aTriangulation->NbTriangles(); ++aTriIter)
    {
      Poly_Triangle aTri = aTriangulation->Triangle(aTriIter);

      int anId[3];
      aTri.Get(anId[0], anId[1], anId[2]);
      if (anOrientation == TopAbs_REVERSED)
      {

        int aTmpIdx = anId[1];
        anId[1]     = anId[2];
        anId[2]     = aTmpIdx;
      }

      anId[0] += aNodeOffset;
      anId[1] += aNodeOffset;
      anId[2] += aNodeOffset;

      aTri.Set(anId[0], anId[1], anId[2]);
      aMesh->SetTriangle(aTriIter + aTriangleOffet, aTri);
    }

    aNodeOffset += aTriangulation->NbNodes();
    aTriangleOffet += aTriangulation->NbTriangles();
  }

  bool isDone = (myASCIIMode ? RWStl::WriteAscii(aMesh, theStream, theProgress)
                             : RWStl::WriteBinary(aMesh, theStream, theProgress));

  if (isDone && (aNbFacesNoTri > 0))
  {

    TCollection_AsciiString aWarningMsg =
      TCollection_AsciiString("Warning: ") + TCollection_AsciiString(aNbFacesNoTri)
      + TCollection_AsciiString((aNbFacesNoTri == 1) ? " face has" : " faces have")
      + TCollection_AsciiString(" been skipped due to null triangulation");
    Message::SendWarning(aWarningMsg);
  }

  return isDone;
}
