#pragma once

#include <RWMesh_CafReader.hpp>
#include <RWObj_TriangulationReader.hpp>

class RWObj_CafReader : public RWMesh_CafReader, protected RWObj_IShapeReceiver
{
  DEFINE_STANDARD_RTTIEXT(RWObj_CafReader, RWMesh_CafReader)
public:
  Standard_EXPORT RWObj_CafReader();

  bool IsSinglePrecision() const { return myIsSinglePrecision; }

  void SetSinglePrecision(bool theIsSinglePrecision) { myIsSinglePrecision = theIsSinglePrecision; }

protected:
  Standard_EXPORT bool performMesh(std::istream&                  theStream,
                                   const TCollection_AsciiString& theFile,
                                   const Message_ProgressRange&   theProgress,
                                   const bool                     theToProbe) override;

protected:
  Standard_EXPORT virtual occ::handle<RWObj_TriangulationReader> createReaderContext();

  Standard_EXPORT void BindNamedShape(const TopoDS_Shape&            theShape,
                                      const TCollection_AsciiString& theName,
                                      const RWObj_Material*          theMaterial,
                                      const bool                     theIsRootShape) override;

protected:
  NCollection_DataMap<TCollection_AsciiString, occ::handle<XCAFDoc_VisMaterial>> myObjMaterialMap;

  bool myIsSinglePrecision;
};
