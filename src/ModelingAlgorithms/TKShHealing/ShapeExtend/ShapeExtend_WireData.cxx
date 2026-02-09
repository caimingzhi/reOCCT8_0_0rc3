

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <Geom2d_Curve.hpp>
#include <ShapeExtend_WireData.hpp>
#include <Standard_Type.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeExtend_WireData, Standard_Transient)

ShapeExtend_WireData::ShapeExtend_WireData()
{
  Clear();
}

ShapeExtend_WireData::ShapeExtend_WireData(const TopoDS_Wire& wire,
                                           const bool         chained,
                                           const bool         theManifold)
{
  Init(wire, chained, theManifold);
}

void ShapeExtend_WireData::Init(const occ::handle<ShapeExtend_WireData>& other)
{
  Clear();
  int i, nb = other->NbEdges();
  for (i = 1; i <= nb; i++)
    Add(other->Edge(i));
  nb = other->NbNonManifoldEdges();
  for (i = 1; i <= nb; i++)
    Add(other->NonmanifoldEdge(i));
  myManifoldMode = other->ManifoldMode();
}

bool ShapeExtend_WireData::Init(const TopoDS_Wire& wire, const bool chained, const bool theManifold)
{
  Clear();
  myManifoldMode   = theManifold;
  bool          OK = true;
  TopoDS_Vertex Vlast;
  for (TopoDS_Iterator it(wire); it.More(); it.Next())
  {
    TopoDS_Edge E = TopoDS::Edge(it.Value());

    if ((E.Orientation() != TopAbs_REVERSED && E.Orientation() != TopAbs_FORWARD))
    {
      myNonmanifoldEdges->Append(E);
      continue;
    }

    TopoDS_Vertex V1, V2;
    for (TopoDS_Iterator itv(E); itv.More(); itv.Next())
    {
      TopoDS_Vertex V = TopoDS::Vertex(itv.Value());
      if (V.Orientation() == TopAbs_FORWARD)
        V1 = V;
      else if (V.Orientation() == TopAbs_REVERSED)
        V2 = V;
    }

    if (!Vlast.IsNull() && !Vlast.IsSame(V1) && theManifold)
    {
      OK = false;
      if (!chained)
        break;
    }
    Vlast = V2;
    if (wire.Orientation() == TopAbs_REVERSED)
      myEdges->Prepend(E);
    else
      myEdges->Append(E);
  }

  if (!myManifoldMode)
  {
    int nb = myNonmanifoldEdges->Length();
    int i  = 1;
    for (; i <= nb; i++)
      myEdges->Append(myNonmanifoldEdges->Value(i));
    myNonmanifoldEdges->Clear();
  }

  if (OK || chained)
    return OK;

  Clear();
  for (BRepTools_WireExplorer we(wire); we.More(); we.Next())
    myEdges->Append(TopoDS::Edge(we.Current()));

  return OK;
}

void ShapeExtend_WireData::Clear()
{
  myEdges            = new NCollection_HSequence<TopoDS_Shape>();
  myNonmanifoldEdges = new NCollection_HSequence<TopoDS_Shape>;
  mySeamF = mySeamR = -1;
  mySeams.Nullify();
  myManifoldMode = true;
}

void ShapeExtend_WireData::ComputeSeams(const bool enforce)
{
  if (mySeamF >= 0 && !enforce)
    return;

  mySeams = new NCollection_HSequence<int>();
  mySeamF = mySeamR = 0;
  TopoDS_Shape                                                  S;
  int                                                           i, nb = NbEdges();
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> ME;
  int*                                                          SE = new int[nb + 1];

  for (i = 1; i <= nb; i++)
  {
    S = Edge(i);
    if (S.Orientation() == TopAbs_REVERSED)
    {
      int num = ME.Add(S);
      SE[num] = i;
    }
  }

  for (i = 1; i <= nb; i++)
  {
    S = Edge(i);
    if (S.Orientation() == TopAbs_REVERSED)
      continue;
    int num = ME.FindIndex(S);
    if (num <= 0)
      continue;
    if (mySeamF == 0)
    {
      mySeamF = i;
      mySeamR = SE[num];
    }
    else
    {
      mySeams->Append(i);
      mySeams->Append(SE[num]);
    }
  }

  delete[] SE;
}

void ShapeExtend_WireData::SetLast(const int num)
{
  if (num == 0)
    return;
  int i, nb = NbEdges();
  for (i = nb; i > num; i--)
  {
    TopoDS_Edge edge = TopoDS::Edge(myEdges->Value(nb));
    myEdges->Remove(nb);
    myEdges->InsertBefore(1, edge);
  }
  mySeamF = -1;
}

void ShapeExtend_WireData::SetDegeneratedLast()
{
  int i, nb = NbEdges();
  for (i = 1; i <= nb; i++)
  {
    if (BRep_Tool::Degenerated(Edge(i)))
    {
      SetLast(i);
      return;
    }
  }
}

void ShapeExtend_WireData::Add(const TopoDS_Edge& edge, const int atnum)
{
  if (edge.Orientation() != TopAbs_REVERSED && edge.Orientation() != TopAbs_FORWARD
      && myManifoldMode)
  {
    myNonmanifoldEdges->Append(edge);
    return;
  }

  if (edge.IsNull())
    return;
  if (atnum == 0)
  {
    myEdges->Append(edge);
  }
  else
  {
    myEdges->InsertBefore(atnum, edge);
  }
  mySeamF = -1;
}

void ShapeExtend_WireData::Add(const TopoDS_Wire& wire, const int atnum)
{
  if (wire.IsNull())
    return;
  int                                n = atnum;
  NCollection_Sequence<TopoDS_Shape> aNMEdges;
  for (TopoDS_Iterator it(wire); it.More(); it.Next())
  {
    TopoDS_Edge edge = TopoDS::Edge(it.Value());
    if (edge.Orientation() != TopAbs_REVERSED && edge.Orientation() != TopAbs_FORWARD)
    {
      if (myManifoldMode)
        myNonmanifoldEdges->Append(edge);
      else
        aNMEdges.Append(edge);
      continue;
    }
    if (n == 0)
    {
      myEdges->Append(edge);
    }
    else
    {
      myEdges->InsertBefore(n, edge);
      n++;
    }
  }
  int i = 1, nb = aNMEdges.Length();
  for (; i <= nb; i++)
    myEdges->Append(aNMEdges.Value(i));
  mySeamF = -1;
}

void ShapeExtend_WireData::Add(const occ::handle<ShapeExtend_WireData>& wire, const int atnum)
{
  if (wire.IsNull())
    return;
  NCollection_Sequence<TopoDS_Shape> aNMEdges;
  int                                n = atnum;
  int                                i = 1;
  for (; i <= wire->NbEdges(); i++)
  {
    TopoDS_Edge aE = wire->Edge(i);
    if (aE.Orientation() == TopAbs_INTERNAL || aE.Orientation() == TopAbs_EXTERNAL)
    {
      aNMEdges.Append(aE);
      continue;
    }

    if (n == 0)
    {
      myEdges->Append(wire->Edge(i));
    }
    else
    {
      myEdges->InsertBefore(n, wire->Edge(i));
      n++;
    }
  }

  for (i = 1; i <= aNMEdges.Length(); i++)
    myEdges->Append(aNMEdges.Value(i));

  for (i = 1; i <= wire->NbNonManifoldEdges(); i++)
  {
    if (myManifoldMode)
      myNonmanifoldEdges->Append(wire->NonmanifoldEdge(i));
    else
    {
      if (n == 0)
        myEdges->Append(wire->Edge(i));

      else
      {
        myEdges->InsertBefore(n, wire->Edge(i));
        n++;
      }
    }
  }

  mySeamF = -1;
}

void ShapeExtend_WireData::Add(const TopoDS_Shape& shape, const int atnum)
{
  if (shape.ShapeType() == TopAbs_EDGE)
    Add(TopoDS::Edge(shape), atnum);
  else if (shape.ShapeType() == TopAbs_WIRE)
    Add(TopoDS::Wire(shape), atnum);
}

void ShapeExtend_WireData::AddOriented(const TopoDS_Edge& edge, const int mode)
{
  if (edge.IsNull() || mode < 0)
    return;
  TopoDS_Edge E = edge;
  if (mode == 1 || mode == 3)
    E.Reverse();
  Add(E, mode / 2);
}

void ShapeExtend_WireData::AddOriented(const TopoDS_Wire& wire, const int mode)
{
  if (wire.IsNull() || mode < 0)
    return;
  TopoDS_Wire W = wire;
  if (mode == 1 || mode == 3)
    W.Reverse();
  Add(W, mode / 2);
}

void ShapeExtend_WireData::AddOriented(const TopoDS_Shape& shape, const int mode)
{
  if (shape.ShapeType() == TopAbs_EDGE)
    AddOriented(TopoDS::Edge(shape), mode);
  else if (shape.ShapeType() == TopAbs_WIRE)
    AddOriented(TopoDS::Wire(shape), mode);
}

void ShapeExtend_WireData::Remove(const int num)
{

  myEdges->Remove(num > 0 ? num : NbEdges());

  mySeamF = -1;
}

void ShapeExtend_WireData::Set(const TopoDS_Edge& edge, const int num)
{
  if (edge.Orientation() != TopAbs_REVERSED && edge.Orientation() != TopAbs_FORWARD
      && myManifoldMode)
  {
    if (num <= myNonmanifoldEdges->Length())
      myNonmanifoldEdges->SetValue(num, edge);
    else
      myNonmanifoldEdges->Append(edge);
  }

  else
    myEdges->SetValue((num > 0 ? num : NbEdges()), edge);
  mySeamF = -1;
}

void ShapeExtend_WireData::Reverse()
{
  int i, nb = NbEdges();

  for (i = 1; i <= nb / 2; i++)
  {
    TopoDS_Shape S1 = myEdges->Value(i);
    S1.Reverse();
    TopoDS_Shape S2 = myEdges->Value(nb + 1 - i);
    S2.Reverse();
    myEdges->SetValue(i, S2);
    myEdges->SetValue(nb + 1 - i, S1);
  }

  if (nb % 2)
  {
    i               = (nb + 1) / 2;
    TopoDS_Shape SI = myEdges->Value(i);
    SI.Reverse();
    myEdges->SetValue(i, SI);
  }
  mySeamF = -1;
}

static void SwapSeam(const TopoDS_Shape& S, const TopoDS_Face& F)
{
  TopoDS_Edge E = TopoDS::Edge(S);
  if (E.IsNull() || F.IsNull())
    return;
  if (E.Orientation() == TopAbs_REVERSED)
    return;

  TopoDS_Face theface = F;
  theface.Orientation(TopAbs_FORWARD);

  occ::handle<Geom2d_Curve> c2df, c2dr;
  double                    uff, ulf, ufr, ulr;

  c2df = BRep_Tool::CurveOnSurface(E, theface, uff, ulf);
  E.Orientation(TopAbs_REVERSED);
  c2dr = BRep_Tool::CurveOnSurface(E, theface, ufr, ulr);
  if (c2df.IsNull() || c2dr.IsNull())
    return;

  E.Orientation(TopAbs_FORWARD);
  BRep_Builder B;
  B.UpdateEdge(E, c2dr, c2df, theface, 0.);
  B.Range(E, theface, uff, ulf);
}

void ShapeExtend_WireData::Reverse(const TopoDS_Face& face)
{
  Reverse();
  if (face.IsNull())
    return;

  ComputeSeams(true);
  if (mySeamF > 0)
    SwapSeam(myEdges->Value(mySeamF), face);
  if (mySeamR > 0)
    SwapSeam(myEdges->Value(mySeamR), face);
  int nb = (mySeams.IsNull() ? 0 : mySeams->Length());
  for (int i = 1; i <= nb; i++)
  {
    SwapSeam(myEdges->Value(mySeams->Value(i)), face);
  }
  mySeamF = -1;
}

int ShapeExtend_WireData::NbEdges() const
{
  return myEdges->Length();
}

TopoDS_Edge ShapeExtend_WireData::Edge(const int num) const
{
  if (num < 0)
  {
    TopoDS_Edge E = Edge(-num);
    E.Reverse();
    return E;
  }
  return TopoDS::Edge(myEdges->Value(num));
}

int ShapeExtend_WireData::NbNonManifoldEdges() const
{
  return myNonmanifoldEdges->Length();
}

TopoDS_Edge ShapeExtend_WireData::NonmanifoldEdge(const int num) const
{
  TopoDS_Edge E;
  if (num < 0)
    return E;

  return TopoDS::Edge(myNonmanifoldEdges->Value(num));
}

int ShapeExtend_WireData::Index(const TopoDS_Edge& edge)
{
  for (int i = 1; i <= NbEdges(); i++)
    if (Edge(i).IsSame(edge) && (Edge(i).Orientation() == edge.Orientation() || !IsSeam(i)))
      return i;
  return 0;
}

bool ShapeExtend_WireData::IsSeam(const int num)
{
  if (mySeamF < 0)
    ComputeSeams();
  if (mySeamF == 0)
    return false;

  if (num == mySeamF || num == mySeamR)
    return true;

  int i, nb = mySeams->Length();
  for (i = 1; i <= nb; i++)
  {
    if (num == mySeams->Value(i))
      return true;
  }
  return false;
}

TopoDS_Wire ShapeExtend_WireData::Wire() const
{
  TopoDS_Wire  W;
  BRep_Builder B;
  B.MakeWire(W);
  int  i, nb = NbEdges();
  bool ismanifold = true;
  for (i = 1; i <= nb; i++)
  {
    TopoDS_Edge aE = Edge(i);
    if (aE.Orientation() != TopAbs_FORWARD && aE.Orientation() != TopAbs_REVERSED)
      ismanifold = false;
    B.Add(W, aE);
  }
  if (ismanifold)
  {
    TopoDS_Vertex vf, vl;
    TopExp::Vertices(W, vf, vl);
    if (!vf.IsNull() && !vl.IsNull() && vf.IsSame(vl))
      W.Closed(true);
  }
  if (myManifoldMode)
  {
    nb = NbNonManifoldEdges();
    for (i = 1; i <= nb; i++)
      B.Add(W, NonmanifoldEdge(i));
  }
  return W;
}

TopoDS_Wire ShapeExtend_WireData::WireAPIMake() const
{
  TopoDS_Wire             W;
  BRepBuilderAPI_MakeWire MW;
  int                     i, nb = NbEdges();
  for (i = 1; i <= nb; i++)
    MW.Add(Edge(i));
  if (myManifoldMode)
  {
    nb = NbNonManifoldEdges();
    for (i = 1; i <= nb; i++)
      MW.Add(NonmanifoldEdge(i));
  }
  if (MW.IsDone())
    W = MW.Wire();
  return W;
}

occ::handle<NCollection_HSequence<TopoDS_Shape>> ShapeExtend_WireData::NonmanifoldEdges() const
{
  return myNonmanifoldEdges;
}

bool& ShapeExtend_WireData::ManifoldMode()
{
  return myManifoldMode;
}
