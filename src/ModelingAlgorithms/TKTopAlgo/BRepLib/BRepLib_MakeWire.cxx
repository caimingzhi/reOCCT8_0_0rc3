#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepLib_MakeWire.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>

BRepLib_MakeWire::BRepLib_MakeWire()
    : myError(BRepLib_EmptyWire)
{
}

BRepLib_MakeWire::BRepLib_MakeWire(const TopoDS_Edge& E)
{
  Add(E);
}

BRepLib_MakeWire::BRepLib_MakeWire(const TopoDS_Edge& E1, const TopoDS_Edge& E2)
{
  Add(E1);
  Add(E2);
}

BRepLib_MakeWire::BRepLib_MakeWire(const TopoDS_Edge& E1,
                                   const TopoDS_Edge& E2,
                                   const TopoDS_Edge& E3)
{
  Add(E1);
  Add(E2);
  Add(E3);
}

BRepLib_MakeWire::BRepLib_MakeWire(const TopoDS_Edge& E1,
                                   const TopoDS_Edge& E2,
                                   const TopoDS_Edge& E3,
                                   const TopoDS_Edge& E4)
{
  Add(E1);
  Add(E2);
  Add(E3);
  Add(E4);
}

BRepLib_MakeWire::BRepLib_MakeWire(const TopoDS_Wire& W)
{
  Add(W);
}

BRepLib_MakeWire::BRepLib_MakeWire(const TopoDS_Wire& W, const TopoDS_Edge& E)
{
  Add(W);
  Add(E);
}

void BRepLib_MakeWire::Add(const TopoDS_Wire& W)
{
  for (TopoDS_Iterator it(W); it.More(); it.Next())
  {
    Add(TopoDS::Edge(it.Value()));
    if (myError != BRepLib_WireDone)
      break;
  }
}

void BRepLib_MakeWire::Add(const TopoDS_Edge& E)
{
  Add(E, true);
}

void BRepLib_MakeWire::Add(const TopoDS_Edge& E, bool IsCheckGeometryProximity)
{

  bool forward = false;

  bool reverse = false;

  bool init = false;

  BRep_Builder    B;
  TopoDS_Iterator it;

  if (myEdge.IsNull())
  {
    init = true;

    B.MakeWire(TopoDS::Wire(myShape));

    myEdge = E;

    for (it.Initialize(myEdge); it.More(); it.Next())
      myVertices.Add(it.Value());
  }

  else
  {
    init                     = myShape.Closed();
    TopoDS_Shape aLocalShape = E.Oriented(TopAbs_FORWARD);
    TopoDS_Edge  EE          = TopoDS::Edge(aLocalShape);

    bool connected = false;
    bool copyedge  = false;

    if (myError != BRepLib_NonManifoldWire)
    {
      if (VF.IsNull() || VL.IsNull())
        myError = BRepLib_NonManifoldWire;
    }

    for (it.Initialize(EE); it.More(); it.Next())
    {

      const TopoDS_Vertex& VE = TopoDS::Vertex(it.Value());

      if (myVertices.Contains(VE))
      {
        connected = true;
        myVertex  = VE;
        if (myError != BRepLib_NonManifoldWire)
        {

          if (VF.IsSame(VL))
          {

            if (!VF.IsSame(VE))
              myError = BRepLib_NonManifoldWire;
          }
          else
          {
            if (VF.IsSame(VE))
            {
              if (VE.Orientation() == TopAbs_FORWARD)
                reverse = true;
              else
                forward = true;
            }
            else if (VL.IsSame(VE))
            {
              if (VE.Orientation() == TopAbs_REVERSED)
                reverse = true;
              else
                forward = true;
            }
            else
              myError = BRepLib_NonManifoldWire;
          }
        }
      }
      else if (IsCheckGeometryProximity)
      {

        gp_Pnt PE = BRep_Tool::Pnt(VE);

        for (int i = 1; i <= myVertices.Extent(); i++)
        {
          const TopoDS_Vertex& VW = TopoDS::Vertex(myVertices.FindKey(i));
          gp_Pnt               PW = BRep_Tool::Pnt(VW);
          double               l  = PE.Distance(PW);

          if ((l < BRep_Tool::Tolerance(VE)) || (l < BRep_Tool::Tolerance(VW)))
          {
            copyedge = true;
            if (myError != BRepLib_NonManifoldWire)
            {

              if (VF.IsSame(VL))
              {

                if (!VF.IsSame(VW))
                  myError = BRepLib_NonManifoldWire;
              }
              else
              {
                if (VF.IsSame(VW))
                {
                  if (VE.Orientation() == TopAbs_FORWARD)
                    reverse = true;
                  else
                    forward = true;
                }
                else if (VL.IsSame(VW))
                {
                  if (VE.Orientation() == TopAbs_REVERSED)
                    reverse = true;
                  else
                    forward = true;
                }
                else
                  myError = BRepLib_NonManifoldWire;
              }
            }
            break;
          }
        }
        if (copyedge)
        {
          connected = true;
        }
      }
    }

    if (!connected)
    {
      myError = BRepLib_DisconnectedWire;
      NotDone();
      return;
    }
    else
    {
      if (!copyedge)
      {
        myEdge = EE;
        for (it.Initialize(EE); it.More(); it.Next())
          myVertices.Add(it.Value());
      }
      else
      {

        TopoDS_Shape Dummy = EE.EmptyCopied();
        myEdge             = TopoDS::Edge(Dummy);

        for (it.Initialize(EE); it.More(); it.Next())
        {

          const TopoDS_Vertex& VE = TopoDS::Vertex(it.Value());
          gp_Pnt               PE = BRep_Tool::Pnt(VE);

          bool newvertex = false;
          for (int i = 1; i <= myVertices.Extent(); i++)
          {
            const TopoDS_Vertex& VW = TopoDS::Vertex(myVertices.FindKey(i));
            gp_Pnt               PW = BRep_Tool::Pnt(VW);
            double               l  = PE.Distance(PW), tolE, tolW;
            tolW                    = BRep_Tool::Tolerance(VW);
            tolE                    = BRep_Tool::Tolerance(VE);

            if ((l < tolE) || (l < tolW))
            {

              double maxtol = .5 * (tolW + tolE + l), cW, cE;
              if (maxtol > tolW && maxtol > tolE)
              {
                cW = (maxtol - tolE) / l;
                cE = 1. - cW;
              }
              else if (maxtol > tolW)
              {
                maxtol = tolE;
                cW     = 0.;
                cE     = 1.;
              }
              else
              {
                maxtol = tolW;
                cW     = 1.;
                cE     = 0.;
              }

              gp_Pnt PC(cW * PW.X() + cE * PE.X(),
                        cW * PW.Y() + cE * PE.Y(),
                        cW * PW.Z() + cE * PE.Z());

              B.UpdateVertex(VW, PC, maxtol);

              newvertex = true;
              myVertex  = VW;
              myVertex.Orientation(VE.Orientation());
              B.Add(myEdge, myVertex);
              B.Transfert(EE, myEdge, VE, myVertex);
              break;
            }
          }
          if (!newvertex)
          {
            myVertices.Add(VE);
            B.Add(myEdge, VE);
            B.Transfert(EE, myEdge, VE, VE);
          }
        }
      }
    }

    if (((forward == reverse) && (E.Orientation() == TopAbs_REVERSED)) || (reverse && !forward))
      myEdge.Reverse();
  }

  B.Add(myShape, myEdge);
  myShape.Closed(false);

  if (init)
    TopExp::Vertices(TopoDS::Wire(myShape), VF, VL);
  else
  {
    if (myError == BRepLib_WireDone)
    {
      TopoDS_Vertex V1, V2, VRef;
      TopExp::Vertices(myEdge, V1, V2);
      if (V1.IsSame(myVertex))
        VRef = V2;
      else if (V2.IsSame(myVertex))
        VRef = V1;
      else
      {
#ifdef OCCT_DEBUG
        std::cout << "MakeWire : There is a PROBLEM !!" << std::endl;
#endif
        myError = BRepLib_NonManifoldWire;
      }

      if (VF.IsSame(VL))
      {

#ifdef OCCT_DEBUG
        if (!VF.IsSame(myVertex))
          std::cout << "MakeWire : There is a PROBLEM !!" << std::endl;
#endif
      }
      else
      {
        if (VF.IsSame(myVertex))
          VF = VRef;
        else if (VL.IsSame(myVertex))
          VL = VRef;
        else
        {
#ifdef OCCT_DEBUG
          std::cout << "MakeWire : Y A UN PROBLEME !!" << std::endl;
#endif
          myError = BRepLib_NonManifoldWire;
        }
      }
    }
    if (myError == BRepLib_NonManifoldWire)
    {
      VF = VL = TopoDS_Vertex();
    }
  }

  if (!VF.IsNull() && !VL.IsNull() && VF.IsSame(VL))
    myShape.Closed(true);

  myError = BRepLib_WireDone;
  Done();
}

const TopoDS_Wire& BRepLib_MakeWire::Wire()
{
  return TopoDS::Wire(Shape());
}

const TopoDS_Edge& BRepLib_MakeWire::Edge() const
{
  return myEdge;
}

const TopoDS_Vertex& BRepLib_MakeWire::Vertex() const
{
  return myVertex;
}

BRepLib_MakeWire::operator TopoDS_Wire()
{
  return Wire();
}

BRepLib_WireError BRepLib_MakeWire::Error() const
{
  return myError;
}
