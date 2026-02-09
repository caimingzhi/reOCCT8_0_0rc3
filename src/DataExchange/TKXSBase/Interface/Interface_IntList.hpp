#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Boolean.hpp>

class Interface_IntList
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Interface_IntList();

  Standard_EXPORT Interface_IntList(const int nbe);

  Standard_EXPORT Interface_IntList(const Interface_IntList& other, const bool copied);

  Standard_EXPORT void Initialize(const int nbe);

  Standard_EXPORT void Internals(int&                                   nbrefs,
                                 occ::handle<NCollection_HArray1<int>>& ents,
                                 occ::handle<NCollection_HArray1<int>>& refs) const;

  Standard_EXPORT int NbEntities() const;

  Standard_EXPORT void SetNbEntities(const int nbe);

  Standard_EXPORT void SetNumber(const int number);

  Standard_EXPORT int Number() const;

  Standard_EXPORT Interface_IntList List(const int number, const bool copied = false) const;

  Standard_EXPORT void SetRedefined(const bool mode);

  Standard_EXPORT void Reservate(const int count);

  Standard_EXPORT void Add(const int ref);

  Standard_EXPORT int Length() const;

  Standard_EXPORT bool IsRedefined(const int num = 0) const;

  Standard_EXPORT int Value(const int num) const;

  Standard_EXPORT bool Remove(const int num);

  Standard_EXPORT void Clear();

  Standard_EXPORT void AdjustSize(const int margin = 0);

private:
  int                                   thenbe;
  int                                   thenbr;
  int                                   thenum;
  int                                   thecount;
  int                                   therank;
  occ::handle<NCollection_HArray1<int>> theents;
  occ::handle<NCollection_HArray1<int>> therefs;
};
