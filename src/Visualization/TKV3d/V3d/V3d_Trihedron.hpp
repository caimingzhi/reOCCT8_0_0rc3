#pragma once

#include <Graphic3d_StructureManager.hpp>
#include <Graphic3d_TransformPers.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_ShadingAspect.hpp>
#include <Prs3d_TextAspect.hpp>
#include <V3d_TypeOfAxe.hpp>

class V3d_View;

class V3d_Trihedron : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(V3d_Trihedron, Standard_Transient)
public:
  Standard_EXPORT V3d_Trihedron();

  Standard_EXPORT ~V3d_Trihedron() override;

  bool IsWireframe() const { return myIsWireframe; }

  void SetWireframe(const bool theAsWireframe)
  {
    if (myIsWireframe != theAsWireframe)
    {
      invalidate();
      myIsWireframe = theAsWireframe;
    }
  }

  const occ::handle<Graphic3d_TransformPers> TransformPersistence() const
  {
    return myTransformPers;
  }

  Standard_EXPORT void SetPosition(const Aspect_TypeOfTriedronPosition thePosition);

  double Scale() const { return myScale; }

  Standard_EXPORT void SetScale(const double theScale);

  double SizeRatio() const { return myRatio; }

  Standard_EXPORT void SetSizeRatio(const double theRatio);

  double ArrowDiameter() const { return myDiameter; }

  Standard_EXPORT void SetArrowDiameter(const double theDiam);

  int NbFacets() const { return myNbFacettes; }

  Standard_EXPORT void SetNbFacets(const int theNbFacets);

  const occ::handle<Prs3d_TextAspect>& LabelAspect(V3d_TypeOfAxe theAxis) const
  {
    return myTextAspects[theAxis];
  }

  Standard_EXPORT void SetLabelsColor(const Quantity_Color& theXColor,
                                      const Quantity_Color& theYColor,
                                      const Quantity_Color& theZColor);

  Standard_EXPORT void SetLabelsColor(const Quantity_Color& theColor);

  const occ::handle<Prs3d_ShadingAspect>& ArrowAspect(V3d_TypeOfAxe theAxis) const
  {
    return myArrowShadingAspects[theAxis];
  }

  Standard_EXPORT void SetArrowsColor(const Quantity_Color& theXColor,
                                      const Quantity_Color& theYColor,
                                      const Quantity_Color& theZColor);

  const occ::handle<Prs3d_ShadingAspect>& OriginAspect() const { return mySphereShadingAspect; }

  const TCollection_AsciiString& Label(V3d_TypeOfAxe theAxis) const { return myLabels[theAxis]; }

  Standard_EXPORT void SetLabels(const TCollection_AsciiString& theX,
                                 const TCollection_AsciiString& theY,
                                 const TCollection_AsciiString& theZ);

  void Display(const occ::handle<V3d_View>& theView) { Display(*theView); }

  Standard_EXPORT void Display(const V3d_View& theView);

  Standard_EXPORT void Erase();

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  Standard_EXPORT void compute();

  void invalidate() { myToCompute = true; }

  Standard_EXPORT void setOffset2d();

private:
  class TrihedronStructure;

protected:
  occ::handle<Prs3d_ShadingAspect> mySphereShadingAspect;
  occ::handle<Prs3d_TextAspect>    myTextAspects[3];
  occ::handle<Prs3d_ShadingAspect> myArrowShadingAspects[3];
  TCollection_AsciiString          myLabels[3];

  occ::handle<Graphic3d_Structure>     myStructure;
  occ::handle<Graphic3d_TransformPers> myTransformPers;

  double myScale;
  double myRatio;
  double myDiameter;
  int    myNbFacettes;
  bool   myIsWireframe;
  bool   myToCompute;
};
