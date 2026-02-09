#include <TObj_Assistant.hpp>

#include <TObj_Model.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_Type.hpp>

NCollection_Sequence<occ::handle<Standard_Transient>>& TObj_Assistant::getModels()
{
  static NCollection_Sequence<occ::handle<Standard_Transient>> sModels;
  return sModels;
}

NCollection_IndexedMap<occ::handle<Standard_Transient>>& TObj_Assistant::getTypes()
{
  static NCollection_IndexedMap<occ::handle<Standard_Transient>> sTypes;
  return sTypes;
}

occ::handle<TObj_Model>& TObj_Assistant::getCurrentModel()
{
  static occ::handle<TObj_Model> sCurrentModel;
  return sCurrentModel;
}

int& TObj_Assistant::getVersion()
{
  static int sVersion = 0;
  return sVersion;
}

occ::handle<TObj_Model> TObj_Assistant::FindModel(const char* theName)
{
  TCollection_ExtendedString aName(theName, true);
  int                        i = getModels().Length();
  occ::handle<TObj_Model>    aModel;
  for (; i > 0; i--)
  {
    aModel = occ::down_cast<TObj_Model>(getModels().Value(i));
    if (aName == aModel->GetModelName()->String())
      break;
  }
  if (i == 0)
    aModel.Nullify();

  return aModel;
}

void TObj_Assistant::BindModel(const occ::handle<TObj_Model>& theModel)
{
  getModels().Append(theModel);
}

void TObj_Assistant::ClearModelMap()
{
  getModels().Clear();
}

occ::handle<Standard_Type> TObj_Assistant::FindType(const int theTypeIndex)
{
  if (theTypeIndex > 0 && theTypeIndex <= getTypes().Extent())
    return occ::down_cast<Standard_Type>(getTypes().FindKey(theTypeIndex));

  return nullptr;
}

int TObj_Assistant::FindTypeIndex(const occ::handle<Standard_Type>& theType)
{
  if (!getTypes().Contains(theType))
    return 0;

  return getTypes().FindIndex(theType);
}

class TObj_Assistant_UnknownType : public Standard_Transient
{
public:
  TObj_Assistant_UnknownType() = default;

  DEFINE_STANDARD_RTTI_INLINE(TObj_Assistant_UnknownType, Standard_Transient)
};

int TObj_Assistant::BindType(const occ::handle<Standard_Type>& theType)
{
  if (theType.IsNull())
  {
    occ::handle<Standard_Transient> anUnknownType;
    anUnknownType = new TObj_Assistant_UnknownType;
    return getTypes().Add(anUnknownType);
  }

  return getTypes().Add(theType);
}

void TObj_Assistant::ClearTypeMap()
{
  getTypes().Clear();
}

void TObj_Assistant::SetCurrentModel(const occ::handle<TObj_Model>& theModel)
{
  getCurrentModel() = theModel;
  getVersion()      = -1;
}

occ::handle<TObj_Model> TObj_Assistant::GetCurrentModel()
{
  return getCurrentModel();
}

void TObj_Assistant::UnSetCurrentModel()
{
  getCurrentModel().Nullify();
}

int TObj_Assistant::GetAppVersion()
{
  int& aVersion = getVersion();
  if (aVersion < 0)
  {
    occ::handle<TObj_Model>& aModel = getCurrentModel();
    if (!aModel.IsNull())
      aVersion = aModel->GetFormatVersion();
  }
  return aVersion;
}
