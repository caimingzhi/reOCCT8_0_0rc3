#pragma once

#include <Standard.hpp>

#include <BinTools_ShapeSet.hpp>
#include <Standard_Integer.hpp>
#include <BinMDF_ADriver.hpp>
#include <BinObjMgt_RRelocationTable.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_IStream.hpp>
#include <Standard_OStream.hpp>
class Message_Messenger;
class TDF_Attribute;
class BinObjMgt_Persistent;
class BinTools_LocationSet;

//! NamedShape Attribute Driver.
class BinMNaming_NamedShapeDriver : public BinMDF_ADriver
{

public:
  Standard_EXPORT BinMNaming_NamedShapeDriver(
    const occ::handle<Message_Messenger>& theMessageDriver);

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT bool Paste(const BinObjMgt_Persistent&       Source,
                             const occ::handle<TDF_Attribute>& Target,
                             BinObjMgt_RRelocationTable&       RelocTable) const override;

  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&                        Source,
    BinObjMgt_Persistent&                                    Target,
    NCollection_IndexedMap<occ::handle<Standard_Transient>>& RelocTable) const override;

  //! Input the shapes from Bin Document file
  Standard_EXPORT void ReadShapeSection(
    Standard_IStream&            theIS,
    const Message_ProgressRange& therange = Message_ProgressRange());

  //! Output the shapes into Bin Document file
  Standard_EXPORT void WriteShapeSection(
    Standard_OStream&            theOS,
    const int                    theDocVer,
    const Message_ProgressRange& therange = Message_ProgressRange());

  //! Clear myShapeSet
  Standard_EXPORT void Clear();

  //! Return true if shape should be stored with triangles.
  bool IsWithTriangles() const { return myWithTriangles; }

  //! Return true if shape should be stored with triangulation normals.
  bool IsWithNormals() const { return myWithNormals; }

  //! set whether to store triangulation
  void SetWithTriangles(const bool isWithTriangles);
  //! set whether to store triangulation with normals
  void SetWithNormals(const bool isWithNormals);
  //! get the shapes locations
  Standard_EXPORT BinTools_LocationSet& GetShapesLocations() const;

  //! Sets the flag for quick part of the document access: shapes are stored in the attribute.
  Standard_EXPORT void EnableQuickPart(const bool theValue) { myIsQuickPart = theValue; }

  //! Returns true if quick part of the document access is enabled: shapes are stored in the
  //! attribute.
  Standard_EXPORT bool IsQuickPart() { return myIsQuickPart; }

  //! Returns shape-set of the needed type
  Standard_EXPORT BinTools_ShapeSetBase* ShapeSet(const bool theReading);

  DEFINE_STANDARD_RTTIEXT(BinMNaming_NamedShapeDriver, BinMDF_ADriver)

private:
  BinTools_ShapeSetBase* myShapeSet;
  bool                   myWithTriangles;
  bool                   myWithNormals;
  //! Enables storing of whole shape data just in the attribute, not in a separated shapes section
  bool myIsQuickPart;
};

inline void BinMNaming_NamedShapeDriver::SetWithTriangles(const bool isWithTriangles)
{
  myWithTriangles = isWithTriangles;
  if (myShapeSet)
    myShapeSet->SetWithTriangles(isWithTriangles);
}

//=================================================================================================

inline void BinMNaming_NamedShapeDriver::SetWithNormals(const bool isWithNormals)
{
  myWithNormals = isWithNormals;
  if (myShapeSet)
    myShapeSet->SetWithNormals(isWithNormals);
}
