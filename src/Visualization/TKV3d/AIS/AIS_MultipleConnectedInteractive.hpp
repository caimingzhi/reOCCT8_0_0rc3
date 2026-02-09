#pragma once

#include <AIS_InteractiveObject.hpp>
#include <AIS_KindOfInteractive.hpp>

class AIS_MultipleConnectedInteractive : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_MultipleConnectedInteractive, AIS_InteractiveObject)
public:
  Standard_EXPORT AIS_MultipleConnectedInteractive();

  occ::handle<AIS_InteractiveObject> Connect(
    const occ::handle<AIS_InteractiveObject>&   theAnotherObj,
    const occ::handle<TopLoc_Datum3D>&          theLocation,
    const occ::handle<Graphic3d_TransformPers>& theTrsfPers)
  {
    return connect(theAnotherObj, theLocation, theTrsfPers);
  }

  AIS_KindOfInteractive Type() const override { return AIS_KindOfInteractive_Object; }

  int Signature() const override { return 1; }

  Standard_EXPORT bool HasConnection() const;

  Standard_EXPORT void Disconnect(const occ::handle<AIS_InteractiveObject>& theInteractive);

  Standard_EXPORT void DisconnectAll();

  Standard_EXPORT bool AcceptShapeDecomposition() const override;

  const occ::handle<SelectMgr_EntityOwner>& GetAssemblyOwner() const override
  {
    return myAssemblyOwner;
  }

  occ::handle<SelectMgr_EntityOwner> GlobalSelOwner() const override { return myAssemblyOwner; }

  Standard_EXPORT void SetContext(const occ::handle<AIS_InteractiveContext>& theCtx) override;

public:
  occ::handle<AIS_InteractiveObject> Connect(
    const occ::handle<AIS_InteractiveObject>& theAnotherObj)
  {
    return connect(theAnotherObj,
                   theAnotherObj->LocalTransformationGeom(),
                   theAnotherObj->TransformPersistence());
  }

  occ::handle<AIS_InteractiveObject> Connect(
    const occ::handle<AIS_InteractiveObject>& theAnotherObj,
    const gp_Trsf&                            theLocation)
  {
    return connect(theAnotherObj,
                   new TopLoc_Datum3D(theLocation),
                   theAnotherObj->TransformPersistence());
  }

  occ::handle<AIS_InteractiveObject> Connect(
    const occ::handle<AIS_InteractiveObject>&   theAnotherObj,
    const gp_Trsf&                              theLocation,
    const occ::handle<Graphic3d_TransformPers>& theTrsfPers)
  {
    return connect(theAnotherObj, new TopLoc_Datum3D(theLocation), theTrsfPers);
  }

protected:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT virtual occ::handle<AIS_InteractiveObject> connect(
    const occ::handle<AIS_InteractiveObject>&   theInteractive,
    const occ::handle<TopLoc_Datum3D>&          theLocation,
    const occ::handle<Graphic3d_TransformPers>& theTrsfPers);

private:
  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& aSelection,
                                        const int                               aMode) override;

protected:
  occ::handle<SelectMgr_EntityOwner> myAssemblyOwner;
};
