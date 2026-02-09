#pragma once

#include <BVH_Box.hpp>
#include <BVH_Properties.hpp>

class BVH_ObjectTransient : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(BVH_ObjectTransient, Standard_Transient)
public:
  virtual const occ::handle<BVH_Properties>& Properties() const { return myProperties; }

  virtual void SetProperties(const occ::handle<BVH_Properties>& theProperties)
  {
    myProperties = theProperties;
  }

  virtual bool IsDirty() const { return myIsDirty; }

  virtual void MarkDirty() { myIsDirty = true; }

protected:
  BVH_ObjectTransient()
      : myIsDirty(false)
  {
  }

protected:
  bool                        myIsDirty;
  occ::handle<BVH_Properties> myProperties;
};

template <class T, int N>
class BVH_Object : public BVH_ObjectTransient
{
public:
  BVH_Object() = default;

  ~BVH_Object() override = default;

public:
  virtual BVH_Box<T, N> Box() const = 0;
};
