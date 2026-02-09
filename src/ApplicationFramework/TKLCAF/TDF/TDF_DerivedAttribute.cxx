

#include <TDF_DerivedAttribute.hpp>

#include <NCollection_DataMap.hpp>
#include <Standard_CStringHasher.hpp>
#include <TCollection_AsciiString.hpp>

#include <mutex>

namespace TDF_DerivedAttributeGlobals
{

  struct CreatorData
  {
    TDF_DerivedAttribute::NewDerived myCreator;
    const char*                      myNameSpace;
    const char*                      myTypeName;
  };

  static NCollection_List<CreatorData>& Creators()
  {
    static NCollection_List<CreatorData> THE_CREATORS_LIST;
    return THE_CREATORS_LIST;
  }

  static NCollection_DataMap<const char*, occ::handle<TDF_Attribute>, Standard_CStringHasher>&
    Attributes()
  {
    static NCollection_DataMap<const char*, occ::handle<TDF_Attribute>, Standard_CStringHasher>
      THE_DERIVED;
    return THE_DERIVED;
  }

  static NCollection_DataMap<const char*, TCollection_AsciiString*, Standard_CStringHasher>& Types()
  {
    static NCollection_DataMap<const char*, TCollection_AsciiString*, Standard_CStringHasher>
      THE_DERIVED_TYPES;
    return THE_DERIVED_TYPES;
  }

  static std::mutex& Mutex()
  {
    static std::mutex THE_DERIVED_MUTEX;
    return THE_DERIVED_MUTEX;
  }
} // namespace TDF_DerivedAttributeGlobals

TDF_DerivedAttribute::NewDerived TDF_DerivedAttribute::Register(NewDerived  theNewAttributeFunction,
                                                                const char* theNameSpace,
                                                                const char* theTypeName)
{
  TDF_DerivedAttributeGlobals::CreatorData aData = {theNewAttributeFunction,
                                                    theNameSpace,
                                                    theTypeName};
  std::lock_guard<std::mutex>              aLock(TDF_DerivedAttributeGlobals::Mutex());
  TDF_DerivedAttributeGlobals::Creators().Append(aData);
  return theNewAttributeFunction;
}

static void Initialize()
{
  if (!TDF_DerivedAttributeGlobals::Creators().IsEmpty())
  {
    NCollection_List<TDF_DerivedAttributeGlobals::CreatorData>::Iterator aCreator;
    for (aCreator.Initialize(TDF_DerivedAttributeGlobals::Creators()); aCreator.More();
         aCreator.Next())
    {
      occ::handle<TDF_Attribute> aDerived            = aCreator.Value().myCreator();
      const char*                aDerivedDynamicType = aDerived->DynamicType()->Name();

      TCollection_AsciiString aTypeName;
      if (aCreator.Value().myNameSpace != nullptr)
      {
        if (aCreator.Value().myNameSpace[0] != '\0')
        {
          aTypeName = aCreator.Value().myNameSpace;
          aTypeName += ':';
        }
      }
      if (aCreator.Value().myTypeName == nullptr)
      {
        aTypeName += aDerivedDynamicType;
      }
      else
      {
        aTypeName += aCreator.Value().myTypeName;
      }

      static NCollection_List<TCollection_AsciiString> THE_TYPES_STORAGE;
      THE_TYPES_STORAGE.Append(aTypeName);
      TDF_DerivedAttributeGlobals::Types().Bind(aDerivedDynamicType, &(THE_TYPES_STORAGE.Last()));
      TDF_DerivedAttributeGlobals::Attributes().Bind(aDerivedDynamicType, aDerived);
    }
    TDF_DerivedAttributeGlobals::Creators().Clear();
  }
}

occ::handle<TDF_Attribute> TDF_DerivedAttribute::Attribute(const char* theType)
{
  std::lock_guard<std::mutex> aLock(TDF_DerivedAttributeGlobals::Mutex());
  Initialize();
  if (const occ::handle<TDF_Attribute>* aResult =
        TDF_DerivedAttributeGlobals::Attributes().Seek(theType))
  {
    return *aResult;
  }

  static const occ::handle<TDF_Attribute> aNullAttrib;
  return aNullAttrib;
}

const TCollection_AsciiString& TDF_DerivedAttribute::TypeName(const char* theType)
{
  std::lock_guard<std::mutex> aLock(TDF_DerivedAttributeGlobals::Mutex());
  Initialize();
  if (TCollection_AsciiString* const* aResult = TDF_DerivedAttributeGlobals::Types().Seek(theType))
  {
    return **aResult;
  }

  return TCollection_AsciiString::EmptyString();
}

void TDF_DerivedAttribute::Attributes(NCollection_List<occ::handle<TDF_Attribute>>& theList)
{
  std::lock_guard<std::mutex> aLock(TDF_DerivedAttributeGlobals::Mutex());
  Initialize();
  NCollection_DataMap<const char*, occ::handle<TDF_Attribute>, Standard_CStringHasher>::Iterator
    anAttrIter;
  for (anAttrIter.Initialize(TDF_DerivedAttributeGlobals::Attributes()); anAttrIter.More();
       anAttrIter.Next())
  {
    theList.Append(anAttrIter.Value());
  }
}
