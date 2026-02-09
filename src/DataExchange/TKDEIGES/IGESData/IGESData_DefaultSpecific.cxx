

#include <IGESData.hpp>
#include <IGESData_DefaultSpecific.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_SpecificLib.hpp>
#include <IGESData_UndefinedEntity.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_UndefinedContent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESData_DefaultSpecific, IGESData_SpecificModule)

IGESData_DefaultSpecific::IGESData_DefaultSpecific()
{
  IGESData_SpecificLib::SetGlobal(this, IGESData::Protocol());
}

void IGESData_DefaultSpecific::OwnDump(const int,
                                       const occ::handle<IGESData_IGESEntity>& ent,
                                       const IGESData_IGESDumper&              dumper,
                                       Standard_OStream&                       S,
                                       const int) const
{
  DeclareAndCast(IGESData_UndefinedEntity, lent, ent);
  if (lent.IsNull())
    return;

  int dstat = lent->DirStatus();
  if (dstat != 0)
    S << " --  Directory Entry Error Status = " << dstat << "  --\n";
  occ::handle<Interface_UndefinedContent> cont = lent->UndefinedContent();
  int                                     nb   = cont->NbParams();
  S << " UNDEFINED ENTITY ...\n"
    << nb << " Parameters (WARNING : Odd Integer Values Interpreted as Entities)\n";
  for (int i = 1; i <= nb; i++)
  {
    Interface_ParamType ptyp = cont->ParamType(i);
    if (ptyp == Interface_ParamVoid)
      S << "	[" << i << ":Void]";
    else if (cont->IsParamEntity(i))
    {
      DeclareAndCast(IGESData_IGESEntity, anent, cont->ParamEntity(i));
      S << "	[" << i << ":IGES]=";
      dumper.PrintDNum(anent, S);
    }
    else
    {
      S << "	[" << i << "]=" << cont->ParamValue(i)->String();
    }
    if (i == (i % 5) * 5)
      S << "\n";
  }
  S << std::endl;
}
