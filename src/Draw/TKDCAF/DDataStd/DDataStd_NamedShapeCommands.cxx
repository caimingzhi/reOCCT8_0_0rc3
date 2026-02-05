#include <DDataStd.hpp>
#include <DDataStd_DrawPresentation.hpp>
#include <DDF.hpp>
#include <Draw_Interpretor.hpp>
#include <Draw_Appli.hpp>

#include <TDF_Data.hpp>
#include <TDF_Label.hpp>

#include <DBRep.hpp>
#include <TopoDS.hpp>

// LES ATTRIBUTES

#include <TNaming_Builder.hpp>

//=======================================================================
// function : DDataStd_SetShape
// purpose  : SetShape (DF, entry, drawshape)
//=======================================================================

static int DDataStd_SetShape(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb == 4)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(arg[1], DF))
      return 1;
    TopoDS_Shape s = DBRep::Get(arg[3]);
    if (s.IsNull())
    {
      di << "shape not found\n";
      return 1;
    }
    TDF_Label L;
    DDF::AddLabel(DF, arg[2], L);
    TNaming_Builder SI(L);
    SI.Generated(s);
    return 0;
  }
  di << "DDataStd_SetShape : Error\n";
  return 1;
}

//=================================================================================================

void DDataStd::NamedShapeCommands(Draw_Interpretor& theCommands)
{

  static bool done = false;
  if (done)
    return;
  done          = true;
  const char* g = "DData : Standard Attribute Commands";

  theCommands.Add("SetShape", "SetShape (DF, entry, drawname)", __FILE__, DDataStd_SetShape, g);
}
