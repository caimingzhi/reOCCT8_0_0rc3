#pragma once

#include <gp_Pnt.hpp>

struct SelectBasics_PickResult
{
public:
  static const SelectBasics_PickResult& Min(const SelectBasics_PickResult& thePickResult1,
                                            const SelectBasics_PickResult& thePickResult2)
  {
    return thePickResult1.Depth() <= thePickResult2.Depth() ? thePickResult1 : thePickResult2;
  }

public:
  SelectBasics_PickResult()
      : myObjPickedPnt(RealLast(), 0.0, 0.0),
        myDepth(RealLast()),
        myDistToCenter(RealLast())
  {
  }

  SelectBasics_PickResult(double theDepth, double theDistToCenter, const gp_Pnt& theObjPickedPnt)
      : myObjPickedPnt(theObjPickedPnt),
        myDepth(theDepth),
        myDistToCenter(theDistToCenter)
  {
  }

public:
  bool IsValid() const { return myDepth != RealLast(); }

  void Invalidate()
  {
    myDepth        = RealLast();
    myObjPickedPnt = gp_Pnt(RealLast(), 0.0, 0.0);
    myNormal.SetValues(0.0f, 0.0f, 0.0f);
  }

  double Depth() const { return myDepth; }

  void SetDepth(double theDepth) { myDepth = theDepth; }

  bool HasPickedPoint() const { return myObjPickedPnt.X() != RealLast(); }

  const gp_Pnt& PickedPoint() const { return myObjPickedPnt; }

  void SetPickedPoint(const gp_Pnt& theObjPickedPnt) { myObjPickedPnt = theObjPickedPnt; }

  double DistToGeomCenter() const { return myDistToCenter; }

  void SetDistToGeomCenter(double theDistToCenter) { myDistToCenter = theDistToCenter; }

  const NCollection_Vec3<float>& SurfaceNormal() const { return myNormal; }

  void SetSurfaceNormal(const NCollection_Vec3<float>& theNormal) { myNormal = theNormal; }

  void SetSurfaceNormal(const gp_Vec& theNormal)
  {
    myNormal.SetValues((float)theNormal.X(), (float)theNormal.Y(), (float)theNormal.Z());
  }

private:
  gp_Pnt                  myObjPickedPnt;
  NCollection_Vec3<float> myNormal;
  double                  myDepth;

  double myDistToCenter;
};
