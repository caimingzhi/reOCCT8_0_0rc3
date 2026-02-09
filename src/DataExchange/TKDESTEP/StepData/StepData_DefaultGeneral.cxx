

#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_GeneralLib.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Interface_UndefinedContent.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <StepData.hpp>
#include <StepData_DefaultGeneral.hpp>
#include <StepData_Protocol.hpp>
#include <StepData_UndefinedEntity.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepData_DefaultGeneral, StepData_GeneralModule)

StepData_DefaultGeneral::StepData_DefaultGeneral()
{

  Interface_GeneralLib::SetGlobal(this, StepData::Protocol());
}

void StepData_DefaultGeneral::FillSharedCase(const int                              casenum,
                                             const occ::handle<Standard_Transient>& ent,
                                             Interface_EntityIterator&              iter) const
{

  if (casenum != 1)
    return;
  DeclareAndCast(StepData_UndefinedEntity, undf, ent);
  occ::handle<Interface_UndefinedContent> cont = undf->UndefinedContent();
  int                                     nb   = cont->NbParams();

  for (int i = 1; i <= nb; i++)
  {
    Interface_ParamType ptype = cont->ParamType(i);
    if (ptype == Interface_ParamSub)
    {

      DeclareAndCast(StepData_UndefinedEntity, subent, cont->ParamEntity(i));
      FillSharedCase(casenum, cont->ParamEntity(i), iter);
    }
    else if (ptype == Interface_ParamIdent)
    {

      iter.GetOneItem(cont->ParamEntity(i));
    }
  }
}

void StepData_DefaultGeneral::CheckCase(const int,
                                        const occ::handle<Standard_Transient>&,
                                        const Interface_ShareTool&,
                                        occ::handle<Interface_Check>&) const
{
}

bool StepData_DefaultGeneral::NewVoid(const int CN, occ::handle<Standard_Transient>& ent) const
{

  if (CN != 1)
    return false;
  ent = new StepData_UndefinedEntity;
  return true;
}

void StepData_DefaultGeneral::CopyCase(const int                              casenum,
                                       const occ::handle<Standard_Transient>& entfrom,
                                       const occ::handle<Standard_Transient>& entto,
                                       Interface_CopyTool&                    TC) const
{

  if (casenum != 1)
    return;
  DeclareAndCast(StepData_UndefinedEntity, undfrom, entfrom);
  DeclareAndCast(StepData_UndefinedEntity, undto, entto);
  undto->GetFromAnother(undfrom, TC);
}
