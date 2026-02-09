#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Time.hpp>
#include <Units_Token.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Transient.hpp>
#include <Standard_CString.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>

class Units_Lexicon : public Standard_Transient
{

public:
  Standard_EXPORT Units_Lexicon();

  Standard_EXPORT void Creates();

  occ::handle<NCollection_HSequence<occ::handle<Units_Token>>> Sequence() const;

  Standard_EXPORT void AddToken(const char* aword, const char* amean, const double avalue);

  virtual void Dump() const;

  DEFINE_STANDARD_RTTIEXT(Units_Lexicon, Standard_Transient)

private:
  occ::handle<NCollection_HSequence<occ::handle<Units_Token>>> thesequenceoftokens;
};

#include <Units_Token.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

inline occ::handle<NCollection_HSequence<occ::handle<Units_Token>>> Units_Lexicon::Sequence() const
{
  return thesequenceoftokens;
}

inline void Units_Lexicon::Dump() const
{
  int index;
  std::cout << " LEXICON : " << std::endl;
  for (index = 1; index <= thesequenceoftokens->Length(); index++)
    thesequenceoftokens->Value(index)->Dump(1, 0);
}
