#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
#include <TopoDS_Shape.hpp>
class TopoDS_Shape;
class gp_Pnt;

class HLRBRep_BiPoint
{
public:
  DEFINE_STANDARD_ALLOC

  HLRBRep_BiPoint()
      : myRg1Line(false),
        myRgNLine(false),
        myOutLine(false),
        myIntLine(false)
  {
  }

  HLRBRep_BiPoint(const double        x1,
                  const double        y1,
                  const double        z1,
                  const double        x2,
                  const double        y2,
                  const double        z2,
                  const TopoDS_Shape& S,
                  const bool          reg1,
                  const bool          regn,
                  const bool          outl,
                  const bool          intl)
      : myP1(x1, y1, z1),
        myP2(x2, y2, z2),
        myShape(S),
        myRg1Line(reg1),
        myRgNLine(regn),
        myOutLine(outl),
        myIntLine(intl)
  {
  }

  const gp_Pnt& P1() const { return myP1; }

  const gp_Pnt& P2() const { return myP2; }

  const TopoDS_Shape& Shape() const { return myShape; }

  void Shape(const TopoDS_Shape& S) { myShape = S; }

  bool Rg1Line() const { return myRg1Line; }

  void Rg1Line(const bool B) { myRg1Line = B; }

  bool RgNLine() const { return myRgNLine; }

  void RgNLine(const bool B) { myRgNLine = B; }

  bool OutLine() const { return myOutLine; }

  void OutLine(const bool B) { myOutLine = B; }

  bool IntLine() const { return myIntLine; }

  void IntLine(const bool B) { myIntLine = B; }

private:
  gp_Pnt       myP1;
  gp_Pnt       myP2;
  TopoDS_Shape myShape;
  bool         myRg1Line;
  bool         myRgNLine;
  bool         myOutLine;
  bool         myIntLine;
};
