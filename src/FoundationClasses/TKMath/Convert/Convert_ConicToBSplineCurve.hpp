#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <Convert_ParameterisationType.hpp>
class gp_Pnt2d;

class Convert_ConicToBSplineCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT int Degree() const;

  Standard_EXPORT int NbPoles() const;

  Standard_EXPORT int NbKnots() const;

  Standard_EXPORT bool IsPeriodic() const;

  Standard_EXPORT gp_Pnt2d Pole(const int Index) const;

  Standard_EXPORT double Weight(const int Index) const;

  Standard_EXPORT double Knot(const int Index) const;

  Standard_EXPORT int Multiplicity(const int Index) const;

  Standard_EXPORT void BuildCosAndSin(const Convert_ParameterisationType        Parametrisation,
                                      occ::handle<NCollection_HArray1<double>>& CosNumerator,
                                      occ::handle<NCollection_HArray1<double>>& SinNumerator,
                                      occ::handle<NCollection_HArray1<double>>& Denominator,
                                      int&                                      Degree,
                                      occ::handle<NCollection_HArray1<double>>& Knots,
                                      occ::handle<NCollection_HArray1<int>>&    Mults) const;

  Standard_EXPORT void BuildCosAndSin(const Convert_ParameterisationType        Parametrisation,
                                      const double                              UFirst,
                                      const double                              ULast,
                                      occ::handle<NCollection_HArray1<double>>& CosNumerator,
                                      occ::handle<NCollection_HArray1<double>>& SinNumerator,
                                      occ::handle<NCollection_HArray1<double>>& Denominator,
                                      int&                                      Degree,
                                      occ::handle<NCollection_HArray1<double>>& Knots,
                                      occ::handle<NCollection_HArray1<int>>&    Mults) const;

protected:
  Standard_EXPORT Convert_ConicToBSplineCurve(const int NumberOfPoles,
                                              const int NumberOfKnots,
                                              const int Degree);

  occ::handle<NCollection_HArray1<gp_Pnt2d>> poles;
  occ::handle<NCollection_HArray1<double>>   weights;
  occ::handle<NCollection_HArray1<double>>   knots;
  occ::handle<NCollection_HArray1<int>>      mults;
  int                                        degree;
  int                                        nbPoles;
  int                                        nbKnots;
  bool                                       isperiodic;
};
