#pragma once

#include <BVH_Box.hpp>
#include <BVH_Properties.hpp>

//! A non-template class for using as base for BVH_Object
//! (just to have a named base class).
class BVH_ObjectTransient : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(BVH_ObjectTransient, Standard_Transient)
public:
  //! Returns properties of the geometric object.
  virtual const occ::handle<BVH_Properties>& Properties() const { return myProperties; }

  //! Sets properties of the geometric object.
  virtual void SetProperties(const occ::handle<BVH_Properties>& theProperties)
  {
    myProperties = theProperties;
  }

  //! Returns TRUE if object state should be updated.
  virtual bool IsDirty() const { return myIsDirty; }

  //! Marks object state as outdated (needs BVH rebuilding).
  virtual void MarkDirty() { myIsDirty = true; }

protected:
  //! Creates new abstract geometric object.
  BVH_ObjectTransient()
      : myIsDirty(false)
  {
  }

protected:
  bool                        myIsDirty;    //!< Marks internal object state as outdated
  occ::handle<BVH_Properties> myProperties; //!< Generic properties assigned to the object
};

//! Abstract geometric object bounded by BVH box.
//! \tparam T Numeric data type
//! \tparam N Vector dimension
template <class T, int N>
class BVH_Object : public BVH_ObjectTransient
{
public:
  //! Creates new abstract geometric object.
  BVH_Object() = default;

  //! Releases resources of geometric object.
  ~BVH_Object() override = default;

public:
  //! Returns AABB of the geometric object.
  virtual BVH_Box<T, N> Box() const = 0;
};
