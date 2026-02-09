

#include <Standard_Persistent.hpp>
#include <Standard_Type.hpp>
#include <Storage_BaseDriver.hpp>
#include <Storage_DefaultCallBack.hpp>
#include <Storage_Schema.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Storage_DefaultCallBack, Storage_CallBack)

Storage_DefaultCallBack::Storage_DefaultCallBack() = default;

occ::handle<Standard_Persistent> Storage_DefaultCallBack::New() const
{
  occ::handle<Standard_Persistent> res = new Standard_Persistent;

  return res;
}

void Storage_DefaultCallBack::Add(const occ::handle<Standard_Persistent>&,
                                  const occ::handle<Storage_Schema>&) const
{
}

void Storage_DefaultCallBack::Write(const occ::handle<Standard_Persistent>&,
                                    const occ::handle<Storage_BaseDriver>&,
                                    const occ::handle<Storage_Schema>&) const
{
}

void Storage_DefaultCallBack::Read(const occ::handle<Standard_Persistent>&,
                                   const occ::handle<Storage_BaseDriver>& theDriver,
                                   const occ::handle<Storage_Schema>&) const
{
  theDriver->SkipObject();
}
