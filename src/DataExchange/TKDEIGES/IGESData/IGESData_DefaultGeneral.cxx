

#include <IGESData.hpp>
#include <IGESData_DefaultGeneral.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_FreeFormatEntity.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESData_UndefinedEntity.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_GeneralLib.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Interface_UndefinedContent.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESData_DefaultGeneral, IGESData_GeneralModule)

IGESData_DefaultGeneral::IGESData_DefaultGeneral()
{
  Interface_GeneralLib::SetGlobal(this, IGESData::Protocol());
}

void IGESData_DefaultGeneral::OwnSharedCase(const int                               CN,
                                            const occ::handle<IGESData_IGESEntity>& ent,
                                            Interface_EntityIterator&               iter) const
{
  if (CN == 0)
    return;
  DeclareAndCast(IGESData_UndefinedEntity, anent, ent);
  if (anent.IsNull())
    return;
  occ::handle<Interface_UndefinedContent> cont = anent->UndefinedContent();
  int                                     nb   = cont->NbParams();
  for (int i = 1; i <= nb; i++)
  {
    if (cont->IsParamEntity(i))
      iter.GetOneItem(cont->ParamEntity(i));
  }
}

IGESData_DirChecker IGESData_DefaultGeneral::DirChecker(
  const int,
  const occ::handle<IGESData_IGESEntity>&) const
{
  IGESData_DirChecker dc;
  return dc;
}

void IGESData_DefaultGeneral::OwnCheckCase(const int,
                                           const occ::handle<IGESData_IGESEntity>&,
                                           const Interface_ShareTool&,
                                           occ::handle<Interface_Check>&) const
{
}

bool IGESData_DefaultGeneral::NewVoid(const int CN, occ::handle<Standard_Transient>& entto) const
{
  entto.Nullify();
  if (CN == 0)
    return false;
  if (CN == 1)
    entto = new IGESData_UndefinedEntity;
  if (CN == 2)
    entto = new IGESData_FreeFormatEntity;
  return (!entto.IsNull());
}

void IGESData_DefaultGeneral::OwnCopyCase(const int                               CN,
                                          const occ::handle<IGESData_IGESEntity>& entfrom,
                                          const occ::handle<IGESData_IGESEntity>& entto,
                                          Interface_CopyTool&                     TC) const
{
  if (CN == 0)
    return;
  DeclareAndCast(IGESData_UndefinedEntity, enfr, entfrom);
  DeclareAndCast(IGESData_UndefinedEntity, ento, entto);

  occ::handle<Interface_UndefinedContent> cont = new Interface_UndefinedContent;
  cont->GetFromAnother(enfr->UndefinedContent(), TC);
  ento->SetNewContent(cont);

  if (enfr->IsKind(STANDARD_TYPE(IGESData_FreeFormatEntity)))
  {
    DeclareAndCast(IGESData_FreeFormatEntity, enf, entfrom);
    DeclareAndCast(IGESData_FreeFormatEntity, ent, entto);
    ent->ClearNegativePointers();
    ent->AddNegativePointers(enf->NegativePointers());
  }
}
