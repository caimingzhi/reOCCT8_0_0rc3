#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Aspect_TypeOfDeflection.hpp>
#include <Standard_Transient.hpp>
class VrmlConverter_IsoAspect;
class VrmlConverter_LineAspect;
class VrmlConverter_ShadingAspect;
class VrmlConverter_PointAspect;

class VrmlConverter_Drawer : public Standard_Transient
{

public:
  Standard_EXPORT VrmlConverter_Drawer();

  Standard_EXPORT void SetTypeOfDeflection(const Aspect_TypeOfDeflection aTypeOfDeflection);

  Standard_EXPORT Aspect_TypeOfDeflection TypeOfDeflection() const;

  Standard_EXPORT void SetMaximalChordialDeviation(const double aChordialDeviation);

  Standard_EXPORT double MaximalChordialDeviation() const;

  Standard_EXPORT void SetDeviationCoefficient(const double aCoefficient);

  Standard_EXPORT double DeviationCoefficient() const;

  Standard_EXPORT void SetDiscretisation(const int d);

  Standard_EXPORT int Discretisation() const;

  Standard_EXPORT void SetMaximalParameterValue(const double Value);

  Standard_EXPORT double MaximalParameterValue() const;

  Standard_EXPORT void SetIsoOnPlane(const bool OnOff);

  Standard_EXPORT bool IsoOnPlane() const;

  Standard_EXPORT occ::handle<VrmlConverter_IsoAspect> UIsoAspect();

  Standard_EXPORT void SetUIsoAspect(const occ::handle<VrmlConverter_IsoAspect>& anAspect);

  Standard_EXPORT occ::handle<VrmlConverter_IsoAspect> VIsoAspect();

  Standard_EXPORT void SetVIsoAspect(const occ::handle<VrmlConverter_IsoAspect>& anAspect);

  Standard_EXPORT occ::handle<VrmlConverter_LineAspect> FreeBoundaryAspect();

  Standard_EXPORT void SetFreeBoundaryAspect(const occ::handle<VrmlConverter_LineAspect>& anAspect);

  Standard_EXPORT void SetFreeBoundaryDraw(const bool OnOff);

  Standard_EXPORT bool FreeBoundaryDraw() const;

  Standard_EXPORT occ::handle<VrmlConverter_LineAspect> WireAspect();

  Standard_EXPORT void SetWireAspect(const occ::handle<VrmlConverter_LineAspect>& anAspect);

  Standard_EXPORT void SetWireDraw(const bool OnOff);

  Standard_EXPORT bool WireDraw() const;

  Standard_EXPORT occ::handle<VrmlConverter_LineAspect> UnFreeBoundaryAspect();

  Standard_EXPORT void SetUnFreeBoundaryAspect(
    const occ::handle<VrmlConverter_LineAspect>& anAspect);

  Standard_EXPORT void SetUnFreeBoundaryDraw(const bool OnOff);

  Standard_EXPORT bool UnFreeBoundaryDraw() const;

  Standard_EXPORT occ::handle<VrmlConverter_LineAspect> LineAspect();

  Standard_EXPORT void SetLineAspect(const occ::handle<VrmlConverter_LineAspect>& anAspect);

  Standard_EXPORT occ::handle<VrmlConverter_PointAspect> PointAspect();

  Standard_EXPORT void SetPointAspect(const occ::handle<VrmlConverter_PointAspect>& anAspect);

  Standard_EXPORT occ::handle<VrmlConverter_ShadingAspect> ShadingAspect();

  Standard_EXPORT void SetShadingAspect(const occ::handle<VrmlConverter_ShadingAspect>& anAspect);

  Standard_EXPORT bool DrawHiddenLine() const;

  Standard_EXPORT void EnableDrawHiddenLine();

  Standard_EXPORT void DisableDrawHiddenLine();

  Standard_EXPORT occ::handle<VrmlConverter_LineAspect> HiddenLineAspect();

  Standard_EXPORT void SetHiddenLineAspect(const occ::handle<VrmlConverter_LineAspect>& anAspect);

  Standard_EXPORT occ::handle<VrmlConverter_LineAspect> SeenLineAspect();

  Standard_EXPORT void SetSeenLineAspect(const occ::handle<VrmlConverter_LineAspect>& anAspect);

  DEFINE_STANDARD_RTTIEXT(VrmlConverter_Drawer, Standard_Transient)

private:
  occ::handle<VrmlConverter_IsoAspect>     myUIsoAspect;
  occ::handle<VrmlConverter_IsoAspect>     myVIsoAspect;
  int                                      myNbPoints;
  bool                                     myIsoOnPlane;
  occ::handle<VrmlConverter_LineAspect>    myFreeBoundaryAspect;
  bool                                     myFreeBoundaryDraw;
  occ::handle<VrmlConverter_LineAspect>    myUnFreeBoundaryAspect;
  bool                                     myUnFreeBoundaryDraw;
  occ::handle<VrmlConverter_LineAspect>    myWireAspect;
  bool                                     myWireDraw;
  occ::handle<VrmlConverter_LineAspect>    myLineAspect;
  occ::handle<VrmlConverter_ShadingAspect> myShadingAspect;
  double                                   myChordialDeviation;
  Aspect_TypeOfDeflection                  myTypeOfDeflection;
  double                                   myMaximalParameterValue;
  double                                   myDeviationCoefficient;
  occ::handle<VrmlConverter_PointAspect>   myPointAspect;
  bool                                     myDrawHiddenLine;
  occ::handle<VrmlConverter_LineAspect>    myHiddenLineAspect;
  occ::handle<VrmlConverter_LineAspect>    mySeenLineAspect;
};
