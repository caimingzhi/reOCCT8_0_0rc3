#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IGESControl_Writer.hpp>
#include <Standard_CString.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <XCAFPrs_Style.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_DataMap.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Map.hpp>

class XSControl_WorkSession;
class TDocStd_Document;
class TCollection_AsciiString;
class TopoDS_Shape;
class XCAFPrs_Style;

class IGESCAFControl_Writer : public IGESControl_Writer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESCAFControl_Writer();

  Standard_EXPORT IGESCAFControl_Writer(const occ::handle<XSControl_WorkSession>& WS,
                                        const bool                                scratch = true);

  Standard_EXPORT IGESCAFControl_Writer(const occ::handle<XSControl_WorkSession>& theWS,
                                        const char*                               theUnit);

  Standard_EXPORT bool Transfer(const occ::handle<TDocStd_Document>& doc,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Transfer(const NCollection_Sequence<TDF_Label>& labels,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Transfer(const TDF_Label&             label,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Perform(const occ::handle<TDocStd_Document>& doc,
                               const TCollection_AsciiString&       filename,
                               const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Perform(const occ::handle<TDocStd_Document>& doc,
                               const char*                          filename,
                               const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void SetColorMode(const bool colormode);

  Standard_EXPORT bool GetColorMode() const;

  Standard_EXPORT void SetNameMode(const bool namemode);

  Standard_EXPORT bool GetNameMode() const;

  Standard_EXPORT void SetLayerMode(const bool layermode);

  Standard_EXPORT bool GetLayerMode() const;

protected:
  Standard_EXPORT bool WriteAttributes(const NCollection_Sequence<TDF_Label>& labels);

  Standard_EXPORT bool WriteLayers(const NCollection_Sequence<TDF_Label>& labels);

  Standard_EXPORT bool WriteNames(const NCollection_Sequence<TDF_Label>& labels);

  Standard_EXPORT void prepareUnit(const TDF_Label& theLabel);

private:
  Standard_EXPORT void MakeColors(
    const TopoDS_Shape& S,
    const NCollection_IndexedDataMap<TopoDS_Shape, XCAFPrs_Style, TopTools_ShapeMapHasher>&
                                                                         settings,
    NCollection_DataMap<XCAFPrs_Style, occ::handle<Standard_Transient>>& colors,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&              Map,
    const XCAFPrs_Style&                                                 inherit);

  bool myColorMode;
  bool myNameMode;
  bool myLayerMode;
};
