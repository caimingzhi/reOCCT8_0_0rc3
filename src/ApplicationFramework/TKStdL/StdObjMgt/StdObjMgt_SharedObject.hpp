#pragma once

#include <Standard_NoSuchObject.hpp>
#include <StdObjMgt_Persistent.hpp>

class StdObjMgt_SharedObject
{
public:
  template <class Transient>
  class AbstractPersistentBase : public Standard_Transient
  {
  public:
    virtual occ::handle<Transient> Import() const = 0;
  };

  template <class TransientT, class Base = StdObjMgt_Persistent>
  class SharedBase : public Base
  {
  public:
    inline void Transient(const occ::handle<TransientT>& theTransient)
    {
      myTransient = theTransient;
    }

    inline const occ::handle<TransientT>& Import() { return myTransient; }

  protected:
    occ::handle<TransientT> myTransient;
  };

  template <class Base, class Transient, class Persistent = AbstractPersistentBase<Transient>>
  class DelayedBase : public Base
  {
  public:
    typedef Transient  TransientBase;
    typedef Persistent PersistentBase;

    virtual occ::handle<Transient> Import() { return myTransient; }

  public:
    occ::handle<Transient> myTransient;
  };

  template <class Base, class PersistentData, class Transient = typename Base::TransientBase>
  class IgnoreData : public Base
  {
  public:
    virtual void Read(StdObjMgt_ReadData& theReadData) { PersistentData().Read(theReadData); }

    virtual void Write(StdObjMgt_WriteData& theWriteData) const
    {
      PersistentData().Write(theWriteData);
    }

    virtual void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
    {
      PersistentData().PChildren(theChildren);
    }

    virtual const char* PName() const { return PersistentData().PName(); }

    virtual occ::handle<Transient> Import() { return nullptr; }
  };

private:
  template <class Base>
  class delayedSubBase : public Base
  {
  public:
    virtual Handle(typename Base::TransientBase) Import()
    {
      if (Base::myTransient.IsNull() && !myPersistent.IsNull())
      {
        Base::myTransient = myPersistent->Import();
        myPersistent.Nullify();
      }

      return Base::myTransient;
    }

  public:
    Handle(typename Base::PersistentBase) myPersistent;
  };

public:
  template <class Base, class Persistent = typename Base::PersistentBase>
  class Delayed : public delayedSubBase<Base>
  {
  private:
    template <class T1, class T2>
    struct DownCast
    {
      static occ::handle<T1> make(const occ::handle<T2>& theT2)
      {
        return occ::down_cast<T1>(theT2);
      }
    };

    template <class T>
    struct DownCast<T, T>
    {
      static occ::handle<T> make(const occ::handle<T>& theT) { return theT; }
    };

  public:
    virtual void Read(StdObjMgt_ReadData& theReadData)
    {
      occ::handle<Persistent> aPersistent = new Persistent;
      aPersistent->Read(theReadData);
      this->myPersistent = aPersistent;
    }

    virtual void Write(StdObjMgt_WriteData& theWriteData) const
    {
      occ::handle<Persistent> aPersistent =
        DownCast<Persistent, typename Base::PersistentBase>::make(this->myPersistent);
      Standard_NoSuchObject_Raise_if(
        aPersistent.IsNull(),
        "StdObjMgt_SharedObject::Delayed::Write - persistent object wasn't set for writing!");
      aPersistent->Write(theWriteData);
    }

    virtual void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
    {
      occ::handle<Persistent> aPersistent =
        DownCast<Persistent, typename Base::PersistentBase>::make(this->myPersistent);
      Standard_NoSuchObject_Raise_if(
        aPersistent.IsNull(),
        "StdObjMgt_SharedObject::Delayed::PChildren - persistent object wasn't set for writing!");
      aPersistent->PChildren(theChildren);
    }

    virtual const char* PName() const
    {
      occ::handle<Persistent> aPersistent =
        DownCast<Persistent, typename Base::PersistentBase>::make(this->myPersistent);
      Standard_NoSuchObject_Raise_if(
        aPersistent.IsNull(),
        "StdObjMgt_SharedObject::Delayed::PName - persistent object wasn't set for writing!");
      return aPersistent->PName();
    }
  };
};
