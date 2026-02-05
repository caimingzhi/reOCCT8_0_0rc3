#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Transfer_Binder.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;

//! This binder binds several (a list of) Transients with a starting
//! entity, when this entity itself corresponds to a simple list
//! of Transients. Each part is not seen as a sub-result of an
//! independent component, but as an item of a built-in list
class Transfer_TransientListBinder : public Transfer_Binder
{

public:
  Standard_EXPORT Transfer_TransientListBinder();

  Standard_EXPORT Transfer_TransientListBinder(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list);

  Standard_EXPORT bool IsMultiple() const override;

  Standard_EXPORT occ::handle<Standard_Type> ResultType() const override;

  Standard_EXPORT const char* ResultTypeName() const override;

  //! Adds an item to the result list
  Standard_EXPORT void AddResult(const occ::handle<Standard_Transient>& res);

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> Result()
    const;

  //! Changes an already defined sub-result
  Standard_EXPORT void SetResult(const int num, const occ::handle<Standard_Transient>& res);

  Standard_EXPORT int NbTransients() const;

  Standard_EXPORT const occ::handle<Standard_Transient>& Transient(const int num) const;

  DEFINE_STANDARD_RTTIEXT(Transfer_TransientListBinder, Transfer_Binder)

private:
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> theres;
};
