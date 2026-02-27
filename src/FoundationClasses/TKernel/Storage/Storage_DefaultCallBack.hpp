#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Storage_CallBack.hpp>
class Standard_Persistent;
namespace app { namespace storage {
class Storage_Schema;
}} // namespace app::storage

namespace app { namespace storage {
class Storage_BaseDriver;
}} // namespace app::storage


namespace app { namespace storage {
class Storage_DefaultCallBack : public app::storage::Storage_CallBack
{
public:
  Standard_EXPORT Storage_DefaultCallBack();

  Standard_EXPORT occ::handle<Standard_Persistent> New() const override;

  Standard_EXPORT void Add(const occ::handle<Standard_Persistent>& thePers,
                           const occ::handle<Storage_Schema>&      theSchema) const override;

  Standard_EXPORT void Write(const occ::handle<Standard_Persistent>& thePers,
                             const occ::handle<Storage_BaseDriver>&  theDriver,
                             const occ::handle<Storage_Schema>&      theSchema) const override;

  Standard_EXPORT void Read(const occ::handle<Standard_Persistent>& thePers,
                            const occ::handle<Storage_BaseDriver>&  theDriver,
                            const occ::handle<Storage_Schema>&      theSchema) const override;

  DEFINE_STANDARD_RTTIEXT(Storage_DefaultCallBack, Storage_CallBack)
};
}} // namespace app::storage

