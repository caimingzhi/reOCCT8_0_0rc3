#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Units_Sentence.hpp>
#include <Standard_CString.hpp>
#include <Units_Quantity.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

//! This class describes all the facilities to
//! manipulate and compute units contained in a string
//! expression.
class Units_UnitSentence : public Units_Sentence
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates and returns a UnitSentence. The string
  //! <astring> describes in natural language the unit or
  //! the composed unit to be analysed.
  Standard_EXPORT Units_UnitSentence(const char* astring);

  //! Creates and returns a UnitSentence. The string
  //! <astring> describes in natural language the unit to be
  //! analysed. The sequence of physical quantities
  //! <asequenceofquantities> describes the available
  //! dictionary of units you want to use.
  Standard_EXPORT Units_UnitSentence(
    const char*                                                            astring,
    const occ::handle<NCollection_HSequence<occ::handle<Units_Quantity>>>& aquantitiessequence);

  //! Analyzes the sequence of tokens created by the
  //! constructor to find the true significance of each
  //! token.
  Standard_EXPORT void Analyse();

  //! For each token which represents a unit, finds in the
  //! sequence of physical quantities all the
  //! characteristics of the unit found.
  Standard_EXPORT void SetUnits(
    const occ::handle<NCollection_HSequence<occ::handle<Units_Quantity>>>& aquantitiessequence);
};
