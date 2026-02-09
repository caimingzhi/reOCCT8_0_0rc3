#include <gp_Dir.hpp>
#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <IGESGeom_ConicArc.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGeom_ConicArc, IGESData_IGESEntity)

IGESGeom_ConicArc::IGESGeom_ConicArc() = default;

void IGESGeom_ConicArc::Init(const double A,
                             const double B,
                             const double C,
                             const double D,
                             const double E,
                             const double F,
                             const double ZT,
                             const gp_XY& aStart,
                             const gp_XY& anEnd)
{
  theA     = A;
  theB     = B;
  theC     = C;
  theD     = D;
  theE     = E;
  theF     = F;
  theZT    = ZT;
  theStart = aStart;
  theEnd   = anEnd;

  int fn = FormNumber();
  if (fn == 0)
    fn = ComputedFormNumber();
  InitTypeAndForm(104, fn);
}

bool IGESGeom_ConicArc::OwnCorrect()
{
  int cfn = ComputedFormNumber();
  if (FormNumber() == cfn)
    return false;
  InitTypeAndForm(104, cfn);
  return true;
}

void IGESGeom_ConicArc::Equation(double& A, double& B, double& C, double& D, double& E, double& F)
  const
{
  A = theA;
  B = theB;
  C = theC;
  D = theD;
  E = theE;
  F = theF;
}

double IGESGeom_ConicArc::ZPlane() const
{
  return theZT;
}

gp_Pnt2d IGESGeom_ConicArc::StartPoint() const
{
  gp_Pnt2d start(theStart.X(), theStart.Y());
  return start;
}

gp_Pnt IGESGeom_ConicArc::TransformedStartPoint() const
{
  gp_XYZ start(theStart.X(), theStart.Y(), theZT);
  if (HasTransf())
    Location().Transforms(start);
  gp_Pnt transStart(start);
  return transStart;
}

gp_Pnt2d IGESGeom_ConicArc::EndPoint() const
{
  gp_Pnt2d end(theEnd.X(), theEnd.Y());
  return end;
}

gp_Pnt IGESGeom_ConicArc::TransformedEndPoint() const
{
  gp_XYZ end(theEnd.X(), theEnd.Y(), theZT);
  if (HasTransf())
    Location().Transforms(end);
  gp_Pnt transEnd(end);
  return transEnd;
}

int IGESGeom_ConicArc::ComputedFormNumber() const
{
  double eps, eps2, eps4;
  eps       = 1.E-08;
  eps2      = eps * eps;
  eps4      = eps2 * eps2;
  double Q1 = theA * (theC * theF - theE * theE / 4.)
              + theB / 2. * (theE * theD / 4. - theB * theF / 2.)
              + theD / 2. * (theB * theE / 4. - theC * theD / 2.);
  double Q2 = theA * theC - theB * theB / 4;
  double Q3 = theA + theC;

  if (Q2 > eps4 && Q1 * Q3 < 0)
    return 1;
  if (Q2 < -eps4 && std::abs(Q1) > eps4)
    return 2;
  if (std::abs(Q2) <= eps4 && std::abs(Q1) > eps4)
    return 3;
  return 0;
}

bool IGESGeom_ConicArc::IsFromParabola() const
{
  int fn = FormNumber();
  if (fn == 0)
    fn = ComputedFormNumber();
  return (fn == 3);
}

bool IGESGeom_ConicArc::IsFromEllipse() const
{
  int fn = FormNumber();
  if (fn == 0)
    fn = ComputedFormNumber();
  return (fn == 1);
}

bool IGESGeom_ConicArc::IsFromHyperbola() const
{
  int fn = FormNumber();
  if (fn == 0)
    fn = ComputedFormNumber();
  return (fn == 2);
}

bool IGESGeom_ConicArc::IsClosed() const
{
  return ((theStart.X() == theEnd.X()) && (theStart.Y() == theEnd.Y()));
}

gp_Dir IGESGeom_ConicArc::Axis() const
{
  gp_Dir axis(gp_Dir::D::Z);
  return axis;
}

gp_Dir IGESGeom_ConicArc::TransformedAxis() const
{
  gp_XYZ axis(0.0, 0.0, 1.0);
  if (!HasTransf())
    return gp_Dir(axis);
  gp_GTrsf loc = Location();
  loc.SetTranslationPart(gp_XYZ(0., 0., 0.));
  loc.Transforms(axis);
  return gp_Dir(axis);
}

void IGESGeom_ConicArc::Definition(gp_Pnt& Center,
                                   gp_Dir& MainAxis,
                                   double& Rmin,
                                   double& Rmax) const
{
  double Xcen, Ycen, Xax, Yax;
  ComputedDefinition(Xcen, Ycen, Xax, Yax, Rmin, Rmax);
  Center.SetCoord(Xcen, Ycen, theZT);
  MainAxis.SetCoord(Xax, Yax, 0.);
}

void IGESGeom_ConicArc::TransformedDefinition(gp_Pnt& Center,
                                              gp_Dir& MainAxis,
                                              double& Rmin,
                                              double& Rmax) const
{
  if (!HasTransf())
  {
    Definition(Center, MainAxis, Rmin, Rmax);
    return;
  }
  double Xcen, Ycen, Xax, Yax;
  ComputedDefinition(Xcen, Ycen, Xax, Yax, Rmin, Rmax);
  gp_GTrsf loc = Location();
  gp_XYZ   cen(Xcen, Ycen, theZT);
  gp_XYZ   axis(Xax, Yax, 0.);
  loc.Transforms(cen);
  loc.SetTranslationPart(gp_XYZ(0., 0., 0.));
  loc.Transforms(axis);
  Center.SetCoord(cen.X(), cen.Y(), cen.Z());
  MainAxis.SetCoord(axis.X(), axis.Y(), axis.Z());
}

void IGESGeom_ConicArc::ComputedDefinition(double& Xcen,
                                           double& Ycen,
                                           double& Xax,
                                           double& Yax,
                                           double& Rmin,
                                           double& Rmax) const
{
  double a, b, c, d, e, f;

  Equation(a, b, c, d, e, f);
  b = b / 2.;
  d = d / 2.;
  e = e / 2.;

  double eps = 1.E-08;

  if (IsFromParabola())
  {
    Rmin = Rmax = -1.;
    if ((std::abs(a) <= eps) && (std::abs(b) <= eps))
    {
      Xcen         = (f * c - e * e) / c / d / 2.;
      Ycen         = e / c;
      double focal = -d / c;
      Xax          = (focal >= 0 ? 1. : -1.);
      Yax          = 0.;
      Rmin = Rmax = std::abs(focal);
    }
    else
    {
      double ss = a + c;
      double cc = -(a * d + b * e) / ss;
      double dd = d + (c * d - b * e) / ss;
      double fc = (a * e - b * d) / ss;
      double ee = e + fc;

      double dn = a * ee - dd * b;
      Xcen      = (cc * ee + f * b) / dn;
      Ycen      = (-cc * dd - f * a) / dn;

      double teta = M_PI / 2.;
      if (std::abs(b) > eps)
        teta = std::atan(-a / b);
      if (fc < 0)
        teta += M_PI;
      Xax = std::cos(teta);
      Yax = std::sin(teta);

      Rmin = Rmax = std::abs(fc) / sqrt(a * a + b * b) / 2.;
    }
  }

  else
  {

    double gdet = a * c * f + 2 * b * d * e - c * d * d - a * e * e - b * b * f;
    double pdet = a * c - b * b;

    Xcen = (b * e - c * d) / pdet;
    Ycen = (b * d - a * e) / pdet;

    double term1 = a - c;
    double term2 = 2 * b;
    double cos2t;
    double auxil;

    if (std::abs(term1) < gp::Resolution())
    {
      cos2t = 1.;
      auxil = term2;
    }
    else
    {
      double t2d = term2 / term1;
      cos2t      = 1. / sqrt(1 + t2d * t2d);
      auxil      = sqrt(term1 * term1 + term2 * term2);
    }

    double cost = sqrt((1 + cos2t) / 2.);
    double sint = sqrt((1 - cos2t) / 2.);

    double aprim = (a + c + auxil) / 2.;
    double cprim = (a + c - auxil) / 2.;

    term1 = -gdet / (aprim * pdet);
    term2 = -gdet / (cprim * pdet);

    if (IsFromEllipse())
    {
      Xax  = cost;
      Yax  = sint;
      Rmin = sqrt(term1);
      Rmax = sqrt(term2);
      if (Rmax < Rmin)
      {
        Rmax = sqrt(term1);
        Rmin = sqrt(term2);
      }
    }
    else if (term1 <= eps)
    {
      Xax  = -sint;
      Yax  = cost;
      Rmin = sqrt(-term1);
      Rmax = sqrt(term2);
    }
    else
    {
      Xax  = cost;
      Yax  = sint;
      Rmin = sqrt(-term2);
      Rmax = sqrt(term1);
    }
  }
}
