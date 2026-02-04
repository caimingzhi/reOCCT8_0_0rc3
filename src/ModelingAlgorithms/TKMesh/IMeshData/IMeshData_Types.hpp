#pragma once


#include <NCollection_Sequence.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Shared.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_DefineAlloc.hpp>
#include <NCollection_OccAllocator.hpp>
#include <IMeshData_ParametersListArrayAdaptor.hpp>
#include <TColStd_MapIteratorOfPackedMapOfInteger.hpp>
// Created on: 2002-07-30
// Created by: Michael SAZONOV
// Copyright (c) 2002-2014 OPEN CASCADE SAS
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


#include <NCollection_UBTree.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_List.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_DataMap.hpp>

/**
 * The algorithm of unbalanced binary  tree of overlapped bounding boxes with
 * the possibility of deleting objects from the tree.
 *
 * In addition to  the requirements to the object type  defined in the parent
 * class this  class requires that the  object can be hashed  and compared to
 * another object (functions HashCode and  IsEqual are defined for it), since
 * the class NCollection_DataMap  is used where the object  plays the role of
 * the key.
 */
template <class TheObjType, class TheBndType>
class NCollection_EBTree : public NCollection_UBTree<TheObjType, TheBndType>
{
public:
  typedef NCollection_UBTree<TheObjType, TheBndType> UBTree;
  typedef typename UBTree::TreeNode                  TreeNode;

  // ---------- PUBLIC METHODS ----------

  /**
   * Constructor.
   */
  NCollection_EBTree(const occ::handle<NCollection_BaseAllocator>& theAllocator = nullptr)
      : UBTree(theAllocator)
  {
  }

  /**
   * Updates the tree with a new object and its bounding box.
   * Extends the functionality of the parent method by maintaining
   * the map myObjNodeMap. Redefined virtual method.
   * @return
   *   False if the tree already contains theObj.
   */
  bool Add(const TheObjType& theObj, const TheBndType& theBnd) override
  {
    bool result = false;
    if (!Contains(theObj))
    {
      // Add object in the tree using parent method
      UBTree::Add(theObj, theBnd);

      // Update the map
      TreeNode& aNewNode = this->ChangeLastNode();
      myObjNodeMap.Bind(theObj, &aNewNode);
      // If the new node is not the root (has a parent) check the neighbour node
      if (!aNewNode.IsRoot())
      {
        TreeNode& aNeiNode = aNewNode.ChangeParent().ChangeChild(0);
        if (aNeiNode.IsLeaf())
        {
          myObjNodeMap.UnBind(aNeiNode.Object());
          myObjNodeMap.Bind(aNeiNode.Object(), &aNeiNode);
        }
      }
      result = true;
    }
    return result;
  }

  /**
   * Removes the given object and updates the tree.
   * @return
   *   False if the tree does not contain theObj
   */
  bool Remove(const TheObjType& theObj);

  /**
   * @return
   *   True if the tree contains the object.
   */
  bool Contains(const TheObjType& theObj) const { return myObjNodeMap.IsBound(theObj); }

  /**
   * @return
   *   The leaf node containing the object.
   */
  const TreeNode& FindNode(const TheObjType& theObj) const { return *myObjNodeMap.Find(theObj); }

  /**
   * Clears the contents of the tree. Redefined virtual method
   */
  void Clear(const occ::handle<NCollection_BaseAllocator>& aNewAlloc = nullptr) override
  {
    myObjNodeMap.Clear();
    UBTree::Clear(aNewAlloc);
  }

private:
  // ---------- PRIVATE METHODS ----------

  /// Copy constructor (prohibited).
  NCollection_EBTree(const NCollection_EBTree&) = delete;

  /// Assignment operator (prohibited).
  NCollection_EBTree& operator=(const NCollection_EBTree&) = delete;

  // ---------- PRIVATE FIELDS ----------

  NCollection_DataMap<TheObjType, TreeNode*> myObjNodeMap; ///< map of object to node pointer
};

// ================== METHODS TEMPLATES =====================

//=======================================================================
// function : Remove
// purpose  : Removes the given object and updates the tree.
//           Returns false if the tree does not contain theObj.
//=======================================================================

template <class TheObjType, class TheBndType>
bool NCollection_EBTree<TheObjType, TheBndType>::Remove(const TheObjType& theObj)
{
  bool result = false;
  if (Contains(theObj))
  {
    TreeNode* pNode = myObjNodeMap(theObj);
    if (pNode->IsRoot())
    {
      // it is the root, so clear all the tree
      Clear();
    }
    else
    {
      // it is a child of some parent,
      // so kill the child that contains theObj
      // and update bounding boxes of all ancestors
      myObjNodeMap.UnBind(theObj);
      TreeNode* pParent = &pNode->ChangeParent();
      pParent->Kill((pNode == &pParent->Child(0) ? 0 : 1), this->Allocator());
      if (pParent->IsLeaf())
      {
        // the parent node became a leaf, so update the map
        myObjNodeMap.UnBind(pParent->Object());
        myObjNodeMap.Bind(pParent->Object(), pParent);
      }
      while (!pParent->IsRoot())
      {
        pParent              = &pParent->ChangeParent();
        pParent->ChangeBnd() = pParent->Child(0).Bnd();
        pParent->ChangeBnd().Add(pParent->Child(1).Bnd());
      }
    }
    result = true;
  }
  return result;
}

// ======================================================================
// Declaration of handled version of NCollection_EBTree.
// In the macros below the arguments are:
// _HEBTREE      - the desired name of handled class
// _OBJTYPE      - the name of the object type
// _BNDTYPE      - the name of the bounding box type
// _HUBTREE      - the name of parent class
//                 (defined using macro DEFINE_HUBTREE)

#define DEFINE_HEBTREE(_HEBTREE, _OBJTYPE, _BNDTYPE, _HUBTREE)                                     \
  class _HEBTREE : public _HUBTREE                                                                 \
  {                                                                                                \
  public:                                                                                          \
    typedef NCollection_UBTree<_OBJTYPE, _BNDTYPE> UBTree;                                         \
    typedef NCollection_EBTree<_OBJTYPE, _BNDTYPE> EBTree;                                         \
                                                                                                   \
    _HEBTREE()                                                                                     \
        : _HUBTREE(new EBTree)                                                                     \
    {                                                                                              \
    }                                                                                              \
    /* Empty constructor */                                                                        \
                                                                                                   \
    /* Access to the methods of EBTree */                                                          \
                                                                                                   \
    bool Remove(const _OBJTYPE& theObj)                                                            \
    {                                                                                              \
      return ChangeETree().Remove(theObj);                                                         \
    }                                                                                              \
                                                                                                   \
    bool Contains(const _OBJTYPE& theObj) const                                                    \
    {                                                                                              \
      return ETree().Contains(theObj);                                                             \
    }                                                                                              \
                                                                                                   \
    const UBTree::TreeNode& FindNode(const _OBJTYPE& theObj) const                                 \
    {                                                                                              \
      return ETree().FindNode(theObj);                                                             \
    }                                                                                              \
                                                                                                   \
    /* Access to the extended tree algorithm */                                                    \
                                                                                                   \
    const EBTree& ETree() const noexcept                                                           \
    {                                                                                              \
      return (const EBTree&)Tree();                                                                \
    }                                                                                              \
    EBTree& ChangeETree() noexcept                                                                 \
    {                                                                                              \
      return (EBTree&)ChangeTree();                                                                \
    }                                                                                              \
                                                                                                   \
    DEFINE_STANDARD_RTTI_INLINE(_HEBTREE, _HUBTREE)                                                \
    /* Type management */                                                                          \
  };                                                                                               \
  DEFINE_STANDARD_HANDLE(_HEBTREE, _HUBTREE)

#define IMPLEMENT_HEBTREE(_HEBTREE, _HUBTREE)


#include <Bnd_Box2d.hpp>
#include <NCollection_CellFilter.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_UBTreeFiller.hpp>
#include <NCollection_IndexedMap.hpp>
#include <BRepMesh_Vertex.hpp>
#include <Bnd_B2.hpp>
#include <BRepMesh_Circle.hpp>
#include <BRepMesh_Triangle.hpp>
#include <BRepMesh_PairOfIndex.hpp>
#include <BRepMesh_Edge.hpp>

#include <memory>
#include <queue>

class IMeshData_Shape;
class IMeshData_Face;
class IMeshData_Wire;
class IMeshData_Edge;
class IMeshData_Curve;
class IMeshData_PCurve;
class IMeshData_Model;
class BRepMesh_VertexInspector;
class BRepMesh_CircleInspector;

#define DEFINE_INC_ALLOC                                                                           \
  DEFINE_NCOLLECTION_ALLOC                                                                         \
  void operator delete(void* /*theAddress*/)                                                       \
  {                                                                                                \
    /*it's inc allocator, nothing to do*/                                                          \
  }

namespace IMeshData
{
//! Default size for memory block allocated by IncAllocator.
/**
 * The idea here is that blocks of the given size are returned to the system
 * rather than retained in the malloc heap, at least on WIN32 and WIN64 platforms.
 */
#ifdef _WIN64
const size_t MEMORY_BLOCK_SIZE_HUGE = 1024 * 1024;
#else
const size_t MEMORY_BLOCK_SIZE_HUGE = 512 * 1024;
#endif

typedef IMeshData_Edge* IEdgePtr;
typedef IMeshData_Face* IFacePtr;

typedef occ::handle<IMeshData_Edge>   IEdgeHandle;
typedef occ::handle<IMeshData_Wire>   IWireHandle;
typedef occ::handle<IMeshData_Face>   IFaceHandle;
typedef occ::handle<IMeshData_Curve>  ICurveHandle;
typedef occ::handle<IMeshData_PCurve> IPCurveHandle;

typedef IMeshData_ParametersListArrayAdaptor<ICurveHandle> ICurveArrayAdaptor;
typedef occ::handle<ICurveArrayAdaptor>                    ICurveArrayAdaptorHandle;

typedef NCollection_Shared<NCollection_EBTree<int, Bnd_Box2d>> BndBox2dTree;
typedef NCollection_UBTreeFiller<int, Bnd_Box2d>               BndBox2dTreeFiller;

// Vectors
typedef NCollection_Shared<NCollection_Vector<IFaceHandle>>        VectorOfIFaceHandles;
typedef NCollection_Shared<NCollection_Vector<IWireHandle>>        VectorOfIWireHandles;
typedef NCollection_Shared<NCollection_Vector<IEdgeHandle>>        VectorOfIEdgeHandles;
typedef NCollection_Shared<NCollection_Vector<IPCurveHandle>>      VectorOfIPCurveHandles;
typedef NCollection_Shared<NCollection_Vector<IEdgePtr>>           VectorOfIEdgePtrs;
typedef NCollection_Shared<NCollection_Vector<bool>>               VectorOfBoolean;
typedef NCollection_Shared<NCollection_Vector<int>>                VectorOfInteger;
typedef NCollection_Shared<NCollection_Vector<TopAbs_Orientation>> VectorOfOrientation;
typedef NCollection_Shared<NCollection_Vector<BRepMesh_Triangle>>  VectorOfElements;
typedef NCollection_Shared<NCollection_Vector<BRepMesh_Circle>>    VectorOfCircle;

typedef NCollection_Shared<NCollection_Array1<BRepMesh_Vertex>> Array1OfVertexOfDelaun;
typedef NCollection_Shared<NCollection_Vector<BRepMesh_Vertex>> VectorOfVertex;

// Sequences
typedef NCollection_Shared<NCollection_Sequence<Bnd_B2d>> SequenceOfBndB2d;
typedef NCollection_Shared<NCollection_Sequence<int>>     SequenceOfInteger;
typedef NCollection_Shared<NCollection_Sequence<double>>  SequenceOfReal;

namespace Model
{
typedef std::deque<gp_Pnt, NCollection_OccAllocator<gp_Pnt>>     SequenceOfPnt;
typedef std::deque<gp_Pnt2d, NCollection_OccAllocator<gp_Pnt2d>> SequenceOfPnt2d;
typedef std::deque<double, NCollection_OccAllocator<double>>     SequenceOfReal;
typedef std::deque<int, NCollection_OccAllocator<int>>           SequenceOfInteger;
} // namespace Model

// Lists
typedef NCollection_Shared<NCollection_List<int>>           ListOfInteger;
typedef NCollection_Shared<NCollection_List<gp_Pnt2d>>      ListOfPnt2d;
typedef NCollection_Shared<NCollection_List<IPCurveHandle>> ListOfIPCurves;

typedef NCollection_Shared<TColStd_PackedMapOfInteger> MapOfInteger;
typedef TColStd_MapIteratorOfPackedMapOfInteger        IteratorOfMapOfInteger;

typedef NCollection_CellFilter<BRepMesh_CircleInspector> CircleCellFilter;
typedef NCollection_CellFilter<BRepMesh_VertexInspector> VertexCellFilter;

typedef NCollection_Shared<NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>>
  DMapOfShapeInteger;
typedef NCollection_Shared<NCollection_DataMap<IFacePtr, ListOfInteger>>
                                                                   DMapOfIFacePtrsListOfInteger;
typedef NCollection_Shared<NCollection_Map<IEdgePtr>>              MapOfIEdgePtr;
typedef NCollection_Shared<NCollection_Map<IFacePtr>>              MapOfIFacePtr;
typedef NCollection_Shared<NCollection_Map<BRepMesh_OrientedEdge>> MapOfOrientedEdges;
typedef NCollection_Shared<NCollection_Map<double>>                MapOfReal;
typedef NCollection_Shared<NCollection_IndexedDataMap<IFacePtr, ListOfIPCurves>>
  IDMapOfIFacePtrsListOfIPCurves;
typedef NCollection_Shared<NCollection_DataMap<IFacePtr, occ::handle<MapOfIEdgePtr>>>
  DMapOfIFacePtrsMapOfIEdgePtrs;
typedef NCollection_Shared<NCollection_IndexedDataMap<BRepMesh_Edge, BRepMesh_PairOfIndex>>
                                                                    IDMapOfLink;
typedef NCollection_Shared<NCollection_DataMap<int, ListOfInteger>> DMapOfIntegerListOfInteger;
typedef NCollection_Shared<NCollection_DataMap<int, bool>>          MapOfIntegerInteger;
typedef NCollection_Shared<NCollection_IndexedMap<double>>          IMapOfReal;

typedef NCollection_Shared<NCollection_Array1<int>> Array1OfInteger;
} // namespace IMeshData

