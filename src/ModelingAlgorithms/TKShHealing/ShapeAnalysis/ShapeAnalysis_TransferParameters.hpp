#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

class ShapeAnalysis_TransferParameters : public Standard_Transient
{

public:
  Standard_EXPORT ShapeAnalysis_TransferParameters();

  Standard_EXPORT ShapeAnalysis_TransferParameters(const TopoDS_Edge& E, const TopoDS_Face& F);

  Standard_EXPORT virtual void Init(const TopoDS_Edge& E, const TopoDS_Face& F);

  Standard_EXPORT void SetMaxTolerance(const double maxtol);

  Standard_EXPORT virtual occ::handle<NCollection_HSequence<double>> Perform(
    const occ::handle<NCollection_HSequence<double>>& Params,
    const bool                                        To2d);

  Standard_EXPORT virtual double Perform(const double Param, const bool To2d);

  Standard_EXPORT virtual void TransferRange(TopoDS_Edge& newEdge,
                                             const double prevPar,
                                             const double currPar,
                                             const bool   To2d);

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
