#pragma once


#include <Adaptor3d_TopolTool.hpp>
#include <Adaptor3d_Surface.hpp>

class gp_Pnt2d;
class gp_Pnt;

//! Class redefine methods of TopolTool from Adaptor3d
//! concerning sample points
class IntTools_TopolTool : public Adaptor3d_TopolTool
{

public:
  //! Empty constructor
  Standard_EXPORT IntTools_TopolTool();

  //! Initializes me by surface
  Standard_EXPORT IntTools_TopolTool(const occ::handle<Adaptor3d_Surface>& theSurface);

  //! Redefined empty initializer
  //!
  //! Warning:
  //! Raises the exception NotImplemented
  Standard_EXPORT void Initialize() override;

  //! Initializes me by surface
  Standard_EXPORT void Initialize(const occ::handle<Adaptor3d_Surface>& theSurface) override;

  Standard_EXPORT void ComputeSamplePoints() override;

  //! Computes the sample-points for the intersections algorithms
  Standard_EXPORT int NbSamplesU() override;

  //! Computes the sample-points for the intersections algorithms
  Standard_EXPORT int NbSamplesV() override;

  //! Computes the sample-points for the intersections algorithms
  Standard_EXPORT int NbSamples() override;

  //! Returns a 2d point from surface myS
  //! and a corresponded 3d point
  //! for given index.
  //! The index should be from 1 to NbSamples()
  Standard_EXPORT void SamplePoint(const int Index, gp_Pnt2d& P2d, gp_Pnt& P3d) override;

  //! compute the sample-points for the intersections algorithms
  //! by adaptive algorithm for BSpline surfaces. For other surfaces algorithm
  //! is the same as in method ComputeSamplePoints(), but only fill arrays of U
  //! and V sample parameters;
  //! theDefl is a required deflection
  //! theNUmin, theNVmin are minimal nb points for U and V.
  Standard_EXPORT void SamplePnts(const double theDefl,
                                  const int    theNUmin,
                                  const int    theNVmin) override;

  DEFINE_STANDARD_RTTIEXT(IntTools_TopolTool, Adaptor3d_TopolTool)

private:
  int    myNbSmplU;
  int    myNbSmplV;
  double myU0;
  double myV0;
  double myDU;
  double myDV;
};

