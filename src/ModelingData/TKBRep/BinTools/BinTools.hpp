#pragma once

#include <BinTools_FormatVersion.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Message_ProgressRange.hpp>

class TopoDS_Shape;

class BinTools
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static Standard_OStream& PutReal(Standard_OStream& OS, const double& theValue);

  Standard_EXPORT static Standard_OStream& PutShortReal(Standard_OStream& OS,
                                                        const float&      theValue);

  Standard_EXPORT static Standard_OStream& PutInteger(Standard_OStream& OS, const int theValue);

  Standard_EXPORT static Standard_OStream& PutBool(Standard_OStream& OS, const bool theValue);

  Standard_EXPORT static Standard_OStream& PutExtChar(Standard_OStream& OS,
                                                      const char16_t    theValue);

  Standard_EXPORT static Standard_IStream& GetReal(Standard_IStream& IS, double& theValue);

  Standard_EXPORT static Standard_IStream& GetShortReal(Standard_IStream& IS, float& theValue);

  Standard_EXPORT static Standard_IStream& GetInteger(Standard_IStream& IS, int& theValue);

  Standard_EXPORT static Standard_IStream& GetBool(Standard_IStream& IS, bool& theValue);

  Standard_EXPORT static Standard_IStream& GetExtChar(Standard_IStream& IS, char16_t& theValue);

  static void Write(const TopoDS_Shape&          theShape,
                    Standard_OStream&            theStream,
                    const Message_ProgressRange& theRange = Message_ProgressRange())
  {
    Write(theShape, theStream, true, false, BinTools_FormatVersion_CURRENT, theRange);
  }

  Standard_EXPORT static void Write(
    const TopoDS_Shape&          theShape,
    Standard_OStream&            theStream,
    const bool                   theWithTriangles,
    const bool                   theWithNormals,
    const BinTools_FormatVersion theVersion,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT static void Read(TopoDS_Shape&                theShape,
                                   Standard_IStream&            theStream,
                                   const Message_ProgressRange& theRange = Message_ProgressRange());

  static bool Write(const TopoDS_Shape&          theShape,
                    const char*                  theFile,
                    const Message_ProgressRange& theRange = Message_ProgressRange())
  {
    return Write(theShape, theFile, true, false, BinTools_FormatVersion_CURRENT, theRange);
  }

  Standard_EXPORT static bool Write(
    const TopoDS_Shape&          theShape,
    const char*                  theFile,
    const bool                   theWithTriangles,
    const bool                   theWithNormals,
    const BinTools_FormatVersion theVersion,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT static bool Read(TopoDS_Shape&                theShape,
                                   const char*                  theFile,
                                   const Message_ProgressRange& theRange = Message_ProgressRange());
};
