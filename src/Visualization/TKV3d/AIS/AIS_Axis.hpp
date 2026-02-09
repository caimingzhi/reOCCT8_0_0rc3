#pragma once

#include <AIS_InteractiveObject.hpp>

enum AIS_TypeOfAxis
{
  AIS_TOAX_Unknown,
  AIS_TOAX_XAxis,
  AIS_TOAX_YAxis,
  AIS_TOAX_ZAxis
};

#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <SelectMgr_Selection.hpp>

class Geom_Line;
class Geom_Axis1Placement;
class Geom_Axis2Placement;
class Prs3d_LineAspect;

class AIS_Axis : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_Axis, AIS_InteractiveObject)
public:
  Standard_EXPORT AIS_Axis(const occ::handle<Geom_Line>& aComponent);

  Standard_EXPORT AIS_Axis(const occ::handle<Geom_Axis2Placement>& aComponent,
                           const AIS_TypeOfAxis                    anAxisType);

  Standard_EXPORT AIS_Axis(const occ::handle<Geom_Axis1Placement>& anAxis);

  Standard_EXPORT AIS_Axis(const gp_Ax1& theAxis, const double theLength = -1);

  const occ::handle<Geom_Line>& Component() const { return myComponent; }

  Standard_EXPORT void SetComponent(const occ::handle<Geom_Line>& aComponent);

  const occ::handle<Geom_Axis2Placement>& Axis2Placement() const { return myAx2; }

  Standard_EXPORT void SetAxis2Placement(const occ::handle<Geom_Axis2Placement>& aComponent,
                                         const AIS_TypeOfAxis                    anAxisType);

  Standard_EXPORT void SetAxis1Placement(const occ::handle<Geom_Axis1Placement>& anAxis);

  AIS_TypeOfAxis TypeOfAxis() const { return myTypeOfAxis; }

  void SetTypeOfAxis(const AIS_TypeOfAxis theTypeAxis) { myTypeOfAxis = theTypeAxis; }

  bool IsXYZAxis() const { return myIsXYZAxis; }

  Standard_EXPORT bool AcceptDisplayMode(const int aMode) const override;

  int Signature() const override { return 2; }

  AIS_KindOfInteractive Type() const override { return AIS_KindOfInteractive_Datum; }

  Standard_EXPORT void SetColor(const Quantity_Color& aColor) override;

  Standard_EXPORT void SetWidth(const double aValue) override;

  Standard_EXPORT void SetDisplayAspect(const occ::handle<Prs3d_LineAspect>& theNewDatumAspect);

  Standard_EXPORT void UnsetColor() override;

  Standard_EXPORT void UnsetWidth() override;

private:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  Standard_EXPORT void ComputeFields();

private:
  occ::handle<Geom_Line>           myComponent;
  occ::handle<Geom_Axis2Placement> myAx2;
  gp_Pnt                           myPfirst;
  gp_Pnt                           myPlast;
  AIS_TypeOfAxis                   myTypeOfAxis;
  bool                             myIsXYZAxis;
  gp_Dir                           myDir;
  double                           myVal;
  const char*                      myText;
  occ::handle<Prs3d_LineAspect>    myLineAspect;
};
