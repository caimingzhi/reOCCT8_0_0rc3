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
    //! Read persistent data from a file.
    Standard_EXPORT void Read(StdObjMgt_ReadData& theReadData) override;
    //! Write persistent data to a file.
    Standard_EXPORT void Write(StdObjMgt_WriteData& theWriteData) const override;

    void PChildren(StdObjMgt_Persistent::SequenceOfPersistent&) const override {}

    //! Get/create a label defined by referenced string.
    Standard_EXPORT TDF_Label Label(const occ::handle<TDF_Data>& theDF) const override;

    //! Get the value.
    const occ::handle<StringClass>& Value() const { return myValue; }

  protected:
    occ::handle<StringClass> myValue;
  };

public:
  class Ascii : public instance<TCollection_HAsciiString, char>
  {
  public:
    //! Get referenced ASCII string.
    Standard_EXPORT occ::handle<TCollection_HAsciiString> AsciiString() const override;

    inline const char* PName() const override { return "PCollection_HAsciiString"; }
  };

  class Extended : public instance<TCollection_HExtendedString, char16_t>
  {
  public:
    //! Get referenced extended string.
    Standard_EXPORT occ::handle<TCollection_HExtendedString> ExtString() const override;

    inline const char* PName() const override { return "PCollection_HExtendedString"; }
  };
};

