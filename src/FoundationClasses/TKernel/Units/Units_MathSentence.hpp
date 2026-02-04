#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Units_Sentence.hpp>

//! This class defines all the methods to create and
//! compute an algebraic formula.
class Units_MathSentence : public Units_Sentence
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates and returns a MathSentence object. The string
  //! <astring> describes an algebraic formula in natural
  //! language.
  Standard_EXPORT Units_MathSentence(const char* astring);
};

