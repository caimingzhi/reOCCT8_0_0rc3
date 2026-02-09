#pragma once

#include <ChFiDS_Spine.hpp>
#include <ChFiDS_ElSpine.hpp>
#include <Law_Function.hpp>
#include <NCollection_List.hpp>
#include <gp_XY.hpp>
#include <NCollection_Sequence.hpp>

class TopoDS_Edge;
class TopoDS_Vertex;
class gp_XY;
class Law_Function;
class Law_Composite;

class ChFiDS_FilSpine : public ChFiDS_Spine
{

public:
  Standard_EXPORT ChFiDS_FilSpine();

  Standard_EXPORT ChFiDS_FilSpine(const double Tol);

  Standard_EXPORT void Reset(const bool AllData = false) override;

  Standard_EXPORT void SetRadius(const double Radius, const TopoDS_Edge& E);

  Standard_EXPORT void UnSetRadius(const TopoDS_Edge& E);

  Standard_EXPORT void SetRadius(const double Radius, const TopoDS_Vertex& V);

  Standard_EXPORT void UnSetRadius(const TopoDS_Vertex& V);

  Standard_EXPORT void SetRadius(const gp_XY& UandR, const int IinC);

  Standard_EXPORT void SetRadius(const double Radius);

  Standard_EXPORT void SetRadius(const occ::handle<Law_Function>& C, const int IinC);

  Standard_EXPORT bool IsConstant() const;

  Standard_EXPORT bool IsConstant(const int IE) const;

  Standard_EXPORT double Radius() const;

  Standard_EXPORT double Radius(const int IE) const;

  Standard_EXPORT double Radius(const TopoDS_Edge& E) const;

  Standard_EXPORT void AppendElSpine(const occ::handle<ChFiDS_ElSpine>& Els) override;

  Standard_EXPORT occ::handle<Law_Composite> Law(const occ::handle<ChFiDS_ElSpine>& Els) const;

  Standard_EXPORT occ::handle<Law_Function>& ChangeLaw(const TopoDS_Edge& E);

  Standard_EXPORT double MaxRadFromSeqAndLaws() const;

  DEFINE_STANDARD_RTTIEXT(ChFiDS_FilSpine, ChFiDS_Spine)

private:
  Standard_EXPORT occ::handle<Law_Composite> ComputeLaw(const occ::handle<ChFiDS_ElSpine>& Els);

  Standard_EXPORT void AppendLaw(const occ::handle<ChFiDS_ElSpine>& Els);

  NCollection_Sequence<gp_XY>                 parandrad;
  NCollection_List<occ::handle<Law_Function>> laws;
};
