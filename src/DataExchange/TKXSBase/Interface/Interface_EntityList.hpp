#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Type.hpp>
class Interface_EntityIterator;

class Interface_EntityList
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Interface_EntityList();

  Standard_EXPORT void Clear();

  Standard_EXPORT void Append(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void Add(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void Remove(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void Remove(const int num);

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT int NbEntities() const;

  Standard_EXPORT const occ::handle<Standard_Transient>& Value(const int num) const;

  Standard_EXPORT void SetValue(const int num, const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void FillIterator(Interface_EntityIterator& iter) const;

  Standard_EXPORT int NbTypedEntities(const occ::handle<Standard_Type>& atype) const;

  Standard_EXPORT occ::handle<Standard_Transient> TypedEntity(
    const occ::handle<Standard_Type>& atype,
    const int                         num = 0) const;

private:
  occ::handle<Standard_Transient> theval;
};
