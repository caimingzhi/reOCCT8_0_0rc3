#pragma once

#include <Standard.hpp>

#include <Bnd_Box.hpp>
#include <NCollection_List.hpp>
#include <BOPDS_Pave.hpp>
#include <Standard_Handle.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Map.hpp>
class BOPDS_PaveBlock;

class BOPDS_PaveBlock : public Standard_Transient
{

public:
  Standard_EXPORT BOPDS_PaveBlock();

  Standard_EXPORT BOPDS_PaveBlock(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT void SetPave1(const BOPDS_Pave& thePave);

  Standard_EXPORT const BOPDS_Pave& Pave1() const;

  Standard_EXPORT void SetPave2(const BOPDS_Pave& thePave);

  Standard_EXPORT const BOPDS_Pave& Pave2() const;

  Standard_EXPORT void SetEdge(const int theEdge);

  Standard_EXPORT int Edge() const;

  Standard_EXPORT bool HasEdge() const;

  Standard_EXPORT bool HasEdge(int& theEdge) const;

  Standard_EXPORT void SetOriginalEdge(const int theEdge);

  Standard_EXPORT int OriginalEdge() const;

  Standard_EXPORT bool IsSplitEdge() const;

  Standard_EXPORT void Range(double& theT1, double& theT2) const;

  Standard_EXPORT bool HasSameBounds(const occ::handle<BOPDS_PaveBlock>& theOther) const;

  Standard_EXPORT void Indices(int& theIndex1, int& theIndex2) const;

  Standard_EXPORT bool IsToUpdate() const;

  Standard_EXPORT void AppendExtPave(const BOPDS_Pave& thePave);

  Standard_EXPORT void AppendExtPave1(const BOPDS_Pave& thePave);

  Standard_EXPORT void RemoveExtPave(const int theVertNum);

  Standard_EXPORT const NCollection_List<BOPDS_Pave>& ExtPaves() const;

  Standard_EXPORT NCollection_List<BOPDS_Pave>& ChangeExtPaves();

  Standard_EXPORT void Update(NCollection_List<occ::handle<BOPDS_PaveBlock>>& theLPB,
                              const bool                                      theFlag = true);

  Standard_EXPORT bool ContainsParameter(const double thePrm,
                                         const double theTol,
                                         int&         theInd) const;

  Standard_EXPORT void SetShrunkData(const double   theTS1,
                                     const double   theTS2,
                                     const Bnd_Box& theBox,
                                     const bool     theIsSplittable);

  Standard_EXPORT void ShrunkData(double&  theTS1,
                                  double&  theTS2,
                                  Bnd_Box& theBox,
                                  bool&    theIsSplittable) const;

  Standard_EXPORT bool HasShrunkData() const;

  Standard_EXPORT void Dump() const;

  bool IsSplittable() const { return myIsSplittable; }

  DEFINE_STANDARD_RTTIEXT(BOPDS_PaveBlock, Standard_Transient)

protected:
  occ::handle<NCollection_BaseAllocator> myAllocator;
  int                                    myEdge;
  int                                    myOriginalEdge;
  BOPDS_Pave                             myPave1;
  BOPDS_Pave                             myPave2;
  NCollection_List<BOPDS_Pave>           myExtPaves;
  double                                 myTS1;
  double                                 myTS2;
  Bnd_Box                                myShrunkBox;
  NCollection_Map<int>                   myMFence;
  bool                                   myIsSplittable;
};
