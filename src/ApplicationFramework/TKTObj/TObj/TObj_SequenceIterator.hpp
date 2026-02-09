#pragma once

#include <NCollection_DataMap.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HExtendedString.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TObj_ObjectIterator.hpp>
class TObj_Object;

class TObj_SequenceIterator : public TObj_ObjectIterator
{

protected:
  Standard_EXPORT TObj_SequenceIterator();

public:
  Standard_EXPORT TObj_SequenceIterator(
    const occ::handle<NCollection_HSequence<occ::handle<TObj_Object>>>& theObjects,
    const occ::handle<Standard_Type>&                                   theType = nullptr);

public:
  Standard_EXPORT bool More() const override;

  Standard_EXPORT void Next() override;

  Standard_EXPORT occ::handle<TObj_Object> Value() const override;

protected:
  int                                                          myIndex;
  occ::handle<Standard_Type>                                   myType;
  occ::handle<NCollection_HSequence<occ::handle<TObj_Object>>> myObjects;

public:
  DEFINE_STANDARD_RTTIEXT(TObj_SequenceIterator, TObj_ObjectIterator)
};

#ifdef _MSC_VER
  #pragma once
#endif
