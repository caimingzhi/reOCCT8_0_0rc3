#pragma once

#include <IMeshData_Face.hpp>

struct IMeshTools_Parameters;

class BRepMesh_DefaultRangeSplitter
{
public:
  BRepMesh_DefaultRangeSplitter()
      : myIsValid(true)
  {
  }

  virtual ~BRepMesh_DefaultRangeSplitter() = default;

  Standard_EXPORT virtual void Reset(const IMeshData::IFaceHandle& theDFace,
                                     const IMeshTools_Parameters&  theParameters);

  Standard_EXPORT virtual void AddPoint(const gp_Pnt2d& thePoint);

  Standard_EXPORT virtual void AdjustRange();

  Standard_EXPORT virtual bool IsValid();

  Standard_EXPORT gp_Pnt2d Scale(const gp_Pnt2d& thePoint, const bool isToFaceBasis) const;

  Standard_EXPORT virtual Handle(IMeshData::ListOfPnt2d) GenerateSurfaceNodes(
    const IMeshTools_Parameters& theParameters) const;

  gp_Pnt Point(const gp_Pnt2d& thePoint2d) const
  {
    return GetSurface()->Value(thePoint2d.X(), thePoint2d.Y());
  }

protected:
  Standard_EXPORT virtual void computeTolerance(const double theLenU, const double theLenV);

  Standard_EXPORT virtual void computeDelta(const double theLengthU, const double theLengthV);

public:
  const IMeshData::IFaceHandle& GetDFace() const { return myDFace; }

  const occ::handle<BRepAdaptor_Surface>& GetSurface() const { return myDFace->GetSurface(); }

  const std::pair<double, double>& GetRangeU() const { return myRangeU; }

  const std::pair<double, double>& GetRangeV() const { return myRangeV; }

  const std::pair<double, double>& GetDelta() const { return myDelta; }

  const std::pair<double, double>& GetToleranceUV() const { return myTolerance; }

private:
  double computeLengthU();

  double computeLengthV();

  void updateRange(const double theGeomFirst,
                   const double theGeomLast,
                   const bool   isPeriodic,
                   double&      theDiscreteFirst,
                   double&      theDiscreteLast);

protected:
  IMeshData::IFaceHandle    myDFace;
  std::pair<double, double> myRangeU;
  std::pair<double, double> myRangeV;
  std::pair<double, double> myDelta;
  std::pair<double, double> myTolerance;
  bool                      myIsValid;
};
