#pragma once

#include <Standard.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>

#include <TDF_Label.hpp>

class StdObjMgt_ReadData;
class StdObjMgt_WriteData;
class TDocStd_Document;
class TDF_Attribute;
class TDF_Data;
class TCollection_HAsciiString;
class TCollection_HExtendedString;

class StdObjMgt_Persistent : public Standard_Transient
{
public:
  Standard_EXPORT StdObjMgt_Persistent();

  typedef occ::handle<StdObjMgt_Persistent> (*Instantiator)();

  template <class Persistent>
  static occ::handle<StdObjMgt_Persistent> Instantiate()
  {
    return new Persistent;
  }

  virtual void Read(StdObjMgt_ReadData& theReadData) = 0;

  virtual void Write(StdObjMgt_WriteData& theWriteData) const = 0;

  typedef NCollection_Sequence<occ::handle<StdObjMgt_Persistent>> SequenceOfPersistent;

  virtual void PChildren(SequenceOfPersistent&) const = 0;

  virtual const char* PName() const = 0;

  Standard_EXPORT virtual void ImportDocument(
    const occ::handle<TDocStd_Document>& theDocument) const;

  Standard_EXPORT virtual occ::handle<TDF_Attribute> CreateAttribute();

  Standard_EXPORT virtual occ::handle<TDF_Attribute> GetAttribute() const;

  Standard_EXPORT virtual void ImportAttribute();

  Standard_EXPORT virtual occ::handle<TCollection_HAsciiString> AsciiString() const;

  Standard_EXPORT virtual occ::handle<TCollection_HExtendedString> ExtString() const;

  Standard_EXPORT virtual TDF_Label Label(const occ::handle<TDF_Data>& theDF) const;

  int TypeNum() const { return myTypeNum; }

  void TypeNum(int theTypeNum) { myTypeNum = theTypeNum; }

  int RefNum() const { return myRefNum; }

  void RefNum(int theRefNum) { myRefNum = theRefNum; }

private:
  int myTypeNum;
  int myRefNum;
};
