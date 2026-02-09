#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Units_Quantity.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Units_Unit.hpp>
class Units_UnitsSystem;
class Units_UnitsDictionary;
class TCollection_AsciiString;

class Units_Explorer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Units_Explorer();

  Standard_EXPORT Units_Explorer(const occ::handle<Units_UnitsSystem>& aunitssystem);

  Standard_EXPORT Units_Explorer(const occ::handle<Units_UnitsDictionary>& aunitsdictionary);

  Standard_EXPORT Units_Explorer(const occ::handle<Units_UnitsSystem>& aunitssystem,
                                 const char*                           aquantity);

  Standard_EXPORT Units_Explorer(const occ::handle<Units_UnitsDictionary>& aunitsdictionary,
                                 const char*                               aquantity);

  Standard_EXPORT void Init(const occ::handle<Units_UnitsSystem>& aunitssystem);

  Standard_EXPORT void Init(const occ::handle<Units_UnitsDictionary>& aunitsdictionary);

  Standard_EXPORT void Init(const occ::handle<Units_UnitsSystem>& aunitssystem,
                            const char*                           aquantity);

  Standard_EXPORT void Init(const occ::handle<Units_UnitsDictionary>& aunitsdictionary,
                            const char*                               aquantity);

  Standard_EXPORT bool MoreQuantity() const;

  Standard_EXPORT void NextQuantity();

  Standard_EXPORT TCollection_AsciiString Quantity() const;

  Standard_EXPORT bool MoreUnit() const;

  Standard_EXPORT void NextUnit();

  Standard_EXPORT TCollection_AsciiString Unit() const;

  Standard_EXPORT bool IsActive() const;

private:
  int                                                             thecurrentquantity{};
  occ::handle<NCollection_HSequence<occ::handle<Units_Quantity>>> thequantitiessequence;
  int                                                             thecurrentunit{};
  occ::handle<NCollection_HSequence<occ::handle<Units_Unit>>>     theunitssequence;
  occ::handle<NCollection_HSequence<int>>                         theactiveunitssequence;
};
