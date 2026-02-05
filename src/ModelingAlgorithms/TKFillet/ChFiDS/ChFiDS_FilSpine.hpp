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

//! Provides data specific to the fillets -
//! vector or rule of evolution (C2).
class ChFiDS_FilSpine : public ChFiDS_Spine
{

public:
  Standard_EXPORT ChFiDS_FilSpine();

  Standard_EXPORT ChFiDS_FilSpine(const double Tol);

  Standard_EXPORT void Reset(const bool AllData = false) override;

  //! initializes the constant vector on edge E.
  Standard_EXPORT void SetRadius(const double Radius, const TopoDS_Edge& E);

  //! resets the constant vector on edge E.
  Standard_EXPORT void UnSetRadius(const TopoDS_Edge& E);

  //! initializes the vector on Vertex V.
  Standard_EXPORT void SetRadius(const double Radius, const TopoDS_Vertex& V);

  //! resets the vector on Vertex V.
  Standard_EXPORT void UnSetRadius(const TopoDS_Vertex& V);

  //! initializes the vector on the point of parameter W.
  Standard_EXPORT void SetRadius(const gp_XY& UandR, const int IinC);

  //! initializes the constant vector on all spine.
  Standard_EXPORT void SetRadius(const double Radius);

  //! initializes the rule of evolution on all spine.
  Standard_EXPORT void SetRadius(const occ::handle<Law_Function>& C, const int IinC);

  //! returns true if the radius is constant
  //! all along the spine.
  Standard_EXPORT bool IsConstant() const;

  //! returns true if the radius is constant
  //! all along the edge E.
  Standard_EXPORT bool IsConstant(const int IE) const;

  //! returns the radius if the fillet is constant
  //! all along the spine.
  Standard_EXPORT double Radius() const;

  //! returns the radius if the fillet is constant
  //! all along the edge E.
  Standard_EXPORT double Radius(const int IE) const;

  //! returns the radius if the fillet is constant
  //! all along the edge E.
  Standard_EXPORT double Radius(const TopoDS_Edge& E) const;

  Standard_EXPORT void AppendElSpine(const occ::handle<ChFiDS_ElSpine>& Els) override;

  Standard_EXPORT occ::handle<Law_Composite> Law(const occ::handle<ChFiDS_ElSpine>& Els) const;

  //! returns the elementary law
  Standard_EXPORT occ::handle<Law_Function>& ChangeLaw(const TopoDS_Edge& E);

  //! returns the maximum radius if the fillet is non-constant
  Standard_EXPORT double MaxRadFromSeqAndLaws() const;

  DEFINE_STANDARD_RTTIEXT(ChFiDS_FilSpine, ChFiDS_Spine)

private:
  Standard_EXPORT occ::handle<Law_Composite> ComputeLaw(const occ::handle<ChFiDS_ElSpine>& Els);

  Standard_EXPORT void AppendLaw(const occ::handle<ChFiDS_ElSpine>& Els);

  NCollection_Sequence<gp_XY>                 parandrad;
  NCollection_List<occ::handle<Law_Function>> laws;
};
