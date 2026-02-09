#pragma once

#include <StdObjMgt_Persistent.hpp>
#include <StdObjMgt_ReadData.hpp>
#include <StdObjMgt_WriteData.hpp>

template <class Transient>
class StdObjMgt_Attribute : public Standard_Transient
{
  class base : public StdObjMgt_Persistent
  {
  public:
    occ::handle<TDF_Attribute> CreateAttribute() override { return myTransient = new Transient; }

    occ::handle<TDF_Attribute> GetAttribute() const override
    {
      return occ::handle<TDF_Attribute>(myTransient);
    }

  protected:
    occ::handle<Transient> myTransient;
  };

public:
  class Static : public base
  {
  };

  template <class DataType>
  class Simple : public Static
  {
  public:
    void Read(StdObjMgt_ReadData& theReadData) override { theReadData >> myData; }

    void Write(StdObjMgt_WriteData& theWriteData) const override { theWriteData << myData; }

    void PChildren(StdObjMgt_Persistent::SequenceOfPersistent&) const override {}

    const char* PName() const override { return "StdObjMgt_Attribute::undefined"; }

  protected:
    DataType myData;
  };

  struct SingleInt : Simple<int>
  {
  };

  struct SingleRef : Simple<occ::handle<StdObjMgt_Persistent>>
  {
  };

private:
  template <class Persistent>
  class container : public base
  {
  public:
    void Read(StdObjMgt_ReadData& theReadData) override
    {
      myPersistent = new Persistent;
      myPersistent->Read(theReadData);
    }

    void Write(StdObjMgt_WriteData& theWriteData) const override
    {
      myPersistent->Write(theWriteData);
    }

    void PChildren(StdObjMgt_Persistent::SequenceOfPersistent&) const override {}

    const char* PName() const override { return myPersistent->PName(); }

    void ImportAttribute() override
    {
      if (myPersistent && this->myTransient)
      {
        myPersistent->Import(this->myTransient);
        myPersistent.Nullify();
      }
    }

  private:
    occ::handle<Persistent> myPersistent;
  };

public:
  template <class Persistent>
  static occ::handle<StdObjMgt_Persistent> Instantiate()
  {
    return new container<Persistent>;
  }
};
