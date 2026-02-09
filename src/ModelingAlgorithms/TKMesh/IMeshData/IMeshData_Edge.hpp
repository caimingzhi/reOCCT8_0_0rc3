#pragma once

#include <TopoDS_Edge.hpp>
#include <IMeshData_Curve.hpp>
#include <IMeshData_PCurve.hpp>
#include <IMeshData_Types.hpp>
#include <BRep_Tool.hpp>

class IMeshData_Edge : public IMeshData_TessellatedShape, public IMeshData_StatusOwner
{
public:
  ~IMeshData_Edge() override = default;

  const TopoDS_Edge& GetEdge() const { return TopoDS::Edge(GetShape()); }

  Standard_EXPORT virtual int PCurvesNb() const = 0;

  Standard_EXPORT virtual const IMeshData::IPCurveHandle& AddPCurve(
    const IMeshData::IFacePtr& theDFace,
    const TopAbs_Orientation   theOrientation) = 0;

  Standard_EXPORT virtual const IMeshData::IPCurveHandle& GetPCurve(
    const IMeshData::IFacePtr& theDFace,
    const TopAbs_Orientation   theOrientation) const = 0;

  Standard_EXPORT virtual const IMeshData::IPCurveHandle& GetPCurve(const int theIndex) const = 0;

  Standard_EXPORT virtual const IMeshData::ListOfInteger& GetPCurves(
    const IMeshData::IFacePtr& theDFace) const = 0;

  void Clear(const bool isKeepEndPoints)
  {
    myCurve->Clear(isKeepEndPoints);
    for (int aPCurveIt = 0; aPCurveIt < PCurvesNb(); ++aPCurveIt)
    {
      GetPCurve(aPCurveIt)->Clear(isKeepEndPoints);
    }
  }

  bool IsFree() const { return (PCurvesNb() == 0); }

  void SetCurve(const IMeshData::ICurveHandle& theCurve) { myCurve = theCurve; }

  const IMeshData::ICurveHandle& GetCurve() const { return myCurve; }

  double GetAngularDeflection() const { return myAngDeflection; }

  void SetAngularDeflection(const double theValue) { myAngDeflection = theValue; }

  bool GetSameParam() const { return mySameParam; }

  void SetSameParam(const bool theValue) { mySameParam = theValue; }

  bool GetSameRange() const { return mySameRange; }

  void SetSameRange(const bool theValue) { mySameRange = theValue; }

  bool GetDegenerated() const { return myDegenerated; }

  void SetDegenerated(const bool theValue) { myDegenerated = theValue; }

  DEFINE_STANDARD_RTTIEXT(IMeshData_Edge, IMeshData_TessellatedShape)

protected:
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
