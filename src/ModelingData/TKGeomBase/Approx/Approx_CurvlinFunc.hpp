#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Surface.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class Approx_CurvlinFunc : public Standard_Transient
{

public:
  Standard_EXPORT Approx_CurvlinFunc(const occ::handle<Adaptor3d_Curve>& C, const double Tol);

  Standard_EXPORT Approx_CurvlinFunc(const occ::handle<Adaptor2d_Curve2d>& C2D,
                                     const occ::handle<Adaptor3d_Surface>& S,
                                     const double                          Tol);

  Standard_EXPORT Approx_CurvlinFunc(const occ::handle<Adaptor2d_Curve2d>& C2D1,
                                     const occ::handle<Adaptor2d_Curve2d>& C2D2,
                                     const occ::handle<Adaptor3d_Surface>& S1,
                                     const occ::handle<Adaptor3d_Surface>& S2,
                                     const double                          Tol);

  Standard_EXPORT void SetTol(const double Tol);

  Standard_EXPORT double FirstParameter() const;

  Standard_EXPORT double LastParameter() const;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T, const GeomAbs_Shape S) const;

  Standard_EXPORT void Trim(const double First, const double Last, const double Tol);

  Standard_EXPORT void Length();

  Standard_EXPORT double Length(Adaptor3d_Curve& C, const double FirstU, const double LasrU) const;

  Standard_EXPORT double GetLength() const;

  Standard_EXPORT double GetUParameter(Adaptor3d_Curve& C,
                                       const double     S,
                                       const int        NumberOfCurve) const;

  Standard_EXPORT double GetSParameter(const double U) const;

  Standard_EXPORT bool EvalCase1(const double                S,
                                 const int                   Order,
                                 NCollection_Array1<double>& Result) const;

  Standard_EXPORT bool EvalCase2(const double                S,
                                 const int                   Order,
                                 NCollection_Array1<double>& Result) const;

  Standard_EXPORT bool EvalCase3(const double                S,
                                 const int                   Order,
                                 NCollection_Array1<double>& Result);

  DEFINE_STANDARD_RTTIEXT(Approx_CurvlinFunc, Standard_Transient)

private:
  Standard_EXPORT void Init();

  Standard_EXPORT void Init(Adaptor3d_Curve&                          C,
                            occ::handle<NCollection_HArray1<double>>& Si,
                            occ::handle<NCollection_HArray1<double>>& Ui) const;

  Standard_EXPORT double GetSParameter(Adaptor3d_Curve& C,
                                       const double     U,
                                       const double     Length) const;

  Standard_EXPORT bool EvalCurOnSur(const double                S,
                                    const int                   Order,
                                    NCollection_Array1<double>& Result,
                                    const int                   NumberOfCurve) const;

  occ::handle<Adaptor3d_Curve>             myC3D;
  occ::handle<Adaptor2d_Curve2d>           myC2D1;
  occ::handle<Adaptor2d_Curve2d>           myC2D2;
  occ::handle<Adaptor3d_Surface>           mySurf1;
  occ::handle<Adaptor3d_Surface>           mySurf2;
  int                                      myCase;
  double                                   myFirstS;
  double                                   myLastS;
  double                                   myFirstU1;
  double                                   myLastU1;
  double                                   myFirstU2;
  double                                   myLastU2;
  double                                   myLength;
  double                                   myLength1;
  double                                   myLength2;
  double                                   myTolLen;
  double                                   myPrevS;
  double                                   myPrevU;
  occ::handle<NCollection_HArray1<double>> myUi_1;
  occ::handle<NCollection_HArray1<double>> mySi_1;
  occ::handle<NCollection_HArray1<double>> myUi_2;
  occ::handle<NCollection_HArray1<double>> mySi_2;
};
