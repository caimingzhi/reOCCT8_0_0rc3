#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_ShortReal.hpp>

enum Intrv_Position
{
  Intrv_Before,
  Intrv_JustBefore,
  Intrv_OverlappingAtStart,
  Intrv_JustEnclosingAtEnd,
  Intrv_Enclosing,
  Intrv_JustOverlappingAtStart,
  Intrv_Similar,
  Intrv_JustEnclosingAtStart,
  Intrv_Inside,
  Intrv_JustOverlappingAtEnd,
  Intrv_OverlappingAtEnd,
  Intrv_JustAfter,
  Intrv_After
};

//! **-----------****             Other
//! ***---*                                   IsBefore
//! ***----------*                            IsJustBefore
//! ***---------------*                       IsOverlappingAtStart
//! ***------------------------*              IsJustEnclosingAtEnd
//! ***-----------------------------------*   IsEnclosing
//! ***----*                       IsJustOverlappingAtStart
//! ***-------------*              IsSimilar
//! ***------------------------*   IsJustEnclosingAtStart
//! ***-*                   IsInside
//! ***------*              IsJustOverlappingAtEnd
//! ***-----------------*   IsOverlappingAtEnd
//! ***--------*   IsJustAfter
//! ***---*   IsAfter
class Intrv_Interval
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Intrv_Interval();

  Standard_EXPORT Intrv_Interval(const double Start, const double End);

  Standard_EXPORT Intrv_Interval(const double Start,
                                 const float  TolStart,
                                 const double End,
                                 const float  TolEnd);

  double Start() const;

  double End() const;

  float TolStart() const;

  float TolEnd() const;

  void Bounds(double& Start, float& TolStart, double& End, float& TolEnd) const;

  void SetStart(const double Start, const float TolStart);

  //! ****+****-------------------->      Old one
  //! ****+****------------------------>      New one to fuse
  //! <<<     <<<
  //! ****+****------------------------>      result
  void FuseAtStart(const double Start, const float TolStart);

  //! ****+****----------->      Old one
  //! <----------**+**                        Tool for cutting
  //! >>>     >>>
  //! ****+****----------->      result
  void CutAtStart(const double Start, const float TolStart);

  void SetEnd(const double End, const float TolEnd);

  //! <---------------------****+****      Old one
  //! <-----------------**+**              New one to fuse
  //! >>>     >>>
  //! <---------------------****+****      result
  void FuseAtEnd(const double End, const float TolEnd);

  //! <-----****+****                      Old one
  //! **+**------>             Tool for cutting
  //! <<<     <<<
  //! <-----****+****                      result
  void CutAtEnd(const double End, const float TolEnd);

  //! True if myStart+myTolStart > myEnd-myTolEnd
  //! or if myEnd+myTolEnd > myStart-myTolStart
  bool IsProbablyEmpty() const;

  //! True if me is Before Other
  //! **-----------****             Other
  //! ***-----*                                   Before
  //! ***------------*                            JustBefore
  //! ***-----------------*                       OverlappingAtStart
  //! ***--------------------------*              JustEnclosingAtEnd
  //! ***-------------------------------------*   Enclosing
  //! ***----*                       JustOverlappingAtStart
  //! ***-------------*              Similar
  //! ***------------------------*   JustEnclosingAtStart
  //! ***-*                   Inside
  //! ***------*              JustOverlappingAtEnd
  //! ***-----------------*   OverlappingAtEnd
  //! ***--------*   JustAfter
  //! ***---*   After
  Standard_EXPORT Intrv_Position Position(const Intrv_Interval& Other) const;

  //! True if me is Before Other
  //! ***----------------**                              me
  //! **-----------****          Other
  bool IsBefore(const Intrv_Interval& Other) const;

  //! True if me is After Other
  //! **-----------****          me
  //! ***----------------**                              Other
  bool IsAfter(const Intrv_Interval& Other) const;

  //! True if me is Inside Other
  //! **-----------****                          me
  //! ***--------------------------**                    Other
  bool IsInside(const Intrv_Interval& Other) const;

  //! True if me is Enclosing Other
  //! ***----------------------------****                  me
  //! ***------------------**                        Other
  bool IsEnclosing(const Intrv_Interval& Other) const;

  //! True if me is just Enclosing Other at start
  //! ***---------------------------****            me
  //! ***------------------**                        Other
  bool IsJustEnclosingAtStart(const Intrv_Interval& Other) const;

  //! True if me is just Enclosing Other at End
  //! ***----------------------------****                  me
  //! ***-----------------****                   Other
  bool IsJustEnclosingAtEnd(const Intrv_Interval& Other) const;

  //! True if me is just before Other
  //! ***--------****                                      me
  //! ***-----------**                        Other
  bool IsJustBefore(const Intrv_Interval& Other) const;

  //! True if me is just after Other
  //! ****-------****                         me
  //! ***-----------**                                     Other
  bool IsJustAfter(const Intrv_Interval& Other) const;

  //! True if me is overlapping Other at start
  //! ***---------------***                                me
  //! ***-----------**                        Other
  bool IsOverlappingAtStart(const Intrv_Interval& Other) const;

  //! True if me is overlapping Other at end
  //! ***-----------**                        me
  //! ***---------------***                                Other
  bool IsOverlappingAtEnd(const Intrv_Interval& Other) const;

  //! True if me is just overlapping Other at start
  //! ***-----------***                                    me
  //! ***------------------------**                        Other
  bool IsJustOverlappingAtStart(const Intrv_Interval& Other) const;

  //! True if me is just overlapping Other at end
  //! ***-----------*                         me
  //! ***------------------------**                        Other
  bool IsJustOverlappingAtEnd(const Intrv_Interval& Other) const;

  //! True if me and Other have the same bounds
  //! *----------------***                                me
  //! ***-----------------**                               Other
  bool IsSimilar(const Intrv_Interval& Other) const;

private:
  double myStart;
  double myEnd;
  float  myTolStart;
  float  myTolEnd;
};

inline double Intrv_Interval::Start() const
{
  return myStart;
}

//=================================================================================================

inline double Intrv_Interval::End() const
{
  return myEnd;
}

//=================================================================================================

inline float Intrv_Interval::TolStart() const
{
  return myTolStart;
}

//=================================================================================================

inline float Intrv_Interval::TolEnd() const
{
  return myTolEnd;
}

//=================================================================================================

inline void Intrv_Interval::Bounds(double& Start, float& TolStart, double& End, float& TolEnd) const
{
  Start    = myStart;
  TolStart = myTolStart;
  End      = myEnd;
  TolEnd   = myTolEnd;
}

//=================================================================================================

inline void Intrv_Interval::SetStart(const double Start, const float TolStart)
{
  myStart    = Start;
  myTolStart = TolStart;
}

//=======================================================================
// function : FuseAtStart
//
//                 ****+****-------------------->      Old one
//             ****+****------------------------>      New one to fuse
//             <<<     <<<
//             ****+****------------------------>      result
//
//=======================================================================

inline void Intrv_Interval::FuseAtStart(const double Start, const float TolStart)
{
  if (myStart != RealFirst())
  {
    double a   = std::min(myStart - myTolStart, Start - TolStart);
    double b   = std::min(myStart + myTolStart, Start + TolStart);
    myStart    = (a + b) / 2;
    myTolStart = (float)(b - a) / 2;
  }
}

//=======================================================================
// function : CutAtStart
//
//                          ****+****----------->      Old one
//             <----------**+**                        Tool for cutting
//                        >>>     >>>
//                          ****+****----------->      result
//
//=======================================================================

inline void Intrv_Interval::CutAtStart(const double Start, const float TolStart)
{
  if (myStart != RealFirst())
  {
    double a   = std::max(myStart - myTolStart, Start - TolStart);
    double b   = std::max(myStart + myTolStart, Start + TolStart);
    myStart    = (a + b) / 2;
    myTolStart = (float)(b - a) / 2;
  }
}

//=================================================================================================

inline void Intrv_Interval::SetEnd(const double End, const float TolEnd)
{
  myEnd    = End;
  myTolEnd = TolEnd;
}

//=======================================================================
// function : FuseAtEnd
//
//             <---------------------****+****      Old one
//             <-----------------**+**              New one to fuse
//                                 >>>     >>>
//             <---------------------****+****      result
//
//=======================================================================

inline void Intrv_Interval::FuseAtEnd(const double End, const float TolEnd)
{
  if (myEnd != RealLast())
  {
    double a = std::max(myEnd - myTolEnd, End - TolEnd);
    double b = std::max(myEnd + myTolEnd, End + TolEnd);
    myEnd    = (a + b) / 2;
    myTolEnd = (float)(b - a) / 2;
  }
}

//=======================================================================
// function : CutAtEnd
//
//             <-----****+****                      Old one
//                         **+**------>             Tool for cutting
//                   <<<     <<<
//             <-----****+****                      result
//
//=======================================================================

inline void Intrv_Interval::CutAtEnd(const double End, const float TolEnd)
{
  if (myEnd != RealLast())
  {
    double a = std::min(myEnd - myTolEnd, End - TolEnd);
    double b = std::min(myEnd + myTolEnd, End + TolEnd);
    myEnd    = (a + b) / 2;
    myTolEnd = (float)(b - a) / 2;
  }
}

//=================================================================================================

inline bool AreFused(const double c1, const float t1, const double c2, const float t2)
{
  return t1 + t2 >= std::abs(c1 - c2);
}

//=================================================================================================

inline bool Intrv_Interval::IsProbablyEmpty() const
{
  return AreFused(myStart, myTolStart, myEnd, myTolEnd);
}

//=======================================================================
//                   **-----------****             Other
//     ***-----*                                   IsBefore
//=======================================================================

inline bool Intrv_Interval::IsBefore(const Intrv_Interval& Other) const
{
  return myTolEnd + Other.myTolStart < Other.myStart - myEnd;
}

//=======================================================================
//                   **-----------****             Other
//                                       ***---*   IsAfter
//=======================================================================

inline bool Intrv_Interval::IsAfter(const Intrv_Interval& Other) const
{
  return myTolStart + Other.myTolEnd < myStart - Other.myEnd;
}

//=======================================================================
//                   **-----------****             Other
//                         ***-*                   IsInside
//=======================================================================

inline bool Intrv_Interval::IsInside(const Intrv_Interval& Other) const
{
  return myTolStart + Other.myTolStart < myStart - Other.myStart
         && myTolEnd + Other.myTolEnd < Other.myEnd - myEnd;
}

//=======================================================================
//                   **-----------****             Other
//     ***-------------------------------------*   IsEnclosing
//=======================================================================

inline bool Intrv_Interval::IsEnclosing(const Intrv_Interval& Other) const
{
  return myTolStart + Other.myTolStart < Other.myStart - myStart
         && myTolEnd + Other.myTolEnd < myEnd - Other.myEnd;
}

//=======================================================================
//                   **-----------****             Other
//                  ***------------------------*   IsJustEnclosingAtStart
//=======================================================================

inline bool Intrv_Interval::IsJustEnclosingAtStart(const Intrv_Interval& Other) const
{
  return AreFused(myStart, myTolStart, Other.myStart, Other.myTolStart)
         && myTolEnd + Other.myTolEnd < myEnd - Other.myEnd;
}

//=======================================================================
//                   **-----------****             Other
//     ***--------------------------*              IsJustEnclosingAtEnd
//=======================================================================

inline bool Intrv_Interval::IsJustEnclosingAtEnd(const Intrv_Interval& Other) const
{
  return myTolStart + Other.myTolStart < Other.myStart - myStart
         && AreFused(Other.myEnd, Other.myTolEnd, myEnd, myTolEnd);
}

//=======================================================================
//                   **-----------****             Other
//     ***------------*                            IsJustBefore
//=======================================================================

inline bool Intrv_Interval::IsJustBefore(const Intrv_Interval& Other) const
{
  return AreFused(myEnd, myTolEnd, Other.myStart, Other.myTolStart);
}

//=======================================================================
//                   **-----------****             Other
//                                  ***--------*   IsJustAfter
//=======================================================================

inline bool Intrv_Interval::IsJustAfter(const Intrv_Interval& Other) const
{
  return AreFused(Other.myEnd, Other.myTolEnd, myStart, myTolStart);
}

//=======================================================================
//                   **-----------****             Other
//     ***-----------------*                       IsOverlappingAtStart
//=======================================================================

inline bool Intrv_Interval::IsOverlappingAtStart(const Intrv_Interval& Other) const
{
  return myTolStart + Other.myTolStart < Other.myStart - myStart
         && myTolEnd + Other.myTolStart < myEnd - Other.myStart
         && myTolEnd + Other.myTolEnd < Other.myEnd - myEnd;
}

//=======================================================================
//                   **-----------****             Other
//                         ***-----------------*   IsOverlappingAtEnd
//=======================================================================

inline bool Intrv_Interval::IsOverlappingAtEnd(const Intrv_Interval& Other) const
{
  return myTolStart + Other.myTolStart < myStart - Other.myStart
         && myTolStart + Other.myTolEnd < Other.myEnd - myStart
         && myTolEnd + Other.myTolEnd < myEnd - Other.myEnd;
}

//=======================================================================
//                   **-----------****             Other
//                  ***----*                       IsJustOverlappingAtStart
//=======================================================================

inline bool Intrv_Interval::IsJustOverlappingAtStart(const Intrv_Interval& Other) const
{
  return AreFused(myStart, myTolStart, Other.myStart, Other.myTolStart)
         && myTolEnd + Other.myTolEnd < Other.myEnd - myEnd;
}

//=======================================================================
//                   **-----------****             Other
//                         ***------*              IsJustOverlappingAtEnd
//=======================================================================

inline bool Intrv_Interval::IsJustOverlappingAtEnd(const Intrv_Interval& Other) const
{
  return myTolStart + Other.myTolStart < myStart - Other.myStart
         && AreFused(Other.myEnd, Other.myTolEnd, myEnd, myTolEnd);
}

//=======================================================================
//                   **-----------****             Other
//                  ***-------------*              IsSimilar
//=======================================================================

inline bool Intrv_Interval::IsSimilar(const Intrv_Interval& Other) const
{
  bool b1, b2;
  b1 = AreFused(myStart, myTolStart, Other.myStart, Other.myTolStart);
  b2 = AreFused(myEnd, myTolEnd, Other.myEnd, Other.myTolEnd);
  return b1 && b2;
}
