#include <Units.hpp>
#include <Units_MathSentence.hpp>

Units_MathSentence::Units_MathSentence(const char* astring)
    : Units_Sentence(Units::LexiconFormula(), astring)
{
  SetConstants();
}
