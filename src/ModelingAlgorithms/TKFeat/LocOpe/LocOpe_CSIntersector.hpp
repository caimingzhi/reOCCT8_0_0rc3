#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <gp_Lin.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Circ.hpp>
#include <Geom_Curve.hpp>
#include <TopAbs_Orientation.hpp>
class LocOpe_PntFace;

class LocOpe_CSIntersector
{
public:
  DEFINE_STANDARD_ALLOC

  LocOpe_CSIntersector();

  LocOpe_CSIntersector(const TopoDS_Shape& S);

  Standard_EXPORT void Init(const TopoDS_Shape& S);

  Standard_EXPORT void Perform(const NCollection_Sequence<gp_Lin>& Slin);

  Standard_EXPORT void Perform(const NCollection_Sequence<gp_Circ>& Scir);

  Standard_EXPORT void Perform(const NCollection_Sequence<occ::handle<Geom_Curve>>& Scur);

  bool IsDone() const;

  Standard_EXPORT int NbPoints(const int I) const;

  Standard_EXPORT const LocOpe_PntFace& Point(const int I, const int Index) const;

  Standard_EXPORT bool LocalizeAfter(const int           I,
                                     const double        From,
                                     const double        Tol,
                                     TopAbs_Orientation& Or,
                                     int&                IndFrom,
                                     int&                IndTo) const;

  Standard_EXPORT bool LocalizeBefore(const int           I,
                                      const double        From,
                                      const double        Tol,
                                      TopAbs_Orientation& Or,
                                      int&                IndFrom,
                                      int&                IndTo) const;

  Standard_EXPORT bool LocalizeAfter(const int           I,
                                     const int           FromInd,
                                     const double        Tol,
                                     TopAbs_Orientation& Or,
                                     int&                IndFrom,
                                     int&                IndTo) const;

  Standard_EXPORT bool LocalizeBefore(const int           I,
                                      const int           FromInd,
                                      const double        Tol,
                                      TopAbs_Orientation& Or,
                                      int&                IndFrom,
                                      int&                IndTo) const;

  Standard_EXPORT void Destroy();

  ~LocOpe_CSIntersector() { Destroy(); }

private:
  bool         myDone;
  TopoDS_Shape myShape;
  void*        myPoints;
  int          myNbelem;
};

#include <StdFail_NotDone.hpp>

inline LocOpe_CSIntersector::LocOpe_CSIntersector()
    : myDone(false),
      myPoints(nullptr),
      myNbelem(0)
{
}

inline LocOpe_CSIntersector::LocOpe_CSIntersector(const TopoDS_Shape& S)
    : myDone(false),
      myShape(S),
      myPoints(nullptr),
      myNbelem(0)
{
}

inline bool LocOpe_CSIntersector::IsDone() const
{
  return myDone;
}
