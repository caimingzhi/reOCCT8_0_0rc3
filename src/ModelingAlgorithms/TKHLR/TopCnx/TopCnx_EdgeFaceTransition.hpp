#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopTrans_CurveTransition.hpp>
#include <TopAbs_Orientation.hpp>
class gp_Dir;

//! TheEdgeFaceTransition is an algorithm to compute
//! the cumulated transition for interferences on an
//! edge.
class TopCnx_EdgeFaceTransition
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an empty algorithm.
  Standard_EXPORT TopCnx_EdgeFaceTransition();

  //! Initialize the algorithm with the local
  //! description of the edge.
  Standard_EXPORT void Reset(const gp_Dir& Tgt, const gp_Dir& Norm, const double Curv);

  //! Initialize the algorithm with a linear Edge.
  Standard_EXPORT void Reset(const gp_Dir& Tgt);

  //! Add a curve element to the boundary. Or is the
  //! orientation of the interference on the boundary
  //! curve. Tr is the transition of the interference.
  //! BTr is the boundary transition of the
  //! interference.
  Standard_EXPORT void AddInterference(const double             Tole,
                                       const gp_Dir&            Tang,
                                       const gp_Dir&            Norm,
                                       const double             Curv,
                                       const TopAbs_Orientation Or,
                                       const TopAbs_Orientation Tr,
                                       const TopAbs_Orientation BTr);

  //! Returns the current cumulated transition.
  Standard_EXPORT TopAbs_Orientation Transition() const;

  //! Returns the current cumulated BoundaryTransition.
  Standard_EXPORT TopAbs_Orientation BoundaryTransition() const;

private:
  TopTrans_CurveTransition myCurveTransition;
  int                      nbBoundForward;
  int                      nbBoundReversed;
};
