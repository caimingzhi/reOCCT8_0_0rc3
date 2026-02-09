#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Type.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
class Interface_IntVal;
class Standard_Transient;

class Interface_EntityIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Interface_EntityIterator();

  Standard_EXPORT Interface_EntityIterator(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list);

  Standard_EXPORT void AddList(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list);

  Standard_EXPORT void AddItem(const occ::handle<Standard_Transient>& anentity);

  Standard_EXPORT void GetOneItem(const occ::handle<Standard_Transient>& anentity);

  Standard_EXPORT void SelectType(const occ::handle<Standard_Type>& atype, const bool keep);

  Standard_EXPORT int NbEntities() const;

  Standard_EXPORT int NbTyped(const occ::handle<Standard_Type>& type) const;

  Standard_EXPORT Interface_EntityIterator Typed(const occ::handle<Standard_Type>& type) const;

  Standard_EXPORT virtual void Start() const;

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next() const;

  Standard_EXPORT const occ::handle<Standard_Transient>& Value() const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> Content()
    const;

  Standard_EXPORT void Destroy();

  Standard_EXPORT virtual ~Interface_EntityIterator();

protected:
  Standard_EXPORT void Reset();

private:
  occ::handle<Interface_IntVal>                                       thecurr;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> thelist;
};
