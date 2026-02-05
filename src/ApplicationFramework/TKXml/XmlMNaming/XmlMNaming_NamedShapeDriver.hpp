#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BRepTools_ShapeSet.hpp>
#include <XmlMDF_ADriver.hpp>
#include <TDocStd_FormatVersion.hpp>
#include <XmlObjMgt_RRelocationTable.hpp>
#include <XmlObjMgt_SRelocationTable.hpp>
#include <XmlObjMgt_Element.hpp>
class Message_Messenger;
class TDF_Attribute;
class XmlObjMgt_Persistent;
class TopTools_LocationSet;

class XmlMNaming_NamedShapeDriver : public XmlMDF_ADriver
{
public:
  Standard_EXPORT XmlMNaming_NamedShapeDriver(const occ::handle<Message_Messenger>& aMessageDriver);

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT bool Paste(const XmlObjMgt_Persistent&       theSource,
                             const occ::handle<TDF_Attribute>& theTarget,
                             XmlObjMgt_RRelocationTable&       theRelocTable) const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>& theSource,
                             XmlObjMgt_Persistent&             theTarget,
                             XmlObjMgt_SRelocationTable&       theRelocTable) const override;

  //! Input the shapes from DOM element
  Standard_EXPORT void ReadShapeSection(
    const XmlObjMgt_Element&     anElement,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  //! Output the shapes into DOM element
  Standard_EXPORT void WriteShapeSection(
    XmlObjMgt_Element&           anElement,
    TDocStd_FormatVersion        theStorageFormatVersion,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  //! Clear myShapeSet
  Standard_EXPORT void Clear();

  //! get the format of topology
  TopTools_LocationSet& GetShapesLocations();

  DEFINE_STANDARD_RTTIEXT(XmlMNaming_NamedShapeDriver, XmlMDF_ADriver)

private:
  BRepTools_ShapeSet myShapeSet;
};

inline TopTools_LocationSet& XmlMNaming_NamedShapeDriver::GetShapesLocations()
{
  return myShapeSet.ChangeLocations();
}
