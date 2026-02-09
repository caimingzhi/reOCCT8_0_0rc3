#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <MoniTool_ValueType.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
#include <TCollection_AsciiString.hpp>

class MoniTool_AttrList
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT MoniTool_AttrList();

  Standard_EXPORT MoniTool_AttrList(const MoniTool_AttrList& other);

  Standard_EXPORT void SetAttribute(const char* name, const occ::handle<Standard_Transient>& val);

  Standard_EXPORT bool RemoveAttribute(const char* name);

  Standard_EXPORT bool GetAttribute(const char*                       name,
                                    const occ::handle<Standard_Type>& type,
                                    occ::handle<Standard_Transient>&  val) const;

  Standard_EXPORT occ::handle<Standard_Transient> Attribute(const char* name) const;

  Standard_EXPORT MoniTool_ValueType AttributeType(const char* name) const;

  Standard_EXPORT void SetIntegerAttribute(const char* name, const int val);

  Standard_EXPORT bool GetIntegerAttribute(const char* name, int& val) const;

  Standard_EXPORT int IntegerAttribute(const char* name) const;

  Standard_EXPORT void SetRealAttribute(const char* name, const double val);

  Standard_EXPORT bool GetRealAttribute(const char* name, double& val) const;

  Standard_EXPORT double RealAttribute(const char* name) const;

  Standard_EXPORT void SetStringAttribute(const char* name, const char* val);

  Standard_EXPORT bool GetStringAttribute(const char* name, const char*& val) const;

  Standard_EXPORT const char* StringAttribute(const char* name) const;

  Standard_EXPORT const NCollection_DataMap<TCollection_AsciiString,
                                            occ::handle<Standard_Transient>>&
                        AttrList() const;

  Standard_EXPORT void SameAttributes(const MoniTool_AttrList& other);

  Standard_EXPORT void GetAttributes(const MoniTool_AttrList& other,
                                     const char*              fromname = "",
                                     const bool               copied   = true);

private:
  NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>> theattrib;
};
