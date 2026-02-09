#include <LDOMString.hpp>
#include <LDOM_MemManager.hpp>

LDOMString LDOMString::CreateDirectString(const char* aValue, const LDOM_MemManager& aDoc)
{
  LDOMString aResult;
  aResult.myPtrDoc = &aDoc;
  aResult.SetDirect(LDOMBasicString::LDOM_AsciiHashed, aValue);
  return aResult;
}

LDOMString::LDOMString(const LDOMBasicString& anOther, const occ::handle<LDOM_MemManager>& aDoc)
    : myPtrDoc(&aDoc->Self())
{
  myType = anOther.Type();
  switch (myType)
  {
    case LDOM_Integer:
      anOther.GetInteger(myVal.i);
      break;
    case LDOM_AsciiFree:
      myType = LDOM_AsciiDoc;
      [[fallthrough]];
    case LDOM_AsciiDocClear:
    case LDOM_AsciiDoc:
    {
      const char* aString = anOther.GetString();
      int         aLen    = (int)(strlen(aString) + 1);
      myVal.ptr           = ((LDOM_MemManager*)myPtrDoc)->Allocate(aLen);
      memcpy(myVal.ptr, aString, aLen);
    }
    break;
    case LDOM_AsciiHashed:
      myVal.ptr = (void*)anOther.GetString();
      break;
    default:
      myType = LDOM_NULL;
  }
}
