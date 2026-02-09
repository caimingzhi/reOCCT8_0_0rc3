

#include <IGESData_IGESDumper.hpp>
#include <IGESDraw_CircArraySubfigure.hpp>
#include <IGESDraw_Drawing.hpp>
#include <IGESDraw_DrawingWithRotation.hpp>
#include <IGESDraw_LabelDisplay.hpp>
#include <IGESDraw_NetworkSubfigure.hpp>
#include <IGESDraw_NetworkSubfigureDef.hpp>
#include <IGESDraw_PerspectiveView.hpp>
#include <IGESDraw_Planar.hpp>
#include <IGESDraw_RectArraySubfigure.hpp>
#include <IGESDraw_SegmentedViewsVisible.hpp>
#include <IGESDraw_SpecificModule.hpp>
#include <IGESDraw_ToolCircArraySubfigure.hpp>
#include <IGESDraw_ToolConnectPoint.hpp>
#include <IGESDraw_ToolDrawing.hpp>
#include <IGESDraw_ToolDrawingWithRotation.hpp>
#include <IGESDraw_ToolLabelDisplay.hpp>
#include <IGESDraw_ToolNetworkSubfigure.hpp>
#include <IGESDraw_ToolNetworkSubfigureDef.hpp>
#include <IGESDraw_ToolPerspectiveView.hpp>
#include <IGESDraw_ToolPlanar.hpp>
#include <IGESDraw_ToolRectArraySubfigure.hpp>
#include <IGESDraw_ToolSegmentedViewsVisible.hpp>
#include <IGESDraw_ToolView.hpp>
#include <IGESDraw_ToolViewsVisible.hpp>
#include <IGESDraw_ToolViewsVisibleWithAttr.hpp>
#include <IGESDraw_View.hpp>
#include <IGESDraw_ViewsVisible.hpp>
#include <IGESDraw_ViewsVisibleWithAttr.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDraw_SpecificModule, IGESData_SpecificModule)

IGESDraw_SpecificModule::IGESDraw_SpecificModule() = default;

void IGESDraw_SpecificModule::OwnDump(const int                               CN,
                                      const occ::handle<IGESData_IGESEntity>& ent,
                                      const IGESData_IGESDumper&              dumper,
                                      Standard_OStream&                       S,
                                      const int                               own) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESDraw_CircArraySubfigure, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolCircArraySubfigure tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESDraw_ConnectPoint, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolConnectPoint tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESDraw_Drawing, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolDrawing tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESDraw_DrawingWithRotation, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolDrawingWithRotation tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESDraw_LabelDisplay, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolLabelDisplay tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESDraw_NetworkSubfigure, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolNetworkSubfigure tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESDraw_NetworkSubfigureDef, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolNetworkSubfigureDef tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESDraw_PerspectiveView, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolPerspectiveView tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESDraw_Planar, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolPlanar tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESDraw_RectArraySubfigure, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolRectArraySubfigure tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESDraw_SegmentedViewsVisible, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolSegmentedViewsVisible tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESDraw_View, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolView tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESDraw_ViewsVisible, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolViewsVisible tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESDraw_ViewsVisibleWithAttr, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolViewsVisibleWithAttr tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    default:
      break;
  }
}

bool IGESDraw_SpecificModule::OwnCorrect(const int                               CN,
                                         const occ::handle<IGESData_IGESEntity>& ent) const
{

  switch (CN)
  {
    case 3:
    {
      DeclareAndCast(IGESDraw_Drawing, anent, ent);
      if (anent.IsNull())
        break;
      IGESDraw_ToolDrawing tool;
      return tool.OwnCorrect(anent);
    }
    case 4:
    {
      DeclareAndCast(IGESDraw_DrawingWithRotation, anent, ent);
      if (anent.IsNull())
        break;
      IGESDraw_ToolDrawingWithRotation tool;
      return tool.OwnCorrect(anent);
    }
    case 9:
    {
      DeclareAndCast(IGESDraw_Planar, anent, ent);
      if (anent.IsNull())
        break;
      IGESDraw_ToolPlanar tool;
      return tool.OwnCorrect(anent);
    }
    case 13:
    {
      DeclareAndCast(IGESDraw_ViewsVisible, anent, ent);
      if (anent.IsNull())
        break;
      IGESDraw_ToolViewsVisible tool;
      return tool.OwnCorrect(anent);
    }
    case 14:
    {
      DeclareAndCast(IGESDraw_ViewsVisibleWithAttr, anent, ent);
      if (anent.IsNull())
        break;
      IGESDraw_ToolViewsVisibleWithAttr tool;
      return tool.OwnCorrect(anent);
    }
    default:
      break;
  }
  return false;
}
