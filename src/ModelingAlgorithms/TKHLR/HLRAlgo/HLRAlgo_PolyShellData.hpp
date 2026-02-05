#pragma once

#include <Bnd_Box.hpp>
#include <HLRAlgo_BiPoint.hpp>
#include <NCollection_List.hpp>
#include <HLRAlgo_PolyData.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

//! All the PolyData of a Shell
class HLRAlgo_PolyShellData : public Standard_Transient
{

public:
  struct ShellIndices
  {
    int Min, Max;
  };

  Standard_EXPORT HLRAlgo_PolyShellData(const int nbFace);

  Standard_EXPORT void UpdateGlobalMinMax(Bnd_Box& theBox);

  Standard_EXPORT void UpdateHiding(const int nbHiding);

  bool Hiding() const { return !myHPolHi.IsEmpty(); }

  NCollection_Array1<occ::handle<HLRAlgo_PolyData>>& PolyData() { return myPolyg; }

  NCollection_Array1<occ::handle<HLRAlgo_PolyData>>& HidingPolyData() { return myHPolHi; }

  NCollection_List<HLRAlgo_BiPoint>& Edges() { return mySegList; }

  ShellIndices& Indices() { return myIndices; }

  DEFINE_STANDARD_RTTIEXT(HLRAlgo_PolyShellData, Standard_Transient)

private:
  ShellIndices                                      myIndices;
  NCollection_Array1<occ::handle<HLRAlgo_PolyData>> myPolyg;
  NCollection_Array1<occ::handle<HLRAlgo_PolyData>> myHPolHi;
  NCollection_List<HLRAlgo_BiPoint>                 mySegList;
};
