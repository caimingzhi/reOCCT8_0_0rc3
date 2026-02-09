#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESData_Status.hpp>
#include <IGESGeom_BoundedSurface.hpp>
#include <IGESGeom_Boundary.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESGeom_ToolBoundedSurface.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Message_Msg.hpp>

IGESGeom_ToolBoundedSurface::IGESGeom_ToolBoundedSurface() = default;

void IGESGeom_ToolBoundedSurface::ReadOwnParams(const occ::handle<IGESGeom_BoundedSurface>& ent,
                                                const occ::handle<IGESData_IGESReaderData>& IR,
                                                IGESData_ParamReader& PR) const
{

  int                                                              num, i;
  int                                                              tempType;
  occ::handle<IGESData_IGESEntity>                                 tempSurface;
  occ::handle<NCollection_HArray1<occ::handle<IGESGeom_Boundary>>> tempBounds;
  IGESData_Status                                                  aStatus;

  if (!PR.ReadInteger(PR.Current(), tempType))
  {
    Message_Msg Msg165("XTSEP_165");
    PR.SendFail(Msg165);
  }
  if (!PR.ReadEntity(IR, PR.Current(), aStatus, tempSurface))
  {
    Message_Msg Msg166("XTSEP_166");
    switch (aStatus)
    {
      case IGESData_ReferenceError:
      {
        Message_Msg Msg216("IGES_216");
        Msg166.Arg(Msg216.Value());
        PR.SendFail(Msg166);
        break;
      }
      case IGESData_EntityError:
      {
        Message_Msg Msg217("IGES_217");
        Msg166.Arg(Msg217.Value());
        PR.SendFail(Msg166);
        break;
      }
      default:
      {
      }
    }
  }

  if (PR.ReadInteger(PR.Current(), num) && (num > 0))
  {
    tempBounds = new NCollection_HArray1<occ::handle<IGESGeom_Boundary>>(1, num);
  }
  else
  {
    Message_Msg Msg167("XTSEP_167");
    PR.SendFail(Msg167);
  }

  if (!tempBounds.IsNull())
  {
    for (i = 1; i <= num; i++)
    {
      occ::handle<IGESData_IGESEntity> tempEnt;

      if (PR.ReadEntity(IR, PR.Current(), aStatus, tempEnt))
        tempBounds->SetValue(i, occ::down_cast<IGESGeom_Boundary>(tempEnt));
      else
      {
        Message_Msg Msg168("XTSEP_168");
        switch (aStatus)
        {
          case IGESData_ReferenceError:
          {
            Message_Msg Msg216("IGES_216");
            Msg168.Arg(Msg216.Value());
            PR.SendFail(Msg168);
            break;
          }
          case IGESData_EntityError:
          {
            Message_Msg Msg217("IGES_217");
            Msg168.Arg(Msg217.Value());
            PR.SendFail(Msg168);
            break;
          }
          default:
          {
          }
        }
      }
    }
  }

  if (!tempBounds.IsNull())
  {
    DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
    ent->Init(tempType, tempSurface, tempBounds);
  }
}

void IGESGeom_ToolBoundedSurface::WriteOwnParams(const occ::handle<IGESGeom_BoundedSurface>& ent,
                                                 IGESData_IGESWriter& IW) const
{
  int i, num;
  IW.Send(ent->RepresentationType());
  IW.Send(ent->Surface());
  IW.Send(ent->NbBoundaries());
  for (num = ent->NbBoundaries(), i = 1; i <= num; i++)
    IW.Send(ent->Boundary(i));
}

void IGESGeom_ToolBoundedSurface::OwnShared(const occ::handle<IGESGeom_BoundedSurface>& ent,
                                            Interface_EntityIterator&                   iter) const
{
  int i, num;
  iter.GetOneItem(ent->Surface());
  for (num = ent->NbBoundaries(), i = 1; i <= num; i++)
    iter.GetOneItem(ent->Boundary(i));
}

void IGESGeom_ToolBoundedSurface::OwnCopy(const occ::handle<IGESGeom_BoundedSurface>& another,
                                          const occ::handle<IGESGeom_BoundedSurface>& ent,
                                          Interface_CopyTool&                         TC) const
{
  int i, num;

  int tempType = another->RepresentationType();
  DeclareAndCast(IGESData_IGESEntity, tempSurface, TC.Transferred(another->Surface()));
  num = another->NbBoundaries();
  occ::handle<NCollection_HArray1<occ::handle<IGESGeom_Boundary>>> tempBounds;
  if (num > 0)
    tempBounds = new NCollection_HArray1<occ::handle<IGESGeom_Boundary>>(1, num);
  for (i = 1; i <= num; i++)
  {
    DeclareAndCast(IGESGeom_Boundary, tempBoundary, TC.Transferred(another->Boundary(i)));
    tempBounds->SetValue(i, tempBoundary);
  }
  ent->Init(tempType, tempSurface, tempBounds);
}

IGESData_DirChecker IGESGeom_ToolBoundedSurface::DirChecker(
  const occ::handle<IGESGeom_BoundedSurface>&) const
{
  IGESData_DirChecker DC(143, 0);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.LineFont(IGESData_DefAny);

  DC.Color(IGESData_DefAny);
  DC.UseFlagRequired(0);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGeom_ToolBoundedSurface::OwnCheck(const occ::handle<IGESGeom_BoundedSurface>& ent,
                                           const Interface_ShareTool&,
                                           occ::handle<Interface_Check>& ach) const
{

  if ((ent->RepresentationType() != 0) && (ent->RepresentationType() != 1))
  {
    Message_Msg Msg165("XTSEP_165");
    ach->SendFail(Msg165);
  }
}

void IGESGeom_ToolBoundedSurface::OwnDump(const occ::handle<IGESGeom_BoundedSurface>& ent,
                                          const IGESData_IGESDumper&                  dumper,
                                          Standard_OStream&                           S,
                                          const int                                   level) const
{
  int sublevel = (level > 4) ? 1 : 0;
  S << "IGESGeom_BoundedSurface\n"
    << "Representation Type   : " << ent->RepresentationType() << "\n"
    << "Surface to be Bounded : ";
  dumper.Dump(ent->Surface(), S, sublevel);
  S << "\n"
    << "Boundary Entities     : ";
  IGESData_DumpEntities(S, dumper, level, 1, ent->NbBoundaries(), ent->Boundary);
  S << std::endl;
}
