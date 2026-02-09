#include <DBRep.hpp>
#include <ShapeProcess_ShapeContext.hpp>
#include <ShapeProcessAPI_ApplySequence.hpp>
#include <SWDRAW.hpp>
#include <SWDRAW_ShapeProcessAPI.hpp>
#include <TopoDS_Shape.hpp>

static int ApplySequence(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc < 4)
  {
    di << "Specify result, shape, resource name and prefix (optional)\n";
    return 1;
  }
  const char* arg1 = argv[1];
  const char* arg2 = argv[2];
  const char* arg3 = argv[3];
  const char* arg4 = "";
  if (argc > 4)
    arg4 = argv[4];
  TopoDS_Shape Shape = DBRep::Get(arg2);
  if (Shape.IsNull())
  {
    di << "Shape unknown : " << arg2 << "\n";
    return 1;
  }

  ShapeProcessAPI_ApplySequence seq(arg3, arg4);

  TopoDS_Shape result = seq.PrepareShape(Shape, true, TopAbs_FACE);

  seq.PrintPreparationResult();
  DBRep::Set(arg1, result);
  return 0;
}

void SWDRAW_ShapeProcessAPI::InitCommands(Draw_Interpretor& theCommands)
{
  static bool initactor = false;
  if (!initactor)
  {

    initactor = true;

    const char* g = SWDRAW::GroupName();

    theCommands.Add("DT_ApplySeq",
                    "DT_ApplySeq result shape rscfilename [prefix]",
                    __FILE__,
                    ApplySequence,
                    g);
  }
}
