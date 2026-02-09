

#include <BRep_Tool.hpp>
#include <ShapeAnalysis_ShapeTolerance.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>

ShapeAnalysis_ShapeTolerance::ShapeAnalysis_ShapeTolerance()
    : myNbTol(0)
{
}

static void AddTol(const double tol, int& nbt, double& cmin, double& cmoy, double& cmax)
{
  nbt++;
  if (nbt == 1)
    cmin = cmoy = cmax = tol;
  else
  {
    if (cmin > tol)
      cmin = tol;
    if (cmax < tol)
      cmax = tol;

    int mult = 1;

    nbt += (mult - 1);
    cmoy += (tol * mult);
  }
}

double ShapeAnalysis_ShapeTolerance::Tolerance(const TopoDS_Shape&    shape,
                                               const int              mode,
                                               const TopAbs_ShapeEnum type)
{
  InitTolerance();
  AddTolerance(shape, type);
  return GlobalTolerance(mode);
}

occ::handle<NCollection_HSequence<TopoDS_Shape>> ShapeAnalysis_ShapeTolerance::OverTolerance(
  const TopoDS_Shape&    shape,
  const double           value,
  const TopAbs_ShapeEnum type) const
{
  if (value >= 0)
    return InTolerance(shape, value, 0., type);
  else
    return InTolerance(shape, 0., value, type);
}

occ::handle<NCollection_HSequence<TopoDS_Shape>> ShapeAnalysis_ShapeTolerance::InTolerance(
  const TopoDS_Shape&    shape,
  const double           valmin,
  const double           valmax,
  const TopAbs_ShapeEnum type) const
{
  double                                           tol;
  bool                                             over = (valmax < valmin);
  occ::handle<NCollection_HSequence<TopoDS_Shape>> sl   = new NCollection_HSequence<TopoDS_Shape>();

  TopExp_Explorer myExp;

  if (type == TopAbs_FACE || type == TopAbs_SHAPE)
  {
    myExp.Init(shape, TopAbs_FACE);
    while (myExp.More())
    {
      tol = BRep_Tool::Tolerance(TopoDS::Face(myExp.Current()));
      if (tol >= valmin && (over || (tol <= valmax)))
        sl->Append(myExp.Current());
      myExp.Next();
    }
  }

  if (type == TopAbs_EDGE || type == TopAbs_SHAPE)
  {
    myExp.Init(shape, TopAbs_EDGE);
    while (myExp.More())
    {
      tol = BRep_Tool::Tolerance(TopoDS::Edge(myExp.Current()));
      if (tol >= valmin && (over || (tol <= valmax)))
        sl->Append(myExp.Current());
      myExp.Next();
    }
  }

  if (type == TopAbs_VERTEX || type == TopAbs_SHAPE)
  {
    myExp.Init(shape, TopAbs_VERTEX);
    while (myExp.More())
    {
      tol = BRep_Tool::Tolerance(TopoDS::Vertex(myExp.Current()));
      if (tol >= valmin && (over || (tol >= valmax)))
        sl->Append(myExp.Current());
      myExp.Next();
    }
  }

  if (type == TopAbs_SHELL)
  {

    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapface;
    myExp.Init(shape, TopAbs_SHELL);
    while (myExp.More())
    {
      bool         iashell = false;
      TopoDS_Shape ash     = myExp.Current();
      for (TopExp_Explorer face(ash, TopAbs_FACE); face.More(); face.Next())
      {
        mapface.Add(face.Current());
        occ::handle<NCollection_HSequence<TopoDS_Shape>> fc =
          InTolerance(face.Current(), valmin, valmax, type);
        if (fc->Length() > 0)
        {
          sl->Append(fc);
          iashell = true;
        }
      }
      if (iashell)
        sl->Append(ash);
      myExp.Next();
    }

    myExp.Init(shape, TopAbs_FACE);
    for (; myExp.More(); myExp.Next())
    {
      bool iaface = false;
      if (mapface.Contains(myExp.Current()))
        continue;
      tol = BRep_Tool::Tolerance(TopoDS::Face(myExp.Current()));
      if (tol >= valmin && (over || (tol <= valmax)))
        iaface = true;
      else
      {

        occ::handle<NCollection_HSequence<TopoDS_Shape>> fl =
          InTolerance(myExp.Current(), valmin, valmax, TopAbs_EDGE);
        if (fl->Length() > 0)
          iaface = true;
        else
        {
          fl = InTolerance(myExp.Current(), valmin, valmax, TopAbs_VERTEX);
          if (fl->Length() > 0)
            iaface = true;
        }
      }
      if (iaface)
        sl->Append(myExp.Current());
    }
  }

  return sl;
}

void ShapeAnalysis_ShapeTolerance::InitTolerance()
{
  myNbTol   = 0;
  myTols[1] = 0;
}

void ShapeAnalysis_ShapeTolerance::AddTolerance(const TopoDS_Shape&    shape,
                                                const TopAbs_ShapeEnum type)
{
  int    nbt = 0;
  double tol, cmin = 0., cmoy = 0., cmax = 0.;

  TopExp_Explorer myExp;

  if (type == TopAbs_FACE || type == TopAbs_SHAPE)
  {
    myExp.Init(shape, TopAbs_FACE);
    while (myExp.More())
    {
      tol = BRep_Tool::Tolerance(TopoDS::Face(myExp.Current()));
      AddTol(tol, nbt, cmin, cmoy, cmax);
      myExp.Next();
    }
  }

  if (type == TopAbs_EDGE || type == TopAbs_SHAPE)
  {
    myExp.Init(shape, TopAbs_EDGE);
    while (myExp.More())
    {
      tol = BRep_Tool::Tolerance(TopoDS::Edge(myExp.Current()));
      AddTol(tol, nbt, cmin, cmoy, cmax);
      myExp.Next();
    }
  }

  if (type == TopAbs_VERTEX || type == TopAbs_SHAPE)
  {
    myExp.Init(shape, TopAbs_VERTEX);
    while (myExp.More())
    {
      tol = BRep_Tool::Tolerance(TopoDS::Vertex(myExp.Current()));
      AddTol(tol, nbt, cmin, cmoy, cmax);
      myExp.Next();
    }
  }

  if (nbt == 0)
    return;
  if (myNbTol == 0 || myTols[0] > cmin)
    myTols[0] = cmin;
  if (myNbTol == 0 || myTols[2] < cmax)
    myTols[2] = cmax;
  myTols[1] += cmoy;
  myNbTol += nbt;
}

double ShapeAnalysis_ShapeTolerance::GlobalTolerance(const int mode) const
{

  double result = 0.;
  if (myNbTol != 0.)
  {
    if (mode < 0)
      result = myTols[0];
    else if (mode == 0)
    {
      if (myTols[0] == myTols[2])
        result = myTols[0];
      else
        result = myTols[1] / myNbTol;
    }
    else
      result = myTols[2];
  }

  return result;
}
