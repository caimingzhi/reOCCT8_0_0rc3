

#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_GeneralModule.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_ShareTool.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Interface_GeneralModule, Standard_Transient)

void Interface_GeneralModule::FillShared(const occ::handle<Interface_InterfaceModel>&,
                                         const int                              casenum,
                                         const occ::handle<Standard_Transient>& ent,
                                         Interface_EntityIterator&              iter) const
{
  FillSharedCase(casenum, ent, iter);
}

void Interface_GeneralModule::Share(Interface_EntityIterator&              iter,
                                    const occ::handle<Standard_Transient>& shared) const
{
  iter.GetOneItem(shared);
}

void Interface_GeneralModule::ListImplied(const occ::handle<Interface_InterfaceModel>&,
                                          const int                              casenum,
                                          const occ::handle<Standard_Transient>& ent,
                                          Interface_EntityIterator&              iter) const
{
  ListImpliedCase(casenum, ent, iter);
}

void Interface_GeneralModule::ListImpliedCase(const int,
                                              const occ::handle<Standard_Transient>&,
                                              Interface_EntityIterator&) const
{
}

bool Interface_GeneralModule::CanCopy(const int, const occ::handle<Standard_Transient>&) const
{
  return false;
}

bool Interface_GeneralModule::Dispatch(const int,
                                       const occ::handle<Standard_Transient>& entfrom,
                                       occ::handle<Standard_Transient>&       entto,
                                       Interface_CopyTool&) const
{
  entto = entfrom;
  return false;
}

bool Interface_GeneralModule::NewCopiedCase(const int,
                                            const occ::handle<Standard_Transient>&,
                                            occ::handle<Standard_Transient>&,
                                            Interface_CopyTool&) const
{
  return false;
}

void Interface_GeneralModule::RenewImpliedCase(const int,
                                               const occ::handle<Standard_Transient>&,
                                               const occ::handle<Standard_Transient>&,
                                               const Interface_CopyTool&) const
{
}

void Interface_GeneralModule::WhenDeleteCase(const int,
                                             const occ::handle<Standard_Transient>&,
                                             const bool) const
{
}

int Interface_GeneralModule::CategoryNumber(const int,
                                            const occ::handle<Standard_Transient>&,
                                            const Interface_ShareTool&) const
{
  return 0;
}

occ::handle<TCollection_HAsciiString> Interface_GeneralModule::Name(
  const int,
  const occ::handle<Standard_Transient>&,
  const Interface_ShareTool&) const
{
  occ::handle<TCollection_HAsciiString> str;
  return str;
}
