

#include <IGESGraph_Color.hpp>
#include <IGESSelect_SignColor.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SignColor, IFSelect_Signature)

static TCollection_AsciiString valbuf;

static const char* ColName(const int mode)
{
  switch (mode)
  {
    case 2:
      return "IGES Color Name";
    case 3:
      return "IGES Color R,G,B";
    case 4:
      return "IGES Color RED Value";
    case 5:
      return "IGES Color GREEN Value";
    case 6:
      return "IGES Color BLUE Value";
    default:
      return "IGES Color Number";
  }
}

IGESSelect_SignColor::IGESSelect_SignColor(const int mode)
    : IFSelect_Signature(ColName(mode)),
      themode(mode)
{
  if (mode == 4 || mode == 5 || mode == 6)
    SetIntCase(true, 0, true, 0);
}

const char* IGESSelect_SignColor::Value(const occ::handle<Standard_Transient>&       ent,
                                        const occ::handle<Interface_InterfaceModel>& model) const
{
  double red = -1, green = -1, blue = -1;
  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (igesent.IsNull())
    return "";
  int rank = igesent->RankColor();
  DeclareAndCast(IGESGraph_Color, color, igesent->Color());
  valbuf.Clear();

  if (themode < 2 || themode > 6)
  {
    if (rank == 0)
      return "(none)";
    if (rank > 0)
    {
      valbuf.AssignCat("S");
      valbuf.AssignCat(IFSelect_Signature::IntValue(rank));
    }
    else
    {
      int num = (model.IsNull() ? 0 : 2 * model->Number(color) - 1);
      valbuf.AssignCat("D");
      valbuf.AssignCat(IFSelect_Signature::IntValue(num));
    }
  }
  else if (themode == 2)
  {
    switch (rank)
    {
      case 0:
        return "(none)";
      case 1:
        return "BLACK";
      case 2:
        return "RED";
      case 3:
        return "GREEN";
      case 4:
        return "BLUE";
      case 5:
        return "YELLOW";
      case 6:
        return "MAGENTA";
      case 7:
        return "CYAN";
      case 8:
        return "WHITE";
      default:
        if (rank > 0)
          return "Unknown Number";
    }
    occ::handle<TCollection_HAsciiString> name;
    if (!color.IsNull())
      name = color->ColorName();
    if (!name.IsNull())
      return name->ToCString();
    int num = (model.IsNull() ? 0 : 2 * model->Number(color) - 1);
    valbuf.AssignCat("D");
    valbuf.AssignCat(IFSelect_Signature::IntValue(num));
  }
  else if (themode == 3)
  {
    switch (rank)
    {
      case 0:
        return "";
      case 1:
        return "0,0,0";
      case 2:
        return "100,0,0";
      case 3:
        return "0,100,0";
      case 4:
        return "0,0,100";
      case 5:
        return "100,100,0";
      case 6:
        return "100,0,100";
      case 7:
        return "0,100,100";
      case 8:
        return "100,100,100";
      default:
        if (rank > 0)
          return "";
    }
    if (!color.IsNull())
      color->RGBIntensity(red, green, blue);
    if (red >= 0)
      valbuf.AssignCat(IFSelect_Signature::IntValue(int(red)));
    valbuf.AssignCat(",");
    if (green >= 0)
      valbuf.AssignCat(IFSelect_Signature::IntValue(int(green)));
    valbuf.AssignCat(",");
    if (blue >= 0)
      valbuf.AssignCat(IFSelect_Signature::IntValue(int(blue)));
  }
  else if (themode == 4)
  {
    switch (rank)
    {
      case 0:
        return "";
      case 1:
        return "0";
      case 2:
        return "100";
      case 3:
        return "0";
      case 4:
        return "0";
      case 5:
        return "100";
      case 6:
        return "100";
      case 7:
        return "0";
      case 8:
        return "100";
      default:
        if (rank > 0)
          return "";
    }
    if (!color.IsNull())
      color->RGBIntensity(red, green, blue);
    if (red >= 0)
      return IFSelect_Signature::IntValue(int(red));
  }
  else if (themode == 5)
  {
    switch (rank)
    {
      case 0:
        return "";
      case 1:
        return "0";
      case 2:
        return "0";
      case 3:
        return "100";
      case 4:
        return "0";
      case 5:
        return "100";
      case 6:
        return "0";
      case 7:
        return "100";
      case 8:
        return "100";
      default:
        if (rank > 0)
          return "";
    }
    if (!color.IsNull())
      color->RGBIntensity(red, green, blue);
    if (green >= 0)
      return IFSelect_Signature::IntValue(int(green));
  }
  else if (themode == 6)
  {
    switch (rank)
    {
      case 0:
        return "";
      case 1:
        return "0";
      case 2:
        return "0";
      case 3:
        return "0";
      case 4:
        return "100";
      case 5:
        return "0";
      case 6:
        return "100";
      case 7:
        return "100";
      case 8:
        return "100";
      default:
        if (rank > 0)
          return "";
    }
    if (!color.IsNull())
      color->RGBIntensity(red, green, blue);
    if (blue >= 0)
      return IFSelect_Signature::IntValue(int(blue));
  }

  return valbuf.ToCString();
}
