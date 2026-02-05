#pragma once

//! Class is a container of the flags used
//! by intersection algorithm
class BOPAlgo_SectionAttribute
{
public:
  //! Default constructor
  BOPAlgo_SectionAttribute()
      : myApproximation(true),
        myPCurve1(true),
        myPCurve2(true)
  {
  }

  //! Constructor
  BOPAlgo_SectionAttribute(const bool theAproximation,
                           const bool thePCurveOnS1,
                           const bool thePCurveOnS2)
      : myApproximation(theAproximation),
        myPCurve1(thePCurveOnS1),
        myPCurve2(thePCurveOnS2)
  {
  }

  //! Sets the Approximation flag
  void Approximation(const bool theApprox) { myApproximation = theApprox; }

  //! Sets the PCurveOnS1 flag
  void PCurveOnS1(const bool thePCurveOnS1) { myPCurve1 = thePCurveOnS1; }

  //! Sets the PCurveOnS2 flag
  void PCurveOnS2(const bool thePCurveOnS2) { myPCurve2 = thePCurveOnS2; }

  //! Returns the Approximation flag
  bool Approximation() const { return myApproximation; }

  //! Returns the PCurveOnS1 flag
  bool PCurveOnS1() const { return myPCurve1; }

  //! Returns the PCurveOnS2 flag
  bool PCurveOnS2() const { return myPCurve2; }

private:
  bool myApproximation;
  bool myPCurve1;
  bool myPCurve2;
};
