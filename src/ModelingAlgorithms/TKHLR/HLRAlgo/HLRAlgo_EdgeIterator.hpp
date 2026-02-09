#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class HLRAlgo_EdgeStatus;

class HLRAlgo_EdgeIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRAlgo_EdgeIterator();

  Standard_EXPORT void InitHidden(HLRAlgo_EdgeStatus& status);

  bool MoreHidden() const;

  Standard_EXPORT void NextHidden();

  void Hidden(double& Start, float& TolStart, double& End, float& TolEnd) const;

  void InitVisible(HLRAlgo_EdgeStatus& status);

  bool MoreVisible() const;

  void NextVisible();

  void Visible(double& Start, float& TolStart, double& End, float& TolEnd);

private:
  int                 myNbVis;
  int                 myNbHid;
  HLRAlgo_EdgeStatus* EVis;
  HLRAlgo_EdgeStatus* EHid;
  int                 iVis;
  int                 iHid;
  double              myHidStart;
  double              myHidEnd;
  float               myHidTolStart;
  float               myHidTolEnd;
};

#include <HLRAlgo_EdgeStatus.hpp>

inline bool HLRAlgo_EdgeIterator::MoreHidden() const
{
  return iHid <= myNbHid + 1;
}

inline void HLRAlgo_EdgeIterator::Hidden(double& Start,
                                         float&  TolStart,
                                         double& End,
                                         float&  TolEnd) const
{
  Start    = myHidStart;
  TolStart = myHidTolStart;
  End      = myHidEnd;
  TolEnd   = myHidTolEnd;
}

inline void HLRAlgo_EdgeIterator::InitVisible(HLRAlgo_EdgeStatus& status)
{
  EVis    = &status;
  iVis    = 1;
  myNbVis = ((HLRAlgo_EdgeStatus*)EVis)->NbVisiblePart();
}

inline bool HLRAlgo_EdgeIterator::MoreVisible() const
{
  return iVis <= myNbVis;
}

inline void HLRAlgo_EdgeIterator::NextVisible()
{
  iVis++;
}

inline void HLRAlgo_EdgeIterator::Visible(double& Start,
                                          float&  TolStart,
                                          double& End,
                                          float&  TolEnd)
{
  ((HLRAlgo_EdgeStatus*)EVis)->VisiblePart(iVis, Start, TolStart, End, TolEnd);
}
