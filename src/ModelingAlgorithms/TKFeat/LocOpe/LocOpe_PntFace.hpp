#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
#include <TopoDS_Face.hpp>
#include <TopAbs_Orientation.hpp>
class gp_Pnt;
class TopoDS_Face;

class LocOpe_PntFace
{
public:
  DEFINE_STANDARD_ALLOC

  LocOpe_PntFace()
      : myPar(0.0),
        myUPar(0.0),
        myVPar(0.0)
  {
  }

  LocOpe_PntFace(const gp_Pnt&            P,
                 const TopoDS_Face&       F,
                 const TopAbs_Orientation Or,
                 const double             Param,
                 const double             UPar,
                 const double             VPar)
      : myPnt(P),
        myFace(F),
        myOri(Or),
        myPar(Param),
        myUPar(UPar),
        myVPar(VPar)
  {
  }

  const gp_Pnt& Pnt() const { return myPnt; }

  const TopoDS_Face& Face() const { return myFace; }

  TopAbs_Orientation Orientation() const { return myOri; }

  TopAbs_Orientation& ChangeOrientation() { return myOri; }

  double Parameter() const { return myPar; }

  double UParameter() const { return myUPar; }

  double VParameter() const { return myVPar; }

private:
  gp_Pnt             myPnt;
  TopoDS_Face        myFace;
  TopAbs_Orientation myOri;
  double             myPar;
  double             myUPar;
  double             myVPar;
};
