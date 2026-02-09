#include <TObj_Persistence.hpp>
#include <TObj_Object.hpp>

NCollection_DataMap<TCollection_AsciiString, void*>& TObj_Persistence::getMapOfTypes()
{
  static NCollection_DataMap<TCollection_AsciiString, void*> myMapOfTypes;
  return myMapOfTypes;
}

TObj_Persistence::TObj_Persistence(const char* theType)
{
  myType = theType;
  getMapOfTypes().Bind(theType, this);
}

TObj_Persistence::~TObj_Persistence()
{
  getMapOfTypes().UnBind(myType);
}

occ::handle<TObj_Object> TObj_Persistence::CreateNewObject(const char*      theType,
                                                           const TDF_Label& theLabel)
{
  if (getMapOfTypes().IsBound(theType))
  {
    TObj_Persistence* tool = (TObj_Persistence*)getMapOfTypes().Find(theType);
    if (tool)
      return tool->New(theLabel);
  }
  return nullptr;
}

void TObj_Persistence::DumpTypes(Standard_OStream& theOs)
{
  NCollection_DataMap<TCollection_AsciiString, void*>::Iterator it(getMapOfTypes());
  for (; it.More(); it.Next())
  {
    theOs << it.Key() << std::endl;
  }
}
