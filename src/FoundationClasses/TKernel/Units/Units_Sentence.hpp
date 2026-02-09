#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Units_Token.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_CString.hpp>
class Units_Lexicon;
class Units_Token;

class Units_Sentence
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Units_Sentence(const occ::handle<Units_Lexicon>& alexicon, const char* astring);

  Standard_EXPORT void SetConstants();

  occ::handle<NCollection_HSequence<occ::handle<Units_Token>>> Sequence() const;

  void Sequence(
    const occ::handle<NCollection_HSequence<occ::handle<Units_Token>>>& asequenceoftokens);

  Standard_EXPORT occ::handle<Units_Token> Evaluate();

  bool IsDone() const;

  void Dump() const;

private:
  occ::handle<NCollection_HSequence<occ::handle<Units_Token>>> thesequenceoftokens;
};

#include <Units_Token.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

inline occ::handle<NCollection_HSequence<occ::handle<Units_Token>>> Units_Sentence::Sequence() const
{
  return thesequenceoftokens;
}

inline void Units_Sentence::Sequence(
  const occ::handle<NCollection_HSequence<occ::handle<Units_Token>>>& asequenceoftokens)
{
  thesequenceoftokens = asequenceoftokens;
}

inline bool Units_Sentence::IsDone() const
{
  return thesequenceoftokens->Length() > 0;
}

inline void Units_Sentence::Dump() const
{
  int index;
  std::cout << " UNIT SENTENCE with : " << std::endl;
  for (index = 1; index <= thesequenceoftokens->Length(); index++)
    thesequenceoftokens->Value(index)->Dump(1, 1);
}
