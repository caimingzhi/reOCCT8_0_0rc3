

#include <SWDRAW.hpp>

#include <BRep_Builder.hpp>
#include <BRepTools.hpp>
#include <DBRep.hpp>
#include <gp_Trsf.hpp>
#include <ShapeProcess_OperLibrary.hpp>
#include <SWDRAW_ShapeAnalysis.hpp>
#include <SWDRAW_ShapeCustom.hpp>
#include <SWDRAW_ShapeExtend.hpp>
#include <SWDRAW_ShapeFix.hpp>
#include <SWDRAW_ShapeProcess.hpp>
#include <SWDRAW_ShapeProcessAPI.hpp>
#include <SWDRAW_ShapeTool.hpp>
#include <SWDRAW_ShapeUpgrade.hpp>

static int dejadraw = 0;

static int LocSet(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc < 2)
  {
    di << argv[0] << "LocSet a [b [c]]: set location for shape \"a\":\n";
    di << "- to Null if one argument is given\n";
    di << "- to location of shape b if two arguments are given\n";
    di << "- to difference of locations of shapes b and c if three arguments are given\n";
    return 1;
  }

  TopoDS_Shape a = DBRep::Get(argv[1]);
  if (a.IsNull())
  {
    di << "No shape named \"" << argv[1] << "\" found\n";
    return 1;
  }
  TopLoc_Location L;
  if (argc > 2)
  {
    TopoDS_Shape b = DBRep::Get(argv[2]);
    if (b.IsNull())
    {
      di << "No shape named \"" << argv[2] << "\" found\n";
      return 1;
    }
    if (argc > 3)
    {
      TopoDS_Shape c = DBRep::Get(argv[3]);
      if (c.IsNull())
      {
        di << "No shape named \"" << argv[3] << "\" found\n";
        return 1;
      }
      L = b.Location().Multiplied(c.Location().Inverted());
    }
    else
      L = b.Location();
  }
  a.Location(L);
  DBRep::Set(argv[1], a);

  return 0;
}

static int LocDump(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc < 2)
  {
    di << argv[0] << "LocDump a: dump location of shape \"a\"\n";
    return 1;
  }

  TopoDS_Shape a = DBRep::Get(argv[1]);
  if (a.IsNull())
  {
    di << "No shape named \"" << argv[1] << "\" found\n";
    return 1;
  }

  const TopLoc_Location& L = a.Location();
  di << "Location of shape " << argv[1] << ":\n";
  di << "Results in:\n";
  gp_Trsf          T = L.Transformation();
  TopLoc_Location  l(T);
  Standard_SStream aSStream;
  l.ShallowDump(aSStream);
  di << aSStream;

  return 0;
}

void SWDRAW::Init(Draw_Interpretor& theCommands)
{
  if (!dejadraw)
  {
    dejadraw = 1;
  }

  SWDRAW_ShapeTool::InitCommands(theCommands);
  SWDRAW_ShapeAnalysis::InitCommands(theCommands);
  SWDRAW_ShapeCustom::InitCommands(theCommands);
  SWDRAW_ShapeExtend::InitCommands(theCommands);
  SWDRAW_ShapeFix::InitCommands(theCommands);
  SWDRAW_ShapeUpgrade::InitCommands(theCommands);
  SWDRAW_ShapeProcess::InitCommands(theCommands);
  SWDRAW_ShapeProcessAPI::InitCommands(theCommands);

  theCommands.Add("LocSet",
                  "a [b [c]]: set loc b->a; use no args to get help",
                  __FILE__,
                  LocSet,
                  "essai");
  theCommands.Add("LocDump", "a: dump location of a", __FILE__, LocDump, "essai");

  ShapeProcess_OperLibrary::Init();
}

const char* SWDRAW::GroupName()
{
  return "Shape Healing";
}
