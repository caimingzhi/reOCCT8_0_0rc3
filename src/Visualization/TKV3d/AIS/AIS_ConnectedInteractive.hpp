#pragma once

#include <AIS_InteractiveObject.hpp>
#include <AIS_KindOfInteractive.hpp>
#include <TopoDS_Shape.hpp>

class AIS_ConnectedInteractive : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_ConnectedInteractive, AIS_InteractiveObject)
public:
  Standard_EXPORT AIS_ConnectedInteractive(
    const PrsMgr_TypeOfPresentation3d aTypeOfPresentation3d = PrsMgr_TOP_AllView);

  AIS_KindOfInteractive Type() const override { return AIS_KindOfInteractive_Object; }

  int Signature() const override { return 0; }

  void Connect(const occ::handle<AIS_InteractiveObject>& theAnotherObj)
  {
    connect(theAnotherObj, occ::handle<TopLoc_Datum3D>());
  }

  void Connect(const occ::handle<AIS_InteractiveObject>& theAnotherObj, const gp_Trsf& theLocation)
  {
    connect(theAnotherObj, new TopLoc_Datum3D(theLocation));
  }

  void Connect(const occ::handle<AIS_InteractiveObject>& theAnotherObj,
               const occ::handle<TopLoc_Datum3D>&        theLocation)
  {
    connect(theAnotherObj, theLocation);
  }

  bool HasConnection() const { return !myReference.IsNull(); }

  const occ::handle<AIS_InteractiveObject>& ConnectedTo() const { return myReference; }

  Standard_EXPORT void Disconnect();

  bool AcceptShapeDecomposition() const override
  {
    return !myReference.IsNull() && myReference->AcceptShapeDecomposition();
  }

  bool AcceptDisplayMode(const int theMode) const override
  {
    return myReference.IsNull() || myReference->AcceptDisplayMode(theMode);
  }

protected:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         theprs,
                               const int                                      theMode) override;

  Standard_EXPORT void computeHLR(const occ::handle<Graphic3d_Camera>&   theProjector,
                                  const occ::handle<TopLoc_Datum3D>&     theTrsf,
                                  const occ::handle<Prs3d_Presentation>& thePrs) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSelection,
                                        const int                               theMode) override;

  Standard_EXPORT void computeSubShapeSelection(
    const occ::handle<SelectMgr_Selection>& theSelection,
    const int                               theMode);

  Standard_EXPORT void updateShape(const bool WithLocation = true);

  Standard_EXPORT void connect(const occ::handle<AIS_InteractiveObject>& theAnotherObj,
                               const occ::handle<TopLoc_Datum3D>&        theLocation);

protected:
  occ::handle<AIS_InteractiveObject> myReference;
  TopoDS_Shape                       myShape;
};
