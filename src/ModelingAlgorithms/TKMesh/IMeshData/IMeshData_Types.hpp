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

#include <NCollection_UBTree.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_List.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_DataMap.hpp>

template <class TheObjType, class TheBndType>
class NCollection_EBTree : public NCollection_UBTree<TheObjType, TheBndType>
{
public:
  typedef NCollection_UBTree<TheObjType, TheBndType> UBTree;
  typedef typename UBTree::TreeNode                  TreeNode;

  NCollection_EBTree(const occ::handle<NCollection_BaseAllocator>& theAllocator = nullptr)
      : UBTree(theAllocator)
  {
  }

  bool Add(const TheObjType& theObj, const TheBndType& theBnd) override
  {
    bool result = false;
    if (!Contains(theObj))
    {

      UBTree::Add(theObj, theBnd);

      TreeNode& aNewNode = this->ChangeLastNode();
      myObjNodeMap.Bind(theObj, &aNewNode);

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

  bool Remove(const TheObjType& theObj);

  bool Contains(const TheObjType& theObj) const { return myObjNodeMap.IsBound(theObj); }

  const TreeNode& FindNode(const TheObjType& theObj) const { return *myObjNodeMap.Find(theObj); }

  void Clear(const occ::handle<NCollection_BaseAllocator>& aNewAlloc = nullptr) override
  {
    myObjNodeMap.Clear();
    UBTree::Clear(aNewAlloc);
  }

private:
  NCollection_EBTree(const NCollection_EBTree&) = delete;

  NCollection_EBTree& operator=(const NCollection_EBTree&) = delete;

  NCollection_DataMap<TheObjType, TreeNode*> myObjNodeMap;
};

template <class TheObjType, class TheBndType>
bool NCollection_EBTree<TheObjType, TheBndType>::Remove(const TheObjType& theObj)
{
  bool result = false;
  if (Contains(theObj))
  {
    TreeNode* pNode = myObjNodeMap(theObj);
    if (pNode->IsRoot())
    {

      Clear();
    }
    else
    {

      myObjNodeMap.UnBind(theObj);
      TreeNode* pParent = &pNode->ChangeParent();
      pParent->Kill((pNode == &pParent->Child(0) ? 0 : 1), this->Allocator());
      if (pParent->IsLeaf())
      {

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
  };                                                                                               \
  DEFINE_STANDARD_HANDLECLASS(_HEBTREE, _HUBTREE, Standard_Transient)

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
  void operator delete(void*) {}

namespace IMeshData
{

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
