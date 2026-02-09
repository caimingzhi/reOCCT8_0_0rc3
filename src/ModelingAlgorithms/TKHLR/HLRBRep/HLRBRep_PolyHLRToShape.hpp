#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt2d.hpp>
#include <TopoDS_Shape.hpp>

class HLRBRep_BiPnt2D
{
public:
  DEFINE_STANDARD_ALLOC

  HLRBRep_BiPnt2D()
      : myRg1Line(false),
        myRgNLine(false),
        myOutLine(false),
        myIntLine(false)
  {
  }

  HLRBRep_BiPnt2D(const double        x1,
                  const double        y1,
                  const double        x2,
                  const double        y2,
                  const TopoDS_Shape& S,
                  const bool          reg1,
                  const bool          regn,
                  const bool          outl,
                  const bool          intl)
      : myP1(x1, y1),
        myP2(x2, y2),
        myShape(S),
        myRg1Line(reg1),
        myRgNLine(regn),
        myOutLine(outl),
        myIntLine(intl)
  {
  }

  HLRBRep_BiPnt2D(const gp_XY&        thePoint1,
                  const gp_XY&        thePoint2,
                  const TopoDS_Shape& S,
                  const bool          reg1,
                  const bool          regn,
                  const bool          outl,
                  const bool          intl)
      : myP1(thePoint1),
        myP2(thePoint2),
        myShape(S),
        myRg1Line(reg1),
        myRgNLine(regn),
        myOutLine(outl),
        myIntLine(intl)
  {
  }

  const gp_Pnt2d& P1() const { return myP1; }

  const gp_Pnt2d& P2() const { return myP2; }

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
  gp_Pnt2d     myP1;
  gp_Pnt2d     myP2;
  TopoDS_Shape myShape;
  bool         myRg1Line;
  bool         myRgNLine;
  bool         myOutLine;
  bool         myIntLine;
};

#include <NCollection_List.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
class HLRBRep_PolyAlgo;
class TopoDS_Shape;

class HLRBRep_PolyHLRToShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_PolyHLRToShape();

  Standard_EXPORT void Update(const occ::handle<HLRBRep_PolyAlgo>& A);

  void Show();

  void Hide();

  TopoDS_Shape VCompound();

  TopoDS_Shape VCompound(const TopoDS_Shape& S);

  TopoDS_Shape Rg1LineVCompound();

  TopoDS_Shape Rg1LineVCompound(const TopoDS_Shape& S);

  TopoDS_Shape RgNLineVCompound();

  TopoDS_Shape RgNLineVCompound(const TopoDS_Shape& S);

  TopoDS_Shape OutLineVCompound();

  TopoDS_Shape OutLineVCompound(const TopoDS_Shape& S);

  TopoDS_Shape HCompound();

  TopoDS_Shape HCompound(const TopoDS_Shape& S);

  TopoDS_Shape Rg1LineHCompound();

  TopoDS_Shape Rg1LineHCompound(const TopoDS_Shape& S);

  TopoDS_Shape RgNLineHCompound();

  TopoDS_Shape RgNLineHCompound(const TopoDS_Shape& S);

  TopoDS_Shape OutLineHCompound();

  TopoDS_Shape OutLineHCompound(const TopoDS_Shape& S);

private:
  Standard_EXPORT TopoDS_Shape InternalCompound(const int           typ,
                                                const bool          visible,
                                                const TopoDS_Shape& S);

  occ::handle<HLRBRep_PolyAlgo>     myAlgo;
  NCollection_List<HLRBRep_BiPnt2D> myBiPntVis;
  NCollection_List<HLRBRep_BiPnt2D> myBiPntHid;
  bool                              myHideMode;
};

#include <TopoDS_Shape.hpp>

inline void HLRBRep_PolyHLRToShape::Show()
{
  myHideMode = false;
}

inline void HLRBRep_PolyHLRToShape::Hide()
{
  myHideMode = true;
}

inline TopoDS_Shape HLRBRep_PolyHLRToShape::VCompound()
{
  return InternalCompound(4, true, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_PolyHLRToShape::VCompound(const TopoDS_Shape& S)
{
  return InternalCompound(4, true, S);
}

inline TopoDS_Shape HLRBRep_PolyHLRToShape::Rg1LineVCompound()
{
  return InternalCompound(2, true, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_PolyHLRToShape::Rg1LineVCompound(const TopoDS_Shape& S)
{
  return InternalCompound(2, true, S);
}

inline TopoDS_Shape HLRBRep_PolyHLRToShape::RgNLineVCompound()
{
  return InternalCompound(3, true, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_PolyHLRToShape::RgNLineVCompound(const TopoDS_Shape& S)
{
  return InternalCompound(3, true, S);
}

inline TopoDS_Shape HLRBRep_PolyHLRToShape::OutLineVCompound()
{
  return InternalCompound(1, true, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_PolyHLRToShape::OutLineVCompound(const TopoDS_Shape& S)
{
  return InternalCompound(1, true, S);
}

inline TopoDS_Shape HLRBRep_PolyHLRToShape::HCompound()
{
  return InternalCompound(4, false, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_PolyHLRToShape::HCompound(const TopoDS_Shape& S)
{
  return InternalCompound(4, false, S);
}

inline TopoDS_Shape HLRBRep_PolyHLRToShape::Rg1LineHCompound()
{
  return InternalCompound(2, false, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_PolyHLRToShape::Rg1LineHCompound(const TopoDS_Shape& S)
{
  return InternalCompound(2, false, S);
}

inline TopoDS_Shape HLRBRep_PolyHLRToShape::RgNLineHCompound()
{
  return InternalCompound(3, false, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_PolyHLRToShape::RgNLineHCompound(const TopoDS_Shape& S)
{
  return InternalCompound(3, false, S);
}

inline TopoDS_Shape HLRBRep_PolyHLRToShape::OutLineHCompound()
{
  return InternalCompound(1, false, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_PolyHLRToShape::OutLineHCompound(const TopoDS_Shape& S)
{
  return InternalCompound(1, false, S);
}
