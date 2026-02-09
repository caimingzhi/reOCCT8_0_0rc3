#pragma once

#include <PrsDim_Dimension.hpp>
#include <gp_Pnt.hpp>
#include <gp_Circ.hpp>
#include <Standard.hpp>
#include <Standard_Macro.hpp>

class PrsDim_RadiusDimension : public PrsDim_Dimension
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_RadiusDimension, PrsDim_Dimension)
public:
  Standard_EXPORT PrsDim_RadiusDimension(const gp_Circ& theCircle);

  Standard_EXPORT PrsDim_RadiusDimension(const gp_Circ& theCircle, const gp_Pnt& theAnchorPoint);

  Standard_EXPORT PrsDim_RadiusDimension(const TopoDS_Shape& theShape);

public:
  const gp_Circ& Circle() const { return myCircle; }

  const gp_Pnt& AnchorPoint() const { return myAnchorPoint; }

  const TopoDS_Shape& Shape() const { return myShape; }

public:
  void SetMeasuredGeometry(const gp_Circ& theCircle)
  {
    SetMeasuredGeometry(theCircle, gp_Pnt(), false);
  }

  Standard_EXPORT void SetMeasuredGeometry(const gp_Circ& theCircle,
                                           const gp_Pnt&  theAnchorPoint,
                                           const bool     theHasAnchor = true);

  void SetMeasuredGeometry(const TopoDS_Shape& theShape)
  {
    SetMeasuredGeometry(theShape, gp_Pnt(), false);
  }

  Standard_EXPORT void SetMeasuredGeometry(const TopoDS_Shape& theShape,
                                           const gp_Pnt&       theAnchorPoint,
                                           const bool          theHasAnchor = true);

  Standard_EXPORT const TCollection_AsciiString& GetDisplayUnits() const override;

  Standard_EXPORT const TCollection_AsciiString& GetModelUnits() const override;

  Standard_EXPORT void SetDisplayUnits(const TCollection_AsciiString& theUnits) override;

  Standard_EXPORT void SetModelUnits(const TCollection_AsciiString& theUnits) override;

  Standard_EXPORT void SetTextPosition(const gp_Pnt& theTextPos) override;

  Standard_EXPORT gp_Pnt GetTextPosition() const override;

protected:
  Standard_EXPORT virtual void ComputePlane();

  Standard_EXPORT bool CheckPlane(const gp_Pln& thePlane) const override;

  Standard_EXPORT double ComputeValue() const override;

  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

protected:
  Standard_EXPORT bool IsValidCircle(const gp_Circ& theCircle) const;

  Standard_EXPORT bool IsValidAnchor(const gp_Circ& theCircle, const gp_Pnt& thePnt) const;

private:
  gp_Circ      myCircle;
  gp_Pnt       myAnchorPoint;
  TopoDS_Shape myShape;
};
