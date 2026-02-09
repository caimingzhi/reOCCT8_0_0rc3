#pragma once

#include <StdObjMgt_Persistent.hpp>

#include <Standard_TypeDef.hpp>
#include <TCollection_HAsciiString.hpp>
#include <TCollection_HExtendedString.hpp>

class StdLPersistent_HString
{
  template <class StringClass, typename CharType>
  class instance : public StdObjMgt_Persistent
  {
  public:
    Standard_EXPORT void Read(StdObjMgt_ReadData& theReadData) override;

    Standard_EXPORT void Write(StdObjMgt_WriteData& theWriteData) const override;

    void PChildren(StdObjMgt_Persistent::SequenceOfPersistent&) const override {}

    Standard_EXPORT TDF_Label Label(const occ::handle<TDF_Data>& theDF) const override;

    const occ::handle<StringClass>& Value() const { return myValue; }

  protected:
    occ::handle<StringClass> myValue;
  };

public:
  class Ascii : public instance<TCollection_HAsciiString, char>
  {
  public:
    Standard_EXPORT occ::handle<TCollection_HAsciiString> AsciiString() const override;

    inline const char* PName() const override { return "PCollection_HAsciiString"; }
  };

  class Extended : public instance<TCollection_HExtendedString, char16_t>
  {
  public:
    Standard_EXPORT occ::handle<TCollection_HExtendedString> ExtString() const override;

    inline const char* PName() const override { return "PCollection_HExtendedString"; }
  };
};
