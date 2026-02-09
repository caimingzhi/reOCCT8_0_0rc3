#pragma once

#include <PrsDim_Relation.hpp>

class Geom_Plane;
class gp_Lin;
class gp_Circ;
class gp_Elips;

class PrsDim_MidPointRelation : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_MidPointRelation, PrsDim_Relation)
public:
  Standard_EXPORT PrsDim_MidPointRelation(const TopoDS_Shape&            aSymmTool,
                                          const TopoDS_Shape&            FirstShape,
                                          const TopoDS_Shape&            SecondShape,
                                          const occ::handle<Geom_Plane>& aPlane);

  bool IsMovable() const override { return true; }

  void SetTool(const TopoDS_Shape& aMidPointTool) { myTool = aMidPointTool; }

  const TopoDS_Shape& GetTool() const { return myTool; }

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  Standard_EXPORT void ComputeFaceFromPnt(const occ::handle<Prs3d_Presentation>& aprs,
                                          const bool                             first);

  Standard_EXPORT void ComputeEdgeFromPnt(const occ::handle<Prs3d_Presentation>& aprs,
                                          const bool                             first);

  Standard_EXPORT void ComputeVertexFromPnt(const occ::handle<Prs3d_Presentation>& aprs,
                                            const bool                             first);

  Standard_EXPORT void ComputePointsOnLine(const gp_Lin& aLin, const bool first);

  Standard_EXPORT void ComputePointsOnLine(const gp_Pnt& pnt1,
                                           const gp_Pnt& pnt2,
                                           const bool    first);

  Standard_EXPORT void ComputePointsOnCirc(const gp_Circ& aCirc,
                                           const gp_Pnt&  pnt1,
                                           const gp_Pnt&  pnt2,
                                           const bool     first);

  Standard_EXPORT void ComputePointsOnElips(const gp_Elips& anEll,
                                            const gp_Pnt&   pnt1,
                                            const gp_Pnt&   pnt2,
                                            const bool      first);

private:
  TopoDS_Shape myTool;
  gp_Pnt       myMidPoint;
  gp_Pnt       myFAttach;
  gp_Pnt       myFirstPnt1;
  gp_Pnt       myFirstPnt2;
  gp_Pnt       mySAttach;
  gp_Pnt       mySecondPnt1;
  gp_Pnt       mySecondPnt2;
};
