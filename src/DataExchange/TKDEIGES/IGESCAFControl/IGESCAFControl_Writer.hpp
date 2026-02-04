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

//! Provides a tool to write DECAF document to the
//! IGES file. Besides transfer of shapes (including
//! assemblies) provided by IGESControl, supports also
//! colors and part names
//! IGESCAFControl_Writer writer();
//! Methods for writing IGES file:
//! writer.Transfer (Document);
//! writer.Write("filename") or writer.Write(OStream) or
//! writer.Perform(Document,"filename");
//! Methods for managing the writing of attributes.
//! Colors
//! writer.SetColorMode(colormode);
//! bool colormode = writer.GetColorMode();
//! Layers
//! writer.SetLayerMode(layermode);
//! bool layermode = writer.GetLayerMode();
//! Names
//! writer.SetNameMode(namemode);
//! bool namemode = writer.GetNameMode();
class IGESCAFControl_Writer : public IGESControl_Writer
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a writer with an empty
  //! IGES model and sets ColorMode, LayerMode and NameMode to true.
  Standard_EXPORT IGESCAFControl_Writer();

  //! Creates a reader tool and attaches it to an already existing Session
  //! Clears the session if it was not yet set for IGES
  Standard_EXPORT IGESCAFControl_Writer(const occ::handle<XSControl_WorkSession>& WS,
                                        const bool                                scratch = true);

  //! Creates a reader tool and attaches it to an already existing Session
  //! Clears the session if it was not yet set for IGES
  //! Sets target Unit for the writing process.
  Standard_EXPORT IGESCAFControl_Writer(const occ::handle<XSControl_WorkSession>& theWS,
                                        const char*                               theUnit);

  //! Transfers a document to a IGES model
  //! Returns True if translation is OK
  Standard_EXPORT bool Transfer(const occ::handle<TDocStd_Document>& doc,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Transfers labels to a IGES model
  //! Returns True if translation is OK
  Standard_EXPORT bool Transfer(const NCollection_Sequence<TDF_Label>& labels,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Transfers label to a IGES model
  //! Returns True if translation is OK
  Standard_EXPORT bool Transfer(const TDF_Label&             label,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Perform(const occ::handle<TDocStd_Document>& doc,
                               const TCollection_AsciiString&       filename,
                               const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Transfers a document and writes it to a IGES file
  //! Returns True if translation is OK
  Standard_EXPORT bool Perform(const occ::handle<TDocStd_Document>& doc,
                               const char*                          filename,
                               const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Set ColorMode for indicate write Colors or not.
  Standard_EXPORT void SetColorMode(const bool colormode);

  Standard_EXPORT bool GetColorMode() const;

  //! Set NameMode for indicate write Name or not.
  Standard_EXPORT void SetNameMode(const bool namemode);

  Standard_EXPORT bool GetNameMode() const;

  //! Set LayerMode for indicate write Layers or not.
  Standard_EXPORT void SetLayerMode(const bool layermode);

  Standard_EXPORT bool GetLayerMode() const;

protected:
  //! Reads colors from DECAF document and assigns them
  //! to corresponding IGES entities
  Standard_EXPORT bool WriteAttributes(const NCollection_Sequence<TDF_Label>& labels);

  //! Reads layers from DECAF document and assigns them
  //! to corresponding IGES entities
  Standard_EXPORT bool WriteLayers(const NCollection_Sequence<TDF_Label>& labels);

  //! Recursivile iterates on subshapes and assign names
  //! to IGES entity
  Standard_EXPORT bool WriteNames(const NCollection_Sequence<TDF_Label>& labels);

  //! Finds length units located in root of label
  //! If it exists, initializes local length unit from it
  //! Else initializes according to Cascade length unit
  Standard_EXPORT void prepareUnit(const TDF_Label& theLabel);

private:
  //! Recursively iterates on subshapes and assigns colors
  //! to faces and edges (if set)
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

