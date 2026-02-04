#pragma once


#include <StdObjMgt_Attribute.hpp>
#include <StdObjMgt_Persistent.hpp>
#include <StdPersistent_HArray1.hpp>
#include <StdLPersistent_HArray1.hpp>
#include <StdLPersistent_HString.hpp>

#include <TNaming_Naming.hpp>

class TNaming_Name;

class StdPersistent_Naming
{
public:
  class NamedShape : public StdObjMgt_Attribute<TNaming_NamedShape>
  {
  public:
    //! Read persistent data from a file.
    inline void Read(StdObjMgt_ReadData& theReadData)
    {
      theReadData >> myOldShapes >> myNewShapes >> myShapeStatus >> myVersion;
    }

    //! Read persistent data from a file.
    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myOldShapes << myNewShapes << myShapeStatus << myVersion;
    }

    //! Gets persistent child objects
    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
    {
      if (!myOldShapes.IsNull())
        theChildren.Append(myOldShapes);
      if (!myNewShapes.IsNull())
        theChildren.Append(myNewShapes);
    }

    //! Returns persistent type name
    inline const char* PName() const { return "PNaming_NamedShape"; }

    //! Import transient attribute from the persistent data.
    void Import(const occ::handle<TNaming_NamedShape>& theAttribute) const;

  private:
    Handle(StdPersistent_HArray1::Shape1) myOldShapes;
    Handle(StdPersistent_HArray1::Shape1) myNewShapes;
    int                                   myShapeStatus;
    int                                   myVersion;
  };

  class Name : public StdObjMgt_Persistent
  {
  public:
    //! Read persistent data from a file.
    Standard_EXPORT void Read(StdObjMgt_ReadData& theReadData) override;
    //! Read persistent data from a file.
    Standard_EXPORT void Write(StdObjMgt_WriteData& theWriteData) const override;

    //! Gets persistent child objects
    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const override
    {
      if (!myArgs.IsNull())
        theChildren.Append(myArgs);
      if (!myStop.IsNull())
        theChildren.Append(myStop);
    }

    //! Returns persistent type name
    inline const char* PName() const override { return "PNaming_Name"; }

    //! Import transient object from the persistent data.
    Standard_EXPORT virtual void Import(TNaming_Name&                theName,
                                        const occ::handle<TDF_Data>& theDF) const;

  private:
    int                                        myType;
    int                                        myShapeType;
    Handle(StdLPersistent_HArray1::Persistent) myArgs;
    occ::handle<StdObjMgt_Persistent>          myStop;
    int                                        myIndex;
  };

  class Name_1 : public Name
  {
  public:
    //! Read persistent data from a file.
    Standard_EXPORT void Read(StdObjMgt_ReadData& theReadData) override;
    //! Read persistent data from a file.
    Standard_EXPORT void Write(StdObjMgt_WriteData& theWriteData) const override;

    //! Gets persistent child objects
    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const override
    {
      Name::PChildren(theChildren);
      if (!myContextLabel.IsNull())
        theChildren.Append(myContextLabel);
    }

    //! Returns persistent type name
    inline const char* PName() const override { return "PNaming_Name_1"; }

    //! Import transient object from the persistent data.
    Standard_EXPORT void Import(TNaming_Name&                theName,
                                const occ::handle<TDF_Data>& theDF) const override;

  private:
    Handle(StdLPersistent_HString::Ascii) myContextLabel;
  };

  class Name_2 : public Name_1
  {
  public:
    //! Read persistent data from a file.
    Standard_EXPORT void Read(StdObjMgt_ReadData& theReadData) override;
    //! Read persistent data from a file.
    Standard_EXPORT void Write(StdObjMgt_WriteData& theWriteData) const override;

    //! Gets persistent child objects
    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const override
    {
      Name_1::PChildren(theChildren);
    }

    //! Returns persistent type name
    inline const char* PName() const override { return "PNaming_Name_2"; }

    //! Import transient object from the persistent data.
    Standard_EXPORT void Import(TNaming_Name&                theName,
                                const occ::handle<TDF_Data>& theDF) const override;

  private:
    int myOrientation;
  };

  class Naming : public StdObjMgt_Attribute<TNaming_Naming>::SingleRef
  {
  public:
    //! Import transient attribute from the persistent data.
    Standard_EXPORT void ImportAttribute() override;
  };

  class Naming_1 : public Naming
  {
  public:
    //! Import transient attribute from the persistent data.
    Standard_EXPORT void ImportAttribute() override;
  };

  typedef Naming Naming_2;
};

