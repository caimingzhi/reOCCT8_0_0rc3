#include <Units_Lexicon.hpp>
#include <Units_NoSuchType.hpp>
#include <Units_Operators.hpp>
#include <Units_Sentence.hpp>
#include <Units_ShiftedToken.hpp>
#include <Units_Token.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

static occ::handle<Units_Token> CreateTokenForNumber(const char* str)
{
  TCollection_AsciiString tstr    = str[0];
  bool                    IsPoint = false;
  size_t                  len     = strlen(str);
  for (size_t in = 1; in < len; in++)
  {
    if (str[in] == '0' || str[in] == '1' || str[in] == '2' || str[in] == '3' || str[in] == '4'
        || str[in] == '5' || str[in] == '6' || str[in] == '7' || str[in] == '8' || str[in] == '9')
    {
      tstr.AssignCat(str[in]);
    }
    else if (str[in] == '.' && !IsPoint)
    {
      tstr.AssignCat(str[in]);
      IsPoint = true;
    }
    else
      break;
  }
  return new Units_Token(tstr.ToCString(), "0");
}

Units_Sentence::Units_Sentence(const occ::handle<Units_Lexicon>& alexicon, const char* astring)
{
  int                      index;
  size_t                   i, limchain;
  occ::handle<Units_Token> token;
  occ::handle<Units_Token> referencetoken;

  thesequenceoftokens = new NCollection_HSequence<occ::handle<Units_Token>>();
  occ::handle<NCollection_HSequence<occ::handle<Units_Token>>> lstlexicon = alexicon->Sequence();
  if (lstlexicon.IsNull())
    throw Units_NoSuchType("BAD LEXICON descriptor");
  limchain = strlen(astring);
  i        = 0;

  TCollection_AsciiString tmpstr = astring;

  TCollection_AsciiString PrevMean;
  TCollection_AsciiString PrevWord;
  while (i < limchain)
  {
    bool                    IsFound  = false;
    TCollection_AsciiString LastWord = "";
    for (index = 1; index <= lstlexicon->Length(); index++)
    {
      referencetoken                = lstlexicon->Value(index);
      TCollection_AsciiString aword = referencetoken->Word();
      int                     num   = tmpstr.Search(aword);
      if (num == 1 && aword.Length() >= LastWord.Length())
      {
        token    = referencetoken->Creates();
        LastWord = aword;
        IsFound  = true;
      }
    }
    if (!IsFound)
    {

      LastWord = tmpstr.SubString(1, 1);
      if (!LastWord.IsIntegerValue())
      {

        thesequenceoftokens->Clear();
#ifdef OCCT_DEBUG
        std::cout << "Warning: can not create correct sentence from string: " << astring
                  << std::endl;
#endif
        return;
      }
      else
      {

        token    = CreateTokenForNumber(tmpstr.ToCString());
        LastWord = token->Word();
      }
    }
    if (i > 0)
    {

      if ((token->Mean() == "M" && (PrevMean == "M" || PrevMean == "MU" || PrevMean == "0"))
          || (token->Mean() == "U" && (PrevMean == "U" || PrevMean == "0"))
          || (token->Mean() == "O" && (PrevMean == "M" || PrevMean == "O"))
          || ((token->Word() == "+" || token->Word() == "-") && PrevWord != "(")
          || (token->Mean() == "S" && (PrevMean == "M"))
          || (token->Mean() == "0" && (PrevMean == "M" || PrevMean == "U" || PrevMean == "MU")))
      {

        thesequenceoftokens->Clear();
#ifdef OCCT_DEBUG
        std::cout << "Warning: can not create correct sentence from string: " << astring
                  << std::endl;
#endif
        return;
      }
    }
    thesequenceoftokens->Append(token);
    PrevMean = token->Mean();
    PrevWord = token->Word();
    i        = i + LastWord.Length();
    tmpstr.Remove(1, LastWord.Length());
  }
}

void Units_Sentence::SetConstants()
{
  int                      index;
  double                   value;
  occ::handle<Units_Token> token;
  TCollection_AsciiString  string;

  for (index = 1; index <= thesequenceoftokens->Length(); index++)
  {
    token = thesequenceoftokens->Value(index);
    if (token->Value() == 0.)
    {
      string = token->Word();
      if (string.IsRealValue())
      {
        value = string.RealValue();
        token->Mean("K");
        token->Value(value);
      }
    }
  }
}

static occ::handle<Units_Token> CalculateLocal(
  const occ::handle<NCollection_HSequence<occ::handle<Units_Token>>>& aSeq)
{

  occ::handle<Units_Token> tok1, tok2;
  int                      i, j;

  if (aSeq->Length() == 1)
  {
    return aSeq->Value(1);
  }

  if (aSeq->Length() == 2)
  {
    if (aSeq->Value(1)->Word() == "+")
      aSeq->Remove(1);
    if (aSeq->Value(1)->Word() == "-")
    {
      tok2                          = aSeq->Value(2);
      TCollection_AsciiString aword = "-";
      aword.AssignCat(tok2->Word());
      tok1 = new Units_Token(aword.ToCString(),
                             tok2->Mean().ToCString(),
                             tok2->Value() * (-1.0),
                             tok2->Dimensions());
      aSeq->Remove(1);
      aSeq->SetValue(1, tok1);
    }
    return aSeq->Value(1);
  }

  bool IsBracket = true;
  while (IsBracket)
  {
    for (i = 1; i <= aSeq->Length(); i++)
    {
      if (aSeq->Value(i)->Word() == "(")
      {
        occ::handle<NCollection_HSequence<occ::handle<Units_Token>>> TmpSeq =
          new NCollection_HSequence<occ::handle<Units_Token>>;
        int NbBrackets = 1;
        for (j = i + 1; j <= aSeq->Length(); j++)
        {
          if (aSeq->Value(j)->Word() == ")")
            NbBrackets--;
          if (aSeq->Value(j)->Word() == "(")
            NbBrackets++;
          if (NbBrackets > 0)
            TmpSeq->Append(aSeq->Value(j));
          else
            break;
        }
        tok1 = CalculateLocal(TmpSeq);
        aSeq->Remove(i + 1, j);
        aSeq->SetValue(i, tok1);
        break;
      }
    }
    if (i > aSeq->Length())
    {
      IsBracket = false;

      for (i = 1; i <= aSeq->Length(); i++)
      {
        if (aSeq->Value(i)->Word() == "**")
        {
          tok1 = aSeq->Value(i - 1);
          tok2 = aSeq->Value(i + 1);
          tok1 = pow(tok1, tok2);
          aSeq->Remove(i);
          aSeq->Remove(i);
          aSeq->SetValue(i - 1, tok1);
          i--;
        }
      }

      for (i = 1; i <= aSeq->Length(); i++)
      {
        if (aSeq->Value(i)->Mean() == "O")
        {
          tok1 = aSeq->Value(i - 1);
          tok2 = aSeq->Value(i + 1);
          if (aSeq->Value(i)->Word() == "/")
            tok1 = tok1 / tok2;
          else
            tok1 = tok1 * tok2;
          aSeq->Remove(i);
          aSeq->Remove(i);
          aSeq->SetValue(i - 1, tok1);
          i--;
        }
      }
    }
  }
  return tok1;
}

occ::handle<Units_Token> Units_Sentence::Evaluate()
{
  occ::handle<Units_Token> rtoken, ktoken;
  if (thesequenceoftokens->Length() == 0)
    return rtoken;

  rtoken = CalculateLocal(thesequenceoftokens);

  return rtoken;
}
