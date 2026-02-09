#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Transfer_Binder.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;

class Transfer_MultipleBinder : public Transfer_Binder
{

public:
  Standard_EXPORT Transfer_MultipleBinder();

  Standard_EXPORT bool IsMultiple() const override;

  Standard_EXPORT occ::handle<Standard_Type> ResultType() const override;

  Standard_EXPORT const char* ResultTypeName() const override;

  Standard_EXPORT void AddResult(const occ::handle<Standard_Transient>& res);

  Standard_EXPORT int NbResults() const;

  Standard_EXPORT occ::handle<Standard_Transient> ResultValue(const int num) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>
                  MultipleResult() const;

  Standard_EXPORT void SetMultipleResult(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& mulres);

  DEFINE_STANDARD_RTTIEXT(Transfer_MultipleBinder, Transfer_Binder)

private:
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> themulres;
};
