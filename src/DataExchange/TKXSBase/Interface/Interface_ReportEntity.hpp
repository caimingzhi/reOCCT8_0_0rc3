#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class Interface_Check;

class Interface_ReportEntity : public Standard_Transient
{

public:
  Standard_EXPORT Interface_ReportEntity(const occ::handle<Standard_Transient>& unknown);

  Standard_EXPORT Interface_ReportEntity(const occ::handle<Interface_Check>&    acheck,
                                         const occ::handle<Standard_Transient>& concerned);

  Standard_EXPORT void SetContent(const occ::handle<Standard_Transient>& content);

  Standard_EXPORT const occ::handle<Interface_Check>& Check() const;

  Standard_EXPORT occ::handle<Interface_Check>& CCheck();

  Standard_EXPORT occ::handle<Standard_Transient> Concerned() const;

  Standard_EXPORT bool HasContent() const;

  Standard_EXPORT bool HasNewContent() const;

  Standard_EXPORT occ::handle<Standard_Transient> Content() const;

  Standard_EXPORT bool IsError() const;

  Standard_EXPORT bool IsUnknown() const;

  DEFINE_STANDARD_RTTIEXT(Interface_ReportEntity, Standard_Transient)

private:
  occ::handle<Interface_Check>    thecheck;
  occ::handle<Standard_Transient> theconcerned;
  occ::handle<Standard_Transient> thecontent;
};
