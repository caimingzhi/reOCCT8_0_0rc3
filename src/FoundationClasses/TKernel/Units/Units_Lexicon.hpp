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

//! This class defines a lexicon useful to analyse and
//! recognize the different key words included in a
//! sentence. The lexicon is stored in a sequence of
//! tokens.
class Units_Lexicon : public Standard_Transient
{

public:
  //! Creates an empty instance of Lexicon.
  Standard_EXPORT Units_Lexicon();

  //! Reads the file <afilename> to create a sequence of tokens
  //! stored in <thesequenceoftokens>.
  Standard_EXPORT void Creates();

  //! Returns the first item of the sequence of tokens.
  occ::handle<NCollection_HSequence<occ::handle<Units_Token>>> Sequence() const;

  //! Adds to the lexicon a new token with <aword>, <amean>,
  //! <avalue> as arguments. If there is already a token
  //! with the field <theword> equal to <aword>, the
  //! existing token is updated.
  Standard_EXPORT void AddToken(const char* aword, const char* amean, const double avalue);

  //! Useful for debugging.
  virtual void Dump() const;

  DEFINE_STANDARD_RTTIEXT(Units_Lexicon, Standard_Transient)

private:
  occ::handle<NCollection_HSequence<occ::handle<Units_Token>>> thesequenceoftokens;
};

#include <Units_Token.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

//=================================================================================================

inline occ::handle<NCollection_HSequence<occ::handle<Units_Token>>> Units_Lexicon::Sequence() const
{
  return thesequenceoftokens;
}

//=================================================================================================

inline void Units_Lexicon::Dump() const
{
  int index;
  std::cout << " LEXICON : " << std::endl;
  for (index = 1; index <= thesequenceoftokens->Length(); index++)
    thesequenceoftokens->Value(index)->Dump(1, 0);
}
