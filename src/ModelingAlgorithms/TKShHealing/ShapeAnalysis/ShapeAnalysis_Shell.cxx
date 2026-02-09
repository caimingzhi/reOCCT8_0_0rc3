

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <ShapeAnalysis_Shell.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>

ShapeAnalysis_Shell::ShapeAnalysis_Shell()
    : myConex(false)
{
}

void ShapeAnalysis_Shell::Clear()
{
  myShells.Clear();
  myBad.Clear();
  myFree.Clear();
  myConex = false;
}

void ShapeAnalysis_Shell::LoadShells(const TopoDS_Shape& shape)
{
  if (shape.IsNull())
    return;

  if (shape.ShapeType() == TopAbs_SHELL)
    myShells.Add(shape);
  else
  {
    for (TopExp_Explorer exs(shape, TopAbs_SHELL); exs.More(); exs.Next())
    {
      const TopoDS_Shape& sh = exs.Current();
      myShells.Add(sh);
    }
  }
}

static bool CheckEdges(const TopoDS_Shape&                                            shape,
                       NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& bads,
                       NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& dirs,
                       NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& revs,
                       NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& ints)
{
  bool res = false;

  if (shape.ShapeType() != TopAbs_EDGE)
  {
    for (TopoDS_Iterator it(shape); it.More(); it.Next())
    {
      if (CheckEdges(it.Value(), bads, dirs, revs, ints))
        res = true;
    }
  }
  else
  {
    TopoDS_Edge E = TopoDS::Edge(shape);
    if (BRep_Tool::Degenerated(E))
      return false;

    if (shape.Orientation() == TopAbs_FORWARD)
    {

      if (dirs.FindIndex(shape) == 0)
        dirs.Add(shape);
      else
      {
        bads.Add(shape);
        res = true;
      }
    }
    if (shape.Orientation() == TopAbs_REVERSED)
    {

      if (revs.FindIndex(shape) == 0)
        revs.Add(shape);
      else
      {
        bads.Add(shape);
        res = true;
      }
    }
    if (shape.Orientation() == TopAbs_INTERNAL)
    {
      if (ints.FindIndex(shape) == 0)
        ints.Add(shape);
    }
  }

  return res;
}

bool ShapeAnalysis_Shell::CheckOrientedShells(const TopoDS_Shape& shape,
                                              const bool          alsofree,
                                              const bool          checkinternaledges)
{
  myConex = false;
  if (shape.IsNull())
    return false;
  bool res = false;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> dirs, revs, ints;
  for (TopExp_Explorer exs(shape, TopAbs_SHELL); exs.More(); exs.Next())
  {
    const TopoDS_Shape& sh = exs.Current();

    if (CheckEdges(sh, myBad, dirs, revs, ints))
      if (myShells.Add(sh))
        res = true;
  }

  if (!alsofree)
    return res;

  int nb = dirs.Extent();
  int i;
  for (i = 1; i <= nb; i++)
  {
    const TopoDS_Shape& sh = dirs.FindKey(i);
    if (!myBad.Contains(sh))
    {
      if (!revs.Contains(sh))
      {
        if (checkinternaledges)
        {
          if (!ints.Contains(sh))
          {
            myFree.Add(sh);
          }
          else
            myConex = true;
        }
        else
        {
          myFree.Add(sh);
        }
      }
      else
        myConex = true;
    }
    else
      myConex = true;
  }

  nb = revs.Extent();
  for (i = 1; i <= nb; i++)
  {
    const TopoDS_Shape& sh = revs.FindKey(i);
    if (!myBad.Contains(sh))
    {
      if (!dirs.Contains(sh))
      {
        if (checkinternaledges)
        {
          if (!ints.Contains(sh))
          {
            myFree.Add(sh);
          }
          else
            myConex = true;
        }
        else
        {
          myFree.Add(sh);
        }
      }
      else
        myConex = true;
    }
    else
      myConex = true;
  }

  return res;
}

bool ShapeAnalysis_Shell::IsLoaded(const TopoDS_Shape& shape) const
{
  if (shape.IsNull())
    return false;
  return myShells.Contains(shape);
}

int ShapeAnalysis_Shell::NbLoaded() const
{
  return myShells.Extent();
}

TopoDS_Shape ShapeAnalysis_Shell::Loaded(const int num) const
{
  return myShells.FindKey(num);
}

bool ShapeAnalysis_Shell::HasBadEdges() const
{
  return (myBad.Extent() > 0);
}

TopoDS_Compound ShapeAnalysis_Shell::BadEdges() const
{
  TopoDS_Compound C;
  BRep_Builder    B;
  B.MakeCompound(C);
  int n = myBad.Extent();
  for (int i = 1; i <= n; i++)
    B.Add(C, myBad.FindKey(i));
  return C;
}

bool ShapeAnalysis_Shell::HasFreeEdges() const
{
  return (myFree.Extent() > 0);
}

TopoDS_Compound ShapeAnalysis_Shell::FreeEdges() const
{
  TopoDS_Compound C;
  BRep_Builder    B;
  B.MakeCompound(C);
  int n = myFree.Extent();
  for (int i = 1; i <= n; i++)
    B.Add(C, myFree.FindKey(i));
  return C;
}

bool ShapeAnalysis_Shell::HasConnectedEdges() const
{
  return myConex;
}
