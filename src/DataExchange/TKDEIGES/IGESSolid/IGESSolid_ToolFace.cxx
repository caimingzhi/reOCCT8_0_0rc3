#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESData_Status.hpp>
#include <IGESSolid_Face.hpp>
#include <IGESSolid_Loop.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESSolid_ToolFace.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Message_Msg.hpp>

IGESSolid_ToolFace::IGESSolid_ToolFace() = default;

void IGESSolid_ToolFace::ReadOwnParams(const occ::handle<IGESSolid_Face>&          ent,
                                       const occ::handle<IGESData_IGESReaderData>& IR,
                                       IGESData_ParamReader&                       PR) const
{

  Message_Msg Msg197("XSTEP_197");
  Message_Msg Msg198("XSTEP_198");

  bool                                                          outerLoopFlag;
  occ::handle<IGESData_IGESEntity>                              anent;
  occ::handle<IGESSolid_Loop>                                   aloop;
  occ::handle<IGESData_IGESEntity>                              tempSurface;
  int                                                           nbloops;
  occ::handle<NCollection_HArray1<occ::handle<IGESSolid_Loop>>> tempLoops;
  IGESData_Status                                               aStatus;

  if (!PR.ReadEntity(IR, PR.Current(), aStatus, tempSurface))
  {
    Message_Msg Msg196("XSTEP_196");
    switch (aStatus)
    {
      case IGESData_ReferenceError:
      {
        Message_Msg Msg216("IGES_216");
        Msg196.Arg(Msg216.Value());
        PR.SendFail(Msg196);
        break;
      }
      case IGESData_EntityError:
      {
        Message_Msg Msg217("IGES_217");
        Msg196.Arg(Msg217.Value());
        PR.SendFail(Msg196);
        break;
      }
      default:
      {
      }
    }
  }
  bool st = PR.ReadInteger(PR.Current(), nbloops);
  if (!st)
  {
    PR.SendFail(Msg197);
  }

  if (st && nbloops > 0)
    tempLoops = new NCollection_HArray1<occ::handle<IGESSolid_Loop>>(1, nbloops);
  else
    PR.SendFail(Msg197);

  PR.ReadBoolean(PR.Current(), Msg198, outerLoopFlag);

  if (!tempLoops.IsNull())
  {
    for (int i = 1; i <= nbloops; i++)
    {

      if (PR.ReadEntity(IR, PR.Current(), aStatus, STANDARD_TYPE(IGESSolid_Loop), aloop))
        tempLoops->SetValue(i, aloop);
      else
      {
        Message_Msg Msg199("XSTEP_199");
        switch (aStatus)
        {
          case IGESData_ReferenceError:
          {
            Message_Msg Msg216("IGES_216");
            Msg199.Arg(Msg216.Value());
            PR.SendFail(Msg199);
            break;
          }
          case IGESData_EntityError:
          {
            Message_Msg Msg217("IGES_217");
            Msg199.Arg(Msg217.Value());
            PR.SendFail(Msg199);
            break;
          }
          case IGESData_TypeError:
          {
            Message_Msg Msg218("IGES_218");
            Msg199.Arg(Msg218.Value());
            PR.SendFail(Msg199);
            break;
          }
          default:
          {
          }
        }
      }
    }
  }
  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempSurface, outerLoopFlag, tempLoops);
}

void IGESSolid_ToolFace::WriteOwnParams(const occ::handle<IGESSolid_Face>& ent,
                                        IGESData_IGESWriter&               IW) const
{
  int upper = ent->NbLoops();
  IW.Send(ent->Surface());
  IW.Send(upper);
  IW.SendBoolean(ent->HasOuterLoop());
  for (int i = 1; i <= upper; i++)
    IW.Send(ent->Loop(i));
}

void IGESSolid_ToolFace::OwnShared(const occ::handle<IGESSolid_Face>& ent,
                                   Interface_EntityIterator&          iter) const
{
  int upper = ent->NbLoops();
  iter.GetOneItem(ent->Surface());
  for (int i = 1; i <= upper; i++)
    iter.GetOneItem(ent->Loop(i));
}

void IGESSolid_ToolFace::OwnCopy(const occ::handle<IGESSolid_Face>& another,
                                 const occ::handle<IGESSolid_Face>& ent,
                                 Interface_CopyTool&                TC) const
{
  DeclareAndCast(IGESData_IGESEntity, tempSurface, TC.Transferred(another->Surface()));
  int  nbloops       = another->NbLoops();
  bool outerLoopFlag = another->HasOuterLoop();

  occ::handle<NCollection_HArray1<occ::handle<IGESSolid_Loop>>> tempLoops =
    new NCollection_HArray1<occ::handle<IGESSolid_Loop>>(1, nbloops);
  for (int i = 1; i <= nbloops; i++)
  {
    DeclareAndCast(IGESSolid_Loop, anent, TC.Transferred(another->Loop(i)));
    tempLoops->SetValue(i, anent);
  }

  ent->Init(tempSurface, outerLoopFlag, tempLoops);
}

IGESData_DirChecker IGESSolid_ToolFace::DirChecker(const occ::handle<IGESSolid_Face>&) const
{
  IGESData_DirChecker DC(510, 1);

  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefAny);

  DC.SubordinateStatusRequired(1);
  return DC;
}

void IGESSolid_ToolFace::OwnCheck(const occ::handle<IGESSolid_Face>& ent,
                                  const Interface_ShareTool&,
                                  occ::handle<Interface_Check>& ach) const
{

  if (ent->NbLoops() <= 0)
  {
    Message_Msg Msg197("XSTEP_197");
    ach->SendFail(Msg197);
  }
}

void IGESSolid_ToolFace::OwnDump(const occ::handle<IGESSolid_Face>& ent,
                                 const IGESData_IGESDumper&         dumper,
                                 Standard_OStream&                  S,
                                 const int                          level) const
{
  S << "IGESSolid_Face\n";

  int sublevel = (level <= 4) ? 0 : 1;
  S << "Surface : ";
  dumper.Dump(ent->Surface(), S, sublevel);
  S << "\n";
  if (ent->HasOuterLoop())
    S << "Outer loop is present (First one)\n";
  else
    S << "Outer loop is not present\n";
  S << "Loops : ";
  IGESData_DumpEntities(S, dumper, level, 1, ent->NbLoops(), ent->Loop);
  S << std::endl;
}
