#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TopTools_LocationSet.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
#include <Standard_IStream.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopTools_FormatVersion.hpp>

class TopoDS_Shape;
class TCollection_AsciiString;

class TopTools_ShapeSet
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopTools_ShapeSet();

  Standard_EXPORT virtual ~TopTools_ShapeSet();

  Standard_EXPORT void SetFormatNb(const int theFormatNb);

  Standard_EXPORT int FormatNb() const;

  Standard_EXPORT virtual void Clear();

  Standard_EXPORT int Add(const TopoDS_Shape& S);

  Standard_EXPORT const TopoDS_Shape& Shape(const int I) const;

  Standard_EXPORT int Index(const TopoDS_Shape& S) const;

  Standard_EXPORT const TopTools_LocationSet& Locations() const;

  Standard_EXPORT TopTools_LocationSet& ChangeLocations();

  Standard_EXPORT Standard_OStream& DumpExtent(Standard_OStream& OS) const;

  Standard_EXPORT void DumpExtent(TCollection_AsciiString& S) const;

  Standard_EXPORT virtual void Dump(Standard_OStream& OS) const;

  Standard_EXPORT virtual void Write(
    Standard_OStream&            OS,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT virtual void Read(
    Standard_IStream&            IS,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void Dump(const TopoDS_Shape& S, Standard_OStream& OS) const;

  Standard_EXPORT void Write(const TopoDS_Shape& S, Standard_OStream& OS) const;

  Standard_EXPORT void Read(TopoDS_Shape& S, Standard_IStream& IS) const;

  Standard_EXPORT virtual void AddGeometry(const TopoDS_Shape& S);

  Standard_EXPORT virtual void DumpGeometry(Standard_OStream& OS) const;

  Standard_EXPORT virtual void WriteGeometry(
    Standard_OStream&            OS,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT virtual void ReadGeometry(
    Standard_IStream&            IS,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT virtual void DumpGeometry(const TopoDS_Shape& S, Standard_OStream& OS) const;

  Standard_EXPORT virtual void WriteGeometry(const TopoDS_Shape& S, Standard_OStream& OS) const;

  Standard_EXPORT virtual void ReadGeometry(const TopAbs_ShapeEnum T,
                                            Standard_IStream&      IS,
                                            TopoDS_Shape&          S);

  Standard_EXPORT virtual void AddShapes(TopoDS_Shape& S1, const TopoDS_Shape& S2);

  Standard_EXPORT virtual void Check(const TopAbs_ShapeEnum T, TopoDS_Shape& S);

  Standard_EXPORT int NbShapes() const;

public:
  static const char* THE_ASCII_VERSIONS[TopTools_FormatVersion_VERSION_3 + 1];

private:
  Standard_EXPORT void Read(TopoDS_Shape& S, Standard_IStream& IS, const int NbShapes) const;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myShapes;
  TopTools_LocationSet                                          myLocations;
  int                                                           myFormatNb;
};
