#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Intrv_Intervals.hpp>

class HLRAlgo_EdgeStatus
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRAlgo_EdgeStatus();

  Standard_EXPORT HLRAlgo_EdgeStatus(const double Start,
                                     const float  TolStart,
                                     const double End,
                                     const float  TolEnd);

  Standard_EXPORT void Initialize(const double Start,
                                  const float  TolStart,
                                  const double End,
                                  const float  TolEnd);

  void Bounds(double& theStart, float& theTolStart, double& theEnd, float& theTolEnd) const
  {
    theStart    = myStart;
    theTolStart = myTolStart;
    theEnd      = myEnd;
    theTolEnd   = myTolEnd;
  }

  Standard_EXPORT int NbVisiblePart() const;

  Standard_EXPORT void VisiblePart(const int Index,
                                   double&   Start,
                                   float&    TolStart,
                                   double&   End,
                                   float&    TolEnd) const;

  Standard_EXPORT void Hide(const double Start,
                            const float  TolStart,
                            const double End,
                            const float  TolEnd,
                            const bool   OnFace,
                            const bool   OnBoundary);

  void HideAll()
  {
    AllVisible(false);
    AllHidden(true);
  }

  void ShowAll()
  {
    AllVisible(true);
    AllHidden(false);
  }

  bool AllHidden() const { return myAllHidden; }

  void AllHidden(const bool B) { myAllHidden = B; }

  bool AllVisible() const { return myAllVisible; }

  void AllVisible(const bool B) { myAllVisible = B; }

private:
  double          myStart;
  double          myEnd;
  float           myTolStart;
  float           myTolEnd;
  bool            myAllHidden;
  bool            myAllVisible;
  Intrv_Intervals myVisibles;
};
