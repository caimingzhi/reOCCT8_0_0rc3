#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopAbs_Orientation.hpp>
#include <Standard_ShortReal.hpp>
#include <TopAbs_State.hpp>

class HLRAlgo_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRAlgo_Intersection();

  Standard_EXPORT HLRAlgo_Intersection(const TopAbs_Orientation Ori,
                                       const int                Lev,
                                       const int                SegInd,
                                       const int                Ind,
                                       const double             P,
                                       const float              Tol,
                                       const TopAbs_State       S);

  void Orientation(const TopAbs_Orientation Ori);

  TopAbs_Orientation Orientation() const;

  void Level(const int Lev);

  int Level() const;

  void SegIndex(const int SegInd);

  int SegIndex() const;

  void Index(const int Ind);

  int Index() const;

  void Parameter(const double P);

  double Parameter() const;

  void Tolerance(const float T);

  float Tolerance() const;

  void State(const TopAbs_State S);

  TopAbs_State State() const;

private:
  TopAbs_Orientation myOrien;
  int                mySegIndex;
  int                myIndex;
  int                myLevel;
  double             myParam;
  float              myToler;
  TopAbs_State       myState;
};

inline void HLRAlgo_Intersection::Orientation(const TopAbs_Orientation Ori)
{
  myOrien = Ori;
}

inline TopAbs_Orientation HLRAlgo_Intersection::Orientation() const
{
  return myOrien;
}

inline void HLRAlgo_Intersection::Level(const int Lev)
{
  myLevel = Lev;
}

inline int HLRAlgo_Intersection::Level() const
{
  return myLevel;
}

inline void HLRAlgo_Intersection::SegIndex(const int SegInd)
{
  mySegIndex = SegInd;
}

inline int HLRAlgo_Intersection::SegIndex() const
{
  return mySegIndex;
}

inline void HLRAlgo_Intersection::Index(const int Ind)
{
  myIndex = Ind;
}

inline int HLRAlgo_Intersection::Index() const
{
  return myIndex;
}

inline void HLRAlgo_Intersection::Parameter(const double P)
{
  myParam = P;
}

inline double HLRAlgo_Intersection::Parameter() const
{
  return myParam;
}

inline void HLRAlgo_Intersection::Tolerance(const float T)
{
  myToler = T;
}

inline float HLRAlgo_Intersection::Tolerance() const
{
  return myToler;
}

inline void HLRAlgo_Intersection::State(const TopAbs_State St)
{
  myState = St;
}

inline TopAbs_State HLRAlgo_Intersection::State() const
{
  return myState;
}
