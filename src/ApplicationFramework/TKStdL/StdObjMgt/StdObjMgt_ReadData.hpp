#pragma once

#include <Standard.hpp>
#include <Storage_BaseDriver.hpp>
#include <NCollection_Array1.hpp>

class StdObjMgt_Persistent;
class Standard_GUID;

//! Auxiliary data used to read persistent objects from a file.
class StdObjMgt_ReadData
{
public:
  //! Auxiliary class used to automate begin and end of
  //! reading object (eating opening and closing parenthesis)
  //! at constructor and destructor
  class ObjectSentry
  {
  public:
    explicit ObjectSentry(StdObjMgt_ReadData& theData)
        : myReadData(&theData)
    {
      myReadData->myDriver->BeginReadObjectData();
    }

    ~ObjectSentry() { myReadData->myDriver->EndReadObjectData(); }

  private:
    StdObjMgt_ReadData* myReadData;

    ObjectSentry(const ObjectSentry&)            = delete;
    ObjectSentry& operator=(const ObjectSentry&) = delete;
  };

  Standard_EXPORT StdObjMgt_ReadData(const occ::handle<Storage_BaseDriver>& theDriver,
                                     const int                              theNumberOfObjects);

  template <class Instantiator>
  void CreatePersistentObject(const int theRef, Instantiator theInstantiator)
  {
    myPersistentObjects(theRef) = theInstantiator();
  }

  Standard_EXPORT void ReadPersistentObject(const int theRef);

  occ::handle<StdObjMgt_Persistent> PersistentObject(const int theRef) const
  {
    return myPersistentObjects(theRef);
  }

  Standard_EXPORT occ::handle<StdObjMgt_Persistent> ReadReference();

  template <class Persistent>
  StdObjMgt_ReadData& operator>>(occ::handle<Persistent>& theTarget)
  {
    theTarget = occ::down_cast<Persistent>(ReadReference());
    return *this;
  }

  StdObjMgt_ReadData& operator>>(occ::handle<StdObjMgt_Persistent>& theTarget)
  {
    theTarget = ReadReference();
    return *this;
  }

  template <class Type>
  StdObjMgt_ReadData& ReadValue(Type& theValue)
  {
    *myDriver >> theValue;
    return *this;
  }

  StdObjMgt_ReadData& operator>>(char& theValue) { return ReadValue(theValue); }

  StdObjMgt_ReadData& operator>>(char16_t& theValue) { return ReadValue(theValue); }

  StdObjMgt_ReadData& operator>>(int& theValue) { return ReadValue(theValue); }

  StdObjMgt_ReadData& operator>>(bool& theValue) { return ReadValue(theValue); }

  StdObjMgt_ReadData& operator>>(double& theValue) { return ReadValue(theValue); }

  StdObjMgt_ReadData& operator>>(float& theValue) { return ReadValue(theValue); }

private:
  occ::handle<Storage_BaseDriver>                       myDriver;
  NCollection_Array1<occ::handle<StdObjMgt_Persistent>> myPersistentObjects;
};

Standard_EXPORT StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData,
                                               Standard_GUID&      theGUID);
