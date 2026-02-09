#include <BRepClass3d.hpp>

#include <BRep_Builder.hpp>
#include <BRepClass3d_SolidClassifier.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_State.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Solid.hpp>

static bool IsInternal(const TopoDS_Shell& aSx);

TopoDS_Shell BRepClass3d::OuterShell(const TopoDS_Solid& aSolid)
{
  bool                        bFound;
  double                      aTol;
  TopoDS_Solid                aSDx;
  TopoDS_Shell                aShell, aDummy;
  TopoDS_Iterator             aIt;
  BRep_Builder                aBB;
  BRepClass3d_SolidClassifier aSC;

  if (aSolid.IsNull())
  {
    return aDummy;
  }

  aTol   = 1.e-7;
  bFound = false;

  int aShellCounter = 0;
  for (aIt.Initialize(aSolid); aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aSx = aIt.Value();
    if (aSx.ShapeType() == TopAbs_SHELL)
    {
      aShell = *((TopoDS_Shell*)&aSx);
      aShellCounter++;
      if (aShellCounter >= 2)
        break;
    }
  }
  if (aShellCounter == 0)
  {
    return aDummy;
  }
  else if (aShellCounter == 1)
  {
    return aShell;
  }

  for (aIt.Initialize(aSolid); aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aSx = aIt.Value();
    if (aSx.ShapeType() == TopAbs_SHELL)
    {
      aShell = *((TopoDS_Shell*)&aSx);
      if (!IsInternal(aShell))
      {
        aSDx = aSolid;
        aSDx.EmptyCopy();
        aBB.Add(aSDx, aShell);

        aSC.Load(aSDx);
        aSC.PerformInfinitePoint(aTol);
        if (aSC.State() == TopAbs_OUT)
        {
          bFound = true;
          break;
        }
      }
    }
  }

  if (!bFound)
  {
    return aDummy;
  }

  return aShell;
}

bool IsInternal(const TopoDS_Shell& aSx)
{
  bool               bInternal;
  TopAbs_Orientation aOr;
  TopoDS_Iterator    aIt;

  bInternal = false;

  aIt.Initialize(aSx);
  if (aIt.More())
  {
    const TopoDS_Shape& aSy = aIt.Value();
    aOr                     = aSy.Orientation();
    bInternal               = (aOr == TopAbs_INTERNAL);
  }

  return bInternal;
}
