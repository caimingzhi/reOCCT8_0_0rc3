#include <Draw_Appli.hpp>
#include <DBRep.hpp>
#include <Draw_Interpretor.hpp>
#include <BRepProj_Projection.hpp>
#include <BRepTest.hpp>

static int prj(Draw_Interpretor& di, int n, const char** a)
{
  if (n != 7)
  {
    di.PrintHelp(a[0]);
    return 1;
  }

  TopoDS_Shape anInputWire  = DBRep::Get(a[2]);
  TopoDS_Shape anInputShape = DBRep::Get(a[3]);
  if (anInputWire.IsNull() || anInputShape.IsNull())
  {
    di << "Null input shapes\n";
    return 1;
  }

  double X = Draw::Atof(a[4]), Y = Draw::Atof(a[5]), Z = Draw::Atof(a[6]);

  bool bCylProj = !strcmp(a[0], "prj");

  BRepProj_Projection aPrj = bCylProj
                               ? BRepProj_Projection(anInputWire, anInputShape, gp_Dir(X, Y, Z))
                               : BRepProj_Projection(anInputWire, anInputShape, gp_Pnt(X, Y, Z));

  if (!aPrj.IsDone())
  {
    di << "Not done\n";
    return 0;
  }

  for (int i = 1; aPrj.More(); aPrj.Next(), ++i)
  {
    char name[255];
    Sprintf(name, "%s_%d", a[1], i);
    DBRep::Set(name, aPrj.Current());
    di << name << " ";
  }

  di << "\n";
  return 0;
}

void BRepTest::ProjectionCommands(Draw_Interpretor& theCommands)
{
  static bool loaded = false;
  if (loaded)
    return;
  loaded = true;

  const char* g = "Projection of wire commands";

  theCommands.Add("prj",
                  "prj result w s x y z: "
                  "Cylindrical projection of w (wire or edge) on s (faces) along direction.\n",
                  __FILE__,
                  prj,
                  g);

  theCommands.Add("cprj",
                  "cprj result w s x y z: "
                  "Conical projection of w (wire or edge) on s (faces).\n",
                  __FILE__,
                  prj,
                  g);
}
