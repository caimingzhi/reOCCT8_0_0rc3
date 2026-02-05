#include <AIS_InteractiveObject.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDF_Label.hpp>
#include <TDocStd_Document.hpp>
#include <XCAFDoc_ShapeTool.hpp>
#include <XCAFPrs_AISObject.hpp>
#include <XCAFPrs_Driver.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XCAFPrs_Driver, TPrsStd_Driver)

//=================================================================================================

bool XCAFPrs_Driver::Update(const TDF_Label& L, occ::handle<AIS_InteractiveObject>& ais)

{
  //  std::cout << "XCAFPrs_Driver::Update" << std::endl;
  // WARNING! The label L can be out of any document
  // (this is a case for reading from the file)
  //  occ::handle<TDocStd_Document> DOC = TDocStd_Document::Get(L);

  XCAFDoc_ShapeTool shapes;
  if (!XCAFDoc_ShapeTool::IsShape(L))
    return false;

  ais = new XCAFPrs_AISObject(L);

  return true;
}

//=================================================================================================

const Standard_GUID& XCAFPrs_Driver::GetID()
{
  static Standard_GUID ID("5b896afc-3adf-11d4-b9b7-0060b0ee281b");
  return ID;
}
