#include <Units_Lexicon.hpp>

#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>
#include <Units_Token.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Units_Lexicon, Standard_Transient)

namespace
{

  struct LexiconItem
  {
    char   Prefix[10];
    char   Operation[2];
    double Value;
  };

  static const LexiconItem THE_LEXICON[] = {

    {"(", "S", 0.0},    {")", "S", 0.0},

    {"+", "O", 0.0},    {"-", "O", 0.0},    {"*", "O", 0.0},       {".", "O", 0.0},
    {"/", "O", 0.0},    {"**", "O", 0.0},

    {"\xB2", "P", 2.0},

    {"p2", "P", 2.0},   {"sq.", "P", 2.0},

    {"\xB3", "P", 3.0},

    {"cu.", "P", 3.0},

    {"y", "M", 1.E-24}, {"z", "M", 1.E-21}, {"a", "M", 1.E-18},    {"f", "M", 1.E-15},
    {"p", "M", 1.E-12}, {"n", "M", 1.E-09}, {"\xB5", "M", 1.E-06},

    {"m", "M", 1.E-03}, {"c", "M", 1.E-02}, {"d", "M", 1.E-01},    {"da", "M", 1.E+01},
    {"h", "M", 1.E+02}, {"k", "M", 1.E+03}, {"M", "M", 1.E+06},    {"G", "M", 1.E+09},
    {"T", "M", 1.E+12}, {"P", "M", 1.E+15}, {"E", "M", 1.E+18},    {"Z", "M", 1.E+21},
    {"Y", "M", 1.E+24},

    {"\xB6", "", M_PI},

    {"Pi", "", M_PI},
  };

} // namespace

Units_Lexicon::Units_Lexicon() = default;

void Units_Lexicon::Creates()
{
  thesequenceoftokens = new NCollection_HSequence<occ::handle<Units_Token>>();

  const int aNbLexiItems = sizeof(THE_LEXICON) / sizeof(LexiconItem);
  for (int anItemIter = 0; anItemIter < aNbLexiItems; ++anItemIter)
  {
    const LexiconItem& anItem = THE_LEXICON[anItemIter];
    if (thesequenceoftokens->IsEmpty())
    {
      occ::handle<Units_Token> aToken =
        new Units_Token(anItem.Prefix, anItem.Operation, anItem.Value);
      thesequenceoftokens->Prepend(aToken);
    }
    else
    {
      AddToken(anItem.Prefix, anItem.Operation, anItem.Value);
    }
  }
}

void Units_Lexicon::AddToken(const char* aword, const char* amean, const double avalue)
{
  occ::handle<Units_Token> token;
  occ::handle<Units_Token> referencetoken;
  bool                     found = false;
  int                      index;

  for (index = 1; index <= thesequenceoftokens->Length(); index++)
  {
    referencetoken = thesequenceoftokens->Value(index);
    if (referencetoken->Word() == aword)
    {
      referencetoken->Update(amean);
      found = true;
      break;
    }
    else if (!(referencetoken->Word() > aword))
    {
      token = new Units_Token(aword, amean, avalue);
      thesequenceoftokens->InsertBefore(index, token);
      found = true;
      break;
    }
  }
  if (!found)
  {
    token = new Units_Token(aword, amean, avalue);
    thesequenceoftokens->Append(token);
  }
}
