#pragma once

#include <Standard_Macro.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>

class LDOM_MemManager;
class LDOM_NullPtr;
class TCollection_AsciiString;
class TCollection_ExtendedString;

class LDOMBasicString
{
  friend class LDOM_MemManager;
  friend class LDOM_Node;

public:
  enum StringType
  {
    LDOM_NULL = 0,
    LDOM_Integer,

    LDOM_AsciiFree,
    LDOM_AsciiDoc,
    LDOM_AsciiDocClear,
    LDOM_AsciiHashed
  };

  Standard_EXPORT ~LDOMBasicString();

  StringType Type() const { return myType; }

  Standard_EXPORT bool GetInteger(int& aResult) const;

  const char* GetString() const
  {
    return myType == LDOM_Integer || myType == LDOM_NULL ? "" : (const char*)myVal.ptr;
  }

  Standard_EXPORT bool equals(const LDOMBasicString& anOther) const;

  Standard_EXPORT LDOMBasicString& operator=(const LDOM_NullPtr*);

  Standard_EXPORT LDOMBasicString& operator=(const LDOMBasicString& anOther);

  bool operator==(const LDOM_NullPtr*) const { return myType == LDOM_NULL; }

  bool operator!=(const LDOM_NullPtr*) const { return myType != LDOM_NULL; }

  bool operator==(const LDOMBasicString& anOther) const
  {
    return myType == anOther.myType && myVal.i == anOther.myVal.i;
  }

  bool operator!=(const LDOMBasicString& anOther) const
  {
    return myType != anOther.myType || myVal.i != anOther.myVal.i;
  }

  Standard_EXPORT operator TCollection_AsciiString() const;

  Standard_EXPORT operator TCollection_ExtendedString() const;

  LDOMBasicString()
      : myType(LDOM_NULL)
  {
    myVal.ptr = nullptr;
  }

  Standard_EXPORT LDOMBasicString(const LDOMBasicString& anOther);

  LDOMBasicString(const int aValue)
      : myType(LDOM_Integer)
  {
    myVal.i = aValue;
  }

  Standard_EXPORT LDOMBasicString(const char* aValue);

  Standard_EXPORT LDOMBasicString(const char* aValue, const occ::handle<LDOM_MemManager>& aDoc);

  Standard_EXPORT LDOMBasicString(const char*                         aValue,
                                  const int                           aLen,
                                  const occ::handle<LDOM_MemManager>& aDoc);

protected:
  void SetDirect(const StringType aType, const char* aValue)
  {
    myType    = aType;
    myVal.ptr = (void*)aValue;
  }

protected:
  StringType myType;

  union
  {
    int   i;
    void* ptr;
  } myVal;

  friend char* db_pretty_print(const LDOMBasicString*, int, char*);
};
