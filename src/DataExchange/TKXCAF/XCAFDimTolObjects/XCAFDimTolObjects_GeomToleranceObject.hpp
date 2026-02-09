#pragma once

#include <Standard.hpp>

#include <XCAFDimTolObjects_GeomToleranceType.hpp>
#include <XCAFDimTolObjects_GeomToleranceTypeValue.hpp>
#include <Standard_Real.hpp>

enum XCAFDimTolObjects_GeomToleranceMatReqModif
{
  XCAFDimTolObjects_GeomToleranceMatReqModif_None,
  XCAFDimTolObjects_GeomToleranceMatReqModif_M,
  XCAFDimTolObjects_GeomToleranceMatReqModif_L
};

enum XCAFDimTolObjects_GeomToleranceZoneModif
{
  XCAFDimTolObjects_GeomToleranceZoneModif_None,
  XCAFDimTolObjects_GeomToleranceZoneModif_Projected,
  XCAFDimTolObjects_GeomToleranceZoneModif_Runout,
  XCAFDimTolObjects_GeomToleranceZoneModif_NonUniform
};

#include <NCollection_Sequence.hpp>
#include <XCAFDimTolObjects_GeomToleranceModif.hpp>
#include <Standard_Transient.hpp>

enum XCAFDimTolObjects_ToleranceZoneAffectedPlane
{
  XCAFDimTolObjects_ToleranceZoneAffectedPlane_None,
  XCAFDimTolObjects_ToleranceZoneAffectedPlane_Intersection,
  XCAFDimTolObjects_ToleranceZoneAffectedPlane_Orientation
};

#include <gp_Pln.hpp>
#include <TopoDS_Shape.hpp>
#include <TCollection_HAsciiString.hpp>

class XCAFDimTolObjects_GeomToleranceObject : public Standard_Transient
{

public:
  Standard_EXPORT XCAFDimTolObjects_GeomToleranceObject();

  Standard_EXPORT XCAFDimTolObjects_GeomToleranceObject(
    const occ::handle<XCAFDimTolObjects_GeomToleranceObject>& theObj);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> GetSemanticName() const;

  Standard_EXPORT void SetSemanticName(const occ::handle<TCollection_HAsciiString>& theName);

  Standard_EXPORT void SetType(const XCAFDimTolObjects_GeomToleranceType theType);

  Standard_EXPORT XCAFDimTolObjects_GeomToleranceType GetType() const;

  Standard_EXPORT void SetTypeOfValue(
    const XCAFDimTolObjects_GeomToleranceTypeValue theTypeOfValue);

  Standard_EXPORT XCAFDimTolObjects_GeomToleranceTypeValue GetTypeOfValue() const;

  Standard_EXPORT void SetValue(const double theValue);

  Standard_EXPORT double GetValue() const;

  Standard_EXPORT void SetMaterialRequirementModifier(
    const XCAFDimTolObjects_GeomToleranceMatReqModif theMatReqModif);

  Standard_EXPORT XCAFDimTolObjects_GeomToleranceMatReqModif GetMaterialRequirementModifier() const;

  Standard_EXPORT void SetZoneModifier(const XCAFDimTolObjects_GeomToleranceZoneModif theZoneModif);

  Standard_EXPORT XCAFDimTolObjects_GeomToleranceZoneModif GetZoneModifier() const;

  Standard_EXPORT void SetValueOfZoneModifier(const double theValue);

  Standard_EXPORT double GetValueOfZoneModifier() const;

  Standard_EXPORT void SetModifiers(
    const NCollection_Sequence<XCAFDimTolObjects_GeomToleranceModif>& theModifiers);

  Standard_EXPORT void AddModifier(const XCAFDimTolObjects_GeomToleranceModif theModifier);

  Standard_EXPORT NCollection_Sequence<XCAFDimTolObjects_GeomToleranceModif> GetModifiers() const;

  Standard_EXPORT void SetMaxValueModifier(const double theModifier);

  Standard_EXPORT double GetMaxValueModifier() const;

  Standard_EXPORT void SetAxis(const gp_Ax2& theAxis);

  Standard_EXPORT gp_Ax2 GetAxis() const;

  Standard_EXPORT bool HasAxis() const;

  void SetPlane(const gp_Ax2& thePlane)
  {
    myPlane    = thePlane;
    myHasPlane = true;
  }

  const gp_Ax2& GetPlane() const { return myPlane; }

  void SetPoint(const gp_Pnt& thePnt)
  {
    myPnt    = thePnt;
    myHasPnt = true;
  }

  const gp_Pnt& GetPoint() const { return myPnt; }

  void SetPointTextAttach(const gp_Pnt& thePntText)
  {
    myPntText    = thePntText;
    myHasPntText = true;
  }

  const gp_Pnt& GetPointTextAttach() const { return myPntText; }

  bool HasPlane() const { return myHasPlane; }

  bool HasPoint() const { return myHasPnt; }

  bool HasPointText() const { return myHasPntText; }

  void SetPresentation(const TopoDS_Shape&                          thePresentation,
                       const occ::handle<TCollection_HAsciiString>& thePresentationName)
  {
    myPresentation     = thePresentation;
    myPresentationName = thePresentationName;
  }

  TopoDS_Shape GetPresentation() const { return myPresentation; }

  occ::handle<TCollection_HAsciiString> GetPresentationName() const { return myPresentationName; }

  bool HasAffectedPlane() const
  {
    return (myAffectedPlaneType != XCAFDimTolObjects_ToleranceZoneAffectedPlane_None);
  }

  XCAFDimTolObjects_ToleranceZoneAffectedPlane GetAffectedPlaneType() const
  {
    return myAffectedPlaneType;
  }

  void SetAffectedPlaneType(const XCAFDimTolObjects_ToleranceZoneAffectedPlane theType)
  {
    myAffectedPlaneType = theType;
  }

  void SetAffectedPlane(const gp_Pln& thePlane) { myAffectedPlane = thePlane; }

  void SetAffectedPlane(const gp_Pln&                                      thePlane,
                        const XCAFDimTolObjects_ToleranceZoneAffectedPlane theType)
  {
    myAffectedPlaneType = theType;
    myAffectedPlane     = thePlane;
  }

  const gp_Pln& GetAffectedPlane() const { return myAffectedPlane; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(XCAFDimTolObjects_GeomToleranceObject, Standard_Transient)

private:
  XCAFDimTolObjects_GeomToleranceType                        myType;
  XCAFDimTolObjects_GeomToleranceTypeValue                   myTypeOfValue;
  double                                                     myValue;
  XCAFDimTolObjects_GeomToleranceMatReqModif                 myMatReqModif;
  XCAFDimTolObjects_GeomToleranceZoneModif                   myZoneModif;
  double                                                     myValueOfZoneModif;
  NCollection_Sequence<XCAFDimTolObjects_GeomToleranceModif> myModifiers;
  double                                                     myMaxValueModif;
  gp_Ax2                                                     myAxis;
  bool                                                       myHasAxis;
  gp_Ax2                                                     myPlane;
  gp_Pnt                                                     myPnt;
  gp_Pnt                                                     myPntText;
  bool                                                       myHasPlane;
  bool                                                       myHasPnt;
  bool                                                       myHasPntText;
  TopoDS_Shape                                               myPresentation;
  occ::handle<TCollection_HAsciiString>                      mySemanticName;
  occ::handle<TCollection_HAsciiString>                      myPresentationName;
  XCAFDimTolObjects_ToleranceZoneAffectedPlane               myAffectedPlaneType;
  gp_Pln                                                     myAffectedPlane;
};
