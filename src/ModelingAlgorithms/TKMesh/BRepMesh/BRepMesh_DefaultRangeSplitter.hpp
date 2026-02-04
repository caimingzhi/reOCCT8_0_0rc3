#pragma once


#include <IMeshData_Face.hpp>

struct IMeshTools_Parameters;

//! Default tool to define range of discrete face model and
//! obtain grid points distributed within this range.
class BRepMesh_DefaultRangeSplitter
{
public:
  //! Constructor.
  BRepMesh_DefaultRangeSplitter()
      : myIsValid(true)
  {
  }

  //! Destructor.
  virtual ~BRepMesh_DefaultRangeSplitter() = default;

  //! Resets this splitter. Must be called before first use.
  Standard_EXPORT virtual void Reset(const IMeshData::IFaceHandle& theDFace,
                                     const IMeshTools_Parameters&  theParameters);

  //! Registers border point.
  Standard_EXPORT virtual void AddPoint(const gp_Pnt2d& thePoint);

  //! Updates discrete range of surface according to its geometric range.
  Standard_EXPORT virtual void AdjustRange();

  //! Returns True if computed range is valid.
  Standard_EXPORT virtual bool IsValid();

  //! Scales the given point from real parametric space
  //! to face basis and otherwise.
  //! @param thePoint point to be scaled.
  //! @param isToFaceBasis if TRUE converts point to face basis,
  //! otherwise performs reverse conversion.
  //! @return scaled point.
  Standard_EXPORT gp_Pnt2d Scale(const gp_Pnt2d& thePoint, const bool isToFaceBasis) const;

  //! Returns list of nodes generated using surface data and specified parameters.
  //! By default returns null ptr.
  Standard_EXPORT virtual Handle(IMeshData::ListOfPnt2d) GenerateSurfaceNodes(
    const IMeshTools_Parameters& theParameters) const;

  //! Returns point in 3d space corresponded to the given
  //! point defined in parametric space of surface.
  gp_Pnt Point(const gp_Pnt2d& thePoint2d) const
  {
    return GetSurface()->Value(thePoint2d.X(), thePoint2d.Y());
  }

protected:
  //! Computes parametric tolerance taking length along U and V into account.
  Standard_EXPORT virtual void computeTolerance(const double theLenU, const double theLenV);

  //! Computes parametric delta taking length along U and V and value of tolerance into account.
  Standard_EXPORT virtual void computeDelta(const double theLengthU, const double theLengthV);

public:
  //! Returns face model.
  const IMeshData::IFaceHandle& GetDFace() const { return myDFace; }

  //! Returns surface.
  const occ::handle<BRepAdaptor_Surface>& GetSurface() const { return myDFace->GetSurface(); }

  //! Returns U range.
  const std::pair<double, double>& GetRangeU() const { return myRangeU; }

  //! Returns V range.
  const std::pair<double, double>& GetRangeV() const { return myRangeV; }

  //! Returns delta.
  const std::pair<double, double>& GetDelta() const { return myDelta; }

  const std::pair<double, double>& GetToleranceUV() const { return myTolerance; }

private:
  //! Computes length along U direction using grid evaluation.
  //! @return computed length along U direction
  double computeLengthU();

  //! Computes length along V direction using grid evaluation.
  //! @return computed length along V direction
  double computeLengthV();

  //! Updates discrete range of surface according to its geometric range.
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

