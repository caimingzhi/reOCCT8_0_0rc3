#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_DataMap.hpp>
#include <BOPDS_CommonBlock.hpp>
#include <NCollection_Map.hpp>
#include <BOPDS_Pair.hpp>
#include <BOPDS_PaveBlock.hpp>
#include <NCollection_Vector.hpp>
#include <BOPDS_FaceInfo.hpp>
#include <BOPDS_IndexRange.hpp>
#include <BOPDS_Interf.hpp>
#include <BOPDS_ShapeInfo.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Precision.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <NCollection_List.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>

class BOPDS_IndexRange;
class BOPDS_ShapeInfo;
class TopoDS_Shape;
class BOPDS_PaveBlock;
class BOPDS_CommonBlock;
class BOPDS_FaceInfo;
class Bnd_Box;

class BOPDS_DS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPDS_DS();

  Standard_EXPORT virtual ~BOPDS_DS();

  Standard_EXPORT BOPDS_DS(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT void Clear();

  Standard_EXPORT const occ::handle<NCollection_BaseAllocator>& Allocator() const;

  Standard_EXPORT void SetArguments(const NCollection_List<TopoDS_Shape>& theLS);

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Arguments() const;

  Standard_EXPORT void Init(const double theFuzz = Precision::Confusion());

  Standard_EXPORT int NbShapes() const;

  Standard_EXPORT int NbSourceShapes() const;

  Standard_EXPORT int NbRanges() const;

  Standard_EXPORT const BOPDS_IndexRange& Range(const int theIndex) const;

  Standard_EXPORT int Rank(const int theIndex) const;

  Standard_EXPORT bool IsNewShape(const int theIndex) const;

  Standard_EXPORT int Append(const BOPDS_ShapeInfo& theSI);

  Standard_EXPORT int Append(const TopoDS_Shape& theS);

  Standard_EXPORT const BOPDS_ShapeInfo& ShapeInfo(const int theIndex) const;

  Standard_EXPORT BOPDS_ShapeInfo& ChangeShapeInfo(const int theIndex);

  Standard_EXPORT const TopoDS_Shape& Shape(const int theIndex) const;

  Standard_EXPORT int Index(const TopoDS_Shape& theS) const;

  Standard_EXPORT const NCollection_Vector<NCollection_List<occ::handle<BOPDS_PaveBlock>>>&
                        PaveBlocksPool() const;

  Standard_EXPORT NCollection_Vector<NCollection_List<occ::handle<BOPDS_PaveBlock>>>&
                  ChangePaveBlocksPool();

  Standard_EXPORT bool HasPaveBlocks(const int theIndex) const;

  Standard_EXPORT const NCollection_List<occ::handle<BOPDS_PaveBlock>>& PaveBlocks(
    const int theIndex) const;

  Standard_EXPORT NCollection_List<occ::handle<BOPDS_PaveBlock>>& ChangePaveBlocks(
    const int theIndex);

  Standard_EXPORT void UpdatePaveBlocks();

  Standard_EXPORT void UpdatePaveBlock(const occ::handle<BOPDS_PaveBlock>& thePB);

  Standard_EXPORT void UpdateCommonBlock(const occ::handle<BOPDS_CommonBlock>& theCB,
                                         const double                          theFuzz);

  Standard_EXPORT bool IsCommonBlock(const occ::handle<BOPDS_PaveBlock>& thePB) const;

  Standard_EXPORT occ::handle<BOPDS_CommonBlock> CommonBlock(
    const occ::handle<BOPDS_PaveBlock>& thePB) const;

  Standard_EXPORT void SetCommonBlock(const occ::handle<BOPDS_PaveBlock>&   thePB,
                                      const occ::handle<BOPDS_CommonBlock>& theCB);

  Standard_EXPORT occ::handle<BOPDS_PaveBlock> RealPaveBlock(
    const occ::handle<BOPDS_PaveBlock>& thePB) const;

  Standard_EXPORT bool IsCommonBlockOnEdge(const occ::handle<BOPDS_PaveBlock>& thePB) const;

  Standard_EXPORT const NCollection_Vector<BOPDS_FaceInfo>& FaceInfoPool() const;

  Standard_EXPORT bool HasFaceInfo(const int theIndex) const;

  Standard_EXPORT const BOPDS_FaceInfo& FaceInfo(const int theIndex) const;

  Standard_EXPORT BOPDS_FaceInfo& ChangeFaceInfo(const int theIndex);

  Standard_EXPORT void UpdateFaceInfoIn(const int theIndex);

  Standard_EXPORT void UpdateFaceInfoIn(const NCollection_Map<int>& theFaces);

  Standard_EXPORT void UpdateFaceInfoOn(const int theIndex);

  Standard_EXPORT void UpdateFaceInfoOn(const NCollection_Map<int>& theFaces);

  Standard_EXPORT void FaceInfoOn(const int                                             theIndex,
                                  NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& theMPB,
                                  NCollection_Map<int>&                                 theMVP);

  Standard_EXPORT void FaceInfoIn(const int                                             theIndex,
                                  NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& theMPB,
                                  NCollection_Map<int>&                                 theMVP);

  Standard_EXPORT void AloneVertices(const int theF, NCollection_List<int>& theLI) const;

  Standard_EXPORT void RefineFaceInfoOn();

  Standard_EXPORT void RefineFaceInfoIn();

  Standard_EXPORT void SubShapesOnIn(
    const int                                             theNF1,
    const int                                             theNF2,
    NCollection_Map<int>&                                 theMVOnIn,
    NCollection_Map<int>&                                 theMVCommon,
    NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& thePBOnIn,
    NCollection_Map<occ::handle<BOPDS_PaveBlock>>&        theCommonPB) const;

  Standard_EXPORT void SharedEdges(const int                                     theF1,
                                   const int                                     theF2,
                                   NCollection_List<int>&                        theLI,
                                   const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT NCollection_DataMap<int, int>& ShapesSD();

  Standard_EXPORT void AddShapeSD(const int theIndex, const int theIndexSD);

  Standard_EXPORT bool HasShapeSD(const int theIndex, int& theIndexSD) const;

  NCollection_Vector<BOPDS_InterfVV>& InterfVV();

  NCollection_Vector<BOPDS_InterfVE>& InterfVE();

  NCollection_Vector<BOPDS_InterfVF>& InterfVF();

  NCollection_Vector<BOPDS_InterfEE>& InterfEE();

  NCollection_Vector<BOPDS_InterfEF>& InterfEF();

  NCollection_Vector<BOPDS_InterfFF>& InterfFF();

  NCollection_Vector<BOPDS_InterfVZ>& InterfVZ();

  NCollection_Vector<BOPDS_InterfEZ>& InterfEZ();

  NCollection_Vector<BOPDS_InterfFZ>& InterfFZ();

  NCollection_Vector<BOPDS_InterfZZ>& InterfZZ();

  static int NbInterfTypes();

  bool AddInterf(const int theI1, const int theI2);

  bool HasInterf(const int theI) const;

  bool HasInterf(const int theI1, const int theI2) const;

  Standard_EXPORT bool HasInterfShapeSubShapes(const int  theI1,
                                               const int  theI2,
                                               const bool theFlag = true) const;

  Standard_EXPORT bool HasInterfSubShapes(const int theI1, const int theI2) const;

  const NCollection_Map<BOPDS_Pair>& Interferences() const;

  Standard_EXPORT void Dump() const;

  Standard_EXPORT bool IsSubShape(const int theI1, const int theI2);

  Standard_EXPORT void Paves(const int theIndex, NCollection_List<BOPDS_Pave>& theLP);

  Standard_EXPORT void UpdatePaveBlocksWithSDVertices();

  Standard_EXPORT void UpdatePaveBlockWithSDVertices(const occ::handle<BOPDS_PaveBlock>& thePB);

  Standard_EXPORT void UpdateCommonBlockWithSDVertices(const occ::handle<BOPDS_CommonBlock>& theCB);

  Standard_EXPORT void InitPaveBlocksForVertex(const int theNV);

  Standard_EXPORT void ReleasePaveBlocks();

  Standard_EXPORT bool IsValidShrunkData(const occ::handle<BOPDS_PaveBlock>& thePB);

  Standard_EXPORT void BuildBndBoxSolid(const int  theIndex,
                                        Bnd_Box&   theBox,
                                        const bool theCheckInverted = true);

protected:
  Standard_EXPORT void InitPaveBlocks(const int theIndex);

  Standard_EXPORT void InitFaceInfo(const int theIndex);

  Standard_EXPORT void InitFaceInfoIn(const int theIndex);

  Standard_EXPORT void InitShape(const int theIndex, const TopoDS_Shape& theS);

  Standard_EXPORT bool CheckCoincidence(const occ::handle<BOPDS_PaveBlock>& thePB1,
                                        const occ::handle<BOPDS_PaveBlock>& thePB2,
                                        const double                        theFuzz);

  occ::handle<NCollection_BaseAllocator>                             myAllocator;
  NCollection_List<TopoDS_Shape>                                     myArguments;
  int                                                                myNbShapes;
  int                                                                myNbSourceShapes;
  NCollection_Vector<BOPDS_IndexRange>                               myRanges;
  NCollection_Vector<BOPDS_ShapeInfo>                                myLines;
  NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>    myMapShapeIndex;
  NCollection_Vector<NCollection_List<occ::handle<BOPDS_PaveBlock>>> myPaveBlocksPool;
  NCollection_DataMap<occ::handle<BOPDS_PaveBlock>, occ::handle<BOPDS_CommonBlock>> myMapPBCB;
  NCollection_Vector<BOPDS_FaceInfo>                                                myFaceInfoPool;
  NCollection_DataMap<int, int>                                                     myShapesSD;
  NCollection_DataMap<int, NCollection_List<int>>                                   myMapVE;
  NCollection_Map<BOPDS_Pair>                                                       myInterfTB;
  NCollection_Vector<BOPDS_InterfVV>                                                myInterfVV;
  NCollection_Vector<BOPDS_InterfVE>                                                myInterfVE;
  NCollection_Vector<BOPDS_InterfVF>                                                myInterfVF;
  NCollection_Vector<BOPDS_InterfEE>                                                myInterfEE;
  NCollection_Vector<BOPDS_InterfEF>                                                myInterfEF;
  NCollection_Vector<BOPDS_InterfFF>                                                myInterfFF;
  NCollection_Vector<BOPDS_InterfVZ>                                                myInterfVZ;
  NCollection_Vector<BOPDS_InterfEZ>                                                myInterfEZ;
  NCollection_Vector<BOPDS_InterfFZ>                                                myInterfFZ;
  NCollection_Vector<BOPDS_InterfZZ>                                                myInterfZZ;
  NCollection_Map<int>                                                              myInterfered;
};

#include <BOPDS_Pair.hpp>

inline NCollection_Vector<BOPDS_InterfVV>& BOPDS_DS::InterfVV()
{
  return myInterfVV;
}

inline NCollection_Vector<BOPDS_InterfVE>& BOPDS_DS::InterfVE()
{
  return myInterfVE;
}

inline NCollection_Vector<BOPDS_InterfVF>& BOPDS_DS::InterfVF()
{
  return myInterfVF;
}

inline NCollection_Vector<BOPDS_InterfEE>& BOPDS_DS::InterfEE()
{
  return myInterfEE;
}

inline NCollection_Vector<BOPDS_InterfEF>& BOPDS_DS::InterfEF()
{
  return myInterfEF;
}

inline NCollection_Vector<BOPDS_InterfFF>& BOPDS_DS::InterfFF()
{
  return myInterfFF;
}

inline NCollection_Vector<BOPDS_InterfVZ>& BOPDS_DS::InterfVZ()
{
  return myInterfVZ;
}

inline NCollection_Vector<BOPDS_InterfEZ>& BOPDS_DS::InterfEZ()
{
  return myInterfEZ;
}

inline NCollection_Vector<BOPDS_InterfFZ>& BOPDS_DS::InterfFZ()
{
  return myInterfFZ;
}

inline NCollection_Vector<BOPDS_InterfZZ>& BOPDS_DS::InterfZZ()
{
  return myInterfZZ;
}

inline int BOPDS_DS::NbInterfTypes()
{
  return 10;
}

inline bool BOPDS_DS::AddInterf(const int theI1, const int theI2)
{
  if (myInterfTB.Add(BOPDS_Pair(theI1, theI2)))
  {
    myInterfered.Add(theI1);
    myInterfered.Add(theI2);
    return true;
  }
  return false;
}

inline bool BOPDS_DS::HasInterf(const int theI) const
{
  return myInterfered.Contains(theI);
}

inline bool BOPDS_DS::HasInterf(const int theI1, const int theI2) const
{
  BOPDS_Pair aPK(theI1, theI2);
  return myInterfTB.Contains(aPK);
}

inline const NCollection_Map<BOPDS_Pair>& BOPDS_DS::Interferences() const
{
  return myInterfTB;
}
