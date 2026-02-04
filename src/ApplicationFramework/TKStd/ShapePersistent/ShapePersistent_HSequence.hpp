#pragma once


#include <Standard_NotImplemented.hpp>

#include <StdObjMgt_Persistent.hpp>
#include <StdObject_gp_Vectors.hpp>

#include <gp_XYZ.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <gp_Pnt.hpp>
#include <gp_Dir.hpp>
#include <gp_Vec.hpp>

class ShapePersistent_HSequence
{
  template <class SequenceClass>
  class node : public StdObjMgt_Persistent
  {
  public:
    typedef typename SequenceClass::value_type ItemType;

  public:
    //! Read persistent data from a file.
    Standard_EXPORT void Read(StdObjMgt_ReadData& theReadData) override;

    //! Write persistent data to a file.
    Standard_EXPORT void Write(StdObjMgt_WriteData& theWriteData) const override;

    //! Gets persistent objects
    void PChildren(SequenceOfPersistent& theChildren) const override
    {
      theChildren.Append(this->myPreviuos);
      theChildren.Append(this->myNext);
    }

    //! Returns persistent type name
    const char* PName() const override
    {
      throw Standard_NotImplemented("ShapePersistent_HSequence::node::PName - not implemented");
    }

    const Handle(node)& Previuos() const { return myPreviuos; }

    const Handle(node)& Next() const { return myNext; }

    const ItemType& Item() const { return myItem; }

  private:
    Handle(node) myPreviuos;
    Handle(node) myNext;
    ItemType     myItem;
  };

  template <class SequenceClass>
  class instance : public StdObjMgt_Persistent
  {
  public:
    typedef node<SequenceClass> Node;

  public:
    //! Empty constructor.
    instance()
        : mySize(0)
    {
    }

    //! Read persistent data from a file.
    Standard_EXPORT void Read(StdObjMgt_ReadData& theReadData) override;

    //! Write persistent data to a file.
    Standard_EXPORT void Write(StdObjMgt_WriteData& theWriteData) const override;

    //! Gets persistent objects
    void PChildren(SequenceOfPersistent& theChildren) const override
    {
      theChildren.Append(this->myFirst);
      theChildren.Append(this->myLast);
    }

    //! Returns persistent type name
    const char* PName() const override
    {
      throw Standard_NotImplemented("ShapePersistent_HSequence::instance::PName - not implemented");
    }

    //! Import transient object from the persistent data.
    Standard_EXPORT occ::handle<SequenceClass> Import() const;

  private:
    occ::handle<Node> myFirst;
    occ::handle<Node> myLast;
    int               mySize;
  };

public:
  typedef instance<NCollection_HSequence<gp_XYZ>> XYZ;
  typedef instance<NCollection_HSequence<gp_Pnt>> Pnt;
  typedef instance<NCollection_HSequence<gp_Dir>> Dir;
  typedef instance<NCollection_HSequence<gp_Vec>> Vec;
};

//=======================================================================
// XYZ
//=======================================================================
template <>
const char* ShapePersistent_HSequence::instance<NCollection_HSequence<gp_XYZ>>::PName() const;

template <>
const char* ShapePersistent_HSequence::node<NCollection_HSequence<gp_XYZ>>::PName() const;

//=======================================================================
// Pnt
//=======================================================================
template <>
const char* ShapePersistent_HSequence::instance<NCollection_HSequence<gp_Pnt>>::PName() const;

template <>
const char* ShapePersistent_HSequence::node<NCollection_HSequence<gp_Pnt>>::PName() const;

//=======================================================================
// Dir
//=======================================================================
template <>
const char* ShapePersistent_HSequence::instance<NCollection_HSequence<gp_Dir>>::PName() const;

template <>
const char* ShapePersistent_HSequence::node<NCollection_HSequence<gp_Dir>>::PName() const;

//=======================================================================
// Vec
//=======================================================================
template <>
const char* ShapePersistent_HSequence::instance<NCollection_HSequence<gp_Vec>>::PName() const;

template <>
const char* ShapePersistent_HSequence::node<NCollection_HSequence<gp_Vec>>::PName() const;

