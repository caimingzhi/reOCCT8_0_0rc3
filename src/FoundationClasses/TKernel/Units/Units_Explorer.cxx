#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Units_Explorer.hpp>
#include <Units_Unit.hpp>
#include <Units_UnitsDictionary.hpp>
#include <Units_UnitsSystem.hpp>

Units_Explorer::Units_Explorer()
{
  thecurrentquantity = 1;
  thecurrentunit     = 1;
}

Units_Explorer::Units_Explorer(const occ::handle<Units_UnitsSystem>& aunitssystem)
{
  Init(aunitssystem);
}

Units_Explorer::Units_Explorer(const occ::handle<Units_UnitsDictionary>& aunitsdictionary)
{
  Init(aunitsdictionary);
}

Units_Explorer::Units_Explorer(const occ::handle<Units_UnitsSystem>& aunitssystem,
                               const char*                           aquantity)
{
  Init(aunitssystem, aquantity);
}

Units_Explorer::Units_Explorer(const occ::handle<Units_UnitsDictionary>& aunitsdictionary,
                               const char*                               aquantity)
{
  Init(aunitsdictionary, aquantity);
}

void Units_Explorer::Init(const occ::handle<Units_UnitsSystem>& aunitssystem)
{
  thecurrentquantity     = 1;
  thequantitiessequence  = aunitssystem->QuantitiesSequence();
  theactiveunitssequence = aunitssystem->ActiveUnitsSequence();
  if (MoreQuantity())
    theunitssequence = thequantitiessequence->Value(thecurrentquantity)->Sequence();
  thecurrentunit = 1;
}

void Units_Explorer::Init(const occ::handle<Units_UnitsDictionary>& aunitsdictionary)
{
  int index;
  thecurrentquantity     = 1;
  thequantitiessequence  = aunitsdictionary->Sequence();
  theactiveunitssequence = new NCollection_HSequence<int>();
  for (index = 1; index <= thequantitiessequence->Length(); index++)
  {
    theactiveunitssequence->Append(1);
  }

  if (MoreQuantity())
    theunitssequence = thequantitiessequence->Value(thecurrentquantity)->Sequence();
  thecurrentunit = 1;
}

void Units_Explorer::Init(const occ::handle<Units_UnitsSystem>& aunitssystem, const char* aquantity)
{
  int index;
  thecurrentquantity     = 0;
  thequantitiessequence  = aunitssystem->QuantitiesSequence();
  theactiveunitssequence = aunitssystem->ActiveUnitsSequence();
  for (index = 1; index <= thequantitiessequence->Length(); index++)
  {
    if (thequantitiessequence->Value(index)->Name() == aquantity)
    {
      thecurrentquantity = index;
      thecurrentunit     = 1;
      theunitssequence   = thequantitiessequence->Value(index)->Sequence();
      return;
    }
  }

#ifdef OCCT_DEBUG
  std::cout << " La grandeur physique " << aquantity << " n'existe pas." << std::endl;
#endif
}

void Units_Explorer::Init(const occ::handle<Units_UnitsDictionary>& aunitsdictionary,
                          const char*                               aquantity)
{
  occ::handle<Units_Quantity> quantity;
  int                         index;
  thecurrentquantity     = 0;
  thequantitiessequence  = aunitsdictionary->Sequence();
  theactiveunitssequence = new NCollection_HSequence<int>();
  for (index = 1; index <= thequantitiessequence->Length(); index++)
  {
    theactiveunitssequence->Append(1);
  }

  for (index = 1; index <= thequantitiessequence->Length(); index++)
  {
    quantity = thequantitiessequence->Value(index);
    if (quantity->Name() == aquantity)
    {
      thecurrentquantity = index;
      thecurrentunit     = 1;
      theunitssequence   = thequantitiessequence->Value(index)->Sequence();
      return;
    }
  }

#ifdef OCCT_DEBUG
  std::cout << " La grandeur physique " << aquantity << " n'existe pas." << std::endl;
#endif
}

bool Units_Explorer::MoreQuantity() const
{
  return thecurrentquantity <= thequantitiessequence->Length();
}

void Units_Explorer::NextQuantity()
{
  thecurrentquantity++;
  thecurrentunit = 1;
  if (MoreQuantity())
    theunitssequence = thequantitiessequence->Value(thecurrentquantity)->Sequence();
}

TCollection_AsciiString Units_Explorer::Quantity() const
{
  return thequantitiessequence->Value(thecurrentquantity)->Name();
}

bool Units_Explorer::MoreUnit() const
{
  return thecurrentunit <= theunitssequence->Length();
}

void Units_Explorer::NextUnit()
{
  thecurrentunit++;
}

TCollection_AsciiString Units_Explorer::Unit() const
{
  return theunitssequence->Value(thecurrentunit)->SymbolsSequence()->Value(1)->String();
}

bool Units_Explorer::IsActive() const
{
  return theactiveunitssequence->Value(thecurrentquantity) == thecurrentunit;
}
