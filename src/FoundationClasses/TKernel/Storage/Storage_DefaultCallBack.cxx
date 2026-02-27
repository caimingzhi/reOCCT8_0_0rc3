

#include <Standard_Persistent.hpp>
#include <Standard_Type.hpp>
#include <Storage_BaseDriver.hpp>
#include <Storage_DefaultCallBack.hpp>
#include <Storage_Schema.hpp>

IMPLEMENT_STANDARD_RTTIEXT(app::storage::Storage_DefaultCallBack, app::storage::Storage_CallBack)

app::storage::Storage_DefaultCallBack::Storage_DefaultCallBack() = default;

occ::handle<Standard_Persistent> app::storage::Storage_DefaultCallBack::New() const
{
  occ::handle<Standard_Persistent> res = new Standard_Persistent;

  return res;
}

void app::storage::Storage_DefaultCallBack::Add(const occ::handle<Standard_Persistent>&,
                                  const occ::handle<app::storage::Storage_Schema>&) const
{
}

void app::storage::Storage_DefaultCallBack::Write(const occ::handle<Standard_Persistent>&,
                                    const occ::handle<app::storage::Storage_BaseDriver>&,
                                    const occ::handle<app::storage::Storage_Schema>&) const
{
}

void app::storage::Storage_DefaultCallBack::Read(const occ::handle<Standard_Persistent>&,
                                   const occ::handle<app::storage::Storage_BaseDriver>& theDriver,
                                   const occ::handle<app::storage::Storage_Schema>&) const
{
  theDriver->SkipObject();
}
