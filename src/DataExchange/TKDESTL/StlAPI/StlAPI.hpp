#pragma once


#include <Poly_Triangulation.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_CString.hpp>
class TopoDS_Shape;

//! Offers the API for STL data manipulation.
class StlAPI
{
public:
  DEFINE_STANDARD_ALLOC

  //! Convert and write shape to STL format.
  //! File is written in binary if aAsciiMode is False otherwise it is written in Ascii (by
  //! default).
  Standard_EXPORT static bool Write(const TopoDS_Shape& theShape,
                                    const char*         theFile,
                                    const bool          theAsciiMode = true);

  //! Legacy interface.
  //! Read STL file and create a shape composed of triangular faces, one per facet.
  //! This approach is very inefficient, especially for large files.
  //! Consider reading STL file to Poly_Triangulation object instead (see class RWStl).
  Standard_DEPRECATED("This method is very inefficient; see RWStl class for better alternative")
  Standard_EXPORT static bool Read(TopoDS_Shape& theShape, const char* aFile);
};

