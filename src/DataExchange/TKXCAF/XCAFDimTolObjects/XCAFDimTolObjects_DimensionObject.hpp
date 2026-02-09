#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <XCAFDimTolObjects_DimensionType.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <XCAFDimTolObjects_DimensionQualifier.hpp>
#include <XCAFDimTolObjects_DimensionFormVariance.hpp>
#include <XCAFDimTolObjects_DimensionGrade.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <XCAFDimTolObjects_DimensionModif.hpp>
#include <TopoDS_Edge.hpp>
#include <gp_Dir.hpp>
#include <gp_Ax2.hpp>
#include <gp_Pnt.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Real.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Vector.hpp>

enum XCAFDimTolObjects_AngularQualifier
{
  XCAFDimTolObjects_AngularQualifier_None,
  XCAFDimTolObjects_AngularQualifier_Small,
  XCAFDimTolObjects_AngularQualifier_Large,
  XCAFDimTolObjects_AngularQualifier_Equal
};

class XCAFDimTolObjects_DimensionObject;

class XCAFDimTolObjects_DimensionObject : public Standard_Transient
{

public:
  Standard_EXPORT XCAFDimTolObjects_DimensionObject();

  Standard_EXPORT XCAFDimTolObjects_DimensionObject(
    const occ::handle<XCAFDimTolObjects_DimensionObject>& theObj);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> GetSemanticName() const;

  Standard_EXPORT void SetSemanticName(const occ::handle<TCollection_HAsciiString>& theName);

  Standard_EXPORT void SetQualifier(const XCAFDimTolObjects_DimensionQualifier theQualifier);

  Standard_EXPORT XCAFDimTolObjects_DimensionQualifier GetQualifier() const;

  Standard_EXPORT bool HasQualifier() const;

  Standard_EXPORT void SetAngularQualifier(
    const XCAFDimTolObjects_AngularQualifier theAngularQualifier);

  Standard_EXPORT XCAFDimTolObjects_AngularQualifier GetAngularQualifier() const;

  Standard_EXPORT bool HasAngularQualifier() const;

  Standard_EXPORT void SetType(const XCAFDimTolObjects_DimensionType theTyupe);

  Standard_EXPORT XCAFDimTolObjects_DimensionType GetType() const;

  Standard_EXPORT double GetValue() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> GetValues() const;

  Standard_EXPORT void SetValue(const double theValue);

  Standard_EXPORT void SetValues(const occ::handle<NCollection_HArray1<double>>& theValue);

  Standard_EXPORT bool IsDimWithRange() const;

  Standard_EXPORT void SetUpperBound(const double theUpperBound);

  Standard_EXPORT void SetLowerBound(const double theLowerBound);

  Standard_EXPORT double GetUpperBound() const;

  Standard_EXPORT double GetLowerBound() const;

  Standard_EXPORT bool IsDimWithPlusMinusTolerance() const;

  Standard_EXPORT bool SetUpperTolValue(const double theUperTolValue);

  Standard_EXPORT bool SetLowerTolValue(const double theLowerTolValue);

  Standard_EXPORT double GetUpperTolValue() const;

  Standard_EXPORT double GetLowerTolValue() const;

  Standard_EXPORT bool IsDimWithClassOfTolerance() const;

  Standard_EXPORT void SetClassOfTolerance(
    const bool                                    theHole,
    const XCAFDimTolObjects_DimensionFormVariance theFormVariance,
    const XCAFDimTolObjects_DimensionGrade        theGrade);

  Standard_EXPORT bool GetClassOfTolerance(bool&                                    theHole,
                                           XCAFDimTolObjects_DimensionFormVariance& theFormVariance,
                                           XCAFDimTolObjects_DimensionGrade&        theGrade) const;

  Standard_EXPORT void SetNbOfDecimalPlaces(const int theL, const int theR);

  Standard_EXPORT void GetNbOfDecimalPlaces(int& theL, int& theR) const;

  Standard_EXPORT NCollection_Sequence<XCAFDimTolObjects_DimensionModif> GetModifiers() const;

  Standard_EXPORT void SetModifiers(
    const NCollection_Sequence<XCAFDimTolObjects_DimensionModif>& theModifiers);

  Standard_EXPORT void AddModifier(const XCAFDimTolObjects_DimensionModif theModifier);

  Standard_EXPORT TopoDS_Edge GetPath() const;

  Standard_EXPORT void SetPath(const TopoDS_Edge& thePath);

  Standard_EXPORT bool GetDirection(gp_Dir& theDir) const;

  Standard_EXPORT bool SetDirection(const gp_Dir& theDir);

  void SetPointTextAttach(const gp_Pnt& thePntText)
  {
    myPntText    = thePntText;
    myHasPntText = true;
  }

  const gp_Pnt& GetPointTextAttach() const { return myPntText; }

  bool HasTextPoint() const { return myHasPntText; }

  void SetPlane(const gp_Ax2& thePlane)
  {
    myPlane    = thePlane;
    myHasPlane = true;
  }

  const gp_Ax2& GetPlane() const { return myPlane; }

  bool HasPlane() const { return myHasPlane; }

  bool HasPoint() const { return myHasConnection1; }

  bool HasPoint2() const { return myHasConnection2; }

  bool IsPointConnection() const { return myConnectionIsPoint1; }

  bool IsPointConnection2() const { return myConnectionIsPoint2; }

  void SetPoint(const gp_Pnt& thePnt)
  {
    myConnection1.SetLocation(thePnt);
    myHasConnection1     = true;
    myConnectionIsPoint1 = true;
  }

  void SetPoint2(const gp_Pnt& thePnt)
  {
    myConnection2.SetLocation(thePnt);
    myHasConnection2     = true;
    myConnectionIsPoint2 = true;
  }

  void SetConnectionAxis(const gp_Ax2& theAxis)
  {
    myConnection1        = theAxis;
    myHasConnection1     = true;
    myConnectionIsPoint1 = false;
  }

  void SetConnectionAxis2(const gp_Ax2& theAxis)
  {
    myConnection2        = theAxis;
    myHasConnection2     = true;
    myConnectionIsPoint2 = false;
  }

  gp_Pnt GetPoint() const { return myConnection1.Location(); }

  gp_Pnt GetPoint2() const { return myConnection2.Location(); }

  gp_Ax2 GetConnectionAxis() const { return myConnection1; }

  gp_Ax2 GetConnectionAxis2() const { return myConnection2; }

  occ::handle<TCollection_HAsciiString> GetConnectionName() const { return myConnectionName1; }

  occ::handle<TCollection_HAsciiString> GetConnectionName2() const { return myConnectionName2; }

  void SetConnectionName(const occ::handle<TCollection_HAsciiString>& theName)
  {
    myConnectionName1 = theName;
  }

  void SetConnectionName2(const occ::handle<TCollection_HAsciiString>& theName)
  {
    myConnectionName2 = theName;
  }

  void SetPresentation(const TopoDS_Shape&                          thePresentation,
                       const occ::handle<TCollection_HAsciiString>& thePresentationName)
  {
    myPresentation     = thePresentation;
    myPresentationName = thePresentationName;
  }

  TopoDS_Shape GetPresentation() const { return myPresentation; }

  Standard_EXPORT occ::handle<TCollection_HAsciiString> GetPresentationName() const
  {
    return myPresentationName;
  }

  bool HasDescriptions() const { return (myDescriptions.Length() > 0); }

  int NbDescriptions() const { return myDescriptions.Length(); }

  occ::handle<TCollection_HAsciiString> GetDescription(const int theNumber) const
  {
    if (theNumber < myDescriptions.Lower() || theNumber > myDescriptions.Upper())
      return new TCollection_HAsciiString();
    return myDescriptions.Value(theNumber);
  }

  occ::handle<TCollection_HAsciiString> GetDescriptionName(const int theNumber) const
  {
    if (theNumber < myDescriptions.Lower() || theNumber > myDescriptions.Upper())
      return new TCollection_HAsciiString();
    return myDescriptionNames.Value(theNumber);
  }

  Standard_EXPORT void RemoveDescription(const int theNumber);

  void AddDescription(const occ::handle<TCollection_HAsciiString> theDescription,
                      const occ::handle<TCollection_HAsciiString> theName)
  {
    myDescriptions.Append(theDescription);
    myDescriptionNames.Append(theName);
  }

  Standard_EXPORT static bool IsDimensionalLocation(const XCAFDimTolObjects_DimensionType theType);

  Standard_EXPORT static bool IsDimensionalSize(const XCAFDimTolObjects_DimensionType theType);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(XCAFDimTolObjects_DimensionObject, Standard_Transient)

private:
  XCAFDimTolObjects_DimensionType                        myType;
  occ::handle<NCollection_HArray1<double>>               myVal;
  XCAFDimTolObjects_DimensionQualifier                   myQualifier;
  XCAFDimTolObjects_AngularQualifier                     myAngularQualifier;
  bool                                                   myIsHole;
  XCAFDimTolObjects_DimensionFormVariance                myFormVariance;
  XCAFDimTolObjects_DimensionGrade                       myGrade;
  int                                                    myL;
  int                                                    myR;
  NCollection_Sequence<XCAFDimTolObjects_DimensionModif> myModifiers;
  TopoDS_Edge                                            myPath;
  gp_Dir                                                 myDir;
  gp_Ax2                                                 myConnection1, myConnection2;
  bool                                                   myHasConnection1, myHasConnection2;
  bool                                                   myConnectionIsPoint1, myConnectionIsPoint2;
  occ::handle<TCollection_HAsciiString>                  myConnectionName1, myConnectionName2;
  gp_Ax2                                                 myPlane;
  bool                                                   myHasPlane;
  bool                                                   myHasPntText;
  gp_Pnt                                                 myPntText;
  TopoDS_Shape                                           myPresentation;
  occ::handle<TCollection_HAsciiString>                  mySemanticName;
  occ::handle<TCollection_HAsciiString>                  myPresentationName;
  NCollection_Vector<occ::handle<TCollection_HAsciiString>> myDescriptions;
  NCollection_Vector<occ::handle<TCollection_HAsciiString>> myDescriptionNames;
};
