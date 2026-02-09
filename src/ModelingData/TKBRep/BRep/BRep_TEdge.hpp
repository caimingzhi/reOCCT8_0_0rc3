#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <BRep_CurveRepresentation.hpp>
#include <NCollection_List.hpp>
#include <TopoDS_TEdge.hpp>
class TopoDS_TShape;

class BRep_TEdge : public TopoDS_TEdge
{

public:
  Standard_EXPORT BRep_TEdge();

  double Tolerance() const;

  void Tolerance(const double T);

  void UpdateTolerance(const double T);

  Standard_EXPORT bool SameParameter() const;

  Standard_EXPORT void SameParameter(const bool S);

  Standard_EXPORT bool SameRange() const;

  Standard_EXPORT void SameRange(const bool S);

  Standard_EXPORT bool Degenerated() const;

  Standard_EXPORT void Degenerated(const bool S);

  const NCollection_List<occ::handle<BRep_CurveRepresentation>>& Curves() const;

  NCollection_List<occ::handle<BRep_CurveRepresentation>>& ChangeCurves();

  Standard_EXPORT occ::handle<TopoDS_TShape> EmptyCopy() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(BRep_TEdge, TopoDS_TEdge)

private:
  double                                                  myTolerance;
  int                                                     myFlags;
  NCollection_List<occ::handle<BRep_CurveRepresentation>> myCurves;
};

inline double BRep_TEdge::Tolerance() const
{
  return myTolerance;
}

inline void BRep_TEdge::Tolerance(const double T)
{
  myTolerance = T;
}

inline void BRep_TEdge::UpdateTolerance(const double T)
{
  if (T > myTolerance)
    myTolerance = T;
}

inline const NCollection_List<occ::handle<BRep_CurveRepresentation>>& BRep_TEdge::Curves() const
{
  return myCurves;
}

inline NCollection_List<occ::handle<BRep_CurveRepresentation>>& BRep_TEdge::ChangeCurves()
{
  return myCurves;
}
