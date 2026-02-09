#include <BRepPrim_OneAxis.hpp>

#include <BRepPrim_Builder.hpp>
#include <gp_Ax2.hpp>
#include <gp_Circ.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <Standard_DomainError.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Vertex.hpp>

namespace
{

  constexpr double THE_PCURVE_OFFSET_FACTOR = 10.0;

  enum VertexIndex
  {
    VAXISTOP = 0,
    VAXISBOT,
    VTOPSTART,
    VTOPEND,
    VBOTSTART,
    VBOTEND,
    NBVERTICES
  };

  enum EdgeIndex
  {
    EAXIS = 0,
    ESTART,
    EEND,
    ETOPSTART,
    ETOPEND,
    EBOTSTART,
    EBOTEND,
    ETOP,
    EBOTTOM,
    NBEDGES
  };

  enum WireIndex
  {
    WLATERAL      = 0,
    WLATERALSTART = WLATERAL,
    WLATERALEND,
    WTOP,
    WBOTTOM,
    WSTART = 5,
    WAXISSTART,
    WEND,
    WAXISEND,
    NBWIRES
  };

  enum FaceIndex
  {
    FLATERAL = 0,
    FTOP,
    FBOTTOM,
    FSTART,
    FEND,
    NBFACES
  };

  static void BRepPrim_OneAxis_Check(const bool V[], const bool E[], const bool W[], const bool F[])
  {
    int i;
    for (i = 0; i < NBVERTICES; i++)
      if (V[i])
        throw Standard_DomainError();
    for (i = 0; i < NBEDGES; i++)
      if (E[i])
        throw Standard_DomainError();
    for (i = 0; i < NBWIRES; i++)
      if (W[i])
        throw Standard_DomainError();
    for (i = 0; i < NBFACES; i++)
      if (F[i])
        throw Standard_DomainError();
  }
} // namespace

BRepPrim_OneAxis::BRepPrim_OneAxis(const BRepPrim_Builder& B,
                                   const gp_Ax2&           A,
                                   const double            VMin,
                                   const double            VMax)
    : myBuilder(B),
      myAxes(A),
      myAngle(2 * M_PI),
      myVMin(VMin),
      myVMax(VMax),
      myMeridianOffset(0)

{

  int i;
  ShellBuilt = false;
  for (i = 0; i < NBVERTICES; i++)
    VerticesBuilt[i] = false;
  for (i = 0; i < NBEDGES; i++)
    EdgesBuilt[i] = false;
  for (i = 0; i < NBWIRES; i++)
    WiresBuilt[i] = false;
  for (i = 0; i < NBFACES; i++)
    FacesBuilt[i] = false;
}

BRepPrim_OneAxis::~BRepPrim_OneAxis() = default;

void BRepPrim_OneAxis::SetMeridianOffset(const double O)
{
  myMeridianOffset = O;
}

const gp_Ax2& BRepPrim_OneAxis::Axes() const
{
  return myAxes;
}

void BRepPrim_OneAxis::Axes(const gp_Ax2& A)
{
  BRepPrim_OneAxis_Check(VerticesBuilt, EdgesBuilt, WiresBuilt, FacesBuilt);
  myAxes = A;
}

double BRepPrim_OneAxis::Angle() const
{
  return myAngle;
}

void BRepPrim_OneAxis::Angle(const double A)
{
  BRepPrim_OneAxis_Check(VerticesBuilt, EdgesBuilt, WiresBuilt, FacesBuilt);
  myAngle = A;
}

double BRepPrim_OneAxis::VMin() const
{
  return myVMin;
}

void BRepPrim_OneAxis::VMin(const double V)
{
  BRepPrim_OneAxis_Check(VerticesBuilt, EdgesBuilt, WiresBuilt, FacesBuilt);
  myVMin = V;
}

double BRepPrim_OneAxis::VMax() const
{
  return myVMax;
}

void BRepPrim_OneAxis::VMax(const double V)
{
  BRepPrim_OneAxis_Check(VerticesBuilt, EdgesBuilt, WiresBuilt, FacesBuilt);
  myVMax = V;
}

bool BRepPrim_OneAxis::MeridianOnAxis(const double V) const
{
  return std::abs(MeridianValue(V).X()) < Precision::Confusion();
}

bool BRepPrim_OneAxis::MeridianClosed() const
{
  if (VMaxInfinite())
    return false;
  if (VMinInfinite())
    return false;
  return MeridianValue(myVMin).IsEqual(MeridianValue(myVMax), Precision::Confusion());
}

bool BRepPrim_OneAxis::VMaxInfinite() const
{
  return Precision::IsPositiveInfinite(myVMax);
}

bool BRepPrim_OneAxis::VMinInfinite() const
{
  return Precision::IsNegativeInfinite(myVMin);
}

bool BRepPrim_OneAxis::isHeightInverted() const
{
  if (VMaxInfinite() || VMinInfinite())
  {
    return false;
  }
  const double yMax = MeridianValue(myVMax).Y();
  const double yMin = MeridianValue(myVMin).Y();

  return yMax < yMin - Precision::Confusion();
}

bool BRepPrim_OneAxis::areHeightsEqual() const
{
  if (VMaxInfinite() || VMinInfinite())
  {
    return false;
  }
  const double yMax = MeridianValue(myVMax).Y();
  const double yMin = MeridianValue(myVMin).Y();
  return std::abs(yMax - yMin) < Precision::Confusion();
}

bool BRepPrim_OneAxis::HasTop() const
{
  if (VMaxInfinite())
    return false;
  if (MeridianClosed())
    return false;
  if (MeridianOnAxis(myVMax))
    return false;
  return true;
}

bool BRepPrim_OneAxis::HasBottom() const
{
  if (VMinInfinite())
    return false;
  if (MeridianClosed())
    return false;
  if (MeridianOnAxis(myVMin))
    return false;
  return true;
}

bool BRepPrim_OneAxis::HasSides() const
{
  return 2 * M_PI - myAngle > Precision::Angular();
}

const TopoDS_Shell& BRepPrim_OneAxis::Shell()
{
  if (!ShellBuilt)
  {
    myBuilder.MakeShell(myShell);

    myBuilder.AddShellFace(myShell, LateralFace());
    if (HasTop())
      myBuilder.AddShellFace(myShell, TopFace());
    if (HasBottom())
      myBuilder.AddShellFace(myShell, BottomFace());
    if (HasSides())
    {
      myBuilder.AddShellFace(myShell, StartFace());
      myBuilder.AddShellFace(myShell, EndFace());
    }

    myShell.Closed(BRep_Tool::IsClosed(myShell));
    myBuilder.CompleteShell(myShell);
    ShellBuilt = true;
  }
  return myShell;
}

const TopoDS_Face& BRepPrim_OneAxis::LateralFace()
{

  if (!FacesBuilt[FLATERAL])
  {

    myFaces[FLATERAL] = MakeEmptyLateralFace();

    if (VMaxInfinite() && VMinInfinite())
    {
      myBuilder.AddFaceWire(myFaces[FLATERAL], LateralStartWire());
      myBuilder.AddFaceWire(myFaces[FLATERAL], LateralEndWire());
    }
    else
      myBuilder.AddFaceWire(myFaces[FLATERAL], LateralWire());

    if (MeridianClosed())
    {

      myBuilder.SetPCurve(myEdges[ETOP],
                          myFaces[FLATERAL],
                          gp_Lin2d(gp_Pnt2d(0, myVMin), gp_Dir2d(gp_Dir2d::D::X)),
                          gp_Lin2d(gp_Pnt2d(0, myVMax), gp_Dir2d(gp_Dir2d::D::X)));
    }
    else
    {
      if (!VMaxInfinite())
      {
        myBuilder.SetPCurve(myEdges[ETOP],
                            myFaces[FLATERAL],
                            gp_Lin2d(gp_Pnt2d(0, myVMax), gp_Dir2d(gp_Dir2d::D::X)));
        if (!HasSides() || MeridianOnAxis(myVMax))
        {

          myBuilder.SetParameters(myEdges[ETOP], TopEndVertex(), 0., myAngle);
        }
      }
      if (!VMinInfinite())
      {
        myBuilder.SetPCurve(myEdges[EBOTTOM],
                            myFaces[FLATERAL],
                            gp_Lin2d(gp_Pnt2d(0, myVMin), gp_Dir2d(gp_Dir2d::D::X)));
        if (!HasSides() || MeridianOnAxis(myVMin))
        {

          myBuilder.SetParameters(myEdges[EBOTTOM], BottomEndVertex(), 0., myAngle);
        }
      }
    }
    if (HasSides())
    {
      myBuilder.SetPCurve(myEdges[ESTART],
                          myFaces[FLATERAL],
                          gp_Lin2d(gp_Pnt2d(0, -myMeridianOffset), gp_Dir2d(gp_Dir2d::D::Y)));

      myBuilder.SetPCurve(myEdges[EEND],
                          myFaces[FLATERAL],
                          gp_Lin2d(gp_Pnt2d(myAngle, -myMeridianOffset), gp_Dir2d(gp_Dir2d::D::Y)));
    }
    else
    {

      myBuilder.SetPCurve(myEdges[ESTART],
                          myFaces[FLATERAL],
                          gp_Lin2d(gp_Pnt2d(myAngle, -myMeridianOffset), gp_Dir2d(gp_Dir2d::D::Y)),
                          gp_Lin2d(gp_Pnt2d(0, -myMeridianOffset), gp_Dir2d(gp_Dir2d::D::Y)));
    }
    myBuilder.CompleteFace(myFaces[FLATERAL]);
    FacesBuilt[FLATERAL] = true;
  }
  return myFaces[FLATERAL];
}

const TopoDS_Face& BRepPrim_OneAxis::TopFace()
{

  if (!FacesBuilt[FTOP])
  {

    Standard_DomainError_Raise_if(!HasTop(), "BRepPrim_OneAxis::TopFace:No top face");

    double z = MeridianValue(myVMax).Y();
    gp_Vec V = myAxes.Direction();
    V.Multiply(z);
    myBuilder.MakeFace(myFaces[FTOP], gp_Pln(myAxes.Translated(V)));

    myBuilder.AddFaceWire(myFaces[FTOP], TopWire());

    myBuilder.SetPCurve(
      myEdges[ETOP],
      myFaces[FTOP],
      gp_Circ2d(gp_Ax2d(gp_Pnt2d(0, 0), gp_Dir2d(gp_Dir2d::D::X)), MeridianValue(myVMax).X()));
    if (HasSides())
    {
      myBuilder.SetPCurve(myEdges[ETOPSTART],
                          myFaces[FTOP],
                          gp_Lin2d(gp_Pnt2d(0, 0), gp_Dir2d(gp_Dir2d::D::X)));
      myBuilder.SetPCurve(myEdges[ETOPEND],
                          myFaces[FTOP],
                          gp_Lin2d(gp_Pnt2d(0, 0), gp_Dir2d(std::cos(myAngle), std::sin(myAngle))));
    }

    myBuilder.CompleteFace(myFaces[FTOP]);
    FacesBuilt[FTOP] = true;
  }

  return myFaces[FTOP];
}

const TopoDS_Face& BRepPrim_OneAxis::BottomFace()
{

  if (!FacesBuilt[FBOTTOM])
  {

    Standard_DomainError_Raise_if(!HasBottom(), "BRepPrim_OneAxis::BottomFace:No bottom face");

    double z = MeridianValue(myVMin).Y();
    gp_Vec V = myAxes.Direction();
    V.Multiply(z);
    gp_Ax2 axes = myAxes.Translated(V);
    myBuilder.MakeFace(myFaces[FBOTTOM], gp_Pln(axes));
    myBuilder.ReverseFace(myFaces[FBOTTOM]);
    myBuilder.AddFaceWire(myFaces[FBOTTOM], BottomWire());

    myBuilder.SetPCurve(
      myEdges[EBOTTOM],
      myFaces[FBOTTOM],
      gp_Circ2d(gp_Ax2d(gp_Pnt2d(0, 0), gp_Dir2d(gp_Dir2d::D::X)), MeridianValue(myVMin).X()));
    if (HasSides())
    {
      myBuilder.SetPCurve(myEdges[EBOTSTART],
                          myFaces[FBOTTOM],
                          gp_Lin2d(gp_Pnt2d(0, 0), gp_Dir2d(gp_Dir2d::D::X)));
      myBuilder.SetPCurve(myEdges[EBOTEND],
                          myFaces[FBOTTOM],
                          gp_Lin2d(gp_Pnt2d(0, 0), gp_Dir2d(std::cos(myAngle), std::sin(myAngle))));
    }

    myBuilder.CompleteFace(myFaces[FBOTTOM]);
    FacesBuilt[FBOTTOM] = true;
  }

  return myFaces[FBOTTOM];
}

const TopoDS_Face& BRepPrim_OneAxis::StartFace()
{

  if (!FacesBuilt[FSTART])
  {

    Standard_DomainError_Raise_if(!HasSides(), "BRepPrim_OneAxes::StartFace:No side faces");

    gp_Ax2 axes(myAxes.Location(), myAxes.YDirection().Reversed(), myAxes.XDirection());
    myBuilder.MakeFace(myFaces[FSTART], gp_Pln(axes));

    if (isHeightInverted() || (areHeightsEqual() && !MeridianClosed()))
    {
      myBuilder.ReverseFace(myFaces[FSTART]);
    }

    if (VMaxInfinite() && VMinInfinite())
      myBuilder.AddFaceWire(myFaces[FSTART], AxisStartWire());

    myBuilder.AddFaceWire(myFaces[FSTART], StartWire());

    SetMeridianPCurve(myEdges[ESTART], myFaces[FSTART]);

    if (EdgesBuilt[EAXIS] && !areHeightsEqual())
      myBuilder.SetPCurve(myEdges[EAXIS],
                          myFaces[FSTART],
                          gp_Lin2d(gp_Pnt2d(0, 0), gp_Dir2d(gp_Dir2d::D::Y)));

    const double aPCurveOffset =
      areHeightsEqual() ? Precision::Confusion() * THE_PCURVE_OFFSET_FACTOR : 0.0;
    if (EdgesBuilt[ETOPSTART])
      myBuilder.SetPCurve(
        myEdges[ETOPSTART],
        myFaces[FSTART],
        gp_Lin2d(gp_Pnt2d(0, MeridianValue(myVMax).Y() + aPCurveOffset), gp_Dir2d(gp_Dir2d::D::X)));
    if (EdgesBuilt[EBOTSTART])
      myBuilder.SetPCurve(
        myEdges[EBOTSTART],
        myFaces[FSTART],
        gp_Lin2d(gp_Pnt2d(0, MeridianValue(myVMin).Y() - aPCurveOffset), gp_Dir2d(gp_Dir2d::D::X)));

    myBuilder.CompleteFace(myFaces[FSTART]);
    FacesBuilt[FSTART] = true;
  }

  return myFaces[FSTART];
}

const TopoDS_Face& BRepPrim_OneAxis::EndFace()
{

  if (!FacesBuilt[FEND])
  {

    Standard_DomainError_Raise_if(!HasSides(), "BRepPrim_OneAxes::EndFace:No side faces");

    gp_Ax2 axes(myAxes.Location(), myAxes.YDirection().Reversed(), myAxes.XDirection());
    axes.Rotate(myAxes.Axis(), myAngle);
    myBuilder.MakeFace(myFaces[FEND], gp_Pln(axes));

    if (!isHeightInverted() && (!areHeightsEqual() || MeridianClosed()))
    {
      myBuilder.ReverseFace(myFaces[FEND]);
    }

    if (VMaxInfinite() && VMinInfinite())
      myBuilder.AddFaceWire(myFaces[FEND], AxisEndWire());
    myBuilder.AddFaceWire(myFaces[FEND], EndWire());

    SetMeridianPCurve(myEdges[EEND], myFaces[FEND]);

    if (EdgesBuilt[EAXIS] && !areHeightsEqual())
      myBuilder.SetPCurve(myEdges[EAXIS],
                          myFaces[FEND],
                          gp_Lin2d(gp_Pnt2d(0, 0), gp_Dir2d(gp_Dir2d::D::Y)));

    const double aPCurveOffset =
      areHeightsEqual() ? Precision::Confusion() * THE_PCURVE_OFFSET_FACTOR : 0.0;
    if (EdgesBuilt[ETOPEND])
      myBuilder.SetPCurve(
        myEdges[ETOPEND],
        myFaces[FEND],
        gp_Lin2d(gp_Pnt2d(0, MeridianValue(myVMax).Y() + aPCurveOffset), gp_Dir2d(gp_Dir2d::D::X)));
    if (EdgesBuilt[EBOTEND])
      myBuilder.SetPCurve(
        myEdges[EBOTEND],
        myFaces[FEND],
        gp_Lin2d(gp_Pnt2d(0, MeridianValue(myVMin).Y() - aPCurveOffset), gp_Dir2d(gp_Dir2d::D::X)));

    myBuilder.CompleteFace(myFaces[FEND]);
    FacesBuilt[FEND] = true;
  }

  return myFaces[FEND];
}

const TopoDS_Wire& BRepPrim_OneAxis::LateralWire()
{

  if (!WiresBuilt[WLATERAL])
  {

    myBuilder.MakeWire(myWires[WLATERAL]);

    if (!VMaxInfinite())
      myBuilder.AddWireEdge(myWires[WLATERAL], TopEdge(), false);
    myBuilder.AddWireEdge(myWires[WLATERAL], EndEdge(), true);
    if (!VMinInfinite())
      myBuilder.AddWireEdge(myWires[WLATERAL], BottomEdge(), true);
    myBuilder.AddWireEdge(myWires[WLATERAL], StartEdge(), false);

    myBuilder.CompleteWire(myWires[WLATERAL]);
    WiresBuilt[WLATERAL] = true;
  }

  return myWires[WLATERAL];
}

const TopoDS_Wire& BRepPrim_OneAxis::LateralStartWire()
{

  if (!WiresBuilt[WLATERALSTART])
  {

    myBuilder.MakeWire(myWires[WLATERALSTART]);

    myBuilder.AddWireEdge(myWires[WLATERALSTART], StartEdge(), false);

    myBuilder.CompleteWire(myWires[WLATERALSTART]);
    WiresBuilt[WLATERALSTART] = true;
  }

  return myWires[WLATERALSTART];
}

const TopoDS_Wire& BRepPrim_OneAxis::LateralEndWire()
{

  if (!WiresBuilt[WLATERALEND])
  {

    myBuilder.MakeWire(myWires[WLATERALEND]);

    myBuilder.AddWireEdge(myWires[WLATERALEND], EndEdge(), true);

    myBuilder.CompleteWire(myWires[WLATERALEND]);
    WiresBuilt[WLATERALEND] = true;
  }

  return myWires[WLATERALEND];
}

const TopoDS_Wire& BRepPrim_OneAxis::TopWire()
{

  if (!WiresBuilt[WTOP])
  {

    Standard_DomainError_Raise_if(!HasTop(), "BRepPrim_OneAxis::TopWire: no top");

    myBuilder.MakeWire(myWires[WTOP]);

    myBuilder.AddWireEdge(myWires[WTOP], TopEdge(), true);
    if (HasSides())
    {
      myBuilder.AddWireEdge(myWires[WTOP], StartTopEdge(), true);
      myBuilder.AddWireEdge(myWires[WTOP], EndTopEdge(), false);
    }
    myBuilder.CompleteWire(myWires[WTOP]);
    WiresBuilt[WTOP] = true;
  }

  return myWires[WTOP];
}

const TopoDS_Wire& BRepPrim_OneAxis::BottomWire()
{

  if (!WiresBuilt[WBOTTOM])
  {

    Standard_DomainError_Raise_if(!HasBottom(), "BRepPrim_OneAxis::BottomWire: no bottom");

    myBuilder.MakeWire(myWires[WBOTTOM]);

    myBuilder.AddWireEdge(myWires[WBOTTOM], BottomEdge(), false);
    if (HasSides())
    {
      myBuilder.AddWireEdge(myWires[WBOTTOM], EndBottomEdge(), true);
      myBuilder.AddWireEdge(myWires[WBOTTOM], StartBottomEdge(), false);
    }

    myBuilder.CompleteWire(myWires[WBOTTOM]);
    WiresBuilt[WBOTTOM] = true;
  }

  return myWires[WBOTTOM];
}

const TopoDS_Wire& BRepPrim_OneAxis::StartWire()
{

  if (!WiresBuilt[WSTART])
  {

    Standard_DomainError_Raise_if(!HasSides(), "BRepPrim_OneAxes::StartWire:no sides");

    myBuilder.MakeWire(myWires[WSTART]);

    const bool isInverted   = isHeightInverted();
    const bool heightsEqual = areHeightsEqual();

    if (HasBottom())
      myBuilder.AddWireEdge(myWires[WSTART], StartBottomEdge(), true);

    if (!MeridianClosed() && !heightsEqual)
    {
      if (!VMaxInfinite() || !VMinInfinite())
        myBuilder.AddWireEdge(myWires[WSTART], AxisEdge(), isInverted);
    }

    if (HasTop())
      myBuilder.AddWireEdge(myWires[WSTART], StartTopEdge(), false);
    myBuilder.AddWireEdge(myWires[WSTART], StartEdge(), true);

    myBuilder.CompleteWire(myWires[WSTART]);
    WiresBuilt[WSTART] = true;
  }

  return myWires[WSTART];
}

const TopoDS_Wire& BRepPrim_OneAxis::AxisStartWire()
{

  if (!WiresBuilt[WAXISSTART])
  {

    Standard_DomainError_Raise_if(!HasSides(), "BRepPrim_OneAxes::AxisStartWire:no sides");

    Standard_DomainError_Raise_if(!VMaxInfinite() || !VMinInfinite(),
                                  "BRepPrim_OneAxes::AxisStartWire:not infinite");

    Standard_DomainError_Raise_if(MeridianClosed(),
                                  "BRepPrim_OneAxes::AxisStartWire:meridian closed");

    myBuilder.MakeWire(myWires[WAXISSTART]);

    myBuilder.AddWireEdge(myWires[WAXISSTART], AxisEdge(), false);

    myBuilder.CompleteWire(myWires[WAXISSTART]);
    WiresBuilt[WAXISSTART] = true;
  }

  return myWires[WAXISSTART];
}

const TopoDS_Wire& BRepPrim_OneAxis::EndWire()
{

  if (!WiresBuilt[WEND])
  {

    Standard_DomainError_Raise_if(!HasSides(), "BRepPrim_OneAxes::EndWire:no sides");

    myBuilder.MakeWire(myWires[WEND]);

    const bool isInverted   = isHeightInverted();
    const bool heightsEqual = areHeightsEqual();

    if (HasTop())
      myBuilder.AddWireEdge(myWires[WEND], EndTopEdge(), true);
    if (!MeridianClosed() && !heightsEqual)
    {
      if (!VMaxInfinite() || !VMinInfinite())
      {
        myBuilder.AddWireEdge(myWires[WEND], AxisEdge(), !isInverted);
      }
    }
    if (HasBottom())
      myBuilder.AddWireEdge(myWires[WEND], EndBottomEdge(), false);
    myBuilder.AddWireEdge(myWires[WEND], EndEdge(), false);

    myBuilder.CompleteWire(myWires[WEND]);
    WiresBuilt[WEND] = true;
  }
  return myWires[WEND];
}

const TopoDS_Wire& BRepPrim_OneAxis::AxisEndWire()
{

  if (!WiresBuilt[WAXISEND])
  {

    Standard_DomainError_Raise_if(!HasSides(), "BRepPrim_OneAxes::AxisEndWire:no sides");

    Standard_DomainError_Raise_if(!VMaxInfinite() || !VMinInfinite(),
                                  "BRepPrim_OneAxes::AxisEndWire:not infinite");

    Standard_DomainError_Raise_if(MeridianClosed(),
                                  "BRepPrim_OneAxes::AxisEndWire:meridian closed");

    myBuilder.MakeWire(myWires[WAXISEND]);

    myBuilder.AddWireEdge(myWires[WAXISEND], AxisEdge(), true);

    myBuilder.CompleteWire(myWires[WAXISEND]);
    WiresBuilt[WAXISEND] = true;
  }
  return myWires[WAXISEND];
}

const TopoDS_Edge& BRepPrim_OneAxis::AxisEdge()
{

  if (!EdgesBuilt[EAXIS])
  {

    Standard_DomainError_Raise_if(!HasSides(), "BRepPrim_OneAxis::AxisEdge:no sides");
    Standard_DomainError_Raise_if(MeridianClosed(), "BRepPrim_OneAxis::AxisEdge:closed");

    if (areHeightsEqual())
    {

      const double aHeight = MeridianValue(myVMax).Y();
      myBuilder.MakeDegeneratedEdge(myEdges[EAXIS]);
      myBuilder.AddEdgeVertex(myEdges[EAXIS], AxisTopVertex(), aHeight, aHeight);
    }
    else
    {

      myBuilder.MakeEdge(myEdges[EAXIS], gp_Lin(myAxes.Axis()));

      const bool   isInverted = isHeightInverted();
      const double yMax       = MeridianValue(myVMax).Y();
      const double yMin       = MeridianValue(myVMin).Y();

      if (!VMaxInfinite())
        myBuilder.AddEdgeVertex(myEdges[EAXIS], AxisTopVertex(), yMax, isInverted);
      if (!VMinInfinite())
        myBuilder.AddEdgeVertex(myEdges[EAXIS], AxisBottomVertex(), yMin, !isInverted);
    }

    myBuilder.CompleteEdge(myEdges[EAXIS]);
    EdgesBuilt[EAXIS] = true;
  }

  return myEdges[EAXIS];
}

const TopoDS_Edge& BRepPrim_OneAxis::StartEdge()
{

  if (!EdgesBuilt[ESTART])
  {

    if (!HasSides() && EdgesBuilt[EEND])
      myEdges[ESTART] = myEdges[EEND];

    else
    {

      myEdges[ESTART] = MakeEmptyMeridianEdge(0.);

      if (MeridianClosed())
      {

        myBuilder.AddEdgeVertex(myEdges[ESTART],
                                TopStartVertex(),
                                myVMin + myMeridianOffset,
                                myVMax + myMeridianOffset);
      }
      else
      {
        if (!VMaxInfinite())
        {
          myBuilder.AddEdgeVertex(myEdges[ESTART],
                                  TopStartVertex(),
                                  myVMax + myMeridianOffset,
                                  false);
        }
        if (!VMinInfinite())
        {
          myBuilder.AddEdgeVertex(myEdges[ESTART],
                                  BottomStartVertex(),
                                  myVMin + myMeridianOffset,
                                  true);
        }
      }
    }

    myBuilder.CompleteEdge(myEdges[ESTART]);
    EdgesBuilt[ESTART] = true;
  }

  return myEdges[ESTART];
}

const TopoDS_Edge& BRepPrim_OneAxis::EndEdge()
{

  if (!EdgesBuilt[EEND])
  {

    if (!HasSides() && EdgesBuilt[ESTART])
      myEdges[EEND] = myEdges[ESTART];

    else
    {

      myEdges[EEND] = MakeEmptyMeridianEdge(myAngle);

      if (MeridianClosed())
      {

        myBuilder.AddEdgeVertex(myEdges[EEND],
                                TopEndVertex(),
                                myVMin + myMeridianOffset,
                                myVMax + myMeridianOffset);
      }
      else
      {
        if (!VMaxInfinite())
        {
          myBuilder.AddEdgeVertex(myEdges[EEND], TopEndVertex(), myVMax + myMeridianOffset, false);
        }
        if (!VMinInfinite())
        {
          myBuilder.AddEdgeVertex(myEdges[EEND],
                                  BottomEndVertex(),
                                  myVMin + myMeridianOffset,
                                  true);
        }
      }
    }

    myBuilder.CompleteEdge(myEdges[EEND]);
    EdgesBuilt[EEND] = true;
  }

  return myEdges[EEND];
}

const TopoDS_Edge& BRepPrim_OneAxis::StartTopEdge()
{

  if (!EdgesBuilt[ETOPSTART])
  {

    Standard_DomainError_Raise_if(!HasTop() || !HasSides(),
                                  "BRepPrim_OneAxis::StartTopEdge:no sides or no top");

    gp_Vec V = myAxes.Direction();
    V.Multiply(MeridianValue(myVMax).Y());
    gp_Pnt P = myAxes.Location().Translated(V);
    myBuilder.MakeEdge(myEdges[ETOPSTART], gp_Lin(P, myAxes.XDirection()));

    myBuilder.AddEdgeVertex(myEdges[ETOPSTART], AxisTopVertex(), 0., true);
    myBuilder.AddEdgeVertex(myEdges[ETOPSTART], TopStartVertex(), MeridianValue(myVMax).X(), false);

    myBuilder.CompleteEdge(myEdges[ETOPSTART]);
    EdgesBuilt[ETOPSTART] = true;
  }

  return myEdges[ETOPSTART];
}

const TopoDS_Edge& BRepPrim_OneAxis::StartBottomEdge()
{

  if (!EdgesBuilt[EBOTSTART])
  {

    Standard_DomainError_Raise_if(!HasBottom() || !HasSides(),
                                  "BRepPrim_OneAxis::StartBottomEdge:no sides or no top");

    gp_Vec V = myAxes.Direction();
    V.Multiply(MeridianValue(myVMin).Y());
    gp_Pnt P = myAxes.Location().Translated(V);
    myBuilder.MakeEdge(myEdges[EBOTSTART], gp_Lin(P, myAxes.XDirection()));

    myBuilder.AddEdgeVertex(myEdges[EBOTSTART],
                            BottomStartVertex(),
                            MeridianValue(myVMin).X(),
                            false);
    myBuilder.AddEdgeVertex(myEdges[EBOTSTART], AxisBottomVertex(), 0., true);

    myBuilder.CompleteEdge(myEdges[EBOTSTART]);
    EdgesBuilt[EBOTSTART] = true;
  }

  return myEdges[EBOTSTART];
}

const TopoDS_Edge& BRepPrim_OneAxis::EndTopEdge()
{

  if (!EdgesBuilt[ETOPEND])
  {

    Standard_DomainError_Raise_if(!HasTop() || !HasSides(),
                                  "BRepPrim_OneAxis::EndTopEdge:no sides or no top");

    gp_Vec V = myAxes.Direction();
    V.Multiply(MeridianValue(myVMax).Y());
    gp_Pnt P = myAxes.Location().Translated(V);
    gp_Lin L(P, myAxes.XDirection());
    L.Rotate(myAxes.Axis(), myAngle);
    myBuilder.MakeEdge(myEdges[ETOPEND], L);

    myBuilder.AddEdgeVertex(myEdges[ETOPEND], AxisTopVertex(), 0., true);
    myBuilder.AddEdgeVertex(myEdges[ETOPEND], TopEndVertex(), MeridianValue(myVMax).X(), false);

    myBuilder.CompleteEdge(myEdges[ETOPEND]);
    EdgesBuilt[ETOPEND] = true;
  }

  return myEdges[ETOPEND];
}

const TopoDS_Edge& BRepPrim_OneAxis::EndBottomEdge()
{

  if (!EdgesBuilt[EBOTEND])
  {

    Standard_DomainError_Raise_if(!HasBottom() || !HasSides(),
                                  "BRepPrim_OneAxis::EndBottomEdge:no sides or no bottom");

    gp_Vec V = myAxes.Direction();
    V.Multiply(MeridianValue(myVMin).Y());
    gp_Pnt P = myAxes.Location().Translated(V);
    gp_Lin L(P, myAxes.XDirection());
    L.Rotate(myAxes.Axis(), myAngle);
    myBuilder.MakeEdge(myEdges[EBOTEND], L);

    myBuilder.AddEdgeVertex(myEdges[EBOTEND], AxisBottomVertex(), 0., true);
    myBuilder.AddEdgeVertex(myEdges[EBOTEND], BottomEndVertex(), MeridianValue(myVMin).X(), false);

    myBuilder.CompleteEdge(myEdges[EBOTEND]);
    EdgesBuilt[EBOTEND] = true;
  }

  return myEdges[EBOTEND];
}

const TopoDS_Edge& BRepPrim_OneAxis::TopEdge()
{

  if (!EdgesBuilt[ETOP])
  {

    if (MeridianClosed() && EdgesBuilt[EBOTTOM])
    {
      myEdges[ETOP] = myEdges[EBOTTOM];
    }

    else
    {

      if (!MeridianOnAxis(myVMax))
      {
        gp_Pnt2d mp = MeridianValue(myVMax);
        gp_Vec   V  = myAxes.Direction();
        V.Multiply(mp.Y());
        gp_Pnt  P = myAxes.Location().Translated(V);
        gp_Circ C(gp_Ax2(P, myAxes.Direction(), myAxes.XDirection()), mp.X());
        myBuilder.MakeEdge(myEdges[ETOP], C);
      }
      else
        myBuilder.MakeDegeneratedEdge(myEdges[ETOP]);

      if (!HasSides())
      {

        myBuilder.AddEdgeVertex(myEdges[ETOP], TopEndVertex(), 0., myAngle);
      }
      else
      {
        myBuilder.AddEdgeVertex(myEdges[ETOP], TopEndVertex(), myAngle, false);
        myBuilder.AddEdgeVertex(myEdges[ETOP], TopStartVertex(), 0., true);
      }
    }

    myBuilder.CompleteEdge(myEdges[ETOP]);
    EdgesBuilt[ETOP] = true;
  }

  return myEdges[ETOP];
}

const TopoDS_Edge& BRepPrim_OneAxis::BottomEdge()
{

  if (!EdgesBuilt[EBOTTOM])
  {

    if (MeridianClosed() && EdgesBuilt[ETOP])
    {
      myEdges[EBOTTOM] = myEdges[ETOP];
    }

    else
    {

      if (!MeridianOnAxis(myVMin))
      {
        gp_Pnt2d mp = MeridianValue(myVMin);
        gp_Vec   V  = myAxes.Direction();
        V.Multiply(mp.Y());
        gp_Pnt  P = myAxes.Location().Translated(V);
        gp_Circ C(gp_Ax2(P, myAxes.Direction(), myAxes.XDirection()), mp.X());
        myBuilder.MakeEdge(myEdges[EBOTTOM], C);
      }
      else
        myBuilder.MakeDegeneratedEdge(myEdges[EBOTTOM]);

      if (!HasSides())
      {

        myBuilder.AddEdgeVertex(myEdges[EBOTTOM], BottomEndVertex(), 0., myAngle);
      }
      else
      {
        myBuilder.AddEdgeVertex(myEdges[EBOTTOM], BottomEndVertex(), myAngle, false);
        myBuilder.AddEdgeVertex(myEdges[EBOTTOM], BottomStartVertex(), 0., true);
      }
    }

    myBuilder.CompleteEdge(myEdges[EBOTTOM]);
    EdgesBuilt[EBOTTOM] = true;
  }

  return myEdges[EBOTTOM];
}

const TopoDS_Vertex& BRepPrim_OneAxis::AxisTopVertex()
{

  if (!VerticesBuilt[VAXISTOP])
  {

    if (MeridianOnAxis(myVMax) && VerticesBuilt[VTOPSTART])
      myVertices[VAXISTOP] = myVertices[VTOPSTART];

    else if (MeridianOnAxis(myVMax) && VerticesBuilt[VTOPEND])
      myVertices[VAXISTOP] = myVertices[VTOPEND];

    else if (VerticesBuilt[VAXISBOT] && areHeightsEqual())
      myVertices[VAXISTOP] = myVertices[VAXISBOT];

    else
    {
      Standard_DomainError_Raise_if(MeridianClosed(), "BRepPrim_OneAxis::AxisTopVertex");
      Standard_DomainError_Raise_if(VMaxInfinite(), "BRepPrim_OneAxis::AxisTopVertex");

      gp_Vec V = myAxes.Direction();
      V.Multiply(MeridianValue(myVMax).Y());
      gp_Pnt P = myAxes.Location().Translated(V);
      myBuilder.MakeVertex(myVertices[VAXISTOP], P);
    }

    VerticesBuilt[VAXISTOP] = true;
  }

  return myVertices[VAXISTOP];
}

const TopoDS_Vertex& BRepPrim_OneAxis::AxisBottomVertex()
{

  if (!VerticesBuilt[VAXISBOT])
  {

    if (MeridianOnAxis(myVMin) && VerticesBuilt[VBOTSTART])
      myVertices[VAXISBOT] = myVertices[VBOTSTART];

    else if (MeridianOnAxis(myVMin) && VerticesBuilt[VBOTEND])
      myVertices[VAXISBOT] = myVertices[VBOTEND];

    else if (VerticesBuilt[VAXISTOP] && areHeightsEqual())
      myVertices[VAXISBOT] = myVertices[VAXISTOP];

    else
    {
      Standard_DomainError_Raise_if(MeridianClosed(), "BRepPrim_OneAxis::AxisBottomVertex");
      Standard_DomainError_Raise_if(VMinInfinite(), "BRepPrim_OneAxis::AxisBottomVertex");

      gp_Vec V = myAxes.Direction();
      V.Multiply(MeridianValue(myVMin).Y());
      gp_Pnt P = myAxes.Location().Translated(V);
      myBuilder.MakeVertex(myVertices[VAXISBOT], P);
    }

    VerticesBuilt[VAXISBOT] = true;
  }

  return myVertices[VAXISBOT];
}

const TopoDS_Vertex& BRepPrim_OneAxis::TopStartVertex()
{

  if (!VerticesBuilt[VTOPSTART])
  {

    if (MeridianOnAxis(myVMax) && VerticesBuilt[VAXISTOP])
      myVertices[VTOPSTART] = myVertices[VAXISTOP];
    else if ((MeridianOnAxis(myVMax) || !HasSides()) && VerticesBuilt[VTOPEND])
      myVertices[VTOPSTART] = myVertices[VTOPEND];
    else if (MeridianClosed() && VerticesBuilt[VBOTSTART])
      myVertices[VTOPSTART] = myVertices[VBOTSTART];
    else if ((MeridianClosed() && !HasSides()) && VerticesBuilt[VBOTEND])
      myVertices[VTOPSTART] = myVertices[VBOTEND];

    else
    {
      gp_Pnt2d mp = MeridianValue(myVMax);
      gp_Vec   V  = myAxes.Direction();
      V.Multiply(mp.Y());
      gp_Pnt P = myAxes.Location().Translated(V);
      V        = myAxes.XDirection();
      V.Multiply(mp.X());
      P.Translate(V);
      myBuilder.MakeVertex(myVertices[VTOPSTART], P);
    }

    VerticesBuilt[VTOPSTART] = true;
  }

  return myVertices[VTOPSTART];
}

const TopoDS_Vertex& BRepPrim_OneAxis::TopEndVertex()
{

  if (!VerticesBuilt[VTOPEND])
  {

    if (MeridianOnAxis(myVMax) && VerticesBuilt[VAXISTOP])
      myVertices[VTOPEND] = myVertices[VAXISTOP];
    else if ((MeridianOnAxis(myVMax) || !HasSides()) && VerticesBuilt[VTOPSTART])
      myVertices[VTOPEND] = myVertices[VTOPSTART];
    else if (MeridianClosed() && VerticesBuilt[VBOTEND])
      myVertices[VTOPEND] = myVertices[VBOTEND];
    else if ((MeridianClosed() && !HasSides()) && VerticesBuilt[VBOTSTART])
      myVertices[VTOPEND] = myVertices[VBOTSTART];

    else
    {
      gp_Pnt2d mp = MeridianValue(myVMax);
      gp_Vec   V  = myAxes.Direction();
      V.Multiply(mp.Y());
      gp_Pnt P = myAxes.Location().Translated(V);
      V        = myAxes.XDirection();
      V.Multiply(mp.X());
      P.Translate(V);
      P.Rotate(myAxes.Axis(), myAngle);
      myBuilder.MakeVertex(myVertices[VTOPEND], P);
    }

    VerticesBuilt[VTOPEND] = true;
  }

  return myVertices[VTOPEND];
}

const TopoDS_Vertex& BRepPrim_OneAxis::BottomStartVertex()
{

  if (!VerticesBuilt[VBOTSTART])
  {

    if (MeridianOnAxis(myVMin) && VerticesBuilt[VAXISBOT])
      myVertices[VBOTSTART] = myVertices[VAXISBOT];
    else if ((MeridianOnAxis(myVMin) || !HasSides()) && VerticesBuilt[VBOTEND])
      myVertices[VBOTSTART] = myVertices[VBOTEND];
    else if (MeridianClosed() && VerticesBuilt[VTOPSTART])
      myVertices[VBOTSTART] = myVertices[VTOPSTART];
    else if ((MeridianClosed() && !HasSides()) && VerticesBuilt[VTOPEND])
      myVertices[VBOTSTART] = myVertices[VTOPEND];

    else
    {
      gp_Pnt2d mp = MeridianValue(myVMin);
      gp_Vec   V  = myAxes.Direction();
      V.Multiply(mp.Y());
      gp_Pnt P = myAxes.Location().Translated(V);
      V        = myAxes.XDirection();
      V.Multiply(mp.X());
      P.Translate(V);
      myBuilder.MakeVertex(myVertices[VBOTSTART], P);
    }

    VerticesBuilt[VBOTSTART] = true;
  }

  return myVertices[VBOTSTART];
}

const TopoDS_Vertex& BRepPrim_OneAxis::BottomEndVertex()
{

  if (!VerticesBuilt[VBOTEND])
  {

    if (MeridianOnAxis(myVMin) && VerticesBuilt[VAXISBOT])
      myVertices[VBOTEND] = myVertices[VAXISBOT];
    else if ((MeridianOnAxis(myVMin) || !HasSides()) && VerticesBuilt[VBOTSTART])
      myVertices[VBOTEND] = myVertices[VBOTSTART];
    else if (MeridianClosed() && VerticesBuilt[VTOPEND])
      myVertices[VBOTEND] = myVertices[VTOPEND];
    else if (MeridianClosed() && !HasSides() && VerticesBuilt[VTOPSTART])
      myVertices[VBOTEND] = myVertices[VTOPSTART];

    else
    {
      gp_Pnt2d mp = MeridianValue(myVMin);
      gp_Vec   V  = myAxes.Direction();
      V.Multiply(mp.Y());
      gp_Pnt P = myAxes.Location().Translated(V);
      V        = myAxes.XDirection();
      V.Multiply(mp.X());
      P.Translate(V);
      P.Rotate(myAxes.Axis(), myAngle);
      myBuilder.MakeVertex(myVertices[VBOTEND], P);
    }

    VerticesBuilt[VBOTEND] = true;
  }

  return myVertices[VBOTEND];
}
