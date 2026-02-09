#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <LocOpe_PntFace.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_Orientation.hpp>
class gp_Ax1;
class TopoDS_Shape;
class gp_Circ;
class LocOpe_PntFace;

class LocOpe_CurveShapeIntersector
{
public:
  DEFINE_STANDARD_ALLOC

  LocOpe_CurveShapeIntersector();

  LocOpe_CurveShapeIntersector(const gp_Ax1& Axis, const TopoDS_Shape& S);

  LocOpe_CurveShapeIntersector(const gp_Circ& C, const TopoDS_Shape& S);

  Standard_EXPORT void Init(const gp_Ax1& Axis, const TopoDS_Shape& S);

  Standard_EXPORT void Init(const gp_Circ& C, const TopoDS_Shape& S);

  bool IsDone() const;

  int NbPoints() const;

  const LocOpe_PntFace& Point(const int Index) const;

  Standard_EXPORT bool LocalizeAfter(const double        From,
                                     TopAbs_Orientation& Or,
                                     int&                IndFrom,
                                     int&                IndTo) const;

  Standard_EXPORT bool LocalizeBefore(const double        From,
                                      TopAbs_Orientation& Or,
                                      int&                IndFrom,
                                      int&                IndTo) const;

  Standard_EXPORT bool LocalizeAfter(const int           FromInd,
                                     TopAbs_Orientation& Or,
                                     int&                IndFrom,
                                     int&                IndTo) const;

  Standard_EXPORT bool LocalizeBefore(const int           FromInd,
                                      TopAbs_Orientation& Or,
                                      int&                IndFrom,
                                      int&                IndTo) const;

private:
  bool                                 myDone;
  NCollection_Sequence<LocOpe_PntFace> myPoints;
};

#include <StdFail_NotDone.hpp>

inline LocOpe_CurveShapeIntersector::LocOpe_CurveShapeIntersector()
    : myDone(false)
{
}

inline LocOpe_CurveShapeIntersector::LocOpe_CurveShapeIntersector(const gp_Ax1&       Axis,
                                                                  const TopoDS_Shape& S)
{
  Init(Axis, S);
}

inline LocOpe_CurveShapeIntersector::LocOpe_CurveShapeIntersector(const gp_Circ&      C,
                                                                  const TopoDS_Shape& S)
{
  Init(C, S);
}

inline bool LocOpe_CurveShapeIntersector::IsDone() const
{
  return myDone;
}

inline int LocOpe_CurveShapeIntersector::NbPoints() const
{
  if (!myDone)
  {
    throw StdFail_NotDone();
  }
  return myPoints.Length();
}

inline const LocOpe_PntFace& LocOpe_CurveShapeIntersector::Point(const int I) const
{
  if (!myDone)
  {
    throw StdFail_NotDone();
  }
  return myPoints(I);
}
