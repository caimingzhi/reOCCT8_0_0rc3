#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Units_Sentence.hpp>

class Units_MathSentence : public Units_Sentence
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Units_MathSentence(const char* astring);
};
