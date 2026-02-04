#pragma once


#include <TCollection_AsciiString.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_Map.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <RWMesh_CoordinateSystemConverter.hpp>
#include <XCAFPrs_Style.hpp>

#include <memory>

class Message_ProgressRange;
class RWMesh_FaceIterator;
class TDocStd_Document;

class Message_LazyProgressScope;
class RWObj_ObjWriterContext;
class RWObj_ObjMaterialMap;

//! OBJ writer context from XCAF document.
class RWObj_CafWriter : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(RWObj_CafWriter, Standard_Transient)
public:
  //! Main constructor.
  //! @param[in] theFile  path to output OBJ file
  Standard_EXPORT RWObj_CafWriter(const TCollection_AsciiString& theFile);

  //! Destructor.
  Standard_EXPORT ~RWObj_CafWriter() override;

  //! Return transformation from OCCT to OBJ coordinate system.
  const RWMesh_CoordinateSystemConverter& CoordinateSystemConverter() const { return myCSTrsf; }

  //! Return transformation from OCCT to OBJ coordinate system.
  RWMesh_CoordinateSystemConverter& ChangeCoordinateSystemConverter() { return myCSTrsf; }

  //! Set transformation from OCCT to OBJ coordinate system.
  void SetCoordinateSystemConverter(const RWMesh_CoordinateSystemConverter& theConverter)
  {
    myCSTrsf = theConverter;
  }

  //! Return default material definition to be used for nodes with only color defined.
  const XCAFPrs_Style& DefaultStyle() const { return myDefaultStyle; }

  //! Set default material definition to be used for nodes with only color defined.
  void SetDefaultStyle(const XCAFPrs_Style& theStyle) { myDefaultStyle = theStyle; }

  //! Write OBJ file and associated MTL material file.
  //! Triangulation data should be precomputed within shapes!
  //! @param[in] theDocument     input document
  //! @param[in] theRootLabels   list of root shapes to export
  //! @param[in] theLabelFilter  optional filter with document nodes to export,
  //!                            with keys defined by XCAFPrs_DocumentExplorer::DefineChildId() and
  //!                            filled recursively (leaves and parent assembly nodes at all
  //!                            levels); when not NULL, all nodes not included into the map will be
  //!                            ignored
  //! @param[in] theFileInfo     map with file metadata to put into OBJ header section
  //! @param[in] theProgress     optional progress indicator
  //! @return FALSE on file writing failure
  Standard_EXPORT virtual bool Perform(
    const occ::handle<TDocStd_Document>&            theDocument,
    const NCollection_Sequence<TDF_Label>&          theRootLabels,
    const NCollection_Map<TCollection_AsciiString>* theLabelFilter,
    const NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theFileInfo,
    const Message_ProgressRange& theProgress);

  //! Write OBJ file and associated MTL material file.
  //! Triangulation data should be precomputed within shapes!
  //! @param[in] theDocument     input document
  //! @param[in] theFileInfo     map with file metadata to put into glTF header section
  //! @param[in] theProgress     optional progress indicator
  //! @return FALSE on file writing failure
  Standard_EXPORT virtual bool Perform(
    const occ::handle<TDocStd_Document>&                                                theDocument,
    const NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theFileInfo,
    const Message_ProgressRange& theProgress);

protected:
  //! Return TRUE if face mesh should be skipped (e.g. because it is invalid or empty).
  Standard_EXPORT virtual bool toSkipFaceMesh(const RWMesh_FaceIterator& theFaceIter);

  //! Collect face triangulation info.
  //! @param[in] theFace  face to process
  //! @param[in][out] theNbNodes   overall number of triangulation nodes (should be appended)
  //! @param[in][out] theNbElems   overall number of triangulation elements (should be appended)
  //! @param[in][out] theNbProgressSteps   overall number of progress steps (should be appended)
  //! @param[in][out] theToCreateMatFile   flag to create material file or not (should be appended)
  Standard_EXPORT virtual void addFaceInfo(const RWMesh_FaceIterator& theFace,
                                           int&                       theNbNodes,
                                           int&                       theNbElems,
                                           double&                    theNbProgressSteps,
                                           bool&                      theToCreateMatFile);

  //! Write the shape.
  //! @param[in] theWriter   OBJ writer context
  //! @param[in] theMatMgr   OBJ material map
  //! @param[in] thePSentry  progress sentry
  //! @param[in] theLabel    document label to process
  //! @param[in] theParentTrsf   parent node transformation
  //! @param[in] theParentStyle  parent node style
  //! @param[in] theName     node name
  Standard_EXPORT virtual bool writeShape(RWObj_ObjWriterContext&        theWriter,
                                          RWObj_ObjMaterialMap&          theMatMgr,
                                          Message_LazyProgressScope&     thePSentry,
                                          const TDF_Label&               theLabel,
                                          const TopLoc_Location&         theParentTrsf,
                                          const XCAFPrs_Style&           theParentStyle,
                                          const TCollection_AsciiString& theName);

  //! Write face triangle vertex positions.
  //! @param[in] theWriter   OBJ writer context
  //! @param[in] thePSentry  progress sentry
  //! @param[in] theFace     current face
  //! @return FALSE on writing file error
  Standard_EXPORT virtual bool writePositions(RWObj_ObjWriterContext&    theWriter,
                                              Message_LazyProgressScope& thePSentry,
                                              const RWMesh_FaceIterator& theFace);

  //! Write face triangle vertex normals.
  //! @param[in] theWriter   OBJ writer context
  //! @param[in] thePSentry  progress sentry
  //! @param[in] theFace     current face
  //! @return FALSE on writing file error
  Standard_EXPORT virtual bool writeNormals(RWObj_ObjWriterContext&    theWriter,
                                            Message_LazyProgressScope& thePSentry,
                                            const RWMesh_FaceIterator& theFace);

  //! Write face triangle vertex texture coordinates.
  //! @param[in] theWriter   OBJ writer context
  //! @param[in] thePSentry  progress sentry
  //! @param[in] theFace     current face
  //! @return FALSE on writing file error
  Standard_EXPORT virtual bool writeTextCoords(RWObj_ObjWriterContext&    theWriter,
                                               Message_LazyProgressScope& thePSentry,
                                               const RWMesh_FaceIterator& theFace);

  //! Write face triangles indices.
  //! @param[in] theWriter   OBJ writer context
  //! @param[in] thePSentry  progress sentry
  //! @param[in] theFace     current face
  //! @return FALSE on writing file error
  Standard_EXPORT virtual bool writeIndices(RWObj_ObjWriterContext&    theWriter,
                                            Message_LazyProgressScope& thePSentry,
                                            const RWMesh_FaceIterator& theFace);

protected:
  TCollection_AsciiString myFile; //!< output OBJ file
  // clang-format off
  RWMesh_CoordinateSystemConverter myCSTrsf;       //!< transformation from OCCT to OBJ coordinate system
  XCAFPrs_Style                    myDefaultStyle; //!< default material definition to be used for nodes with only color defined
  // clang-format on
};

