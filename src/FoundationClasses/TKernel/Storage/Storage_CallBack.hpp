#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class Standard_Persistent;
class Storage_Schema;
class Storage_BaseDriver;

class Storage_CallBack : public Standard_Transient
{
public:
  Standard_EXPORT virtual occ::handle<Standard_Persistent> New() const = 0;

  Standard_EXPORT virtual void Add(const occ::handle<Standard_Persistent>& aPers,
                                   const occ::handle<Storage_Schema>&      aSchema) const = 0;

  Standard_EXPORT virtual void Write(const occ::handle<Standard_Persistent>& aPers,
                                     const occ::handle<Storage_BaseDriver>&  aDriver,
                                     const occ::handle<Storage_Schema>&      aSchema) const = 0;

  Standard_EXPORT virtual void Read(const occ::handle<Standard_Persistent>& aPers,
                                    const occ::handle<Storage_BaseDriver>&  aDriver,
                                    const occ::handle<Storage_Schema>&      aSchema) const = 0;

  DEFINE_STANDARD_RTTIEXT(Storage_CallBack, Standard_Transient)
};

