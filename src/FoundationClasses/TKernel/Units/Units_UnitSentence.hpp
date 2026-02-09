#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Units_Sentence.hpp>
#include <Standard_CString.hpp>
#include <Units_Quantity.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

class Units_UnitSentence : public Units_Sentence
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Units_UnitSentence(const char* astring);

  Standard_EXPORT Units_UnitSentence(
    const char*                                                            astring,
    const occ::handle<NCollection_HSequence<occ::handle<Units_Quantity>>>& aquantitiessequence);

  Standard_EXPORT void Analyse();

  Standard_EXPORT void SetUnits(
    const occ::handle<NCollection_HSequence<occ::handle<Units_Quantity>>>& aquantitiessequence);
};
