#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
class gp_Pnt;

class Convert_ElementarySurfaceToBSplineSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT int UDegree() const;

  Standard_EXPORT int VDegree() const;

  Standard_EXPORT int NbUPoles() const;

  Standard_EXPORT int NbVPoles() const;

  Standard_EXPORT int NbUKnots() const;

  Standard_EXPORT int NbVKnots() const;

  Standard_EXPORT bool IsUPeriodic() const;

  Standard_EXPORT bool IsVPeriodic() const;

  Standard_EXPORT gp_Pnt Pole(const int UIndex, const int VIndex) const;

  Standard_EXPORT double Weight(const int UIndex, const int VIndex) const;

  Standard_EXPORT double UKnot(const int UIndex) const;

  Standard_EXPORT double VKnot(const int UIndex) const;

  Standard_EXPORT int UMultiplicity(const int UIndex) const;

  Standard_EXPORT int VMultiplicity(const int VIndex) const;

protected:
  Standard_EXPORT Convert_ElementarySurfaceToBSplineSurface(const int NumberOfUPoles,
                                                            const int NumberOfVPoles,
                                                            const int NumberOfUKnots,
                                                            const int NumberOfVKnots,
                                                            const int UDegree,
                                                            const int VDegree);

  NCollection_Array2<gp_Pnt> poles;
  NCollection_Array2<double> weights;
  NCollection_Array1<double> uknots;
  NCollection_Array1<int>    umults;
  NCollection_Array1<double> vknots;
  NCollection_Array1<int>    vmults;
  int                        udegree;
  int                        vdegree;
  int                        nbUPoles;
  int                        nbVPoles;
  int                        nbUKnots;
  int                        nbVKnots;
  bool                       isuperiodic;
  bool                       isvperiodic;
};
