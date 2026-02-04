#pragma once


#include <TopoDS_Edge.hpp>
#include <IMeshData_Curve.hpp>
#include <IMeshData_PCurve.hpp>
#include <IMeshData_Types.hpp>
#include <BRep_Tool.hpp>

//! Interface class representing discrete model of an edge.
class IMeshData_Edge : public IMeshData_TessellatedShape, public IMeshData_StatusOwner
{
public:
  //! Destructor.
  ~IMeshData_Edge() override = default;

  //! Returns TopoDS_Edge attached to model.
  const TopoDS_Edge& GetEdge() const { return TopoDS::Edge(GetShape()); }

  //! Returns number of pcurves assigned to current edge.
  Standard_EXPORT virtual int PCurvesNb() const = 0;

  //! Adds discrete pcurve for the specified discrete face.
  Standard_EXPORT virtual const IMeshData::IPCurveHandle& AddPCurve(
    const IMeshData::IFacePtr& theDFace,
    const TopAbs_Orientation   theOrientation) = 0;

  //! Returns pcurve for the specified discrete face.
  Standard_EXPORT virtual const IMeshData::IPCurveHandle& GetPCurve(
    const IMeshData::IFacePtr& theDFace,
    const TopAbs_Orientation   theOrientation) const = 0;

  //! Returns pcurve with the given index.
  Standard_EXPORT virtual const IMeshData::IPCurveHandle& GetPCurve(const int theIndex) const = 0;

  //! Returns an array of pcurves indices for the specified discrete face.
  Standard_EXPORT virtual const IMeshData::ListOfInteger& GetPCurves(
    const IMeshData::IFacePtr& theDFace) const = 0;

  //! Clears curve and all pcurves assigned to the edge from discretization.
  void Clear(const bool isKeepEndPoints)
  {
    myCurve->Clear(isKeepEndPoints);
    for (int aPCurveIt = 0; aPCurveIt < PCurvesNb(); ++aPCurveIt)
    {
      GetPCurve(aPCurveIt)->Clear(isKeepEndPoints);
    }
  }

  //! Returns true in case if the edge is free one, i.e. it does not have pcurves.
  bool IsFree() const { return (PCurvesNb() == 0); }

  //! Sets 3d curve associated with current edge.
  void SetCurve(const IMeshData::ICurveHandle& theCurve) { myCurve = theCurve; }

  //! Returns 3d curve associated with current edge.
  const IMeshData::ICurveHandle& GetCurve() const { return myCurve; }

  //! Gets value of angular deflection for the discrete model.
  double GetAngularDeflection() const { return myAngDeflection; }

  //! Sets value of angular deflection for the discrete model.
  void SetAngularDeflection(const double theValue) { myAngDeflection = theValue; }

  //! Returns same param flag.
  //! By default equals to flag stored in topological shape.
  bool GetSameParam() const { return mySameParam; }

  //! Updates same param flag.
  void SetSameParam(const bool theValue) { mySameParam = theValue; }

  //! Returns same range flag.
  //! By default equals to flag stored in topological shape.
  bool GetSameRange() const { return mySameRange; }

  //! Updates same range flag.
  void SetSameRange(const bool theValue) { mySameRange = theValue; }

  //! Returns degenerative flag.
  //! By default equals to flag stored in topological shape.
  bool GetDegenerated() const { return myDegenerated; }

  //! Updates degenerative flag.
  void SetDegenerated(const bool theValue) { myDegenerated = theValue; }

  DEFINE_STANDARD_RTTIEXT(IMeshData_Edge, IMeshData_TessellatedShape)

protected:
  //! Constructor.
  //! Initializes empty model.
  IMeshData_Edge(const TopoDS_Edge& theEdge)
      : IMeshData_TessellatedShape(theEdge),
        mySameParam(BRep_Tool::SameParameter(theEdge)),
        mySameRange(BRep_Tool::SameRange(theEdge)),
        myDegenerated(BRep_Tool::Degenerated(theEdge)),
        myAngDeflection(RealLast())
  {
  }

private:
  bool                    mySameParam;
  bool                    mySameRange;
  bool                    myDegenerated;
  double                  myAngDeflection;
  IMeshData::ICurveHandle myCurve;
};

