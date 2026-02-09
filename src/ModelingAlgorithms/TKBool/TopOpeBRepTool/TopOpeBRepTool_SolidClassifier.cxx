#include <BRepClass3d_SolidClassifier.hpp>
#include <gp_Pnt.hpp>
#include <TopOpeBRepTool_SolidClassifier.hpp>

TopOpeBRepTool_SolidClassifier::TopOpeBRepTool_SolidClassifier()
{
  Clear();
}

TopOpeBRepTool_SolidClassifier::~TopOpeBRepTool_SolidClassifier()
{
  int i, aNb;

  aNb = myShapeClassifierMap.Extent();
  for (i = 1; i <= aNb; ++i)
  {
    void*                        anAddr = myShapeClassifierMap(i);
    BRepClass3d_SolidClassifier* pClsf  = (BRepClass3d_SolidClassifier*)anAddr;
    delete pClsf;
  }
  myShapeClassifierMap.Clear();
}

void TopOpeBRepTool_SolidClassifier::LoadSolid(const TopoDS_Solid& SOL)
{
  bool found = myShapeClassifierMap.Contains(SOL);

  if (!found)
  {
    myPClassifier = new BRepClass3d_SolidClassifier(SOL);
    myShapeClassifierMap.Add(SOL, (void*)myPClassifier);
  }
  else
  {
    myPClassifier = (BRepClass3d_SolidClassifier*)myShapeClassifierMap.ChangeFromKey(SOL);
  }
}

void TopOpeBRepTool_SolidClassifier::LoadShell(const TopoDS_Shell& SHE)
{
  bool found = myShapeClassifierMap.Contains(SHE);
  if (!found)
  {
    myBuilder.MakeSolid(mySolid);
    myBuilder.Add(mySolid, SHE);

    myPClassifier = new BRepClass3d_SolidClassifier(mySolid);
    myShapeClassifierMap.Add(SHE, (void*)myPClassifier);
  }
  else
  {
    myPClassifier = (BRepClass3d_SolidClassifier*)myShapeClassifierMap.ChangeFromKey(SHE);
  }
}

void TopOpeBRepTool_SolidClassifier::Clear()
{
  myPClassifier = nullptr;

  myShapeClassifierMap.Clear();

  myState = TopAbs_UNKNOWN;
  myShell.Nullify();
  mySolid.Nullify();
}

TopAbs_State TopOpeBRepTool_SolidClassifier::Classify(const TopoDS_Solid& SOL,
                                                      const gp_Pnt&       P,
                                                      const double        Tol)
{
  myPClassifier = nullptr;
  myState       = TopAbs_UNKNOWN;
  LoadSolid(SOL);
  if (myPClassifier == nullptr)
    return myState;
  myPClassifier->Perform(P, Tol);
  myState                  = myPClassifier->State();
  const TopoDS_Shape& fres = myPClassifier->Face();
  if (fres.IsNull())
  {

    return myState;
  }
  TopAbs_Orientation ofres = fres.Orientation();
  if (ofres == TopAbs_EXTERNAL)
  {
    if (myState == TopAbs_IN)
      myState = TopAbs_OUT;
    else if (myState == TopAbs_OUT)
      myState = TopAbs_OUT;
    else if (myState == TopAbs_ON)
      myState = TopAbs_ON;
    else if (myState == TopAbs_UNKNOWN)
      myState = TopAbs_OUT;
  }
  else if (ofres == TopAbs_INTERNAL)
  {
    if (myState == TopAbs_IN)
      myState = TopAbs_IN;
    else if (myState == TopAbs_OUT)
      myState = TopAbs_IN;
    else if (myState == TopAbs_ON)
      myState = TopAbs_ON;
    else if (myState == TopAbs_UNKNOWN)
      myState = TopAbs_IN;
  }
  return myState;
}

TopAbs_State TopOpeBRepTool_SolidClassifier::Classify(const TopoDS_Shell& SHE,
                                                      const gp_Pnt&       P,
                                                      const double        Tol)
{
  myPClassifier = nullptr;
  myState       = TopAbs_UNKNOWN;
  LoadShell(SHE);
  if (myPClassifier == nullptr)
    return myState;
  myPClassifier->Perform(P, Tol);
  myState = myPClassifier->State();
  return myState;
}

TopAbs_State TopOpeBRepTool_SolidClassifier::State() const
{
  return myState;
}
