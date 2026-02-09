#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Aspect_TypeOfDeflection.hpp>

enum Graphic3d_GroupAspect
{
  Graphic3d_ASPECT_LINE,
  Graphic3d_ASPECT_TEXT,
  Graphic3d_ASPECT_MARKER,
  Graphic3d_ASPECT_FILL_AREA
};

#include <Graphic3d_PresentationAttributes.hpp>
#include <Graphic3d_ShaderProgram.hpp>
#include <Standard_Real.hpp>
#include <Prs3d_VertexDrawMode.hpp>

#include <TCollection_AsciiString.hpp>

class Prs3d_DimensionUnits
{
public:
  Prs3d_DimensionUnits()
      : myLengthUnits("m"),
        myAngleUnits("rad")
  {
  }

  Prs3d_DimensionUnits(const Prs3d_DimensionUnits& theUnits)
      : myLengthUnits(theUnits.GetLengthUnits()),
        myAngleUnits(theUnits.GetAngleUnits())
  {
  }

  void SetAngleUnits(const TCollection_AsciiString& theUnits) { myAngleUnits = theUnits; }

  const TCollection_AsciiString& GetAngleUnits() const { return myAngleUnits; }

  void SetLengthUnits(const TCollection_AsciiString& theUnits) { myLengthUnits = theUnits; }

  const TCollection_AsciiString& GetLengthUnits() const { return myLengthUnits; }

private:
  TCollection_AsciiString myLengthUnits;
  TCollection_AsciiString myAngleUnits;
};

#include <Prs3d_TypeOfHLR.hpp>
#include <Standard_Transient.hpp>
#include <GeomAbs_Shape.hpp>

class Prs3d_IsoAspect;
class Prs3d_LineAspect;
class Prs3d_TextAspect;
class Prs3d_ShadingAspect;
class Prs3d_PointAspect;
class Prs3d_PlaneAspect;
class Prs3d_ArrowAspect;
class Prs3d_DatumAspect;
class Prs3d_DimensionAspect;
class TCollection_AsciiString;

class Prs3d_Drawer : public Graphic3d_PresentationAttributes
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_Drawer, Graphic3d_PresentationAttributes)
public:
  Standard_EXPORT Prs3d_Drawer();

  Standard_EXPORT void SetupOwnDefaults();

  Standard_EXPORT void SetTypeOfDeflection(const Aspect_TypeOfDeflection theTypeOfDeflection);

  Aspect_TypeOfDeflection TypeOfDeflection() const
  {
    return myHasOwnTypeOfDeflection || myLink.IsNull() ? myTypeOfDeflection
                                                       : myLink->TypeOfDeflection();
  }

  bool HasOwnTypeOfDeflection() const { return myHasOwnTypeOfDeflection; }

  void UnsetOwnTypeOfDeflection()
  {
    myHasOwnTypeOfDeflection = false;
    myTypeOfDeflection       = Aspect_TOD_RELATIVE;
  }

  void SetMaximalChordialDeviation(const double theChordialDeviation)
  {
    myChordialDeviation = theChordialDeviation;
  }

  double MaximalChordialDeviation() const
  {
    return myChordialDeviation > 0.0
             ? myChordialDeviation
             : (!myLink.IsNull() ? myLink->MaximalChordialDeviation() : 0.0001);
  }

  bool HasOwnMaximalChordialDeviation() const { return myChordialDeviation > 0.0; }

  void UnsetOwnMaximalChordialDeviation() { myChordialDeviation = -1.0; }

  Standard_EXPORT void SetTypeOfHLR(const Prs3d_TypeOfHLR theTypeOfHLR);

  Standard_EXPORT Prs3d_TypeOfHLR TypeOfHLR() const;

  bool HasOwnTypeOfHLR() const { return (myTypeOfHLR != Prs3d_TOH_NotSet); }

  void SetMaximalParameterValue(const double theValue) { myMaximalParameterValue = theValue; }

  double MaximalParameterValue() const
  {
    return myMaximalParameterValue > 0.0
             ? myMaximalParameterValue
             : (!myLink.IsNull() ? myLink->MaximalParameterValue() : 500000.0);
  }

  bool HasOwnMaximalParameterValue() const { return myMaximalParameterValue > 0.0; }

  void UnsetOwnMaximalParameterValue() { myMaximalParameterValue = -1.0; }

  Standard_EXPORT void SetIsoOnPlane(const bool theIsEnabled);

  bool IsoOnPlane() const
  {
    return myHasOwnIsoOnPlane || myLink.IsNull() ? myIsoOnPlane : myLink->IsoOnPlane();
  }

  bool HasOwnIsoOnPlane() const { return myHasOwnIsoOnPlane; }

  void UnsetOwnIsoOnPlane()
  {
    myHasOwnIsoOnPlane = false;
    myIsoOnPlane       = false;
  }

  bool IsoOnTriangulation() const
  {
    return myHasOwnIsoOnTriangulation || myLink.IsNull() ? myIsoOnTriangulation
                                                         : myLink->IsoOnTriangulation();
  }

  bool HasOwnIsoOnTriangulation() const { return myHasOwnIsoOnTriangulation; }

  void UnsetOwnIsoOnTriangulation()
  {
    myHasOwnIsoOnTriangulation = false;
    myIsoOnTriangulation       = false;
  }

  Standard_EXPORT void SetIsoOnTriangulation(const bool theToEnable);

  void SetDiscretisation(const int theValue) { myNbPoints = theValue; }

  int Discretisation() const
  {
    return myNbPoints != -1 ? myNbPoints : (!myLink.IsNull() ? myLink->Discretisation() : 30);
  }

  bool HasOwnDiscretisation() const { return myNbPoints != -1; }

  void UnsetOwnDiscretisation() { myNbPoints = -1; }

  Standard_EXPORT void SetDeviationCoefficient(const double theCoefficient);

  double DeviationCoefficient() const
  {
    return myDeviationCoefficient > 0.0
             ? myDeviationCoefficient
             : (!myLink.IsNull() ? myLink->DeviationCoefficient() : 0.001);
  }

  void SetDeviationCoefficient() { myDeviationCoefficient = -1.0; }

  bool HasOwnDeviationCoefficient() const { return myDeviationCoefficient > 0.0; }

  double PreviousDeviationCoefficient() const
  {
    return HasOwnDeviationCoefficient() ? myPreviousDeviationCoefficient : 0.0;
  }

  void UpdatePreviousDeviationCoefficient()
  {
    if (HasOwnDeviationCoefficient())
    {
      myPreviousDeviationCoefficient = DeviationCoefficient();
    }
  }

  Standard_EXPORT void SetDeviationAngle(const double theAngle);

  double DeviationAngle() const
  {
    return myDeviationAngle > 0.0
             ? myDeviationAngle
             : (!myLink.IsNull() ? myLink->DeviationAngle() : 20.0 * M_PI / 180.0);
  }

  void SetDeviationAngle() { myDeviationAngle = -1.0; }

  bool HasOwnDeviationAngle() const { return myDeviationAngle > 0.0; }

  double PreviousDeviationAngle() const
  {
    return HasOwnDeviationAngle() ? myPreviousDeviationAngle : 0.0;
  }

  void UpdatePreviousDeviationAngle()
  {
    if (HasOwnDeviationAngle())
    {
      myPreviousDeviationAngle = DeviationAngle();
    }
  }

  Standard_EXPORT void SetAutoTriangulation(const bool theIsEnabled);

  bool IsAutoTriangulation() const
  {
    return myHasOwnIsAutoTriangulated || myLink.IsNull() ? myIsAutoTriangulated
                                                         : myLink->IsAutoTriangulation();
  }

  bool HasOwnIsAutoTriangulation() const { return myHasOwnIsAutoTriangulated; }

  void UnsetOwnIsAutoTriangulation()
  {
    myHasOwnIsAutoTriangulated = false;
    myIsAutoTriangulated       = true;
  }

  Standard_EXPORT const occ::handle<Prs3d_IsoAspect>& UIsoAspect() const;

  void SetUIsoAspect(const occ::handle<Prs3d_IsoAspect>& theAspect) { myUIsoAspect = theAspect; }

  bool HasOwnUIsoAspect() const { return !myUIsoAspect.IsNull(); }

  Standard_EXPORT const occ::handle<Prs3d_IsoAspect>& VIsoAspect() const;

  void SetVIsoAspect(const occ::handle<Prs3d_IsoAspect>& theAspect) { myVIsoAspect = theAspect; }

  bool HasOwnVIsoAspect() const { return !myVIsoAspect.IsNull(); }

  Standard_EXPORT const occ::handle<Prs3d_LineAspect>& WireAspect() const;

  void SetWireAspect(const occ::handle<Prs3d_LineAspect>& theAspect) { myWireAspect = theAspect; }

  bool HasOwnWireAspect() const { return !myWireAspect.IsNull(); }

  Standard_EXPORT void SetWireDraw(const bool theIsEnabled);

  bool WireDraw() const
  {
    return myHasOwnWireDraw || myLink.IsNull() ? myWireDraw : myLink->WireDraw();
  }

  bool HasOwnWireDraw() const { return myHasOwnWireDraw; }

  void UnsetOwnWireDraw()
  {
    myHasOwnWireDraw = false;
    myWireDraw       = true;
  }

  Standard_EXPORT const occ::handle<Prs3d_PointAspect>& PointAspect() const;

  void SetPointAspect(const occ::handle<Prs3d_PointAspect>& theAspect)
  {
    myPointAspect = theAspect;
  }

  bool HasOwnPointAspect() const { return !myPointAspect.IsNull(); }

  Standard_EXPORT bool SetupOwnPointAspect(
    const occ::handle<Prs3d_Drawer>& theDefaults = occ::handle<Prs3d_Drawer>());

  Standard_EXPORT const occ::handle<Prs3d_LineAspect>& LineAspect() const;

  void SetLineAspect(const occ::handle<Prs3d_LineAspect>& theAspect) { myLineAspect = theAspect; }

  bool HasOwnLineAspect() const { return !myLineAspect.IsNull(); }

  Standard_EXPORT bool SetOwnLineAspects(
    const occ::handle<Prs3d_Drawer>& theDefaults = occ::handle<Prs3d_Drawer>());

  Standard_EXPORT bool SetOwnDatumAspects(
    const occ::handle<Prs3d_Drawer>& theDefaults = occ::handle<Prs3d_Drawer>());

  Standard_EXPORT const occ::handle<Prs3d_TextAspect>& TextAspect() const;

  void SetTextAspect(const occ::handle<Prs3d_TextAspect>& theAspect) { myTextAspect = theAspect; }

  bool HasOwnTextAspect() const { return !myTextAspect.IsNull(); }

  Standard_EXPORT const occ::handle<Prs3d_ShadingAspect>& ShadingAspect() const;

  void SetShadingAspect(const occ::handle<Prs3d_ShadingAspect>& theAspect)
  {
    myShadingAspect = theAspect;
  }

  bool HasOwnShadingAspect() const { return !myShadingAspect.IsNull(); }

  Standard_EXPORT bool SetupOwnShadingAspect(
    const occ::handle<Prs3d_Drawer>& theDefaults = occ::handle<Prs3d_Drawer>());

  Standard_EXPORT const occ::handle<Prs3d_LineAspect>& SeenLineAspect() const;

  void SetSeenLineAspect(const occ::handle<Prs3d_LineAspect>& theAspect)
  {
    mySeenLineAspect = theAspect;
  }

  bool HasOwnSeenLineAspect() const { return !mySeenLineAspect.IsNull(); }

  Standard_EXPORT const occ::handle<Prs3d_PlaneAspect>& PlaneAspect() const;

  void SetPlaneAspect(const occ::handle<Prs3d_PlaneAspect>& theAspect)
  {
    myPlaneAspect = theAspect;
  }

  bool HasOwnPlaneAspect() const { return !myPlaneAspect.IsNull(); }

  Standard_EXPORT const occ::handle<Prs3d_ArrowAspect>& ArrowAspect() const;

  void SetArrowAspect(const occ::handle<Prs3d_ArrowAspect>& theAspect)
  {
    myArrowAspect = theAspect;
  }

  bool HasOwnArrowAspect() const { return !myArrowAspect.IsNull(); }

  Standard_EXPORT void SetLineArrowDraw(const bool theIsEnabled);

  bool LineArrowDraw() const
  {
    return myHasOwnLineArrowDraw || myLink.IsNull() ? myLineArrowDraw : myLink->LineArrowDraw();
  }

  bool HasOwnLineArrowDraw() const { return myHasOwnLineArrowDraw; }

  void UnsetOwnLineArrowDraw()
  {
    myHasOwnLineArrowDraw = false;
    myLineArrowDraw       = false;
  }

  Standard_EXPORT const occ::handle<Prs3d_LineAspect>& HiddenLineAspect() const;

  void SetHiddenLineAspect(const occ::handle<Prs3d_LineAspect>& theAspect)
  {
    myHiddenLineAspect = theAspect;
  }

  bool HasOwnHiddenLineAspect() const { return !myHiddenLineAspect.IsNull(); }

  bool DrawHiddenLine() const
  {
    return myHasOwnDrawHiddenLine || myLink.IsNull() ? myDrawHiddenLine : myLink->DrawHiddenLine();
  }

  Standard_EXPORT void EnableDrawHiddenLine();

  Standard_EXPORT void DisableDrawHiddenLine();

  bool HasOwnDrawHiddenLine() const { return myHasOwnDrawHiddenLine; }

  void UnsetOwnDrawHiddenLine()
  {
    myHasOwnDrawHiddenLine = false;
    myDrawHiddenLine       = false;
  }

  Standard_EXPORT const occ::handle<Prs3d_LineAspect>& VectorAspect() const;

  void SetVectorAspect(const occ::handle<Prs3d_LineAspect>& theAspect)
  {
    myVectorAspect = theAspect;
  }

  bool HasOwnVectorAspect() const { return !myVectorAspect.IsNull(); }

  Standard_EXPORT void SetVertexDrawMode(const Prs3d_VertexDrawMode theMode);

  Standard_EXPORT Prs3d_VertexDrawMode VertexDrawMode() const;

  bool HasOwnVertexDrawMode() const { return (myVertexDrawMode != Prs3d_VDM_Inherited); }

  Standard_EXPORT const occ::handle<Prs3d_DatumAspect>& DatumAspect() const;

  void SetDatumAspect(const occ::handle<Prs3d_DatumAspect>& theAspect)
  {
    myDatumAspect = theAspect;
  }

  bool HasOwnDatumAspect() const { return !myDatumAspect.IsNull(); }

  Standard_EXPORT const occ::handle<Prs3d_LineAspect>& SectionAspect() const;

  void SetSectionAspect(const occ::handle<Prs3d_LineAspect>& theAspect)
  {
    mySectionAspect = theAspect;
  }

  bool HasOwnSectionAspect() const { return !mySectionAspect.IsNull(); }

  void SetFreeBoundaryAspect(const occ::handle<Prs3d_LineAspect>& theAspect)
  {
    myFreeBoundaryAspect = theAspect;
  }

  Standard_EXPORT const occ::handle<Prs3d_LineAspect>& FreeBoundaryAspect() const;

  bool HasOwnFreeBoundaryAspect() const { return !myFreeBoundaryAspect.IsNull(); }

  Standard_EXPORT void SetFreeBoundaryDraw(const bool theIsEnabled);

  bool FreeBoundaryDraw() const
  {
    return myHasOwnFreeBoundaryDraw || myLink.IsNull() ? myFreeBoundaryDraw
                                                       : myLink->FreeBoundaryDraw();
  }

  bool HasOwnFreeBoundaryDraw() const { return myHasOwnFreeBoundaryDraw; }

  void UnsetOwnFreeBoundaryDraw()
  {
    myHasOwnFreeBoundaryDraw = false;
    myFreeBoundaryDraw       = true;
  }

  void SetUnFreeBoundaryAspect(const occ::handle<Prs3d_LineAspect>& theAspect)
  {
    myUnFreeBoundaryAspect = theAspect;
  }

  Standard_EXPORT const occ::handle<Prs3d_LineAspect>& UnFreeBoundaryAspect() const;

  bool HasOwnUnFreeBoundaryAspect() const { return !myUnFreeBoundaryAspect.IsNull(); }

  Standard_EXPORT void SetUnFreeBoundaryDraw(const bool theIsEnabled);

  bool UnFreeBoundaryDraw() const
  {
    return myHasOwnUnFreeBoundaryDraw || myLink.IsNull() ? myUnFreeBoundaryDraw
                                                         : myLink->UnFreeBoundaryDraw();
  }

  bool HasOwnUnFreeBoundaryDraw() const { return myHasOwnUnFreeBoundaryDraw; }

  void UnsetOwnUnFreeBoundaryDraw()
  {
    myHasOwnUnFreeBoundaryDraw = false;
    myUnFreeBoundaryDraw       = true;
  }

  void SetFaceBoundaryAspect(const occ::handle<Prs3d_LineAspect>& theAspect)
  {
    myFaceBoundaryAspect = theAspect;
  }

  Standard_EXPORT const occ::handle<Prs3d_LineAspect>& FaceBoundaryAspect() const;

  bool HasOwnFaceBoundaryAspect() const { return !myFaceBoundaryAspect.IsNull(); }

  Standard_EXPORT bool SetupOwnFaceBoundaryAspect(
    const occ::handle<Prs3d_Drawer>& theDefaults = occ::handle<Prs3d_Drawer>());

  Standard_EXPORT void SetFaceBoundaryDraw(const bool theIsEnabled);

  bool FaceBoundaryDraw() const
  {
    return myHasOwnFaceBoundaryDraw || myLink.IsNull() ? myFaceBoundaryDraw
                                                       : myLink->FaceBoundaryDraw();
  }

  bool HasOwnFaceBoundaryDraw() const { return myHasOwnFaceBoundaryDraw; }

  void UnsetOwnFaceBoundaryDraw()
  {
    myHasOwnFaceBoundaryDraw = false;
    myFaceBoundaryDraw       = false;
  }

  bool HasOwnFaceBoundaryUpperContinuity() const { return myFaceBoundaryUpperContinuity != -1; }

  GeomAbs_Shape FaceBoundaryUpperContinuity() const
  {
    return HasOwnFaceBoundaryUpperContinuity()
             ? (GeomAbs_Shape)myFaceBoundaryUpperContinuity
             : (!myLink.IsNull() ? myLink->FaceBoundaryUpperContinuity() : GeomAbs_CN);
  }

  void SetFaceBoundaryUpperContinuity(GeomAbs_Shape theMostAllowedEdgeClass)
  {
    myFaceBoundaryUpperContinuity = theMostAllowedEdgeClass;
  }

  void UnsetFaceBoundaryUpperContinuity() { myFaceBoundaryUpperContinuity = -1; }

  Standard_EXPORT const occ::handle<Prs3d_DimensionAspect>& DimensionAspect() const;

  void SetDimensionAspect(const occ::handle<Prs3d_DimensionAspect>& theAspect)
  {
    myDimensionAspect = theAspect;
  }

  bool HasOwnDimensionAspect() const { return !myDimensionAspect.IsNull(); }

  Standard_EXPORT void SetDimLengthModelUnits(const TCollection_AsciiString& theUnits);

  Standard_EXPORT void SetDimAngleModelUnits(const TCollection_AsciiString& theUnits);

  const TCollection_AsciiString& DimLengthModelUnits() const
  {
    return myHasOwnDimLengthModelUnits || myLink.IsNull() ? myDimensionModelUnits.GetLengthUnits()
                                                          : myLink->DimLengthModelUnits();
  }

  const TCollection_AsciiString& DimAngleModelUnits() const
  {
    return myHasOwnDimAngleModelUnits || myLink.IsNull() ? myDimensionModelUnits.GetAngleUnits()
                                                         : myLink->DimAngleModelUnits();
  }

  bool HasOwnDimLengthModelUnits() const { return myHasOwnDimLengthModelUnits; }

  void UnsetOwnDimLengthModelUnits()
  {
    myHasOwnDimLengthModelUnits = false;
    myDimensionModelUnits.SetLengthUnits("m");
  }

  bool HasOwnDimAngleModelUnits() const { return myHasOwnDimAngleModelUnits; }

  void UnsetOwnDimAngleModelUnits()
  {
    myHasOwnDimAngleModelUnits = false;
    myDimensionModelUnits.SetAngleUnits("rad");
  }

  Standard_EXPORT void SetDimLengthDisplayUnits(const TCollection_AsciiString& theUnits);

  Standard_EXPORT void SetDimAngleDisplayUnits(const TCollection_AsciiString& theUnits);

  const TCollection_AsciiString& DimLengthDisplayUnits() const
  {
    return myHasOwnDimLengthDisplayUnits || myLink.IsNull()
             ? myDimensionDisplayUnits.GetLengthUnits()
             : myLink->DimLengthDisplayUnits();
  }

  const TCollection_AsciiString& DimAngleDisplayUnits() const
  {
    return myHasOwnDimAngleDisplayUnits || myLink.IsNull() ? myDimensionDisplayUnits.GetAngleUnits()
                                                           : myLink->DimAngleDisplayUnits();
  }

  bool HasOwnDimLengthDisplayUnits() const { return myHasOwnDimLengthDisplayUnits; }

  void UnsetOwnDimLengthDisplayUnits()
  {
    myHasOwnDimLengthDisplayUnits = false;
    myDimensionDisplayUnits.SetLengthUnits("m");
  }

  bool HasOwnDimAngleDisplayUnits() const { return myHasOwnDimAngleDisplayUnits; }

  void UnsetOwnDimAngleDisplayUnits()
  {
    myHasOwnDimAngleDisplayUnits = false;
    myDimensionDisplayUnits.SetAngleUnits("deg");
  }

public:
  const occ::handle<Prs3d_Drawer>& Link() const { return myLink; }

  bool HasLink() const { return !myLink.IsNull(); }

  void Link(const occ::handle<Prs3d_Drawer>& theDrawer) { SetLink(theDrawer); }

  void SetLink(const occ::handle<Prs3d_Drawer>& theDrawer) { myLink = theDrawer; }

  Standard_EXPORT void ClearLocalAttributes();

  Standard_EXPORT bool SetShaderProgram(const occ::handle<Graphic3d_ShaderProgram>& theProgram,
                                        const Graphic3d_GroupAspect                 theAspect,
                                        const bool theToOverrideDefaults = false);

  Standard_EXPORT bool SetShadingModel(Graphic3d_TypeOfShadingModel theModel,
                                       bool                         theToOverrideDefaults = false);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

public:
  Standard_DEPRECATED("SetDeviationAngle() should be used instead")

  void SetHLRAngle(const double theAngle) { SetDeviationAngle(theAngle); }

  Standard_DEPRECATED("DeviationAngle() should be used instead")

  double HLRAngle() const { return DeviationAngle(); }

  Standard_DEPRECATED("SetDeviationAngle() should be used instead")

  void SetHLRAngle() { SetDeviationAngle(); }

  Standard_DEPRECATED("HasOwnDeviationAngle() should be used instead")

  bool HasOwnHLRDeviationAngle() const { return HasOwnDeviationAngle(); }

  Standard_DEPRECATED("PreviousDeviationAngle() should be used instead")

  double PreviousHLRDeviationAngle() const { return PreviousDeviationAngle(); }

protected:
  occ::handle<Prs3d_Drawer> myLink;

  int                     myNbPoints;
  double                  myMaximalParameterValue;
  double                  myChordialDeviation;
  Aspect_TypeOfDeflection myTypeOfDeflection;
  bool                    myHasOwnTypeOfDeflection;
  Prs3d_TypeOfHLR         myTypeOfHLR;
  double                  myDeviationCoefficient;
  double                  myPreviousDeviationCoefficient;
  double                  myDeviationAngle;
  double                  myPreviousDeviationAngle;
  bool                    myIsoOnPlane;
  bool                    myHasOwnIsoOnPlane;
  bool                    myIsoOnTriangulation;
  bool                    myHasOwnIsoOnTriangulation;
  bool                    myIsAutoTriangulated;
  bool                    myHasOwnIsAutoTriangulated;

  occ::handle<Prs3d_IsoAspect>     myUIsoAspect;
  occ::handle<Prs3d_IsoAspect>     myVIsoAspect;
  occ::handle<Prs3d_LineAspect>    myWireAspect;
  bool                             myWireDraw;
  bool                             myHasOwnWireDraw;
  occ::handle<Prs3d_PointAspect>   myPointAspect;
  occ::handle<Prs3d_LineAspect>    myLineAspect;
  occ::handle<Prs3d_TextAspect>    myTextAspect;
  occ::handle<Prs3d_ShadingAspect> myShadingAspect;
  occ::handle<Prs3d_PlaneAspect>   myPlaneAspect;
  occ::handle<Prs3d_LineAspect>    mySeenLineAspect;
  occ::handle<Prs3d_ArrowAspect>   myArrowAspect;
  bool                             myLineArrowDraw;
  bool                             myHasOwnLineArrowDraw;
  occ::handle<Prs3d_LineAspect>    myHiddenLineAspect;
  bool                             myDrawHiddenLine;
  bool                             myHasOwnDrawHiddenLine;
  occ::handle<Prs3d_LineAspect>    myVectorAspect;
  Prs3d_VertexDrawMode             myVertexDrawMode;
  occ::handle<Prs3d_DatumAspect>   myDatumAspect;
  occ::handle<Prs3d_LineAspect>    mySectionAspect;

  occ::handle<Prs3d_LineAspect> myFreeBoundaryAspect;
  bool                          myFreeBoundaryDraw;
  bool                          myHasOwnFreeBoundaryDraw;
  occ::handle<Prs3d_LineAspect> myUnFreeBoundaryAspect;
  bool                          myUnFreeBoundaryDraw;
  bool                          myHasOwnUnFreeBoundaryDraw;
  occ::handle<Prs3d_LineAspect> myFaceBoundaryAspect;

  int myFaceBoundaryUpperContinuity;

  bool myFaceBoundaryDraw;
  bool myHasOwnFaceBoundaryDraw;

  occ::handle<Prs3d_DimensionAspect> myDimensionAspect;
  Prs3d_DimensionUnits               myDimensionModelUnits;
  bool                               myHasOwnDimLengthModelUnits;
  bool                               myHasOwnDimAngleModelUnits;
  Prs3d_DimensionUnits               myDimensionDisplayUnits;
  bool                               myHasOwnDimLengthDisplayUnits;
  bool                               myHasOwnDimAngleDisplayUnits;
};
