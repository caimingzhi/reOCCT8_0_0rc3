#pragma once

#include <Standard_Real.hpp>

struct DBRep_Params
{
public:
  int    NbIsos;
  double Size;
  int    Discretization;
  bool   DispTriangles;
  bool   DisplayPolygons;
  double HLRAngle;
  double HAngMin;
  double HAngMax;
  bool   WithHLR;
  bool   WithRg1;
  bool   WithRgN;
  bool   WithHid;

  DBRep_Params()
      : NbIsos(2),
        Size(100.0),
        Discretization(30),
        DispTriangles(false),
        DisplayPolygons(false),
        HLRAngle(35.0 * M_PI / 180.0),
        HAngMin(1.0 * M_PI / 180.0),
        HAngMax(35.0 * M_PI / 180.0),
        WithHLR(false),
        WithRg1(true),
        WithRgN(false),
        WithHid(false)
  {
  }
};

#include <Draw_Interpretor.hpp>
#include <TopoDS_Shape.hpp>

class DBRep
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Set(const char* Name, const TopoDS_Shape& S);

  static TopoDS_Shape Get(const char*&     theName,
                          TopAbs_ShapeEnum theType       = TopAbs_SHAPE,
                          bool             theToComplain = false)
  {
    return getShape(theName, theType, theToComplain);
  }

  static TopoDS_Shape Get(TCollection_AsciiString& theName,
                          TopAbs_ShapeEnum         theType       = TopAbs_SHAPE,
                          bool                     theToComplain = false)
  {
    const char*  aNamePtr = theName.ToCString();
    TopoDS_Shape aShape   = getShape(aNamePtr, theType, theToComplain);
    if (aNamePtr != theName.ToCString())
    {
      theName = aNamePtr;
    }
    return aShape;
  }

  static TopoDS_Shape GetExisting(const TCollection_AsciiString& theName,
                                  TopAbs_ShapeEnum               theType       = TopAbs_SHAPE,
                                  bool                           theToComplain = false)
  {
    if (theName.Length() == 1 && theName.Value(1) == '.')
    {
      return TopoDS_Shape();
    }

    const char* aNamePtr = theName.ToCString();
    return getShape(aNamePtr, theType, theToComplain);
  }

  Standard_EXPORT static void BasicCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static DBRep_Params& Parameters();

  static bool HLRMode() { return Parameters().WithHLR; }

  static bool Rg1Mode() { return Parameters().WithRg1; }

  static bool RgNMode() { return Parameters().WithRgN; }

  static bool HidMode() { return Parameters().WithHid; }

  static double HLRAngle() { return Parameters().HLRAngle; }

  static int NbIsos() { return Parameters().NbIsos; }

  static int Discretisation() { return Parameters().Discretization; }

protected:
  Standard_EXPORT static TopoDS_Shape getShape(const char*&     theName,
                                               TopAbs_ShapeEnum theType,
                                               bool             theToComplain);
};
