#include <DDataStd.hpp>
#include <DDF.hpp>
#include <Draw_Appli.hpp>
#include <Draw_Interpretor.hpp>
#include <Draw_Viewer.hpp>
#include <TCollection_AsciiString.hpp>
#include <gp_Pnt.hpp>
#include <TNaming_Tool.hpp>
#include <TDF_ChildIterator.hpp>
#include <TDataXtd_Point.hpp>

#include <DDataStd_DrawPresentation.hpp>
#include <Message.hpp>

#ifndef _WIN32
extern Draw_Viewer dout;
#else
Standard_IMPORT Draw_Viewer dout;
#endif

static int DDataStd_PNT(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb == 6)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(arg[1], DF))
      return 1;
    TDF_Label L;
    DDF::AddLabel(DF, arg[2], L);
    double x = Draw::Atof(arg[3]);
    double y = Draw::Atof(arg[4]);
    double z = Draw::Atof(arg[5]);
    TDataXtd_Point::Set(L, gp_Pnt(x, y, z));
    return 0;
  }
  di << "DDataStd_PNT : Error : not done\n";
  return 1;
}

static int DDataStd_Rmdraw(Draw_Interpretor&, int nb, const char** arg)
{
  if (nb != 2)
  {
    Message::SendFail() << "Syntax error: wrong number of arguments";
    return 1;
  }

  if (occ::handle<Draw_Drawable3D> D3D = Draw::Get(arg[1]))
  {
    dout.RemoveDrawable(D3D);
    return 0;
  }
  else
  {
    Message::SendFail() << "Syntax error: variable '" << arg[1] << "' not found";
    return 1;
  }
}

static int DDataStd_DrawOwner(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb == 2)
  {
    occ::handle<Draw_Drawable3D> D = Draw::Get(arg[1]);
    if (!D.IsNull())
    {
      TCollection_AsciiString entry;
      TCollection_AsciiString name(D->Name());
      int                     index = name.Search("_0:");
      if (index > 0)
      {
        entry = name.Split(index);
        name.Remove(index);
        di << entry.ToCString();
      }
      else
        di << name.ToCString();
    }
    else
      di << 0;
    return 0;
  }
  di << "DDataStd_DrawOwner : Error\n";
  return 1;
}

static int DDataStd_DrawDisplay(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb == 3)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(arg[1], DF))
      return 1;
    TDF_Label L;
    if (!DDF::FindLabel(DF, arg[2], L))
      return 1;
    DDataStd_DrawPresentation::Display(L);
    return 0;
  }
  di << "DDataStd_DrawDisplay : Error\n";
  return 1;
}

static int DDataStd_DrawErase(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb == 3)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(arg[1], DF))
      return 1;
    TDF_Label L;
    if (!DDF::FindLabel(DF, arg[2], L))
      return 1;
    DDataStd_DrawPresentation::Erase(L);
    return 0;
  }
  di << "DDataStd_DrawErase : Error\n";
  return 1;
}

static int DDataStd_DrawUpdate(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb == 3)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(arg[1], DF))
      return 1;
    TDF_Label L;
    if (!DDF::FindLabel(DF, arg[2], L))
      return 1;
    DDataStd_DrawPresentation::Update(L);
    return 0;
  }
  di << "DDataStd_DrawUpdate : Error\n";
  return 1;
}

static int DDataStd_DrawRepaint(Draw_Interpretor&, int, const char**)
{
  dout.Repaint3D();
  dout.Flush();
  return 0;
}

void DDataStd::DrawDisplayCommands(Draw_Interpretor& theCommands)
{

  static bool done = false;
  if (done)
    return;
  done          = true;
  const char* g = "SKETCH commands";

  theCommands.Add("PNT", "PNT (DF, entry, x, y, z)", __FILE__, DDataStd_PNT, g);

  theCommands.Add("rmdraw", "rmdraw(name)", __FILE__, DDataStd_Rmdraw, g);

  theCommands.Add("DrawOwner", "DrawOwner (drawable)", __FILE__, DDataStd_DrawOwner, g);

  theCommands.Add("DrawDisplay", "DrawDisplay (DF, entry)", __FILE__, DDataStd_DrawDisplay, g);

  theCommands.Add("DrawErase", "DrawErase (DF, entry)", __FILE__, DDataStd_DrawErase, g);

  theCommands.Add("DrawUpdate", "DrawUpdate (DF, entry)", __FILE__, DDataStd_DrawUpdate, g);

  theCommands.Add("DrawRepaint", "update the draw viewer", __FILE__, DDataStd_DrawRepaint, g);
}
