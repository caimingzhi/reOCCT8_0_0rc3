#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include "../RWStepAP214/RWStepAP214_GeneralModule.hpp"
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <StepData_ReadWriteModule.hpp>
#include <STEPSelections_SelectDerived.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>

IMPLEMENT_STANDARD_RTTIEXT(STEPSelections_SelectDerived, StepSelect_StepType)

STEPSelections_SelectDerived::STEPSelections_SelectDerived()

  = default;

static occ::handle<Standard_Type> GetStepType(const occ::handle<StepData_ReadWriteModule>& module,
                                              const TCollection_AsciiString&               type)
{
  occ::handle<Standard_Type> atype;
  if (module.IsNull())
    return atype;
  int num = module->CaseStep(type);
  if (num == 0)
    return atype;
  occ::handle<Standard_Transient> ent;
  RWStepAP214_GeneralModule       genModul;
  genModul.NewVoid(num, ent);
  atype = ent->DynamicType();
  return atype;
}

bool STEPSelections_SelectDerived::Matches(const occ::handle<Standard_Transient>& ent,
                                           const occ::handle<Interface_InterfaceModel>&,
                                           const TCollection_AsciiString& text,
                                           const bool) const
{
  int                                   CN;
  occ::handle<StepData_ReadWriteModule> module;
  bool                                  ok = thelib.Select(ent, module, CN);
  if (!ok)
    return false;
  occ::handle<Standard_Type> checker = GetStepType(module, text);
  if (checker.IsNull())
    return false;

  bool plex = module->IsComplex(CN);
  if (!plex)
  {
    DeclareAndCast(Standard_Type, atype, ent);
    if (atype.IsNull())
      atype = ent->DynamicType();
    return atype->SubType(checker);
  }
  else
  {
    NCollection_Sequence<TCollection_AsciiString> list;
    module->ComplexType(CN, list);
    int nb = list.Length();
    for (int i = 1; i <= nb; i++)
    {
      occ::handle<Standard_Type> atype = GetStepType(module, list.Value(i));
      if (atype->SubType(checker))
        return true;
    }
  }
  return false;
}
