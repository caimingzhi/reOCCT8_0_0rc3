#pragma once

#include <Standard_Handle.hpp>
#include <Standard_IStream.hpp>

class TopoDS_Shape;

class StlAPI_Reader
{
public:
  Standard_EXPORT bool Read(TopoDS_Shape& theShape, const char* theFileName);

  Standard_EXPORT bool Read(TopoDS_Shape& theShape, Standard_IStream& theStream);
};
