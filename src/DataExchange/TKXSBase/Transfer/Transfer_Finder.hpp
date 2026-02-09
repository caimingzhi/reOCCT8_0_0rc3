#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
#include <Interface_ParamType.hpp>
#include <TCollection_AsciiString.hpp>

class Transfer_Finder : public Standard_Transient
{

public:
  Standard_EXPORT size_t GetHashCode() const;

  Standard_EXPORT virtual bool Equates(const occ::handle<Transfer_Finder>& other) const = 0;

  Standard_EXPORT virtual occ::handle<Standard_Type> ValueType() const;

  Standard_EXPORT virtual const char* ValueTypeName() const;

  Standard_EXPORT void SetAttribute(const char* name, const occ::handle<Standard_Transient>& val);

  Standard_EXPORT bool RemoveAttribute(const char* name);

  Standard_EXPORT bool GetAttribute(const char*                       name,
                                    const occ::handle<Standard_Type>& type,
                                    occ::handle<Standard_Transient>&  val) const;

  Standard_EXPORT occ::handle<Standard_Transient> Attribute(const char* name) const;

  Standard_EXPORT Interface_ParamType AttributeType(const char* name) const;

  Standard_EXPORT void SetIntegerAttribute(const char* name, const int val);

  Standard_EXPORT bool GetIntegerAttribute(const char* name, int& val) const;

  Standard_EXPORT int IntegerAttribute(const char* name) const;

  Standard_EXPORT void SetRealAttribute(const char* name, const double val);

  Standard_EXPORT bool GetRealAttribute(const char* name, double& val) const;

  Standard_EXPORT double RealAttribute(const char* name) const;

  Standard_EXPORT void SetStringAttribute(const char* name, const char* val);

  Standard_EXPORT bool GetStringAttribute(const char* name, const char*& val) const;

  Standard_EXPORT const char* StringAttribute(const char* name) const;

  Standard_EXPORT NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>>&
                  AttrList();

  Standard_EXPORT void SameAttributes(const occ::handle<Transfer_Finder>& other);

  Standard_EXPORT void GetAttributes(const occ::handle<Transfer_Finder>& other,
                                     const char*                         fromname = "",
                                     const bool                          copied   = true);

  DEFINE_STANDARD_RTTIEXT(Transfer_Finder, Standard_Transient)

protected:
  Standard_EXPORT void SetHashCode(const size_t code);

private:
  size_t                                                                        thecode;
  NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>> theattrib;
};
