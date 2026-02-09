#pragma once

#include <Prs3d_LineAspect.hpp>

class Prs3d_PlaneAspect : public Prs3d_BasicAspect
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_PlaneAspect, Prs3d_BasicAspect)
public:
  Standard_EXPORT Prs3d_PlaneAspect();

  const occ::handle<Prs3d_LineAspect>& EdgesAspect() const { return myEdgesAspect; }

  const occ::handle<Prs3d_LineAspect>& IsoAspect() const { return myIsoAspect; }

  const occ::handle<Prs3d_LineAspect>& ArrowAspect() const { return myArrowAspect; }

  void SetArrowsLength(const double theLength) { myArrowsLength = theLength; }

  double ArrowsLength() const { return myArrowsLength; }

  void SetArrowsSize(const double theSize) { myArrowsSize = theSize; }

  double ArrowsSize() const { return myArrowsSize; }

  void SetArrowsAngle(const double theAngle) { myArrowsAngle = theAngle; }

  double ArrowsAngle() const { return myArrowsAngle; }

  void SetDisplayCenterArrow(const bool theToDraw) { myDrawCenterArrow = theToDraw; }

  bool DisplayCenterArrow() const { return myDrawCenterArrow; }

  void SetDisplayEdgesArrows(const bool theToDraw) { myDrawEdgesArrows = theToDraw; }

  bool DisplayEdgesArrows() const { return myDrawEdgesArrows; }

  void SetDisplayEdges(const bool theToDraw) { myDrawEdges = theToDraw; }

  bool DisplayEdges() const { return myDrawEdges; }

  void SetDisplayIso(const bool theToDraw) { myDrawIso = theToDraw; }

  bool DisplayIso() const { return myDrawIso; }

  void SetPlaneLength(const double theLX, const double theLY)
  {
    myPlaneXLength = theLX;
    myPlaneYLength = theLY;
  }

  double PlaneXLength() const { return myPlaneXLength; }

  double PlaneYLength() const { return myPlaneYLength; }

  void SetIsoDistance(const double theL) { myIsoDistance = theL; }

  double IsoDistance() const { return myIsoDistance; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  occ::handle<Prs3d_LineAspect> myEdgesAspect;
  occ::handle<Prs3d_LineAspect> myIsoAspect;
  occ::handle<Prs3d_LineAspect> myArrowAspect;
  double                        myArrowsLength;
  double                        myArrowsSize;
  double                        myArrowsAngle;
  double                        myPlaneXLength;
  double                        myPlaneYLength;
  double                        myIsoDistance;
  bool                          myDrawCenterArrow;
  bool                          myDrawEdgesArrows;
  bool                          myDrawEdges;
  bool                          myDrawIso;
};
