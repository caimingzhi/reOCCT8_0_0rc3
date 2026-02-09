#pragma once

#include <HLRAlgo_WiresBlock.hpp>

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <HLRAlgo_EdgeStatus.hpp>
#include <HLRBRep_Curve.hpp>
class TopoDS_Edge;

#ifdef Status
  #undef Status
#endif

class HLRBRep_EdgeData
{
public:
  DEFINE_STANDARD_ALLOC

  HLRBRep_EdgeData()
      : myFlags(0),
        myHideCount(0)
  {
    Selected(true);
  }

  Standard_EXPORT void Set(const bool         Reg1,
                           const bool         RegN,
                           const TopoDS_Edge& EG,
                           const int          V1,
                           const int          V2,
                           const bool         Out1,
                           const bool         Out2,
                           const bool         Cut1,
                           const bool         Cut2,
                           const double       Start,
                           const float        TolStart,
                           const double       End,
                           const float        TolEnd);

  bool Selected() const;

  void Selected(const bool B);

  bool Rg1Line() const;

  void Rg1Line(const bool B);

  bool RgNLine() const;

  void RgNLine(const bool B);

  bool Vertical() const;

  void Vertical(const bool B);

  bool Simple() const;

  void Simple(const bool B);

  bool OutLVSta() const;

  void OutLVSta(const bool B);

  bool OutLVEnd() const;

  void OutLVEnd(const bool B);

  bool CutAtSta() const;

  void CutAtSta(const bool B);

  bool CutAtEnd() const;

  void CutAtEnd(const bool B);

  bool VerAtSta() const;

  void VerAtSta(const bool B);

  bool VerAtEnd() const;

  void VerAtEnd(const bool B);

  bool AutoIntersectionDone() const;

  void AutoIntersectionDone(const bool B);

  bool Used() const;

  void Used(const bool B);

  int HideCount() const;

  void HideCount(const int I);

  int VSta() const;

  void VSta(const int I);

  int VEnd() const;

  void VEnd(const int I);

  void UpdateMinMax(const HLRAlgo_EdgesBlock::MinMaxIndices& theTotMinMax)
  {
    myMinMax = theTotMinMax;
  }

  HLRAlgo_EdgesBlock::MinMaxIndices& MinMax() { return myMinMax; }

  HLRAlgo_EdgeStatus& Status();

  HLRBRep_Curve& ChangeGeometry();

  const HLRBRep_Curve& Geometry() const;

  HLRBRep_Curve* Curve() { return &myGeometry; }

  float Tolerance() const;

protected:
  enum EMaskFlags
  {
    EMaskSelected = 1,
    EMaskUsed     = 2,
    EMaskRg1Line  = 4,
    EMaskVertical = 8,
    EMaskSimple   = 16,
    EMaskOutLVSta = 32,
    EMaskOutLVEnd = 64,
    EMaskIntDone  = 128,
    EMaskCutAtSta = 256,
    EMaskCutAtEnd = 512,
    EMaskVerAtSta = 1024,
    EMaskVerAtEnd = 2048,
    EMaskRgNLine  = 4096
  };

private:
  int                               myFlags;
  int                               myHideCount;
  int                               myVSta;
  int                               myVEnd;
  HLRAlgo_EdgesBlock::MinMaxIndices myMinMax;
  HLRAlgo_EdgeStatus                myStatus;
  HLRBRep_Curve                     myGeometry;
  float                             myTolerance;
};

inline bool HLRBRep_EdgeData::Selected() const
{
  return (myFlags & EMaskSelected) != 0;
}

inline void HLRBRep_EdgeData::Selected(const bool B)
{
  if (B)
    myFlags |= EMaskSelected;
  else
    myFlags &= ~EMaskSelected;
}

inline bool HLRBRep_EdgeData::Rg1Line() const
{
  return (myFlags & EMaskRg1Line) != 0;
}

inline void HLRBRep_EdgeData::Rg1Line(const bool B)
{
  if (B)
    myFlags |= EMaskRg1Line;
  else
    myFlags &= ~EMaskRg1Line;
}

inline bool HLRBRep_EdgeData::RgNLine() const
{
  return (myFlags & EMaskRgNLine) != 0;
}

inline void HLRBRep_EdgeData::RgNLine(const bool B)
{
  if (B)
    myFlags |= EMaskRgNLine;
  else
    myFlags &= ~EMaskRgNLine;
}

inline bool HLRBRep_EdgeData::Vertical() const
{
  return (myFlags & EMaskVertical) != 0;
}

inline void HLRBRep_EdgeData::Vertical(const bool B)
{
  if (B)
    myFlags |= EMaskVertical;
  else
    myFlags &= ~EMaskVertical;
}

inline bool HLRBRep_EdgeData::Simple() const
{
  return (myFlags & EMaskSimple) != 0;
}

inline void HLRBRep_EdgeData::Simple(const bool B)
{
  if (B)
    myFlags |= EMaskSimple;
  else
    myFlags &= ~EMaskSimple;
}

inline bool HLRBRep_EdgeData::OutLVSta() const
{
  return (myFlags & EMaskOutLVSta) != 0;
}

inline void HLRBRep_EdgeData::OutLVSta(const bool B)
{
  if (B)
    myFlags |= EMaskOutLVSta;
  else
    myFlags &= ~EMaskOutLVSta;
}

inline bool HLRBRep_EdgeData::OutLVEnd() const
{
  return (myFlags & EMaskOutLVEnd) != 0;
}

inline void HLRBRep_EdgeData::OutLVEnd(const bool B)
{
  if (B)
    myFlags |= EMaskOutLVEnd;
  else
    myFlags &= ~EMaskOutLVEnd;
}

inline bool HLRBRep_EdgeData::CutAtSta() const
{
  return (myFlags & EMaskCutAtSta) != 0;
}

inline void HLRBRep_EdgeData::CutAtSta(const bool B)
{
  if (B)
    myFlags |= EMaskCutAtSta;
  else
    myFlags &= ~EMaskCutAtSta;
}

inline bool HLRBRep_EdgeData::CutAtEnd() const
{
  return (myFlags & EMaskCutAtEnd) != 0;
}

inline void HLRBRep_EdgeData::CutAtEnd(const bool B)
{
  if (B)
    myFlags |= EMaskCutAtEnd;
  else
    myFlags &= ~EMaskCutAtEnd;
}

inline bool HLRBRep_EdgeData::VerAtSta() const
{
  return (myFlags & EMaskVerAtSta) != 0;
}

inline void HLRBRep_EdgeData::VerAtSta(const bool B)
{
  if (B)
    myFlags |= EMaskVerAtSta;
  else
    myFlags &= ~EMaskVerAtSta;
}

inline bool HLRBRep_EdgeData::VerAtEnd() const
{
  return (myFlags & EMaskVerAtEnd) != 0;
}

inline void HLRBRep_EdgeData::VerAtEnd(const bool B)
{
  if (B)
    myFlags |= EMaskVerAtEnd;
  else
    myFlags &= ~EMaskVerAtEnd;
}

inline bool HLRBRep_EdgeData::AutoIntersectionDone() const
{
  return (myFlags & EMaskIntDone) != 0;
}

inline void HLRBRep_EdgeData::AutoIntersectionDone(const bool B)
{
  if (B)
    myFlags |= EMaskIntDone;
  else
    myFlags &= ~EMaskIntDone;
}

inline bool HLRBRep_EdgeData::Used() const
{
  return (myFlags & EMaskUsed) != 0;
}

inline void HLRBRep_EdgeData::Used(const bool B)
{
  if (B)
    myFlags |= EMaskUsed;
  else
    myFlags &= ~EMaskUsed;
}

inline int HLRBRep_EdgeData::HideCount() const
{
  return myHideCount;
}

inline void HLRBRep_EdgeData::HideCount(const int I)
{
  myHideCount = I;
}

inline int HLRBRep_EdgeData::VSta() const
{
  return myVSta;
}

inline void HLRBRep_EdgeData::VSta(const int I)
{
  myVSta = I;
}

inline int HLRBRep_EdgeData::VEnd() const
{
  return myVEnd;
}

inline void HLRBRep_EdgeData::VEnd(const int I)
{
  myVEnd = I;
}

inline HLRAlgo_EdgeStatus& HLRBRep_EdgeData::Status()
{
  return myStatus;
}

inline HLRBRep_Curve& HLRBRep_EdgeData::ChangeGeometry()
{
  return myGeometry;
}

inline const HLRBRep_Curve& HLRBRep_EdgeData::Geometry() const
{
  return myGeometry;
}

inline float HLRBRep_EdgeData::Tolerance() const
{
  return myTolerance;
}
