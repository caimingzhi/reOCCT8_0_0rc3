#pragma once

#include <Standard.hpp>

#include <XCAFDimTolObjects_DatumTargetType.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <XCAFDimTolObjects_DatumSingleModif.hpp>
#include <XCAFDimTolObjects_DatumModifWithValue.hpp>
#include <Standard_Real.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Transient.hpp>
#include <gp_Ax2.hpp>
class XCAFDimTolObjects_DatumObject;

class XCAFDimTolObjects_DatumObject : public Standard_Transient
{

public:
  Standard_EXPORT XCAFDimTolObjects_DatumObject();

  Standard_EXPORT XCAFDimTolObjects_DatumObject(
    const occ::handle<XCAFDimTolObjects_DatumObject>& theObj);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> GetSemanticName() const;

  Standard_EXPORT void SetSemanticName(const occ::handle<TCollection_HAsciiString>& theName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> GetName() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& theTag);

  Standard_EXPORT NCollection_Sequence<XCAFDimTolObjects_DatumSingleModif> GetModifiers() const;

  Standard_EXPORT void SetModifiers(
    const NCollection_Sequence<XCAFDimTolObjects_DatumSingleModif>& theModifiers);

  Standard_EXPORT void GetModifierWithValue(XCAFDimTolObjects_DatumModifWithValue& theModifier,
                                            double&                                theValue) const;

  Standard_EXPORT void SetModifierWithValue(const XCAFDimTolObjects_DatumModifWithValue theModifier,
                                            const double                                theValue);

  Standard_EXPORT void AddModifier(const XCAFDimTolObjects_DatumSingleModif theModifier);

  Standard_EXPORT TopoDS_Shape GetDatumTarget() const;

  Standard_EXPORT void SetDatumTarget(const TopoDS_Shape& theShape);

  Standard_EXPORT int GetPosition() const;

  Standard_EXPORT void SetPosition(const int thePosition);

  Standard_EXPORT bool IsDatumTarget() const;

  Standard_EXPORT void IsDatumTarget(const bool theIsDT);

  Standard_EXPORT XCAFDimTolObjects_DatumTargetType GetDatumTargetType() const;

  Standard_EXPORT void SetDatumTargetType(const XCAFDimTolObjects_DatumTargetType theType);

  Standard_EXPORT gp_Ax2 GetDatumTargetAxis() const;

  Standard_EXPORT void SetDatumTargetAxis(const gp_Ax2& theAxis);

  Standard_EXPORT double GetDatumTargetLength() const;

  Standard_EXPORT void SetDatumTargetLength(const double theLength);

  Standard_EXPORT double GetDatumTargetWidth() const;

  Standard_EXPORT void SetDatumTargetWidth(const double theWidth);

  Standard_EXPORT int GetDatumTargetNumber() const;

  Standard_EXPORT void SetDatumTargetNumber(const int theNumber);

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

  bool HasDatumTargetParams() { return myIsValidDT; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(XCAFDimTolObjects_DatumObject, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>                    myName;
  NCollection_Sequence<XCAFDimTolObjects_DatumSingleModif> myModifiers;
  XCAFDimTolObjects_DatumModifWithValue                    myModifierWithValue;
  double                                                   myValueOfModifier;
  TopoDS_Shape                                             myDatumTarget;
  int                                                      myPosition;
  bool                                                     myIsDTarget;
  bool                                                     myIsValidDT;
  XCAFDimTolObjects_DatumTargetType                        myDTargetType;
  double                                                   myLength;
  double                                                   myWidth;
  int                                                      myDatumTargetNumber;
  gp_Ax2                                                   myAxis;
  gp_Ax2                                                   myPlane;
  gp_Pnt                                                   myPnt;
  gp_Pnt                                                   myPntText;
  bool                                                     myHasPlane;
  bool                                                     myHasPnt;
  bool                                                     myHasPntText;
  TopoDS_Shape                                             myPresentation;
  occ::handle<TCollection_HAsciiString>                    mySemanticName;
  occ::handle<TCollection_HAsciiString>                    myPresentationName;
};
