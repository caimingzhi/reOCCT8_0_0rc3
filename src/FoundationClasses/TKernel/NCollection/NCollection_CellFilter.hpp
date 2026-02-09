#pragma once

#include <NCollection_LocalArray.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_HashUtils.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_IncAllocator.hpp>

enum NCollection_CellFilter_Action
{
  CellFilter_Keep  = 0,
  CellFilter_Purge = 1
};

template <class Inspector>
class NCollection_CellFilter
{
public:
  typedef typename Inspector::Target Target;
  typedef typename Inspector::Point  Point;

public:
  NCollection_CellFilter(const int                                    theDim,
                         const double                                 theCellSize = 0,
                         const occ::handle<NCollection_IncAllocator>& theAlloc    = nullptr)
      : myCellSize(0, theDim - 1)
  {
    myDim = theDim;
    Reset(theCellSize, theAlloc);
  }

  NCollection_CellFilter(const double                                 theCellSize = 0,
                         const occ::handle<NCollection_IncAllocator>& theAlloc    = nullptr)
      : myCellSize(0, Inspector::Dimension - 1)
  {
    myDim = Inspector::Dimension;
    Reset(theCellSize, theAlloc);
  }

  void Reset(double theCellSize, const occ::handle<NCollection_IncAllocator>& theAlloc = nullptr)
  {
    for (int i = 0; i < myDim; i++)
      myCellSize(i) = theCellSize;
    resetAllocator(theAlloc);
  }

  void Reset(NCollection_Array1<double>&                  theCellSize,
             const occ::handle<NCollection_IncAllocator>& theAlloc = nullptr)
  {
    myCellSize = theCellSize;
    resetAllocator(theAlloc);
  }

  void Add(const Target& theTarget, const Point& thePnt)
  {
    Cell aCell(thePnt, myCellSize);
    add(aCell, theTarget);
  }

  void Add(const Target& theTarget, const Point& thePntMin, const Point& thePntMax)
  {

    Cell aCellMin(thePntMin, myCellSize);
    Cell aCellMax(thePntMax, myCellSize);
    Cell aCell = aCellMin;

    iterateAdd(myDim - 1, aCell, aCellMin, aCellMax, theTarget);
  }

  void Remove(const Target& theTarget, const Point& thePnt)
  {
    Cell aCell(thePnt, myCellSize);
    remove(aCell, theTarget);
  }

  void Remove(const Target& theTarget, const Point& thePntMin, const Point& thePntMax)
  {

    Cell aCellMin(thePntMin, myCellSize);
    Cell aCellMax(thePntMax, myCellSize);
    Cell aCell = aCellMin;

    iterateRemove(myDim - 1, aCell, aCellMin, aCellMax, theTarget);
  }

  void Inspect(const Point& thePnt, Inspector& theInspector)
  {
    Cell aCell(thePnt, myCellSize);
    inspect(aCell, theInspector);
  }

  void Inspect(const Point& thePntMin, const Point& thePntMax, Inspector& theInspector)
  {

    Cell aCellMin(thePntMin, myCellSize);
    Cell aCellMax(thePntMax, myCellSize);
    Cell aCell = aCellMin;

    iterateInspect(myDim - 1, aCell, aCellMin, aCellMax, theInspector);
  }

#if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x530)
public:
#else
protected:
#endif

  struct ListNode
  {
    ListNode() { throw Standard_NoSuchObject("NCollection_CellFilter::ListNode()"); }

    Target    Object;
    ListNode* Next;
  };

  typedef int Cell_IndexType;

  struct Cell
  {
  public:
    Cell(const Point& thePnt, const NCollection_Array1<double>& theCellSize)
        : index(theCellSize.Size()),
          Objects(nullptr)
    {
      for (int i = 0; i < theCellSize.Size(); i++)
      {
        double aVal = (double)(Inspector::Coord(i, thePnt) / theCellSize(theCellSize.Lower() + i));

        index[i] = Cell_IndexType((aVal > INT_MAX - 1)   ? fmod(aVal, (double)INT_MAX)
                                  : (aVal < INT_MIN + 1) ? fmod(aVal, (double)INT_MIN)
                                                         : aVal);
      }
    }

    Cell(const Cell& theOther)
        : index(theOther.index.Size())
    {
      (*this) = theOther;
    }

    void operator=(const Cell& theOther) noexcept
    {
      int aDim = int(theOther.index.Size());
      for (int anIdx = 0; anIdx < aDim; anIdx++)
        index[anIdx] = theOther.index[anIdx];

      Objects                   = theOther.Objects;
      ((Cell&)theOther).Objects = nullptr;
    }

    ~Cell()
    {
      for (ListNode* aNode = Objects; aNode; aNode = aNode->Next)
        aNode->Object.~Target();

      Objects = nullptr;
    }

    bool IsEqual(const Cell& theOther) const noexcept
    {
      int aDim = int(theOther.index.Size());
      for (int i = 0; i < aDim; i++)
        if (index[i] != theOther.index[i])
          return false;
      return true;
    }

    bool operator==(const Cell& theOther) const noexcept { return IsEqual(theOther); }

  public:
    NCollection_LocalArray<Cell_IndexType, 10> index;
    ListNode*                                  Objects;
  };

  struct CellHasher
  {
    size_t operator()(const Cell& theCell) const noexcept
    {

      const std::size_t aDim = theCell.index.Size();
      return opencascade::hashBytes(&theCell.index[0],
                                    static_cast<int>(aDim * sizeof(Cell_IndexType)));
    }

    bool operator()(const Cell& theCell1, const Cell& theCell2) const noexcept
    {
      return theCell1 == theCell2;
    }
  };

  typedef NCollection_Map<Cell, CellHasher> CellMap;

protected:
  void resetAllocator(const occ::handle<NCollection_IncAllocator>& theAlloc)
  {
    if (theAlloc.IsNull())
      myAllocator = new NCollection_IncAllocator;
    else
      myAllocator = theAlloc;
    myCells.Clear(myAllocator);
  }

  void add(const Cell& theCell, const Target& theTarget)
  {

    Cell& aMapCell = (Cell&)myCells.Added(theCell);

    ListNode* aNode = (ListNode*)myAllocator->Allocate(sizeof(ListNode));
    new (&aNode->Object) Target(theTarget);
    aNode->Next      = aMapCell.Objects;
    aMapCell.Objects = aNode;
  }

  void iterateAdd(int           idim,
                  Cell&         theCell,
                  const Cell&   theCellMin,
                  const Cell&   theCellMax,
                  const Target& theTarget)
  {
    const Cell_IndexType aStart = theCellMin.index[idim];
    const Cell_IndexType anEnd  = theCellMax.index[idim];
    for (Cell_IndexType i = aStart; i <= anEnd; ++i)
    {
      theCell.index[idim] = i;
      if (idim)
      {
        iterateAdd(idim - 1, theCell, theCellMin, theCellMax, theTarget);
      }
      else
      {
        add(theCell, theTarget);
      }
    }
  }

  void remove(const Cell& theCell, const Target& theTarget)
  {

    if (!myCells.Contains(theCell))
      return;

    Cell&     aMapCell = (Cell&)myCells.Added(theCell);
    ListNode* aNode    = aMapCell.Objects;
    ListNode* aPrev    = nullptr;
    while (aNode)
    {
      ListNode* aNext = aNode->Next;
      if (Inspector::IsEqual(aNode->Object, theTarget))
      {
        aNode->Object.~Target();
        (aPrev ? aPrev->Next : aMapCell.Objects) = aNext;
      }
      else
        aPrev = aNode;
      aNode = aNext;
    }
  }

  void iterateRemove(int           idim,
                     Cell&         theCell,
                     const Cell&   theCellMin,
                     const Cell&   theCellMax,
                     const Target& theTarget)
  {
    const Cell_IndexType aStart = theCellMin.index[idim];
    const Cell_IndexType anEnd  = theCellMax.index[idim];
    for (Cell_IndexType i = aStart; i <= anEnd; ++i)
    {
      theCell.index[idim] = i;
      if (idim)
      {
        iterateRemove(idim - 1, theCell, theCellMin, theCellMax, theTarget);
      }
      else
      {
        remove(theCell, theTarget);
      }
    }
  }

  void inspect(const Cell& theCell, Inspector& theInspector)
  {

    if (!myCells.Contains(theCell))
      return;

    Cell&     aMapCell = (Cell&)myCells.Added(theCell);
    ListNode* aNode    = aMapCell.Objects;
    ListNode* aPrev    = nullptr;
    while (aNode)
    {
      ListNode*                     aNext    = aNode->Next;
      NCollection_CellFilter_Action anAction = theInspector.Inspect(aNode->Object);

      if (anAction == CellFilter_Purge)
      {
        aNode->Object.~Target();
        (aPrev ? aPrev->Next : aMapCell.Objects) = aNext;
      }
      else
        aPrev = aNode;
      aNode = aNext;
    }
  }

  void iterateInspect(int         idim,
                      Cell&       theCell,
                      const Cell& theCellMin,
                      const Cell& theCellMax,
                      Inspector&  theInspector)
  {
    const Cell_IndexType aStart = theCellMin.index[idim];
    const Cell_IndexType anEnd  = theCellMax.index[idim];
    for (Cell_IndexType i = aStart; i <= anEnd; ++i)
    {
      theCell.index[idim] = i;
      if (idim)
      {
        iterateInspect(idim - 1, theCell, theCellMin, theCellMax, theInspector);
      }
      else
      {
        inspect(theCell, theInspector);
      }
    }
  }

protected:
  int                                    myDim;
  occ::handle<NCollection_BaseAllocator> myAllocator;
  CellMap                                myCells;
  NCollection_Array1<double>             myCellSize;
};

class gp_XYZ;

struct NCollection_CellFilter_InspectorXYZ
{

  enum
  {
    Dimension = 3
  };

  typedef gp_XYZ Point;

  static double Coord(int i, const Point& thePnt) { return thePnt.Coord(i + 1); }

  Point Shift(const Point& thePnt, double theTol) const
  {
    return Point(thePnt.X() + theTol, thePnt.Y() + theTol, thePnt.Z() + theTol);
  }
};

class gp_XY;

struct NCollection_CellFilter_InspectorXY
{

  enum
  {
    Dimension = 2
  };

  typedef gp_XY Point;

  static double Coord(int i, const Point& thePnt) { return thePnt.Coord(i + 1); }

  Point Shift(const Point& thePnt, double theTol) const
  {
    return Point(thePnt.X() + theTol, thePnt.Y() + theTol);
  }
};
