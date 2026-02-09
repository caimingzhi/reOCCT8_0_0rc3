#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_XY.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <gp_XYZ.hpp>
class gp_XYZ;
class gp_XY;

#ifdef Status
  #undef Status
#endif

class ShapeAnalysis_WireOrder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeAnalysis_WireOrder();

  Standard_EXPORT ShapeAnalysis_WireOrder(const bool   theMode3D,
                                          const double theTolerance,
                                          const bool   theModeBoth = false);

  Standard_EXPORT void SetMode(const bool   theMode3D,
                               const double theTolerance,
                               const bool   theModeBoth = false);

  Standard_EXPORT double Tolerance() const;

  Standard_EXPORT void Clear();

  Standard_EXPORT void Add(const gp_XYZ& theStart3d, const gp_XYZ& theEnd3d);

  Standard_EXPORT void Add(const gp_XY& theStart2d, const gp_XY& theEnd2d);

  Standard_EXPORT void Add(const gp_XYZ& theStart3d,
                           const gp_XYZ& theEnd3d,
                           const gp_XY&  theStart2d,
                           const gp_XY&  theEnd2d);

  Standard_EXPORT int NbEdges() const;

  Standard_EXPORT bool& KeepLoopsMode();

  Standard_EXPORT void Perform(const bool closed = true);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int Status() const;

  Standard_EXPORT int Ordered(const int theIdx) const;

  Standard_EXPORT void XYZ(const int theIdx, gp_XYZ& theStart3D, gp_XYZ& theEnd3D) const;

  Standard_EXPORT void XY(const int theIdx, gp_XY& theStart2D, gp_XY& theEnd2D) const;

  Standard_EXPORT double Gap(const int num = 0) const;

  Standard_EXPORT void SetChains(const double gap);

  Standard_EXPORT int NbChains() const;

  Standard_EXPORT void Chain(const int num, int& n1, int& n2) const;

  Standard_EXPORT void SetCouples(const double gap);

  Standard_EXPORT int NbCouples() const;

  Standard_EXPORT void Couple(const int num, int& n1, int& n2) const;

private:
  enum ModeType
  {
    Mode2D,
    Mode3D,
    ModeBoth
  };

  occ::handle<NCollection_HArray1<int>>      myOrd;
  occ::handle<NCollection_HArray1<int>>      myChains;
  occ::handle<NCollection_HArray1<int>>      myCouples;
  occ::handle<NCollection_HSequence<gp_XYZ>> myXYZ;
  occ::handle<NCollection_HSequence<gp_XY>>  myXY;
  double                                     myTol;
  double                                     myGap;
  int                                        myStat;
  bool                                       myKeepLoops;
  ModeType                                   myMode;
};
