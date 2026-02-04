#pragma once


#include <RWMesh_CafReader.hpp>
#include <RWObj_TriangulationReader.hpp>

//! The OBJ mesh reader into XDE document.
class RWObj_CafReader : public RWMesh_CafReader, protected RWObj_IShapeReceiver
{
  DEFINE_STANDARD_RTTIEXT(RWObj_CafReader, RWMesh_CafReader)
public:
  //! Empty constructor.
  Standard_EXPORT RWObj_CafReader();

  //! Return single precision flag for reading vertex data (coordinates); FALSE by default.
  bool IsSinglePrecision() const { return myIsSinglePrecision; }

  //! Setup single/double precision flag for reading vertex data (coordinates).
  void SetSinglePrecision(bool theIsSinglePrecision) { myIsSinglePrecision = theIsSinglePrecision; }

protected:
  //! Read the mesh from specified file.
  Standard_EXPORT bool performMesh(std::istream&                  theStream,
                                   const TCollection_AsciiString& theFile,
                                   const Message_ProgressRange&   theProgress,
                                   const bool                     theToProbe) override;

protected:
  //! Create reader context.
  //! Can be overridden by sub-class to read triangulation into application-specific data structures
  //! instead of Poly_Triangulation.
  Standard_EXPORT virtual occ::handle<RWObj_TriangulationReader> createReaderContext();

  //! @param theShape       shape to register
  //! @param theName        shape name
  //! @param theMaterial    shape material
  //! @param theIsRootShape indicates that this is a root object (free shape)
  Standard_EXPORT void BindNamedShape(const TopoDS_Shape&            theShape,
                                      const TCollection_AsciiString& theName,
                                      const RWObj_Material*          theMaterial,
                                      const bool                     theIsRootShape) override;

protected:
  NCollection_DataMap<TCollection_AsciiString, occ::handle<XCAFDoc_VisMaterial>> myObjMaterialMap;
  // clang-format off
  bool myIsSinglePrecision; //!< flag for reading vertex data with single or double floating point precision
  // clang-format on
};

