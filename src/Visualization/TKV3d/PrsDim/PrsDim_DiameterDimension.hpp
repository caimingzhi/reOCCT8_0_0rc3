#pragma once

#include <PrsDim_Dimension.hpp>
#include <gp_Pnt.hpp>
#include <gp_Circ.hpp>
#include <Standard.hpp>
#include <Standard_Macro.hpp>
#include <Standard_Type.hpp>

class PrsDim_DiameterDimension : public PrsDim_Dimension
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_DiameterDimension, PrsDim_Dimension)
public:
  Standard_EXPORT PrsDim_DiameterDimension(const gp_Circ& theCircle);

  Standard_EXPORT PrsDim_DiameterDimension(const gp_Circ& theCircle, const gp_Pln& thePlane);

  Standard_EXPORT PrsDim_DiameterDimension(const TopoDS_Shape& theShape);

  Standard_EXPORT PrsDim_DiameterDimension(const TopoDS_Shape& theShape, const gp_Pln& thePlane);

public:
  const gp_Circ& Circle() const { return myCircle; }

  Standard_EXPORT gp_Pnt AnchorPoint();

  const TopoDS_Shape& Shape() const { return myShape; }

public:
  Standard_EXPORT void SetMeasuredGeometry(const gp_Circ& theCircle);

  Standard_EXPORT void SetMeasuredGeometry(const TopoDS_Shape& theShape);

  Standard_EXPORT const TCollection_AsciiString& GetDisplayUnits() const override;

  Standard_EXPORT const TCollection_AsciiString& GetModelUnits() const override;

  Standard_EXPORT void SetDisplayUnits(const TCollection_AsciiString& theUnits) override;

  Standard_EXPORT void SetModelUnits(const TCollection_AsciiString& theUnits) override;

  Standard_EXPORT void SetTextPosition(const gp_Pnt& theTextPos) override;

  Standard_EXPORT gp_Pnt GetTextPosition() const override;

protected:
  Standard_EXPORT virtual void ComputeAnchorPoint();

  Standard_EXPORT virtual void ComputePlane();

  Standard_EXPORT bool CheckPlane(const gp_Pln& thePlane) const override;

  Standard_EXPORT double ComputeValue() const override;

  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePresentation,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeFlyoutSelection(
    const occ::handle<SelectMgr_Selection>&   theSelection,
    const occ::handle<SelectMgr_EntityOwner>& theEntityOwner) override;

protected:
  Standard_EXPORT void ComputeSidePoints(const gp_Circ& theCircle,
                                         gp_Pnt&        theFirstPnt,
                                         gp_Pnt&        theSecondPnt);

  Standard_EXPORT bool IsValidCircle(const gp_Circ& theCircle) const;

  Standard_EXPORT bool IsValidAnchor(const gp_Circ& theCircle, const gp_Pnt& thePnt) const;

private:
  gp_Circ      myCircle;
  gp_Pnt       myAnchorPoint;
  TopoDS_Shape myShape;
};
