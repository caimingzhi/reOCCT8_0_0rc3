#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Bnd_Box.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Vector.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>

#include <array>

class gp_Pln;
class Bnd_VoxelGrid;

class Bnd_BoundSortBox
{
public:
  DEFINE_STANDARD_ALLOC

private:
  using VectorInt = NCollection_Vector<int>;

public:
  Standard_EXPORT Bnd_BoundSortBox();

  Standard_EXPORT void Initialize(const occ::handle<NCollection_HArray1<Bnd_Box>>& theSetOfBoxes);

  Standard_EXPORT void Initialize(const Bnd_Box&                                   theEnclosingBox,
                                  const occ::handle<NCollection_HArray1<Bnd_Box>>& theSetOfBoxes);

  Standard_EXPORT void Initialize(const Bnd_Box& theEnclosingBox, const int theNbBoxes);

  Standard_EXPORT void Add(const Bnd_Box& theBox, const int theIndex);

  Standard_EXPORT const NCollection_List<int>& Compare(const Bnd_Box& theBox);

  Standard_EXPORT const NCollection_List<int>& Compare(const gp_Pln& thePlane);

private:
  void calculateCoefficients();

  void resetVoxelGrid();

  void sortBoxes();

  std::array<int, 6> getBoundingVoxels(const Bnd_Box& theBox) const;

  void addBox(const Bnd_Box& theBox, const int theIndex);

  Bnd_Box                                   myEnclosingBox;
  occ::handle<NCollection_HArray1<Bnd_Box>> myBoxes;
  double                                    myCoeffX;
  double                                    myCoeffY;
  double                                    myCoeffZ;
  int                                       myResolution;
  NCollection_List<int>                     myLastResult;
  VectorInt                                 myLargeBoxes;
  occ::handle<Bnd_VoxelGrid>                myVoxelGrid;
};
