#pragma once

class BOPAlgo_SectionAttribute
{
public:
  BOPAlgo_SectionAttribute()
      : myApproximation(true),
        myPCurve1(true),
        myPCurve2(true)
  {
  }

  BOPAlgo_SectionAttribute(const bool theAproximation,
                           const bool thePCurveOnS1,
                           const bool thePCurveOnS2)
      : myApproximation(theAproximation),
        myPCurve1(thePCurveOnS1),
        myPCurve2(thePCurveOnS2)
  {
  }

  void Approximation(const bool theApprox) { myApproximation = theApprox; }

  void PCurveOnS1(const bool thePCurveOnS1) { myPCurve1 = thePCurveOnS1; }

  void PCurveOnS2(const bool thePCurveOnS2) { myPCurve2 = thePCurveOnS2; }

  bool Approximation() const { return myApproximation; }

  bool PCurveOnS1() const { return myPCurve1; }

  bool PCurveOnS2() const { return myPCurve2; }

private:
  bool myApproximation;
  bool myPCurve1;
  bool myPCurve2;
};
