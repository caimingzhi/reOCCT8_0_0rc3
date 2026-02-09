#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Transfer_StatusResult.hpp>
#include <Transfer_StatusExec.hpp>
#include <Standard_Transient.hpp>
class Interface_Check;

#ifdef Status
  #undef Status
#endif

class Transfer_Binder : public Standard_Transient
{

public:
  Standard_EXPORT void Merge(const occ::handle<Transfer_Binder>& other);

  Standard_EXPORT virtual bool IsMultiple() const;

  Standard_EXPORT virtual occ::handle<Standard_Type> ResultType() const = 0;

  Standard_EXPORT virtual const char* ResultTypeName() const = 0;

  Standard_EXPORT void AddResult(const occ::handle<Transfer_Binder>& next);

  Standard_EXPORT occ::handle<Transfer_Binder> NextResult() const;

  Standard_EXPORT bool HasResult() const;

  Standard_EXPORT void SetAlreadyUsed();

  Standard_EXPORT Transfer_StatusResult Status() const;

  Standard_EXPORT Transfer_StatusExec StatusExec() const;

  Standard_EXPORT void SetStatusExec(const Transfer_StatusExec stat);

  Standard_EXPORT void AddFail(const char* mess, const char* orig = "");

  Standard_EXPORT void AddWarning(const char* mess, const char* orig = "");

  Standard_EXPORT const occ::handle<Interface_Check> Check() const;

  Standard_EXPORT occ::handle<Interface_Check> CCheck();

  Standard_EXPORT ~Transfer_Binder() override;

  DEFINE_STANDARD_RTTIEXT(Transfer_Binder, Standard_Transient)

protected:
  Standard_EXPORT Transfer_Binder();

  Standard_EXPORT void SetResultPresent();

private:
  Standard_EXPORT void CutResult(const occ::handle<Transfer_Binder>& next);

  Transfer_StatusResult        thestatus;
  Transfer_StatusExec          theexecst;
  occ::handle<Interface_Check> thecheck;
  occ::handle<Transfer_Binder> thenextr;
  occ::handle<Transfer_Binder> theendr;
};
