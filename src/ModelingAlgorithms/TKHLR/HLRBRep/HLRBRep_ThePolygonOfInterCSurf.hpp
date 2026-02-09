#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Bnd_Box.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class Standard_OutOfRange;
class gp_Lin;
class HLRBRep_LineTool;
class Bnd_Box;
class gp_Pnt;

class HLRBRep_ThePolygonOfInterCSurf
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_ThePolygonOfInterCSurf(const gp_Lin& Curve, const int NbPnt);

  Standard_EXPORT HLRBRep_ThePolygonOfInterCSurf(const gp_Lin& Curve,
                                                 const double  U1,
                                                 const double  U2,
                                                 const int     NbPnt);

  Standard_EXPORT HLRBRep_ThePolygonOfInterCSurf(const gp_Lin&                     Curve,
                                                 const NCollection_Array1<double>& Upars);

  const Bnd_Box& Bounding() const { return TheBnd; }

  double DeflectionOverEstimation() const { return TheDeflection; }

  void SetDeflectionOverEstimation(const double x)
  {
    TheDeflection = x;
    TheBnd.Enlarge(TheDeflection);
  }

  void Closed(const bool flag) { ClosedPolygon = flag; }

  bool Closed() const { return false; }

  int NbSegments() const { return NbPntIn - 1; }

  const gp_Pnt& BeginOfSeg(const int theIndex) const { return ThePnts(theIndex); }

  const gp_Pnt& EndOfSeg(const int theIndex) const { return ThePnts(theIndex + 1); }

  double InfParameter() const { return Binf; }

  double SupParameter() const { return Bsup; }

  Standard_EXPORT double ApproxParamOnCurve(const int Index, const double ParamOnLine) const;

  Standard_EXPORT void Dump() const;

protected:
  Standard_EXPORT void Init(const gp_Lin& Curve);

  Standard_EXPORT void Init(const gp_Lin& Curve, const NCollection_Array1<double>& Upars);

private:
  Bnd_Box                                  TheBnd;
  double                                   TheDeflection;
  int                                      NbPntIn;
  NCollection_Array1<gp_Pnt>               ThePnts;
  bool                                     ClosedPolygon;
  double                                   Binf;
  double                                   Bsup;
  occ::handle<NCollection_HArray1<double>> myParams;
};
