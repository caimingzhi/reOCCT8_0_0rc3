#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Intrv_Intervals.hpp>

//! This class describes the Hidden Line status of an
//! Edge. It contains:
//!
//! The Bounds of the Edge and their tolerances
//!
//! Two flags indicating if the edge is full visible
//! or full hidden
//! TheSequenceof visible Intervals on the Edge.
class HLRAlgo_EdgeStatus
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRAlgo_EdgeStatus();

  //! Creates a new EdgeStatus. Default visible. The
  //! Edge is bounded by the interval <Start>, <End>
  //! with the tolerances <TolStart>, <TolEnd>.
  Standard_EXPORT HLRAlgo_EdgeStatus(const double Start,
                                     const float  TolStart,
                                     const double End,
                                     const float  TolEnd);

  //! Initialize an EdgeStatus. Default visible. The
  //! Edge is bounded by the interval <Start>, <End>
  //! with the tolerances <TolStart>, <TolEnd>.
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

  //! Hides the interval <Start>, <End> with the
  //! tolerances <TolStart>, <TolEnd>. This interval is
  //! subtracted from the visible parts. If the hidden
  //! part is on (or under) the face the flag <OnFace>
  //! is True (or False). If the hidden part is on
  //! (or inside) the boundary of the face the flag
  //! <OnBoundary> is True (or False).
  Standard_EXPORT void Hide(const double Start,
                            const float  TolStart,
                            const double End,
                            const float  TolEnd,
                            const bool   OnFace,
                            const bool   OnBoundary);

  //! Hide the whole Edge.
  void HideAll()
  {
    AllVisible(false);
    AllHidden(true);
  }

  //! Show the whole Edge.
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

