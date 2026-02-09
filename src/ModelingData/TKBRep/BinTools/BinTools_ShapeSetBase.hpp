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

Standard_OStream& operator<<(Standard_OStream& OS, const gp_Pnt& P);

class BinTools_ShapeSetBase
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BinTools_ShapeSetBase();

  Standard_EXPORT virtual ~BinTools_ShapeSetBase();

  bool IsWithTriangles() const { return myWithTriangles; }

  bool IsWithNormals() const { return myWithNormals; }

  void SetWithTriangles(const bool theWithTriangles) { myWithTriangles = theWithTriangles; }

  void SetWithNormals(const bool theWithNormals) { myWithNormals = theWithNormals; }

  Standard_EXPORT void SetFormatNb(const int theFormatNb);

  Standard_EXPORT int FormatNb() const { return myFormatNb; }

  Standard_EXPORT virtual void Clear() {}

  Standard_EXPORT virtual void Write(Standard_OStream&,
                                     const Message_ProgressRange& = Message_ProgressRange())
  {
  }

  Standard_EXPORT virtual void Read(Standard_IStream&,
                                    const Message_ProgressRange& = Message_ProgressRange())
  {
  }

  Standard_EXPORT virtual void Write(const TopoDS_Shape&, Standard_OStream&) {}

  Standard_EXPORT virtual void Read(Standard_IStream&, TopoDS_Shape&) {}

  static const char* THE_ASCII_VERSIONS[BinTools_FormatVersion_UPPER + 1];

private:
  int  myFormatNb;
  bool myWithTriangles;
  bool myWithNormals;
};
