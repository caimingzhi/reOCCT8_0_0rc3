

#include <StdLPersistent_HString.hpp>
#include <StdObjMgt_ReadData.hpp>
#include <StdObjMgt_WriteData.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>

template <class StringClass, typename CharType>
void StdLPersistent_HString::instance<StringClass, CharType>::Read(StdObjMgt_ReadData& theReadData)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);

  int aSize;
  theReadData >> aSize;
  myValue = new StringClass(aSize, 0);

  for (int i = 1; i <= aSize; i++)
  {
    CharType aChar;
    theReadData >> aChar;
    myValue->SetValue(i, aChar);
  }
}

template <class StringClass, typename CharType>
void StdLPersistent_HString::instance<StringClass, CharType>::Write(
  StdObjMgt_WriteData& theWriteData) const
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  int aSize = myValue->Length();
  theWriteData << aSize;

  for (int i = 1; i <= aSize; i++)
  {
    CharType aChar(0);
    theWriteData << aChar;
  }
}

template <class StringClass, typename CharType>
TDF_Label StdLPersistent_HString::instance<StringClass, CharType>::Label(
  const occ::handle<TDF_Data>& theDF) const
{
  TDF_Label aLabel;

  if (!myValue.IsNull())
    TDF_Tool::Label(theDF, myValue->String(), aLabel, true);

  return aLabel;
}

occ::handle<TCollection_HAsciiString> StdLPersistent_HString::Ascii::AsciiString() const
{
  return myValue;
}

occ::handle<TCollection_HExtendedString> StdLPersistent_HString::Extended::ExtString() const
{
  return myValue;
}

template class StdLPersistent_HString::instance<TCollection_HAsciiString, char>;

template class StdLPersistent_HString::instance<TCollection_HExtendedString, char16_t>;
