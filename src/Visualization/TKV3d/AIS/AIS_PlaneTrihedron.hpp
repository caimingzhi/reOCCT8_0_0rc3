#pragma once

#include <AIS_InteractiveObject.hpp>
#include <TCollection_AsciiString.hpp>

class AIS_Line;
class AIS_Point;
class Geom_Plane;

class AIS_PlaneTrihedron : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_PlaneTrihedron, AIS_InteractiveObject)
public:
  Standard_EXPORT AIS_PlaneTrihedron(const occ::handle<Geom_Plane>& aPlane);

  Standard_EXPORT occ::handle<Geom_Plane> Component();

  Standard_EXPORT void SetComponent(const occ::handle<Geom_Plane>& aPlane);

  Standard_EXPORT occ::handle<AIS_Line> XAxis() const;

  Standard_EXPORT occ::handle<AIS_Line> YAxis() const;

  Standard_EXPORT occ::handle<AIS_Point> Position() const;

  Standard_EXPORT void SetLength(const double theLength);

  Standard_EXPORT double GetLength() const;

  Standard_EXPORT bool AcceptDisplayMode(const int aMode) const override;

  int Signature() const override { return 4; }

  AIS_KindOfInteractive Type() const override { return AIS_KindOfInteractive_Datum; }

  Standard_EXPORT void SetColor(const Quantity_Color& theColor) override;

  void SetXLabel(const TCollection_AsciiString& theLabel) { myXLabel = theLabel; }

  void SetYLabel(const TCollection_AsciiString& theLabel) { myYLabel = theLabel; }

protected:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& theprsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

private:
  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

private:
  occ::handle<Geom_Plane>            myPlane;
  occ::handle<AIS_InteractiveObject> myShapes[3];
  TCollection_AsciiString            myXLabel;
  TCollection_AsciiString            myYLabel;
};
