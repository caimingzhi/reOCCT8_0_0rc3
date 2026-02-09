

#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDraw_CircArraySubfigure.hpp>
#include <IGESDraw_Drawing.hpp>
#include <IGESDraw_DrawingWithRotation.hpp>
#include <IGESDraw_LabelDisplay.hpp>
#include <IGESDraw_NetworkSubfigure.hpp>
#include <IGESDraw_NetworkSubfigureDef.hpp>
#include <IGESDraw_PerspectiveView.hpp>
#include <IGESDraw_Planar.hpp>
#include <IGESDraw_ReadWriteModule.hpp>
#include <IGESDraw_RectArraySubfigure.hpp>
#include <IGESDraw_SegmentedViewsVisible.hpp>
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

IMPLEMENT_STANDARD_RTTIEXT(IGESDraw_ReadWriteModule, IGESData_ReadWriteModule)

IGESDraw_ReadWriteModule::IGESDraw_ReadWriteModule() = default;

int IGESDraw_ReadWriteModule::CaseIGES(const int typenum, const int formnum) const
{
  switch (typenum)
  {
    case 132:
      return 2;
    case 320:
      return 7;
    case 402:
      switch (formnum)
      {
        case 3:
          return 13;
        case 4:
          return 14;
        case 5:
          return 5;
        case 16:
          return 9;
        case 19:
          return 11;
        default:
          break;
      }
      break;
    case 404:
      return formnum + 3;
    case 410:
      if (formnum == 0)
        return 12;
      else if (formnum == 1)
        return 8;
      break;
    case 412:
      return 10;
    case 414:
      return 1;
    case 420:
      return 6;
    default:
      break;
  }
  return 0;
}

void IGESDraw_ReadWriteModule::ReadOwnParams(const int                                   CN,
                                             const occ::handle<IGESData_IGESEntity>&     ent,
                                             const occ::handle<IGESData_IGESReaderData>& IR,
                                             IGESData_ParamReader&                       PR) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESDraw_CircArraySubfigure, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolCircArraySubfigure tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESDraw_ConnectPoint, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolConnectPoint tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESDraw_Drawing, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolDrawing tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESDraw_DrawingWithRotation, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolDrawingWithRotation tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESDraw_LabelDisplay, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolLabelDisplay tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESDraw_NetworkSubfigure, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolNetworkSubfigure tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESDraw_NetworkSubfigureDef, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolNetworkSubfigureDef tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESDraw_PerspectiveView, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolPerspectiveView tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESDraw_Planar, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolPlanar tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESDraw_RectArraySubfigure, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolRectArraySubfigure tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESDraw_SegmentedViewsVisible, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolSegmentedViewsVisible tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESDraw_View, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolView tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESDraw_ViewsVisible, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolViewsVisible tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESDraw_ViewsVisibleWithAttr, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolViewsVisibleWithAttr tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    default:
      break;
  }
}

void IGESDraw_ReadWriteModule::WriteOwnParams(const int                               CN,
                                              const occ::handle<IGESData_IGESEntity>& ent,
                                              IGESData_IGESWriter&                    IW) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESDraw_CircArraySubfigure, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolCircArraySubfigure tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESDraw_ConnectPoint, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolConnectPoint tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESDraw_Drawing, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolDrawing tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESDraw_DrawingWithRotation, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolDrawingWithRotation tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESDraw_LabelDisplay, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolLabelDisplay tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESDraw_NetworkSubfigure, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolNetworkSubfigure tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESDraw_NetworkSubfigureDef, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolNetworkSubfigureDef tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESDraw_PerspectiveView, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolPerspectiveView tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESDraw_Planar, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolPlanar tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESDraw_RectArraySubfigure, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolRectArraySubfigure tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESDraw_SegmentedViewsVisible, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolSegmentedViewsVisible tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESDraw_View, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolView tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESDraw_ViewsVisible, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolViewsVisible tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESDraw_ViewsVisibleWithAttr, anent, ent);
      if (anent.IsNull())
        return;
      IGESDraw_ToolViewsVisibleWithAttr tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    default:
      break;
  }
}
