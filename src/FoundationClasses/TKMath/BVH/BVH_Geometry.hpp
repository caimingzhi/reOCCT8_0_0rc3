// Created on: 2013-12-20
// Created by: Denis BOGOLEPOV
// Copyright (c) 2013-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef BVH_Geometry_HeaderFile
#define BVH_Geometry_HeaderFile
// Created on: 2013-12-20
// Created by: Denis BOGOLEPOV
// Copyright (c) 2013-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef BVH_ObjectSet_HeaderFile
#define BVH_ObjectSet_HeaderFile

#include <BVH_Set.hpp>
#include <BVH_Object.hpp>

//! Array of abstract entities (bounded by BVH boxes) to built BVH.
//! \tparam T Numeric data type
//! \tparam N Vector dimension
template <class T, int N>
class BVH_ObjectSet : public BVH_Set<T, N>
{
public:
  //! Type of array of geometric objects.
  typedef NCollection_Vector<opencascade::handle<BVH_Object<T, N>>> BVH_ObjectList;

public:
  //! Creates new set of geometric objects.
  BVH_ObjectSet() = default;

  //! Releases resources of set of geometric objects.
  ~BVH_ObjectSet() override = default;

public:
  //! Removes all geometric objects.
  virtual void Clear()
  {
    for (typename BVH_ObjectList::Iterator anObjectIter(myObjects); anObjectIter.More();
         anObjectIter.Next())
    {
      anObjectIter.ChangeValue().Nullify();
    }
    myObjects.Clear();
  }

  //! Returns reference to the array of geometric objects.
  BVH_ObjectList& Objects() { return myObjects; }

  //! Returns reference to the array of geometric objects.
  const BVH_ObjectList& Objects() const { return myObjects; }

public:
  //! Return total number of objects.
  int Size() const override { return myObjects.Size(); }

  //! Returns AABB of entire set of objects.
  using BVH_Set<T, N>::Box;

  //! Returns AABB of the given object.
  BVH_Box<T, N> Box(const int theIndex) const override { return myObjects.Value(theIndex)->Box(); }

  //! Returns centroid position along the given axis.
  T Center(const int theIndex, const int theAxis) const override
  {
    // Note: general implementation, not optimal
    return BVH::CenterAxis<T, N>::Center(myObjects.Value(theIndex)->Box(), theAxis);
  }

  //! Performs transposing the two given objects in the set.
  void Swap(const int theIndex1, const int theIndex2) override
  {
    std::swap(myObjects.ChangeValue(theIndex1), myObjects.ChangeValue(theIndex2));
  }

protected:
  BVH_ObjectList myObjects; //!< Array of geometric objects
};

#endif // _BVH_ObjectSet_Header

#include <BVH_Builder.hpp>
#include <BVH_BinnedBuilder.hpp>

//! BVH geometry as a set of abstract geometric objects
//! organized with bounding volume hierarchy (BVH).
//! \tparam T Numeric data type
//! \tparam N Vector dimension
template <class T, int N>
class BVH_Geometry : public BVH_ObjectSet<T, N>
{
public:
  //! Creates uninitialized BVH geometry.
  BVH_Geometry()
      : myIsDirty(false),
        myBVH(new BVH_Tree<T, N>()),
        // set default builder - binned SAH split
        myBuilder(new BVH_BinnedBuilder<T, N, BVH_Constants_NbBinsOptimal>(
          BVH_Constants_LeafNodeSizeSingle))
  {
    //
  }

  //! Creates uninitialized BVH geometry.
  BVH_Geometry(const opencascade::handle<BVH_Builder<T, N>>& theBuilder)
      : myIsDirty(false),
        myBVH(new BVH_Tree<T, N>()),
        myBuilder(theBuilder)
  {
    //
  }

  //! Releases resources of BVH geometry.
  ~BVH_Geometry() override
  {
    myBVH.Nullify();
    myBuilder.Nullify();
  }

public:
  //! Returns TRUE if geometry state should be updated.
  virtual bool IsDirty() const { return myIsDirty; }

  //! Marks geometry as outdated.
  virtual void MarkDirty() { myIsDirty = true; }

  //! Returns AABB of the given object.
  using BVH_ObjectSet<T, N>::Box;

  //! Returns AABB of the whole geometry.
  BVH_Box<T, N> Box() const override
  {
    if (myIsDirty)
    {
      myBox = BVH_Set<T, N>::Box();
    }
    return myBox;
  }

  //! Returns BVH tree (and builds it if necessary).
  virtual const opencascade::handle<BVH_Tree<T, N>>& BVH()
  {
    if (myIsDirty)
    {
      Update();
    }
    return myBVH;
  }

  //! Returns the method (builder) used to construct BVH.
  virtual const opencascade::handle<BVH_Builder<T, N>>& Builder() const { return myBuilder; }

  //! Sets the method (builder) used to construct BVH.
  virtual void SetBuilder(const opencascade::handle<BVH_Builder<T, N>>& theBuilder)
  {
    myBuilder = theBuilder;
  }

protected:
  //! Updates internal geometry state.
  virtual void Update()
  {
    if (myIsDirty)
    {
      myBuilder->Build(this, myBVH.operator->(), Box());
      myIsDirty = false;
    }
  }

protected:
  bool                                   myIsDirty; //!< Is geometry state outdated?
  opencascade::handle<BVH_Tree<T, N>>    myBVH;     //!< Constructed high-level BVH
  opencascade::handle<BVH_Builder<T, N>> myBuilder; //!< Builder for high-level BVH

  mutable BVH_Box<T, N> myBox; //!< Cached bounding box of geometric objects
};

#endif // _BVH_Geometry_Header
