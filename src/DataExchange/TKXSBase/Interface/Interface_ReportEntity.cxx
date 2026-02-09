

#include <Interface_Check.hpp>
#include <Interface_ReportEntity.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Interface_ReportEntity, Standard_Transient)

Interface_ReportEntity::Interface_ReportEntity(const occ::handle<Standard_Transient>& unknown)
{
  theconcerned = unknown;
  thecontent   = unknown;
}

Interface_ReportEntity::Interface_ReportEntity(const occ::handle<Interface_Check>&    acheck,
                                               const occ::handle<Standard_Transient>& concerned)
    : thecheck(acheck)
{
  theconcerned = concerned;
  thecheck->SetEntity(concerned);
}

void Interface_ReportEntity::SetContent(const occ::handle<Standard_Transient>& content)
{
  thecontent = content;
}

const occ::handle<Interface_Check>& Interface_ReportEntity::Check() const
{
  return thecheck;
}

occ::handle<Interface_Check>& Interface_ReportEntity::CCheck()
{
  return thecheck;
}

occ::handle<Standard_Transient> Interface_ReportEntity::Concerned() const
{
  return theconcerned;
}

bool Interface_ReportEntity::HasContent() const
{
  return (!thecontent.IsNull());
}

bool Interface_ReportEntity::HasNewContent() const
{
  return (!thecontent.IsNull() && thecontent != theconcerned);
}

occ::handle<Standard_Transient> Interface_ReportEntity::Content() const
{
  return thecontent;
}

bool Interface_ReportEntity::IsError() const
{
  return (thecheck->NbFails() > 0);
}

bool Interface_ReportEntity::IsUnknown() const
{
  return ((thecheck->NbFails() == 0) && (thecheck->NbWarnings() == 0)
          && (theconcerned == thecontent));
}
