#include <BRep_Builder.hpp>
#include <BRepTopAdaptor_FClass2d.hpp>
#include <Standard_Failure.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Wire.hpp>
#include <TopOpeBRepTool_face.hpp>

//=================================================================================================

TopOpeBRepTool_face::TopOpeBRepTool_face() = default;

static void FUN_reverse(const TopoDS_Face& f, TopoDS_Face& frev)
{
  BRep_Builder B;
  TopoDS_Shape aLocalShape = f.EmptyCopied();
  frev                     = TopoDS::Face(aLocalShape);
  //  frev = TopoDS::Face(f.EmptyCopied());
  TopoDS_Iterator it(f);
  while (it.More())
  {
    B.Add(frev, it.Value().Reversed());
    it.Next();
  }
}

//=================================================================================================

bool TopOpeBRepTool_face::Init(const TopoDS_Wire& W, const TopoDS_Face& Fref)
{
  myFfinite.Nullify();
  myW = W;

  // fres :
  //  TopoDS_Face fres;
  //  occ::handle<Geom_Surface> su = BRep_Tool::Surface(Fref);
  //  BRep_Builder B; B.MakeFace(fres,su,Precision::Confusion());
  TopoDS_Shape aLocalShape = Fref.EmptyCopied();
  TopoDS_Face  fres        = TopoDS::Face(aLocalShape);
  //  TopoDS_Face fres = TopoDS::Face(Fref.EmptyCopied());
  BRep_Builder B;
  B.Add(fres, W);
  B.NaturalRestriction(fres, true);

  // <myfinite> :
  BRepTopAdaptor_FClass2d FClass(fres, 0.);
  bool                    infinite = (FClass.PerformInfinitePoint() == TopAbs_IN);
  myfinite                         = !infinite;

  // <myFfinite> :
  if (myfinite)
    myFfinite = fres;
  else
    FUN_reverse(fres, myFfinite);
  return true;
}

//=================================================================================================

bool TopOpeBRepTool_face::IsDone() const
{
  return (!myFfinite.IsNull());
}

//=================================================================================================

bool TopOpeBRepTool_face::Finite() const
{
  if (!IsDone())
    throw Standard_Failure("TopOpeBRepTool_face NOT DONE");
  return myfinite;
}

//=================================================================================================

const TopoDS_Face& TopOpeBRepTool_face::Ffinite() const
{
  if (!IsDone())
    throw Standard_Failure("TopOpeBRepTool_face NOT DONE");
  return myFfinite;
}

//=================================================================================================

const TopoDS_Wire& TopOpeBRepTool_face::W() const
{
  return myW;
}

//=======================================================================
// function : TopoDS_Face&
// purpose  :
//=======================================================================

TopoDS_Face TopOpeBRepTool_face::RealF() const
{
  if (myfinite)
    return myFfinite;
  TopoDS_Face realf;
  FUN_reverse(myFfinite, realf);
  return realf;
}
