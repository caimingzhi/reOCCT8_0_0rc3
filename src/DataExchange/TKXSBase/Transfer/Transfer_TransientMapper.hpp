#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Transfer_Finder.hpp>
class Standard_Transient;
class Transfer_DataInfo;
class Transfer_Finder;

class Transfer_TransientMapper : public Transfer_Finder
{

public:
  Standard_EXPORT Transfer_TransientMapper(const occ::handle<Standard_Transient>& akey);

  Standard_EXPORT const occ::handle<Standard_Transient>& Value() const;

  Standard_EXPORT bool Equates(const occ::handle<Transfer_Finder>& other) const override;

  Standard_EXPORT occ::handle<Standard_Type> ValueType() const override;

  Standard_EXPORT const char* ValueTypeName() const override;

  DEFINE_STANDARD_RTTI_INLINE(Transfer_TransientMapper, Transfer_Finder)

private:
  occ::handle<Standard_Transient> theval;
};
