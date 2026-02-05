#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>
#include <Standard_IStream.hpp>
#include <Message_ProgressRange.hpp>
#include <BinTools_FormatVersion.hpp>

class TopoDS_Shape;
class gp_Pnt;

//! Writes to the stream a gp_Pnt data
Standard_OStream& operator<<(Standard_OStream& OS, const gp_Pnt& P);

//! A base class for all readers/writers of TopoDS_Shape into/from stream.
class BinTools_ShapeSetBase
{
public:
  DEFINE_STANDARD_ALLOC

  //! A default constructor.
  Standard_EXPORT BinTools_ShapeSetBase();

  Standard_EXPORT virtual ~BinTools_ShapeSetBase();

  //! Return true if shape should be stored with triangles.
  bool IsWithTriangles() const { return myWithTriangles; }

  //! Return true if shape should be stored triangulation with normals.
  bool IsWithNormals() const { return myWithNormals; }

  //! Define if shape will be stored with triangles.
  //! Ignored (always written) if face defines only triangulation (no surface).
  void SetWithTriangles(const bool theWithTriangles) { myWithTriangles = theWithTriangles; }

  //! Define if shape will be stored triangulation with normals.
  //! Ignored (always written) if face defines only triangulation (no surface).
  void SetWithNormals(const bool theWithNormals) { myWithNormals = theWithNormals; }

  //! Sets the BinTools_FormatVersion.
  Standard_EXPORT void SetFormatNb(const int theFormatNb);

  //! Returns the BinTools_FormatVersion.
  Standard_EXPORT int FormatNb() const { return myFormatNb; }

  //! Clears the content of the set.
  Standard_EXPORT virtual void Clear() {}

  //! Writes the content of me on the stream <OS> in binary
  //! format that can be read back by Read.
  //!
  //! Writes the locations.
  //!
  //! Writes the geometry calling WriteGeometry.
  //!
  //! Dumps the shapes from last to first.
  //! For each shape:
  //! Write the type.
  //! calls WriteGeometry(S).
  //! Write the flags, the subshapes.
  Standard_EXPORT virtual void Write(
    Standard_OStream& /*OS*/,
    const Message_ProgressRange& /*theRange*/ = Message_ProgressRange())
  {
  }

  //! Reads the content of me from the binary stream <IS>. me
  //! is first cleared.
  //!
  //! Reads the locations.
  //!
  //! Reads the geometry calling ReadGeometry.
  //!
  //! Reads the shapes.
  //! For each shape
  //! Reads the type.
  //! calls ReadGeometry(T,S).
  //! Reads the flag, the subshapes.
  Standard_EXPORT virtual void Read(
    Standard_IStream& /*IS*/,
    const Message_ProgressRange& /*theRange*/ = Message_ProgressRange())
  {
  }

  //! Writes on <OS> the shape <S>. Writes the
  //! orientation, the index of the TShape and the index
  //! of the Location.
  Standard_EXPORT virtual void Write(const TopoDS_Shape& /*theShape*/,
                                     Standard_OStream& /*theStream*/)
  {
  }

  //! An empty virtual method for redefinition in shape-reader.
  Standard_EXPORT virtual void Read(Standard_IStream& /*theStream*/, TopoDS_Shape& /*theShape*/) {}

  static const char* THE_ASCII_VERSIONS[BinTools_FormatVersion_UPPER + 1];

private:
  int  myFormatNb;
  bool myWithTriangles;
  bool myWithNormals;
};
