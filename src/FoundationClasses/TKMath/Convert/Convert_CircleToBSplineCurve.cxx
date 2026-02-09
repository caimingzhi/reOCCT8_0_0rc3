

#include <Convert_CircleToBSplineCurve.hpp>
#include <gp.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Trsf2d.hpp>
#include <Precision.hpp>
#include <Standard_DomainError.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

Convert_CircleToBSplineCurve::Convert_CircleToBSplineCurve(
  const gp_Circ2d&                   C,
  const Convert_ParameterisationType Parameterisation)
    : Convert_ConicToBSplineCurve(0, 0, 0)
{

  int ii;

  double                                   R, value;
  occ::handle<NCollection_HArray1<double>> CosNumeratorPtr, SinNumeratorPtr;

  R = C.Radius();
  if (Parameterisation != Convert_TgtThetaOver2 && Parameterisation != Convert_RationalC1)
  {

    isperiodic = false;
    Convert_ConicToBSplineCurve::BuildCosAndSin(Parameterisation,
                                                0,
                                                2 * M_PI,
                                                CosNumeratorPtr,
                                                SinNumeratorPtr,
                                                weights,
                                                degree,
                                                knots,
                                                mults);
  }
  else
  {
    isperiodic = true;
    Convert_ConicToBSplineCurve::BuildCosAndSin(Parameterisation,
                                                CosNumeratorPtr,
                                                SinNumeratorPtr,
                                                weights,
                                                degree,
                                                knots,
                                                mults);
  }

  nbPoles = CosNumeratorPtr->Length();
  nbKnots = knots->Length();

  poles = new NCollection_HArray1<gp_Pnt2d>(1, nbPoles);

  gp_Dir2d  Ox = C.XAxis().Direction();
  gp_Dir2d  Oy = C.YAxis().Direction();
  gp_Trsf2d Trsf;
  Trsf.SetTransformation(C.XAxis(), gp::OX2d());
  if (Ox.X() * Oy.Y() - Ox.Y() * Oy.X() > 0.0e0)
  {
    value = R;
  }
  else
  {
    value = -R;
  }

  for (ii = 1; ii <= nbPoles; ii++)
  {
    poles->ChangeArray1()(ii).SetCoord(1, R * CosNumeratorPtr->Value(ii));
    poles->ChangeArray1()(ii).SetCoord(2, value * SinNumeratorPtr->Value(ii));
    poles->ChangeArray1()(ii).Transform(Trsf);
  }
}

Convert_CircleToBSplineCurve::Convert_CircleToBSplineCurve(
  const gp_Circ2d&                   C,
  const double                       UFirst,
  const double                       ULast,
  const Convert_ParameterisationType Parameterisation)
    : Convert_ConicToBSplineCurve(0, 0, 0)
{
  double delta = ULast - UFirst;
  double Eps   = Precision::PConfusion();

  if ((delta > (2 * M_PI + Eps)) || (delta <= 0.0e0))
  {
    throw Standard_DomainError("Convert_CircleToBSplineCurve");
  }

  int                                      ii;
  double                                   R, value;
  occ::handle<NCollection_HArray1<double>> CosNumeratorPtr, SinNumeratorPtr;

  R          = C.Radius();
  isperiodic = false;
  Convert_ConicToBSplineCurve::BuildCosAndSin(Parameterisation,
                                              UFirst,
                                              ULast,
                                              CosNumeratorPtr,
                                              SinNumeratorPtr,
                                              weights,
                                              degree,
                                              knots,
                                              mults);

  nbPoles = CosNumeratorPtr->Length();
  nbKnots = knots->Length();

  poles = new NCollection_HArray1<gp_Pnt2d>(1, nbPoles);

  gp_Dir2d  Ox = C.XAxis().Direction();
  gp_Dir2d  Oy = C.YAxis().Direction();
  gp_Trsf2d Trsf;
  Trsf.SetTransformation(C.XAxis(), gp::OX2d());
  if (Ox.X() * Oy.Y() - Ox.Y() * Oy.X() > 0.0e0)
  {
    value = R;
  }
  else
  {
    value = -R;
  }

  for (ii = 1; ii <= nbPoles; ii++)
  {
    poles->ChangeArray1()(ii).SetCoord(1, R * CosNumeratorPtr->Value(ii));
    poles->ChangeArray1()(ii).SetCoord(2, value * SinNumeratorPtr->Value(ii));
    poles->ChangeArray1()(ii).Transform(Trsf);
  }
}
