#pragma once


#include <Standard.hpp>
#include <Storage_BaseDriver.hpp>

class StdObjMgt_Persistent;
class Standard_GUID;

//! Auxiliary data used to write persistent objects to a file.
class StdObjMgt_WriteData
{
public:
  //! Auxiliary class used to automate begin and end of
  //! writing object (adding opening and closing parenthesis)
  //! at constructor and destructor
  class ObjectSentry
  {
  public:
    explicit ObjectSentry(StdObjMgt_WriteData& theData)
        : myWriteData(&theData)
    {
      myWriteData->myDriver->BeginWriteObjectData();
    }

    ~ObjectSentry() { myWriteData->myDriver->EndWriteObjectData(); }

  private:
    StdObjMgt_WriteData* myWriteData;

    ObjectSentry(const ObjectSentry&)            = delete;
    ObjectSentry& operator=(const ObjectSentry&) = delete;
  };

  Standard_EXPORT StdObjMgt_WriteData(const occ::handle<Storage_BaseDriver>& theDriver);

  Standard_EXPORT void WritePersistentObject(
    const occ::handle<StdObjMgt_Persistent>& thePersistent);

  template <class Persistent>
  StdObjMgt_WriteData& operator<<(const occ::handle<Persistent>& thePersistent)
  {
    myDriver->PutReference(thePersistent ? thePersistent->RefNum() : 0);
    return *this;
  }

  Standard_EXPORT StdObjMgt_WriteData& operator<<(
    const occ::handle<StdObjMgt_Persistent>& thePersistent);

  template <class Type>
  StdObjMgt_WriteData& WriteValue(const Type& theValue)
  {
    *myDriver << theValue;
    return *this;
  }

  StdObjMgt_WriteData& operator<<(const char& theValue) { return WriteValue(theValue); }

  StdObjMgt_WriteData& operator<<(const char16_t& theValue) { return WriteValue(theValue); }

  StdObjMgt_WriteData& operator<<(const int& theValue) { return WriteValue(theValue); }

  StdObjMgt_WriteData& operator<<(const bool& theValue) { return WriteValue(theValue); }

  StdObjMgt_WriteData& operator<<(const double& theValue) { return WriteValue(theValue); }

  StdObjMgt_WriteData& operator<<(const float& theValue) { return WriteValue(theValue); }

private:
  occ::handle<Storage_BaseDriver> myDriver;
};

Standard_EXPORT StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData,
                                                const Standard_GUID& theGUID);

