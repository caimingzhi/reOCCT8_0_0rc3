#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESGeom_BSplineCurve.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGeom_BSplineCurve, IGESData_IGESEntity)

IGESGeom_BSplineCurve::IGESGeom_BSplineCurve() = default;

void IGESGeom_BSplineCurve::Init(const int                                       anIndex,
                                 const int                                       aDegree,
                                 const bool                                      aPlanar,
                                 const bool                                      aClosed,
                                 const bool                                      aPolynom,
                                 const bool                                      aPeriodic,
                                 const occ::handle<NCollection_HArray1<double>>& allKnots,
                                 const occ::handle<NCollection_HArray1<double>>& allWeights,
                                 const occ::handle<NCollection_HArray1<gp_XYZ>>& allPoles,
                                 const double                                    aUmin,
                                 const double                                    aUmax,
                                 const gp_XYZ&                                   aNorm)
{
  if (!allPoles.IsNull())
  {
    if (allKnots->Lower() != -aDegree || allKnots->Upper() != anIndex + 1 || allPoles->Lower() != 0)
    {
      throw Standard_DimensionMismatch("IGESGeom_BSplineCurve : Init");
    }
    if (!allWeights.IsNull())
    {
      if (allPoles->Length() != allWeights->Length() || allWeights->Upper() != anIndex
          || allWeights->Lower() != 0)
      {
        throw Standard_DimensionMismatch("IGESGeom_BSplineCurve : Init");
      }
    }
  }

  theIndex     = anIndex;
  theDegree    = aDegree;
  isPlanar     = aPlanar;
  isClosed     = aClosed;
  isPolynomial = aPolynom;
  isPeriodic   = aPeriodic;
  theKnots     = allKnots;
  theWeights   = allWeights;
  thePoles     = allPoles;
  theUmin      = aUmin;
  theUmax      = aUmax;
  theNorm      = aNorm;
  InitTypeAndForm(126, FormNumber());
  // FormNumber  precises the shape  0-5
}

void IGESGeom_BSplineCurve::SetFormNumber(const int form)
{
  if (form < 0 || form > 5)
    throw Standard_OutOfRange("IGESGeom_BSplineCurve : SetFormNumber");
  InitTypeAndForm(126, form);
}

int IGESGeom_BSplineCurve::UpperIndex() const
{
  return theIndex;
}

int IGESGeom_BSplineCurve::Degree() const
{
  return theDegree;
}

bool IGESGeom_BSplineCurve::IsPlanar() const
{
  return isPlanar;
}

bool IGESGeom_BSplineCurve::IsClosed() const
{
  return isClosed;
}

bool IGESGeom_BSplineCurve::IsPolynomial(const bool flag) const
{
  if (flag || theWeights.IsNull())
    return isPolynomial;
  int    i, i1 = theWeights->Lower(), i2 = theWeights->Upper();
  double w0 = theWeights->Value(i1);
  for (i = i1 + 1; i <= i2; i++)
    if (std::abs(theWeights->Value(i) - w0) > 1.e-10)
      return false;
  return true;
}

bool IGESGeom_BSplineCurve::IsPeriodic() const
{
  return isPeriodic;
}

int IGESGeom_BSplineCurve::NbKnots() const
{
  return (theKnots.IsNull() ? 0 : theKnots->Length());
}

double IGESGeom_BSplineCurve::Knot(const int anIndex) const
{
  return theKnots->Value(anIndex);
}

int IGESGeom_BSplineCurve::NbPoles() const
{
  return (thePoles.IsNull() ? 0 : thePoles->Length());
}

double IGESGeom_BSplineCurve::Weight(const int anIndex) const
{
  return theWeights->Value(anIndex);
}

gp_Pnt IGESGeom_BSplineCurve::Pole(const int anIndex) const
{
  gp_XYZ tempXYZ = thePoles->Value(anIndex);
  gp_Pnt Pole(tempXYZ);
  return Pole;
}

gp_Pnt IGESGeom_BSplineCurve::TransformedPole(const int anIndex) const
{
  gp_XYZ tempXYZ = thePoles->Value(anIndex);
  if (HasTransf())
    Location().Transforms(tempXYZ);
  gp_Pnt Pole(tempXYZ);
  return Pole;
}

double IGESGeom_BSplineCurve::UMin() const
{
  return theUmin;
}

double IGESGeom_BSplineCurve::UMax() const
{
  return theUmax;
}

gp_XYZ IGESGeom_BSplineCurve::Normal() const
{
  return theNorm;
}
