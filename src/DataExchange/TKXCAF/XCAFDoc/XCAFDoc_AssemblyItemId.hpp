#pragma once

#include <Standard_GUID.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_List.hpp>

class XCAFDoc_AssemblyItemId
{

public:
  Standard_EXPORT XCAFDoc_AssemblyItemId();

  Standard_EXPORT XCAFDoc_AssemblyItemId(const NCollection_List<TCollection_AsciiString>& thePath);

  Standard_EXPORT XCAFDoc_AssemblyItemId(const TCollection_AsciiString& theString);

  Standard_EXPORT void Init(const NCollection_List<TCollection_AsciiString>& thePath);

  Standard_EXPORT void Init(const TCollection_AsciiString& theString);

  Standard_EXPORT bool IsNull() const;

  Standard_EXPORT void Nullify();

  Standard_EXPORT bool IsChild(const XCAFDoc_AssemblyItemId& theOther) const;

  Standard_EXPORT bool IsDirectChild(const XCAFDoc_AssemblyItemId& theOther) const;

  Standard_EXPORT bool IsEqual(const XCAFDoc_AssemblyItemId& theOther) const;

  Standard_EXPORT const NCollection_List<TCollection_AsciiString>& GetPath() const;

  Standard_EXPORT TCollection_AsciiString ToString() const;

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  bool operator==(const XCAFDoc_AssemblyItemId& theOther) const { return IsEqual(theOther); }

private:
  NCollection_List<TCollection_AsciiString> myPath;
};

namespace std
{

  template <>
  struct hash<XCAFDoc_AssemblyItemId>
  {
    size_t operator()(const XCAFDoc_AssemblyItemId& theAssemblyItemId) const
    {
      return std::hash<TCollection_AsciiString>{}(theAssemblyItemId.ToString());
    }
  };

} // namespace std
