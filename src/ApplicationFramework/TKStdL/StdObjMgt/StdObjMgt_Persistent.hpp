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

//! Root class for a temporary persistent object that reads data from a file
//! and then creates transient object using the data.
class StdObjMgt_Persistent : public Standard_Transient
{
public:
  Standard_EXPORT StdObjMgt_Persistent();

  //! Derived class instance create function.
  typedef occ::handle<StdObjMgt_Persistent> (*Instantiator)();

  //! Create a derived class instance.
  template <class Persistent>
  static occ::handle<StdObjMgt_Persistent> Instantiate()
  {
    return new Persistent;
  }

  //! Read persistent data from a file.
  virtual void Read(StdObjMgt_ReadData& theReadData) = 0;

  //! Write persistent data to a file.
  virtual void Write(StdObjMgt_WriteData& theWriteData) const = 0;

  typedef NCollection_Sequence<occ::handle<StdObjMgt_Persistent>> SequenceOfPersistent;

  //! Gets persistent child objects
  virtual void PChildren(SequenceOfPersistent&) const = 0;

  //! Returns persistent type name
  virtual const char* PName() const = 0;

  //! Import transient document from the persistent data
  //! (to be overridden by document class;
  //! does nothing by default for other classes).
  Standard_EXPORT virtual void ImportDocument(
    const occ::handle<TDocStd_Document>& theDocument) const;

  //! Create an empty transient attribute
  //! (to be overridden by attribute classes;
  //! does nothing and returns a null handle by default for other classes).
  Standard_EXPORT virtual occ::handle<TDF_Attribute> CreateAttribute();

  //! Get transient attribute for the persistent data
  //! (to be overridden by attribute classes;
  //! returns a null handle by default for non-attribute classes).
  Standard_EXPORT virtual occ::handle<TDF_Attribute> GetAttribute() const;

  //! Import transient attribute from the persistent data
  //! (to be overridden by attribute classes;
  //! does nothing by default for non-attribute classes).
  Standard_EXPORT virtual void ImportAttribute();

  //! Get referenced ASCII string
  //! (to be overridden by ASCII string class;
  //! returns a null handle by default for other classes).
  Standard_EXPORT virtual occ::handle<TCollection_HAsciiString> AsciiString() const;

  //! Get referenced extended string
  //! (to be overridden by extended string class;
  //! returns a null handle by default for other classes).
  Standard_EXPORT virtual occ::handle<TCollection_HExtendedString> ExtString() const;

  //! Get a label expressed by referenced extended string
  //! (to be overridden by extended string class;
  //! returns a null label by default for other classes).
  Standard_EXPORT virtual TDF_Label Label(const occ::handle<TDF_Data>& theDF) const;

  //! Returns the assigned persistent type number
  int TypeNum() const { return myTypeNum; }

  //! Assigns a persistent type number to the object
  void TypeNum(int theTypeNum) { myTypeNum = theTypeNum; }

  //! Returns the object reference number
  int RefNum() const { return myRefNum; }

  //! Sets an object reference number
  void RefNum(int theRefNum) { myRefNum = theRefNum; }

private:
  int myTypeNum;
  int myRefNum;
};

