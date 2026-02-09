#pragma once

#include <Prs3d_ArrowAspect.hpp>
#include <Prs3d_DatumAttribute.hpp>

enum Prs3d_DatumAxes
{
  Prs3d_DatumAxes_XAxis   = 0x01,
  Prs3d_DatumAxes_YAxis   = 0x02,
  Prs3d_DatumAxes_ZAxis   = 0x04,
  Prs3d_DatumAxes_XYAxes  = Prs3d_DatumAxes_XAxis | Prs3d_DatumAxes_YAxis,
  Prs3d_DatumAxes_YZAxes  = Prs3d_DatumAxes_YAxis | Prs3d_DatumAxes_ZAxis,
  Prs3d_DatumAxes_XZAxes  = Prs3d_DatumAxes_XAxis | Prs3d_DatumAxes_ZAxis,
  Prs3d_DatumAxes_XYZAxes = Prs3d_DatumAxes_XAxis | Prs3d_DatumAxes_YAxis | Prs3d_DatumAxes_ZAxis,

  Prs3d_DA_XAxis   = Prs3d_DatumAxes_XAxis,
  Prs3d_DA_YAxis   = Prs3d_DatumAxes_YAxis,
  Prs3d_DA_ZAxis   = Prs3d_DatumAxes_ZAxis,
  Prs3d_DA_XYAxis  = Prs3d_DatumAxes_XYAxes,
  Prs3d_DA_YZAxis  = Prs3d_DatumAxes_YZAxes,
  Prs3d_DA_XZAxis  = Prs3d_DatumAxes_XZAxes,
  Prs3d_DA_XYZAxis = Prs3d_DatumAxes_XYZAxes
};

#include <Prs3d_DatumParts.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_PointAspect.hpp>
#include <Prs3d_ShadingAspect.hpp>
#include <Prs3d_TextAspect.hpp>

class Prs3d_DatumAspect : public Prs3d_BasicAspect
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_DatumAspect, Prs3d_BasicAspect)
public:
  Standard_EXPORT Prs3d_DatumAspect();

  const occ::handle<Prs3d_LineAspect>& LineAspect(Prs3d_DatumParts thePart) const
  {
    return myLineAspects[thePart];
  }

  const occ::handle<Prs3d_ShadingAspect>& ShadingAspect(Prs3d_DatumParts thePart) const
  {
    return myShadedAspects[thePart];
  }

  const occ::handle<Prs3d_TextAspect>& TextAspect(Prs3d_DatumParts thePart) const
  {
    return myTextAspects[thePart];
  }

  void SetTextAspect(const occ::handle<Prs3d_TextAspect>& theTextAspect)
  {
    myTextAspects[Prs3d_DatumParts_XAxis] = theTextAspect;
    myTextAspects[Prs3d_DatumParts_YAxis] = theTextAspect;
    myTextAspects[Prs3d_DatumParts_ZAxis] = theTextAspect;
  }

  const occ::handle<Prs3d_PointAspect>& PointAspect() const { return myPointAspect; }

  void SetPointAspect(const occ::handle<Prs3d_PointAspect>& theAspect)
  {
    myPointAspect = theAspect;
  }

  const occ::handle<Prs3d_ArrowAspect>& ArrowAspect() const { return myArrowAspect; }

  void SetArrowAspect(const occ::handle<Prs3d_ArrowAspect>& theAspect)
  {
    myArrowAspect = theAspect;
  }

  Standard_EXPORT bool DrawDatumPart(Prs3d_DatumParts thePart) const;

  void SetDrawDatumAxes(Prs3d_DatumAxes theType) { myAxes = theType; }

  Prs3d_DatumAxes DatumAxes() const { return myAxes; }

  double Attribute(Prs3d_DatumAttribute theType) const { return myAttributes[theType]; }

  void SetAttribute(Prs3d_DatumAttribute theType, const double theValue)
  {
    myAttributes[theType] = theValue;
  }

  Standard_EXPORT double AxisLength(Prs3d_DatumParts thePart) const;

  void SetAxisLength(double theL1, double theL2, double theL3)
  {
    myAttributes[Prs3d_DatumAttribute_XAxisLength] = theL1;
    myAttributes[Prs3d_DatumAttribute_YAxisLength] = theL2;
    myAttributes[Prs3d_DatumAttribute_ZAxisLength] = theL3;
  }

  bool ToDrawLabels() const { return myToDrawLabels; }

  void SetDrawLabels(bool theToDraw) { myToDrawLabels = theToDraw; }

  void SetToDrawLabels(bool theToDraw) { myToDrawLabels = theToDraw; }

  bool ToDrawArrows() const { return myToDrawArrows; }

  void SetDrawArrows(bool theToDraw) { myToDrawArrows = theToDraw; }

  Standard_EXPORT void CopyAspectsFrom(const occ::handle<Prs3d_DatumAspect>& theOther);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

public:
  Standard_EXPORT static Prs3d_DatumParts ArrowPartForAxis(Prs3d_DatumParts thePart);

public:
  Standard_DEPRECATED(
    "This method is deprecated - TextAspect() with axis parameter should be called instead")

  const occ::handle<Prs3d_TextAspect>& TextAspect() const
  {
    return myTextAspects[Prs3d_DatumParts_XAxis];
  }

protected:
  occ::handle<Prs3d_ShadingAspect> myShadedAspects[Prs3d_DatumParts_NB];
  occ::handle<Prs3d_LineAspect>    myLineAspects[Prs3d_DatumParts_NB];
  occ::handle<Prs3d_TextAspect>    myTextAspects[Prs3d_DatumParts_NB];
  occ::handle<Prs3d_PointAspect>   myPointAspect;
  occ::handle<Prs3d_ArrowAspect>   myArrowAspect;
  double                           myAttributes[Prs3d_DatumAttribute_NB];
  Prs3d_DatumAxes                  myAxes;
  bool                             myToDrawLabels;
  bool                             myToDrawArrows;
};
