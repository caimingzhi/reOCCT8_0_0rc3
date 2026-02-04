#pragma once


#include <Standard_Handle.hpp>
#include <Standard_IStream.hpp>

class TopoDS_Shape;

//! Reading from stereolithography format.
//! Reads STL file and creates a shape composed of triangular faces, one per facet.
//! IMPORTANT: This approach is very inefficient, especially for large files.
//! IMPORTANT: Consider reading STL file to Poly_Triangulation object instead (see class RWStl).
class StlAPI_Reader
{
public:
  //! Reads STL file to the TopoDS_Shape (each triangle is converted to the face).
  //! @return True if reading is successful
  Standard_EXPORT bool Read(TopoDS_Shape& theShape, const char* theFileName);

  //! Reads STL data from stream to the TopoDS_Shape (each triangle is converted to the face).
  //! @param theShape result shape
  //! @param theStream stream to read from
  //! @return True if reading is successful
  Standard_EXPORT bool Read(TopoDS_Shape& theShape, Standard_IStream& theStream);
};

