#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <BRepAlgoAPI_BooleanOperation.hpp>
class BOPAlgo_PaveFiller;
class TopoDS_Shape;
class gp_Pln;
class Geom_Surface;

class BRepAlgoAPI_Section : public BRepAlgoAPI_BooleanOperation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepAlgoAPI_Section();
  Standard_EXPORT ~BRepAlgoAPI_Section() override;

  Standard_EXPORT BRepAlgoAPI_Section(const BOPAlgo_PaveFiller& PF);

  Standard_EXPORT BRepAlgoAPI_Section(const TopoDS_Shape& S1,
                                      const TopoDS_Shape& S2,
                                      const bool          PerformNow = true);

  Standard_EXPORT BRepAlgoAPI_Section(const TopoDS_Shape&       S1,
                                      const TopoDS_Shape&       S2,
                                      const BOPAlgo_PaveFiller& aDSF,
                                      const bool                PerformNow = true);

  Standard_EXPORT BRepAlgoAPI_Section(const TopoDS_Shape& S1,
                                      const gp_Pln&       Pl,
                                      const bool          PerformNow = true);

  Standard_EXPORT BRepAlgoAPI_Section(const TopoDS_Shape&              S1,
                                      const occ::handle<Geom_Surface>& Sf,
                                      const bool                       PerformNow = true);

  Standard_EXPORT BRepAlgoAPI_Section(const occ::handle<Geom_Surface>& Sf,
                                      const TopoDS_Shape&              S2,
                                      const bool                       PerformNow = true);

  Standard_EXPORT BRepAlgoAPI_Section(const occ::handle<Geom_Surface>& Sf1,
                                      const occ::handle<Geom_Surface>& Sf2,
                                      const bool                       PerformNow = true);

  Standard_EXPORT void Init1(const TopoDS_Shape& S1);

  Standard_EXPORT void Init1(const gp_Pln& Pl);

  Standard_EXPORT void Init1(const occ::handle<Geom_Surface>& Sf);

  Standard_EXPORT void Init2(const TopoDS_Shape& S2);

  Standard_EXPORT void Init2(const gp_Pln& Pl);

  Standard_EXPORT void Init2(const occ::handle<Geom_Surface>& Sf);

  Standard_EXPORT void Approximation(const bool B);

  Standard_EXPORT void ComputePCurveOn1(const bool B);

  Standard_EXPORT void ComputePCurveOn2(const bool B);

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT bool HasAncestorFaceOn1(const TopoDS_Shape& E, TopoDS_Shape& F) const;

  Standard_EXPORT bool HasAncestorFaceOn2(const TopoDS_Shape& E, TopoDS_Shape& F) const;

protected:
  Standard_EXPORT void Init(const bool PerformNow);

  Standard_EXPORT void SetAttributes() override;

private:
  bool myApprox;
  bool myComputePCurve1;
  bool myComputePCurve2;
};
