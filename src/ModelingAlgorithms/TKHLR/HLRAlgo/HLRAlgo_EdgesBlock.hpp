#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Transient.hpp>
#include <TopAbs_Orientation.hpp>

class HLRAlgo_EdgesBlock : public Standard_Transient
{

public:
  struct MinMaxIndices
  {
    int Min[8], Max[8];

    MinMaxIndices& Minimize(const MinMaxIndices& theMinMaxIndices)
    {
      for (int aI = 0; aI < 8; ++aI)
      {
        if (Min[aI] > theMinMaxIndices.Min[aI])
        {
          Min[aI] = theMinMaxIndices.Min[aI];
        }
        if (Max[aI] > theMinMaxIndices.Max[aI])
        {
          Max[aI] = theMinMaxIndices.Max[aI];
        }
      }
      return *this;
    }

    MinMaxIndices& Maximize(const MinMaxIndices& theMinMaxIndices)
    {
      for (int aI = 0; aI < 8; ++aI)
      {
        if (Min[aI] < theMinMaxIndices.Min[aI])
        {
          Min[aI] = theMinMaxIndices.Min[aI];
        }
        if (Max[aI] < theMinMaxIndices.Max[aI])
        {
          Max[aI] = theMinMaxIndices.Max[aI];
        }
      }
      return *this;
    }
  };

  Standard_EXPORT HLRAlgo_EdgesBlock(const int NbEdges);

  int NbEdges() const { return myEdges.Upper(); }

  void Edge(const int I, const int EI) { myEdges(I) = EI; }

  int Edge(const int I) const { return myEdges(I); }

  void Orientation(const int I, const TopAbs_Orientation Or)
  {
    myFlags(I) &= ~EMaskOrient;
    myFlags(I) |= ((int)Or & (int)EMaskOrient);
  }

  TopAbs_Orientation Orientation(const int I) const
  {
    return ((TopAbs_Orientation)(myFlags(I) & EMaskOrient));
  }

  bool OutLine(const int I) const { return (myFlags(I) & EMaskOutLine) != 0; }

  void OutLine(const int I, const bool B)
  {
    if (B)
      myFlags(I) |= EMaskOutLine;
    else
      myFlags(I) &= ~EMaskOutLine;
  }

  bool Internal(const int I) const { return (myFlags(I) & EMaskInternal) != 0; }

  void Internal(const int I, const bool B)
  {
    if (B)
      myFlags(I) |= EMaskInternal;
    else
      myFlags(I) &= ~EMaskInternal;
  }

  bool Double(const int I) const { return (myFlags(I) & EMaskDouble) != 0; }

  void Double(const int I, const bool B)
  {
    if (B)
      myFlags(I) |= EMaskDouble;
    else
      myFlags(I) &= ~EMaskDouble;
  }

  bool IsoLine(const int I) const { return (myFlags(I) & EMaskIsoLine) != 0; }

  void IsoLine(const int I, const bool B)
  {
    if (B)
      myFlags(I) |= EMaskIsoLine;
    else
      myFlags(I) &= ~EMaskIsoLine;
  }

  void UpdateMinMax(const MinMaxIndices& TotMinMax) { myMinMax = TotMinMax; }

  MinMaxIndices& MinMax() { return myMinMax; }

  DEFINE_STANDARD_RTTIEXT(HLRAlgo_EdgesBlock, Standard_Transient)

protected:
  enum EMskFlags
  {
    EMaskOrient   = 15,
    EMaskOutLine  = 16,
    EMaskInternal = 32,
    EMaskDouble   = 64,
    EMaskIsoLine  = 128
  };

private:
  NCollection_Array1<int> myEdges;
  NCollection_Array1<int> myFlags;
  MinMaxIndices           myMinMax;
};
