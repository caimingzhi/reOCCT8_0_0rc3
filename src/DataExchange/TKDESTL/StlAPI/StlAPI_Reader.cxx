

#include <StlAPI_Reader.hpp>

#include <BRepBuilderAPI_MakeShapeOnMesh.hpp>
#include <BRepBuilderAPI_Sewing.hpp>
#include <RWStl.hpp>

bool StlAPI_Reader::Read(TopoDS_Shape& theShape, const char* theFileName)
{
  occ::handle<Poly_Triangulation> aMesh = RWStl::ReadFile(theFileName);
  if (aMesh.IsNull())
    return false;

  BRepBuilderAPI_MakeShapeOnMesh aConverter(aMesh);
  aConverter.Build();
  if (!aConverter.IsDone())
    return false;

  TopoDS_Shape aResult = aConverter.Shape();
  if (aResult.IsNull())
    return false;

  theShape = aResult;
  return true;
}

bool StlAPI_Reader::Read(TopoDS_Shape& theShape, Standard_IStream& theStream)
{
  occ::handle<Poly_Triangulation> aMesh = RWStl::ReadStream(theStream);
  if (aMesh.IsNull())
    return false;

  BRepBuilderAPI_MakeShapeOnMesh aConverter(aMesh);
  aConverter.Build();
  if (!aConverter.IsDone())
    return false;

  TopoDS_Shape aResult = aConverter.Shape();
  if (aResult.IsNull())
    return false;

  theShape = aResult;
  return true;
}
