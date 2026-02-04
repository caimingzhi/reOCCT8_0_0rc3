#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

//! This tool is used for transferring parameters
//! from 3d curve of the edge to pcurve and vice versa.
//!
//! Default behaviour is to trsnafer parameters with help
//! of linear transformation:
//!
//! T2d = myShift + myScale * T3d
//! where
//! myScale = ( Last2d - First2d ) / ( Last3d - First3d )
//! myShift = First2d - First3d * myScale
//! [First3d, Last3d] and [First2d, Last2d] are ranges of
//! edge on curve and pcurve
//!
//! This behaviour can be redefined in derived classes, for example,
//! using projection.
class ShapeAnalysis_TransferParameters : public Standard_Transient
{

public:
  //! Creates empty tool with myShift = 0 and myScale = 1
  Standard_EXPORT ShapeAnalysis_TransferParameters();

  //! Creates a tool and initializes it with edge and face
  Standard_EXPORT ShapeAnalysis_TransferParameters(const TopoDS_Edge& E, const TopoDS_Face& F);

  //! Initialize a tool with edge and face
  Standard_EXPORT virtual void Init(const TopoDS_Edge& E, const TopoDS_Face& F);

  //! Sets maximal tolerance to use linear recomputation of
  //! parameters.
  Standard_EXPORT void SetMaxTolerance(const double maxtol);

  //! Transfers parameters given by sequence Params from 3d curve
  //! to pcurve (if To2d is True) or back (if To2d is False)
  Standard_EXPORT virtual occ::handle<NCollection_HSequence<double>> Perform(
    const occ::handle<NCollection_HSequence<double>>& Params,
    const bool                                        To2d);

  //! Transfers parameter given by sequence Params from 3d curve
  //! to pcurve (if To2d is True) or back (if To2d is False)
  Standard_EXPORT virtual double Perform(const double Param, const bool To2d);

  //! Recomputes range of curves from NewEdge.
  //! If Is2d equals True parameters are recomputed by curve2d else by curve3d.
  Standard_EXPORT virtual void TransferRange(TopoDS_Edge& newEdge,
                                             const double prevPar,
                                             const double currPar,
                                             const bool   To2d);

  //! Returns True if 3d curve of edge and pcurve are SameRange
  //! (in default implementation, if myScale == 1 and myShift == 0)
  Standard_EXPORT virtual bool IsSameRange() const;

  DEFINE_STANDARD_RTTIEXT(ShapeAnalysis_TransferParameters, Standard_Transient)

protected:
  double      myFirst;
  double      myLast;
  TopoDS_Edge myEdge;
  double      myMaxTolerance;

private:
  double      myShift;
  double      myScale;
  double      myFirst2d;
  double      myLast2d;
  TopoDS_Face myFace;
};

