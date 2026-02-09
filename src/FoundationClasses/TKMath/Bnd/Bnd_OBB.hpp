#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Real.hpp>

#include <Bnd_Box.hpp>
#include <gp_Ax3.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Array1.hpp>

class Bnd_OBB
{
public:
  DEFINE_STANDARD_ALLOC

  Bnd_OBB()
      : myIsAABox(false)
  {
    myHDims[0] = myHDims[1] = myHDims[2] = -1.0;
  }

  Bnd_OBB(const gp_Pnt& theCenter,
          const gp_Dir& theXDirection,
          const gp_Dir& theYDirection,
          const gp_Dir& theZDirection,
          const double  theHXSize,
          const double  theHYSize,
          const double  theHZSize)
      : myCenter(theCenter.XYZ()),
        myIsAABox(false)
  {
    myAxes[0] = theXDirection.XYZ();
    myAxes[1] = theYDirection.XYZ();
    myAxes[2] = theZDirection.XYZ();

    Standard_ASSERT_VOID(theHXSize >= 0.0, "Negative value of X-size");
    Standard_ASSERT_VOID(theHYSize >= 0.0, "Negative value of Y-size");
    Standard_ASSERT_VOID(theHZSize >= 0.0, "Negative value of Z-size");

    myHDims[0] = theHXSize;
    myHDims[1] = theHYSize;
    myHDims[2] = theHZSize;
  }

  Bnd_OBB(const Bnd_Box& theBox)
      : myIsAABox(true)
  {
    if (theBox.IsVoid())
    {
      myHDims[0] = myHDims[1] = myHDims[2] = -1.0;
      myIsAABox                            = false;
      return;
    }

    double aX1, aY1, aZ1, aX2, aY2, aZ2;
    theBox.Get(aX1, aY1, aZ1, aX2, aY2, aZ2);

    myAxes[0].SetCoord(1.0, 0.0, 0.0);
    myAxes[1].SetCoord(0.0, 1.0, 0.0);
    myAxes[2].SetCoord(0.0, 0.0, 1.0);

    myHDims[0] = 0.5 * (aX2 - aX1);
    myHDims[1] = 0.5 * (aY2 - aY1);
    myHDims[2] = 0.5 * (aZ2 - aZ1);

    myCenter.SetCoord(0.5 * (aX2 + aX1), 0.5 * (aY2 + aY1), 0.5 * (aZ2 + aZ1));
  }

  Standard_EXPORT void ReBuild(const NCollection_Array1<gp_Pnt>& theListOfPoints,
                               const NCollection_Array1<double>* theListOfTolerances = nullptr,
                               const bool                        theIsOptimal        = false);

  void SetCenter(const gp_Pnt& theCenter) { myCenter = theCenter.XYZ(); }

  void SetXComponent(const gp_Dir& theXDirection, const double theHXSize)
  {
    Standard_ASSERT_VOID(theHXSize >= 0.0, "Negative value of X-size");

    myAxes[0]  = theXDirection.XYZ();
    myHDims[0] = theHXSize;
  }

  void SetYComponent(const gp_Dir& theYDirection, const double theHYSize)
  {
    Standard_ASSERT_VOID(theHYSize >= 0.0, "Negative value of Y-size");

    myAxes[1]  = theYDirection.XYZ();
    myHDims[1] = theHYSize;
  }

  void SetZComponent(const gp_Dir& theZDirection, const double theHZSize)
  {
    Standard_ASSERT_VOID(theHZSize >= 0.0, "Negative value of Z-size");

    myAxes[2]  = theZDirection.XYZ();
    myHDims[2] = theHZSize;
  }

  gp_Ax3 Position() const { return gp_Ax3(myCenter, ZDirection(), XDirection()); }

  const gp_XYZ& Center() const { return myCenter; }

  const gp_XYZ& XDirection() const { return myAxes[0]; }

  const gp_XYZ& YDirection() const { return myAxes[1]; }

  const gp_XYZ& ZDirection() const { return myAxes[2]; }

  double XHSize() const { return myHDims[0]; }

  double YHSize() const { return myHDims[1]; }

  double ZHSize() const { return myHDims[2]; }

  bool IsVoid() const { return ((myHDims[0] < 0.0) || (myHDims[1] < 0.0) || (myHDims[2] < 0.0)); }

  void SetVoid()
  {
    myHDims[0] = myHDims[1] = myHDims[2] = -1.0;
    myCenter = myAxes[0] = myAxes[1] = myAxes[2] = gp_XYZ();
    myIsAABox                                    = false;
  }

  void SetAABox(const bool& theFlag) { myIsAABox = theFlag; }

  bool IsAABox() const { return myIsAABox; }

  void Enlarge(const double theGapAdd)
  {
    const double aGap = std::abs(theGapAdd);
    myHDims[0] += aGap;
    myHDims[1] += aGap;
    myHDims[2] += aGap;
  }

  bool GetVertex(gp_Pnt theP[8]) const
  {
    if (IsVoid())
      return false;

    theP[0].SetXYZ(myCenter - myHDims[0] * myAxes[0] - myHDims[1] * myAxes[1]
                   - myHDims[2] * myAxes[2]);
    theP[1].SetXYZ(myCenter + myHDims[0] * myAxes[0] - myHDims[1] * myAxes[1]
                   - myHDims[2] * myAxes[2]);
    theP[2].SetXYZ(myCenter - myHDims[0] * myAxes[0] + myHDims[1] * myAxes[1]
                   - myHDims[2] * myAxes[2]);
    theP[3].SetXYZ(myCenter + myHDims[0] * myAxes[0] + myHDims[1] * myAxes[1]
                   - myHDims[2] * myAxes[2]);
    theP[4].SetXYZ(myCenter - myHDims[0] * myAxes[0] - myHDims[1] * myAxes[1]
                   + myHDims[2] * myAxes[2]);
    theP[5].SetXYZ(myCenter + myHDims[0] * myAxes[0] - myHDims[1] * myAxes[1]
                   + myHDims[2] * myAxes[2]);
    theP[6].SetXYZ(myCenter - myHDims[0] * myAxes[0] + myHDims[1] * myAxes[1]
                   + myHDims[2] * myAxes[2]);
    theP[7].SetXYZ(myCenter + myHDims[0] * myAxes[0] + myHDims[1] * myAxes[1]
                   + myHDims[2] * myAxes[2]);

    return true;
  }

  double SquareExtent() const
  {
    return 4.0 * (myHDims[0] * myHDims[0] + myHDims[1] * myHDims[1] + myHDims[2] * myHDims[2]);
  }

  Standard_EXPORT bool IsOut(const Bnd_OBB& theOther) const;

  Standard_EXPORT bool IsOut(const gp_Pnt& theP) const;

  Standard_EXPORT bool IsCompletelyInside(const Bnd_OBB& theOther) const;

  Standard_EXPORT void Add(const Bnd_OBB& theOther);

  Standard_EXPORT void Add(const gp_Pnt& theP);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  void ProcessOnePoint(const gp_Pnt& theP)
  {
    myIsAABox  = true;
    myHDims[0] = myHDims[1] = myHDims[2] = 0.0;
    myAxes[0].SetCoord(1.0, 0.0, 0.0);
    myAxes[1].SetCoord(0.0, 1.0, 0.0);
    myAxes[2].SetCoord(0.0, 0.0, 1.0);
    myCenter = theP.XYZ();
  }

private:
  gp_XYZ myCenter;

  gp_XYZ myAxes[3];

  double myHDims[3];

  bool myIsAABox;
};
