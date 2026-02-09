#include <BOPTest.hpp>

#include <BOPTools_AlgoTools.hpp>
#include <BOPTools_AlgoTools2D.hpp>
#include <DBRep.hpp>
#include <IntTools_Context.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopExp_Explorer.hpp>
#include <Draw.hpp>
#include <BOPAlgo_Tools.hpp>
#include <BRepLib.hpp>

static int attachpcurve(Draw_Interpretor&, int, const char**);
static int edgestowire(Draw_Interpretor&, int, const char**);
static int edgestofaces(Draw_Interpretor&, int, const char**);
static int BuildPcurvesOnPlane(Draw_Interpretor&, int, const char**);

void BOPTest::UtilityCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  const char* group = "BOPTest commands";

  theCommands.Add("attachpcurve", "attachpcurve eold enew face", __FILE__, attachpcurve, group);
  theCommands.Add("edgestowire", "edgestowire wire edges", __FILE__, edgestowire, group);
  theCommands.Add("edgestofaces",
                  "edgestofaces faces edges [-a AngTol -s Shared(0/1)]",
                  __FILE__,
                  edgestofaces,
                  group);
  theCommands.Add("buildpcurvesonplane",
                  "buildpcurvesonplane shape",
                  __FILE__,
                  BuildPcurvesOnPlane,
                  group);
}

static int attachpcurve(Draw_Interpretor& theDI, int theNArg, const char** theArgVal)
{
  if (theNArg != 4)
  {
    theDI << "Use: " << theArgVal[0] << " eold enew face\n";
    return 1;
  }

  TopoDS_Shape aShEOld(DBRep::Get(theArgVal[1]));
  TopoDS_Shape aShENew(DBRep::Get(theArgVal[2]));
  TopoDS_Shape aShFace(DBRep::Get(theArgVal[3]));

  if (aShEOld.IsNull())
  {
    theDI << theArgVal[1] << " is null shape\n";
    return 1;
  }
  else if (aShEOld.ShapeType() != TopAbs_EDGE)
  {
    theDI << theArgVal[1] << " is not an edge\n";
    return 1;
  }

  if (aShENew.IsNull())
  {
    theDI << theArgVal[2] << " is null shape\n";
    return 1;
  }
  else if (aShENew.ShapeType() != TopAbs_EDGE)
  {
    theDI << theArgVal[2] << " is not an edge\n";
    return 1;
  }

  if (aShFace.IsNull())
  {
    theDI << theArgVal[3] << " is null shape\n";
    return 1;
  }
  else if (aShFace.ShapeType() != TopAbs_FACE)
  {
    theDI << theArgVal[3] << " is not a face\n";
    return 1;
  }

  TopoDS_Edge aEOld = TopoDS::Edge(aShEOld);
  TopoDS_Edge aENew = TopoDS::Edge(aShENew);
  TopoDS_Face aFace = TopoDS::Face(aShFace);

  occ::handle<IntTools_Context> aCtx = new IntTools_Context;
  const int iRet = BOPTools_AlgoTools2D::AttachExistingPCurve(aEOld, aENew, aFace, aCtx);

  if (iRet)
  {
    theDI << "Error! Code: " << iRet << "\n";
  }
  else
  {
    theDI << "PCurve is attached successfully\n";
  }

  return 0;
}

static int edgestowire(Draw_Interpretor& theDI, int theNArg, const char** theArgVal)
{
  if (theNArg != 3)
  {
    theDI << "Use: edgestowire wire edges\n";
    return 1;
  }

  TopoDS_Shape anEdges = DBRep::Get(theArgVal[2]);
  if (anEdges.IsNull())
  {
    theDI << "no edges\n";
    return 1;
  }

  BOPTools_AlgoTools::OrientEdgesOnWire(anEdges);
  DBRep::Set(theArgVal[1], anEdges);
  return 0;
}

static int edgestofaces(Draw_Interpretor& theDI, int theNArg, const char** theArgVal)
{
  if (theNArg < 3)
  {
    theDI << "Use: edgestofaces faces edges [-a AngTol -s Shared(0/1)]\n";
    theDI << " AngTol - angular tolerance for comparing the planes;\n";
    theDI << " Shared - boolean flag which defines whether the input\n";
    theDI << "          edges are already shared or have to be intersected.\n";
    return 1;
  }

  TopoDS_Shape anEdges = DBRep::Get(theArgVal[2]);
  if (anEdges.IsNull())
  {
    theDI << "no edges\n";
    return 1;
  }

  double anAngTol = 1.e-8;
  bool   bShared  = false;

  for (int i = 3; i < theNArg; ++i)
  {
    if (!strcmp(theArgVal[i], "-a") && (i + 1 < theNArg))
    {
      anAngTol = Draw::Atof(theArgVal[i + 1]);
    }
    if (!strcmp(theArgVal[i], "-s") && (i + 1 < theNArg))
    {
      bShared = (Draw::Atoi(theArgVal[i + 1]) == 1);
    }
  }

  TopoDS_Shape aWires;
  int          iErr = BOPAlgo_Tools::EdgesToWires(anEdges, aWires, bShared, anAngTol);
  if (iErr)
  {
    theDI << "Unable to build wires from given edges\n";
    return 0;
  }

  TopoDS_Shape aFaces;
  bool         bDone = BOPAlgo_Tools::WiresToFaces(aWires, aFaces, anAngTol);
  if (!bDone)
  {
    theDI << "Unable to build faces from wires\n";
    return 0;
  }

  DBRep::Set(theArgVal[1], aFaces);
  return 0;
}

static int BuildPcurvesOnPlane(Draw_Interpretor& theDI, int theNArg, const char** theArgVal)
{
  if (theNArg != 2)
  {
    theDI << "Use: " << theArgVal[0] << " shape\n";
    return 1;
  }

  TopoDS_Shape aShape(DBRep::Get(theArgVal[1]));
  if (aShape.IsNull())
  {
    theDI << theArgVal[1] << " is null shape\n";
    return 1;
  }

  TopExp_Explorer exp(aShape, TopAbs_FACE);
  for (; exp.More(); exp.Next())
  {
    const TopoDS_Face&  aF = TopoDS::Face(exp.Current());
    BRepAdaptor_Surface aS(aF, false);
    if (aS.GetType() == GeomAbs_Plane)
    {
      NCollection_List<TopoDS_Shape> aLE;
      TopExp_Explorer                exp1(aF, TopAbs_EDGE);
      for (; exp1.More(); exp1.Next())
        aLE.Append(exp1.Current());
      BRepLib::BuildPCurveForEdgesOnPlane(aLE, aF);
    }
  }
  return 0;
}
