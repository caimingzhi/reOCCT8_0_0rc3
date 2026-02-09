

#include <Interface_Check.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ParamList.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <StepData_ESDescr.hpp>
#include <StepData_FieldList.hpp>
#include <StepData_PDescr.hpp>
#include <StepData_SelectArrReal.hpp>
#include <StepData_SelectInt.hpp>
#include <StepData_SelectMember.hpp>
#include <StepData_SelectNamed.hpp>
#include <StepData_SelectReal.hpp>
#include <StepData_SelectType.hpp>
#include <StepData_StepReaderData.hpp>
#include <NCollection_IncAllocator.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>
#include <NCollection_UtfIterator.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <NCollection_IndexedMap.hpp>
#include <StepData_UndefinedEntity.hpp>
#include <Resource_Unicode.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(StepData_StepReaderData, Interface_FileReaderData)

#define Maxlst 64

static int convertCharacterTo16bit(const char16_t theCharacter)
{
  switch (theCharacter)
  {
    case '0':
      return 0;
    case '1':
      return 1;
    case '2':
      return 2;
    case '3':
      return 3;
    case '4':
      return 4;
    case '5':
      return 5;
    case '6':
      return 6;
    case '7':
      return 7;
    case '8':
      return 8;
    case '9':
      return 9;
    case 'A':
    case 'a':
      return 10;
    case 'B':
    case 'b':
      return 11;
    case 'C':
    case 'c':
      return 12;
    case 'D':
    case 'd':
      return 13;
    case 'E':
    case 'e':
      return 14;
    case 'F':
    case 'f':
      return 15;
    default:
      return 0;
  }
}

void StepData_StepReaderData::cleanText(const occ::handle<TCollection_HAsciiString>& theVal) const
{
  if (theVal->Length() == 2)
  {
    theVal->Clear();
    return;
  }
  TCollection_ExtendedString aResString;
  const bool                 toConversion = mySourceCodePage != Resource_FormatType_NoConversion;
  Resource_Unicode::ConvertFormatToUnicode(mySourceCodePage, theVal->ToCString() + 1, aResString);
  int                        aResStringSize = aResString.Length() - 1;
  TCollection_ExtendedString aTempExtString;
  int                        aSetCharInd = 1;

  Resource_FormatType aLocalFormatType = Resource_FormatType_iso8859_1;

  for (int aStringInd = 1; aStringInd <= aResStringSize; ++aStringInd)
  {
    const char16_t aChar = aResString.Value(aStringInd);
    aSetCharInd          = aStringInd;
    if (aChar == '\\' && aStringInd <= aResStringSize - 3)
    {
      bool           isConverted  = false;
      const char16_t aDirChar     = aResString.Value(aStringInd + 1);
      const bool     isSecSlash   = aResString.Value(aStringInd + 2) == '\\';
      const bool     isThirdSlash = aResString.Value(aStringInd + 3) == '\\';

      if (aDirChar == 'P' && isThirdSlash)
      {
        const char aPageId = UpperCase(static_cast<char>(aResString.Value(aStringInd + 2) & 255));
        if (aPageId >= 'A' && aPageId <= 'I')
        {
          aLocalFormatType = (Resource_FormatType)(Resource_FormatType_iso8859_1 + (aPageId - 'A'));
        }
        else
        {
          thecheck->AddWarning(
            "String control directive \\P*\\ with an unsupported symbol in place of *");
        }
        isConverted = true;
        aStringInd += 3;
      }

      else if (aDirChar == 'S' && isSecSlash)
      {
        char       aResChar         = static_cast<char>(aResString.Value(aStringInd + 3) | 0x80);
        const char aStrForCovert[2] = {aResChar, '\0'};
        Resource_Unicode::ConvertFormatToUnicode(aLocalFormatType, aStrForCovert, aTempExtString);
        isConverted = true;
        aStringInd += 3;
      }

      else if (aDirChar == 'X' && aStringInd <= aResStringSize - 4 && isSecSlash)
      {
        char aResChar = (char)convertCharacterTo16bit(aResString.Value(aStringInd + 3));
        aResChar =
          (aResChar << 4) | (char)convertCharacterTo16bit(aResString.Value(aStringInd + 4));
        const char aStrForConvert[2] = {aResChar, '\0'};

        aTempExtString = TCollection_ExtendedString(aStrForConvert, false);

        isConverted = true;
        aStringInd += 4;
      }

      else if (aDirChar == 'X' && isThirdSlash)
      {
        int  aFirstInd = aStringInd + 3;
        int  aLastInd  = aStringInd;
        bool isClosed  = false;

        for (; aStringInd <= aResStringSize && !isClosed; ++aStringInd)
        {
          if (aResStringSize - aStringInd > 2 && aResString.Value(aStringInd) == '\\'
              && aResString.Value(aStringInd + 1) == 'X' && aResString.Value(aStringInd + 2) == '0'
              && aResString.Value(aStringInd + 3) == '\\')
          {
            aLastInd   = aStringInd - 1;
            aStringInd = aStringInd + 2;
            isClosed   = true;
          }
        }
        if (!isClosed)
        {
          aLastInd = aStringInd = aResStringSize;
        }
        const int aStrLen = aLastInd - aFirstInd;

        if (aResString.Value(aFirstInd - 1) == '2' && aResStringSize - aFirstInd > 3)
        {
          int anIterStep = (aStrLen % 4 == 0) ? 4 : 3;
          if (aStrLen % anIterStep)
          {
            aTempExtString.AssignCat('?');
            thecheck->AddWarning(
              "String control directive \\X2\\ is followed by number of digits not multiple of 4");
          }
          else
          {
            char16_t aUtfCharacter = '\0';
            for (int aCharInd = 1; aCharInd <= aStrLen; ++aCharInd)
            {
              aUtfCharacter |= convertCharacterTo16bit(aResString.Value(aCharInd + aFirstInd));
              if (aCharInd % anIterStep == 0)
              {
                aTempExtString.AssignCat(aUtfCharacter);
                aUtfCharacter = '\0';
              }
              aUtfCharacter = aUtfCharacter << 4;
            }
          }
        }

        else if (aResString.Value(aFirstInd - 1) == '4' && aResStringSize - aFirstInd > 7)
        {
          if (aStrLen % 8)
          {
            aTempExtString.AssignCat('?');
            thecheck->AddWarning(
              "String control directive \\X4\\ is followed by number of digits not multiple of 8");
          }
          else
          {
            char32_t aUtfCharacter[2] = {'\0', '\0'};
            for (int aCharInd = 1; aCharInd <= aStrLen; ++aCharInd)
            {
              aUtfCharacter[0] |= convertCharacterTo16bit(aResString.Value(aCharInd + aFirstInd));
              if (aCharInd % 8 == 0)
              {
                NCollection_UtfIterator<char32_t> aUtfIter(aUtfCharacter);
                char16_t                          aStringBuffer[3];
                char16_t*                         aUtfPntr = aUtfIter.GetUtf16(aStringBuffer);
                *aUtfPntr++                                = '\0';
                TCollection_ExtendedString aUtfString(aStringBuffer);
                aTempExtString.AssignCat(aUtfString);
                aUtfCharacter[0] = '\0';
              }
              aUtfCharacter[0] = aUtfCharacter[0] << 4;
            }
          }
        }
        isConverted = true;
      }
      if (isConverted)
      {
        if (toConversion)
        {

          aResStringSize -= aStringInd - aSetCharInd - aTempExtString.Length() + 1;

          aResString.SetValue(aSetCharInd, aTempExtString);
          aSetCharInd += aTempExtString.Length();
          aResString.SetValue(aSetCharInd, aResString.ToExtString() + aStringInd);
          aStringInd = aSetCharInd - 1;
          aResString.Trunc(aResStringSize);
          ;
        }
        aTempExtString.Clear();
        continue;
      }
    }
    if (aStringInd <= aResStringSize - 1)
    {
      const char16_t aCharNext = aResString.Value(aStringInd + 1);
      if (aCharNext == aChar && (aChar == '\'' || aChar == '\\'))
      {

        aResString.SetValue(aSetCharInd, aResString.ToExtString() + aStringInd);

        aResStringSize--;
        aResString.Trunc(aResStringSize);
      }
      else if (aChar == '\\')
      {
        const bool isDirective =
          aStringInd <= aResStringSize - 2 && aResString.Value(aStringInd + 2) == '\\';
        if (isDirective)
        {
          if (aCharNext == 'N')
          {
            aResString.SetValue(aSetCharInd++, '\n');

            aResString.SetValue(aSetCharInd, aResString.ToExtString() + aStringInd + 2);
            aResStringSize -= 2;
            aResString.Trunc(aResStringSize);
            continue;
          }
          else if (aCharNext == 'T')
          {
            aResString.SetValue(aSetCharInd++, '\t');
            aResString.SetValue(aSetCharInd, aResString.ToExtString() + aStringInd + 2);

            aResStringSize -= 2;
            aResString.Trunc(aResStringSize);
            continue;
          }
        }
      }
    }
    if (aChar == '\n' || aChar == '\r')
    {
      aResString.SetValue(aSetCharInd, aResString.ToExtString() + aStringInd);
      aResStringSize--;
      aResString.Trunc(aResStringSize);
      aStringInd--;
    }
  }
  theVal->Clear();
  aResString.Trunc(aResStringSize);
  TCollection_AsciiString aTmpString(aResString, 0);
  theVal->AssignCat(aTmpString.ToCString());
}

StepData_StepReaderData::StepData_StepReaderData(const int                 nbheader,
                                                 const int                 nbtotal,
                                                 const int                 nbpar,
                                                 const Resource_FormatType theSourceCodePage)
    : Interface_FileReaderData(nbtotal, nbpar),
      theidents(1, nbtotal),
      thetypes(1, nbtotal),
      mySourceCodePage(theSourceCodePage)
{

  thenbscop = 0;
  thenbents = 0;
  thelastn  = 0;
  thenbhead = nbheader;

  thecheck = new Interface_Check;
}

void StepData_StepReaderData::SetRecord(const int   num,
                                        const char* ident,
                                        const char* type,
                                        const int)
{
  int numlst;

  if (type[0] != '(')
    thenbents++;

  thetypes.ChangeValue(num) = thenametypes.Add(TCollection_AsciiString(type));

  if (ident[0] == '$')
  {
    if (strlen(ident) > 2)
      numlst = atoi(&ident[1]);
    else
      numlst = ident[1] - 48;
    if (thelastn < numlst)
      thelastn = numlst;
    theidents.SetValue(num, -2 - numlst);
  }
  else if (ident[0] == '#')
  {
    numlst = atoi(&ident[1]);
    theidents.SetValue(num, numlst);
    if (numlst == 0 && num > thenbhead)
    {

      for (int prev = num - 1; prev > thenbhead; prev--)
      {
        if (theidents(prev) >= 0)
        {

          themults.Bind(prev, num);
          if (thenametypes.FindKey(thetypes.Value(num))
                .IsLess(thenametypes.FindKey(thetypes.Value(prev))))
          {

            TCollection_AsciiString errm("Complex Type incorrect : ");
            errm.AssignCat(thenametypes.FindKey(thetypes.Value(prev)));
            errm.AssignCat(" / ");
            errm.AssignCat(thenametypes.FindKey(thetypes.Value(num)));
            errm.AssignCat(" ... ");
            while (theidents(prev) <= 0)
            {
              prev--;
              if (prev <= 0)
                break;
            }

            Message_Messenger::StreamBuffer sout = Message::SendTrace();
            sout << "  ***  Incorrect record " << num << " (on " << NbRecords() << " -> "
                 << num * 100 / NbRecords() << " % in File)  ***";
            if (prev > 0)
              sout << "  Ident #" << theidents(prev);
            sout << "\n" << errm << std::endl;
            thecheck->AddWarning(errm.ToCString(), "Complex Type incorrect : ");
          }
          break;
        }
      }
    }
  }
  else if (!strcmp(ident, "SCOPE"))
  {
    theidents.SetValue(num, -1);
    thenbscop++;
  }
  else if (!strcmp(ident, "ENDSCOPE"))
    theidents.SetValue(num, -2);
}

void StepData_StepReaderData::AddStepParam(const int                 num,
                                           const char*               aval,
                                           const Interface_ParamType atype,
                                           const int                 nument)
{
  if (atype == Interface_ParamSub)
  {
    int numid = 0;
    if (aval[2] != '\0')
    {
      numid = atoi(&aval[1]);

      Interface_FileReaderData::AddParam(num, aval, atype, numid);
    }
    else
    {
      char* numlstchar = (char*)(aval + 1);
      numid            = (*numlstchar) - 48;

      Interface_FileReaderData::AddParam(num, aval, atype, numid);
    }
  }
  else if (atype == Interface_ParamIdent)
  {
    int numid = atoi(&aval[1]);
    Interface_FileReaderData::AddParam(num, aval, atype, numid);
  }
  else
  {
    Interface_FileReaderData::AddParam(num, aval, atype, nument);
  }
}

const TCollection_AsciiString& StepData_StepReaderData::RecordType(const int num) const
{
  return thenametypes.FindKey(thetypes.Value(num));
}

const char* StepData_StepReaderData::CType(const int num) const
{
  return thenametypes.FindKey(thetypes.Value(num)).ToCString();
}

int StepData_StepReaderData::RecordIdent(const int num) const
{
  return theidents(num);
}

int StepData_StepReaderData::SubListNumber(const int num, const int nump, const bool aslast) const
{
  if (nump == 0 || nump > NbParams(num))
    return 0;
  const Interface_FileParameter& FP = Param(num, nump);
  if (FP.ParamType() != Interface_ParamSub)
    return 0;
  if (aslast)
  {
    if (nump != NbParams(num))
      return 0;
  }
  return FP.EntityNumber();
}

bool StepData_StepReaderData::IsComplex(const int num) const
{

  return themults.IsBound(num);
}

void StepData_StepReaderData::ComplexType(
  const int                                      num,
  NCollection_Sequence<TCollection_AsciiString>& types) const
{
  if (theidents(num) < 0)
    return;
  for (int i = num; i > 0; i = NextForComplex(i))
  {
    types.Append(RecordType(i));
  }
}

int StepData_StepReaderData::NextForComplex(const int num) const
{
  int next = 0;
  if (themults.IsBound(num))
    next = themults.Find(num);
  return next;
}

bool StepData_StepReaderData::NamedForComplex(const char*                   name,
                                              const int                     num0,
                                              int&                          num,
                                              occ::handle<Interface_Check>& ach) const
{

  int n = (num <= 0 ? num0 : NextForComplex(num));

  if ((n != 0) && (!strcmp(RecordType(n).ToCString(), name)))
  {
    num = n;
    return true;
  }

  if (n == 0)
    NamedForComplex(name, num0, n, ach);

  char        txtmes[200];
  const char* errmess = "Parameter n0.%d (%s) not a LIST";
  Sprintf(txtmes, errmess, num0, name);
  for (n = num0; n > 0; n = NextForComplex(n))
  {
    if (!strcmp(RecordType(n).ToCString(), name))
    {
      num     = n;
      errmess = "Complex Record n0.%d, member type %s not in alphabetic order";
      Sprintf(txtmes, errmess, num0, name);
      ach->AddWarning(txtmes, errmess);
      return false;
    }
  }
  num     = 0;
  errmess = "Complex Record n0.%d, member type %s not found";
  Sprintf(txtmes, errmess, num0, name);
  ach->AddFail(txtmes, errmess);
  return false;
}

bool StepData_StepReaderData::NamedForComplex(const char*                   theName,
                                              const char*                   theShortName,
                                              const int                     num0,
                                              int&                          num,
                                              occ::handle<Interface_Check>& ach) const
{
  int n = (num <= 0 ? num0 : NextForComplex(num));

  if ((n != 0)
      && (!strcmp(RecordType(n).ToCString(), theName)
          || !strcmp(RecordType(n).ToCString(), theShortName)))
  {
    num = n;
    return true;
  }

  char        txtmes[200];
  const char* errmess = "Parameter n0.%d (%s) not a LIST";
  Sprintf(txtmes, errmess, num0, theName);
  for (n = num0; n > 0; n = NextForComplex(n))
  {
    if (!strcmp(RecordType(n).ToCString(), theName)
        || !strcmp(RecordType(n).ToCString(), theShortName))
    {
      num     = n;
      errmess = "Complex Record n0.%d, member type %s not in alphabetic order";
      Sprintf(txtmes, errmess, num0, theName);
      ach->AddWarning(txtmes, errmess);
      return false;
    }
  }
  num     = 0;
  errmess = "Complex Record n0.%d, member type %s not found";
  Sprintf(txtmes, errmess, num0, theName);
  ach->AddFail(txtmes, errmess);
  return false;
}

bool StepData_StepReaderData::CheckNbParams(const int                     num,
                                            const int                     nbreq,
                                            occ::handle<Interface_Check>& ach,
                                            const char*                   mess) const
{
  if (NbParams(num) == nbreq)
    return true;
  char        txtmes[200];
  const char* errmess;
  if (mess[0] == '\0')
    errmess = "Count of Parameters is not %d";
  else
    errmess = "Count of Parameters is not %d for %s";
  Sprintf(txtmes, errmess, nbreq, mess);
  ach->AddFail(txtmes, errmess);
  return false;
}

bool StepData_StepReaderData::ReadSubList(const int                     num,
                                          const int                     nump,
                                          const char*                   mess,
                                          occ::handle<Interface_Check>& ach,
                                          int&                          numsub,
                                          const bool                    optional,
                                          const int,
                                          const int) const
{
  char txtmes[200];
  numsub = SubListNumber(num, nump, false);
  if (numsub > 0)
  {
    const int aNbParams = NbParams(numsub);
    if (aNbParams == 0)
    {
      const char* anErrMess = "Parameter n0.%d (%s) is an empty LIST";
      Sprintf(txtmes, anErrMess, nump, mess);
      ach->AddWarning(txtmes, anErrMess);
    }
    return true;
  }

  numsub      = 0;
  bool isvoid = (Param(num, nump).ParamType() == Interface_ParamVoid);
  if (isvoid && optional)
    return false;

  const char* errmess = "Parameter n0.%d (%s) not a LIST";
  Sprintf(txtmes, errmess, nump, mess);
  ach->AddFail(txtmes, errmess);
  return false;
}

int StepData_StepReaderData::ReadSub(const int                           numsub,
                                     const char*                         mess,
                                     occ::handle<Interface_Check>&       ach,
                                     const occ::handle<StepData_PDescr>& descr,
                                     occ::handle<Standard_Transient>&    val) const
{
  int nbp = NbParams(numsub);
  if (nbp == 0)
    return 0;
  const TCollection_AsciiString& rectyp = RecordType(numsub);
  if (nbp == 1 && rectyp.ToCString()[0] != '(')
  {

    occ::handle<StepData_SelectNamed> sn = new StepData_SelectNamed;
    val                                  = sn;
    sn->SetName(rectyp.ToCString());
    occ::handle<Standard_Transient> aSN = sn;
    if (ReadAny(numsub, 1, mess, ach, descr, aSN))
      return sn->Kind();
    else
      return 0;
  }

  const Interface_FileParameter&                                          FP0 = Param(numsub, 1);
  Interface_ParamType                                                     FT, FT0 = FP0.ParamType();
  const char*                                                             str = FP0.CValue();
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>       htr;
  occ::handle<NCollection_HArray1<int>>                                   hin;
  occ::handle<NCollection_HArray1<double>>                                hre;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> hst;
  int                                                                     kod = 0;
  switch (FT0)
  {
    case Interface_ParamMisc:
      return -1;
    case Interface_ParamInteger:
      kod = 1;
      break;
    case Interface_ParamReal:
      kod = 5;
      break;
    case Interface_ParamIdent:
      kod = 7;
      break;
    case Interface_ParamVoid:
      kod = 0;
      break;
    case Interface_ParamText:
      kod = 6;
      break;
    case Interface_ParamEnum:
      kod = 4;
      break;

    case Interface_ParamLogical:
      return -1;
    case Interface_ParamSub:
      kod = 0;
      break;
    case Interface_ParamHexa:
      return -1;
    case Interface_ParamBinary:
      return -1;
    default:
      return -1;
  }
  if (kod == 1 || kod == 3)
  {
    hin = new NCollection_HArray1<int>(1, nbp);
    val = hin;
  }
  else if (kod == 5)
  {
    hre = new NCollection_HArray1<double>(1, nbp);
    val = hre;
  }
  else if (kod == 6)
  {
    hst = new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, nbp);
    val = hst;
  }
  else
  {
    htr = new NCollection_HArray1<occ::handle<Standard_Transient>>(1, nbp);
    val = htr;
  }

  for (int ip = 1; ip <= nbp; ip++)
  {
    const Interface_FileParameter& FP = Param(numsub, ip);
    str                               = FP.CValue();
    FT                                = FP.ParamType();
    switch (kod)
    {
      case 1:
      {
        if (FT != Interface_ParamInteger)
        {
          kod = 0;
          break;
        }
        hin->SetValue(ip, atoi(str));
        break;
      }
      case 2:
      case 3:
      {
        if (FT != Interface_ParamEnum)
        {
          kod = 0;
          break;
        }
        if (!strcmp(str, ".F."))
          hin->SetValue(ip, 0);
        else if (!strcmp(str, ".T."))
          hin->SetValue(ip, 1);
        else if (!strcmp(str, ".U."))
          hin->SetValue(ip, 2);
        else
          kod = 0;
        break;
      }
      case 4:
      {
        if (FT != Interface_ParamEnum)
        {
          kod = 0;
          break;
        }
        occ::handle<StepData_SelectNamed> sn = new StepData_SelectNamed;
        sn->SetEnum(-1, str);
        htr->SetValue(ip, sn);
        break;
      }
      case 5:
      {
        if (FT != Interface_ParamReal)
        {
          kod = 0;
          break;
        }
        hre->SetValue(ip, Interface_FileReaderData::Fastof(str));
        break;
      }
      case 6:
      {
        if (FT != Interface_ParamText)
        {
          kod = 0;
          break;
        }
        occ::handle<TCollection_HAsciiString> txt = new TCollection_HAsciiString(str);
        cleanText(txt);
        hst->SetValue(ip, txt);
        break;
      }
      case 7:
      {
        occ::handle<Standard_Transient> ent = BoundEntity(FP.EntityNumber());
        htr->SetValue(ip, ent);
        break;
      }
      default:
        break;
    }

    if (kod > 0)
      continue;

    if (htr.IsNull())
    {
      htr = new NCollection_HArray1<occ::handle<Standard_Transient>>(1, nbp);
      val = htr;
      int jp;
      if (!hin.IsNull())
      {
        for (jp = 1; jp < ip; jp++)
        {
          occ::handle<StepData_SelectInt> sin = new StepData_SelectInt;
          sin->SetInt(hin->Value(jp));
          htr->SetValue(jp, sin);
        }
      }
      if (!hre.IsNull())
      {
        for (jp = 1; jp < ip; jp++)
        {
          occ::handle<StepData_SelectReal> sre = new StepData_SelectReal;
          sre->SetReal(hre->Value(jp));
          htr->SetValue(jp, sre);
        }
      }
      if (!hst.IsNull())
      {
        for (jp = 1; jp < ip; jp++)
        {
          htr->SetValue(jp, hst->Value(jp));
        }
      }
    }

    switch (FT)
    {
      case Interface_ParamMisc:
        break;
      case Interface_ParamInteger:
      {
        occ::handle<StepData_SelectInt> sin = new StepData_SelectInt;
        sin->SetInteger(atoi(str));
        htr->SetValue(ip, sin);
        break;
      }
      case Interface_ParamReal:
      {
        occ::handle<StepData_SelectReal> sre = new StepData_SelectReal;
        sre->SetReal(Interface_FileReaderData::Fastof(str));
        break;
      }
      case Interface_ParamIdent:
        htr->SetValue(ip, BoundEntity(FP.EntityNumber()));
        break;
      case Interface_ParamVoid:
        break;
      case Interface_ParamEnum:
      {
        occ::handle<StepData_SelectInt>   sin;
        occ::handle<StepData_SelectNamed> sna;
        int                               logic = -1;

        StepData_Logical slog = StepData_LUnknown;
        if (str[0] == '.' && str[2] == '.' && str[3] == '\0')
        {
          if (str[1] == 'F')
          {
            slog  = StepData_LFalse;
            logic = 0;
          }
          else if (str[1] == 'T')
          {
            slog  = StepData_LTrue;
            logic = 1;
          }
          else if (str[1] == 'U')
          {
            slog  = StepData_LUnknown;
            logic = 2;
          }
        }
        if (logic >= 0)
        {
          sin = new StepData_SelectInt;
          sin->SetLogical(slog);
          htr->SetValue(ip, sin);
        }
        else
        {
          sna = new StepData_SelectNamed;
          sna->SetEnum(logic, str);
          htr->SetValue(ip, sna);
        }
        break;
      }
      case Interface_ParamLogical:
        break;
      case Interface_ParamText:
      {
        occ::handle<TCollection_HAsciiString> txt = new TCollection_HAsciiString(str);
        cleanText(txt);
        htr->SetValue(ip, txt);
        break;
      }
      case Interface_ParamSub:
      {
        occ::handle<Standard_Transient> sub;
        int                             nent = FP.EntityNumber();
        int                             kind = ReadSub(nent, mess, ach, descr, sub);
        if (kind < 0)
          break;
        htr->SetValue(ip, sub);
        break;
      }
      case Interface_ParamHexa:
        break;
      case Interface_ParamBinary:
        break;
      default:
        break;
    }
    return -1;
  }
  return 8;
}

bool StepData_StepReaderData::ReadMember(const int                           num,
                                         const int                           nump,
                                         const char*                         mess,
                                         occ::handle<Interface_Check>&       ach,
                                         occ::handle<StepData_SelectMember>& val) const
{
  occ::handle<Standard_Transient> v = val;
  occ::handle<StepData_PDescr>    nuldescr;
  if (v.IsNull())
  {
    return ReadAny(num, nump, mess, ach, nuldescr, v)
           && !(val = occ::down_cast<StepData_SelectMember>(v)).IsNull();
  }
  bool res = ReadAny(num, nump, mess, ach, nuldescr, v);
  if (v == val)
    return res;

  char        txtmes[200];
  const char* errmess = "Parameter n0.%d (%s) : does not match SELECT clause";
  Sprintf(txtmes, errmess, nump, mess);
  ach->AddFail(txtmes, errmess);
  return false;
}

bool StepData_StepReaderData::ReadField(const int                           num,
                                        const int                           nump,
                                        const char*                         mess,
                                        occ::handle<Interface_Check>&       ach,
                                        const occ::handle<StepData_PDescr>& descr,
                                        StepData_Field&                     fild) const
{
  const Interface_FileParameter&  FP  = Param(num, nump);
  const char*                     str = FP.CValue();
  bool                            OK  = true;
  int                             nent, kind;
  occ::handle<Standard_Transient> sub;
  Interface_ParamType             FT = FP.ParamType();
  switch (FT)
  {
    case Interface_ParamMisc:
      OK = false;
      break;
    case Interface_ParamInteger:
      fild.SetInteger(atoi(str));
      break;
    case Interface_ParamReal:
      fild.SetReal(Interface_FileReaderData::Fastof(str));
      break;
    case Interface_ParamIdent:
      nent = FP.EntityNumber();
      if (nent > 0)
        fild.SetEntity(BoundEntity(nent));
      break;
    case Interface_ParamVoid:
      break;
    case Interface_ParamText:
    {
      occ::handle<TCollection_HAsciiString> txt = new TCollection_HAsciiString(str);
      cleanText(txt);
      fild.Set(txt);
      break;
    }
    case Interface_ParamEnum:
      if (!strcmp(str, ".T."))
        fild.SetLogical(StepData_LTrue);
      else if (!strcmp(str, ".F."))
        fild.SetLogical(StepData_LFalse);
      else if (!strcmp(str, ".U."))
        fild.SetLogical(StepData_LUnknown);
      else
        fild.SetEnum(-1, str);
      break;
    case Interface_ParamLogical:
      OK = false;
      break;
    case Interface_ParamSub:
      nent = FP.EntityNumber();
      kind = ReadSub(nent, mess, ach, descr, sub);
      if (kind < 0)
        break;
      fild.Clear(kind);
      fild.Set(sub);
      break;
    case Interface_ParamHexa:
      OK = false;
      break;
    case Interface_ParamBinary:
      OK = false;
      break;
    default:
      OK = false;
      break;
  }

  if (!OK)
  {
    if (!strcmp(str, "*"))
      fild.SetDerived();
  }
  return true;
}

bool StepData_StepReaderData::ReadList(const int                            num,
                                       occ::handle<Interface_Check>&        ach,
                                       const occ::handle<StepData_ESDescr>& descr,
                                       StepData_FieldList&                  list) const
{

  int i, nb = list.NbFields();
  if (!CheckNbParams(num, nb, ach, descr->TypeName()))
    return false;
  for (i = 1; i <= nb; i++)
  {
    occ::handle<StepData_PDescr> pde  = descr->Field(i);
    StepData_Field&              fild = list.CField(i);
    ReadField(num, i, pde->Name(), ach, pde, fild);
  }
  return true;
}

bool StepData_StepReaderData::ReadAny(const int                           num,
                                      const int                           nump,
                                      const char*                         mess,
                                      occ::handle<Interface_Check>&       ach,
                                      const occ::handle<StepData_PDescr>& descr,
                                      occ::handle<Standard_Transient>&    val) const
{
  const Interface_FileParameter& FP  = Param(num, nump);
  const char*                    str = FP.CValue();
  Interface_ParamType            FT  = FP.ParamType();

  switch (FT)
  {
    case Interface_ParamMisc:
      break;
    case Interface_ParamInteger:
    {
      if (!val.IsNull())
      {
        DeclareAndCast(StepData_SelectMember, sm, val);
        sm->SetReal(Interface_FileReaderData::Fastof(str));
        return true;
      }
      occ::handle<StepData_SelectInt> sin = new StepData_SelectInt;
      sin->SetInteger(atoi(str));
      val = sin;
      return true;
    }
    case Interface_ParamReal:
    {
      if (!val.IsNull())
      {
        DeclareAndCast(StepData_SelectMember, sm, val);
        sm->SetReal(Interface_FileReaderData::Fastof(str));
        return true;
      }
      occ::handle<StepData_SelectReal> sre = new StepData_SelectReal;
      sre->SetReal(Interface_FileReaderData::Fastof(str));
      val = sre;
      return true;
    }
    case Interface_ParamIdent:
    {
      int nent = FP.EntityNumber();
      if (nent > 0)
        val = BoundEntity(nent);
      return (!val.IsNull());
    }
    case Interface_ParamVoid:
      break;
    case Interface_ParamEnum:
    {
      occ::handle<StepData_SelectMember> sm;
      if (!val.IsNull())
        sm = GetCasted(StepData_SelectMember, val);
      occ::handle<StepData_SelectInt>   sin;
      occ::handle<StepData_SelectNamed> sna;
      int                               logic = -1;

      StepData_Logical slog = StepData_LUnknown;
      if (str[0] == '.' && str[2] == '.' && str[3] == '\0')
      {
        if (str[1] == 'F')
        {
          slog  = StepData_LFalse;
          logic = 0;
        }
        else if (str[1] == 'T')
        {
          slog  = StepData_LTrue;
          logic = 1;
        }
        else if (str[1] == 'U')
        {
          slog  = StepData_LUnknown;
          logic = 2;
        }
      }
      if (logic >= 0)
      {
        if (!sm.IsNull())
          sm->SetLogical(slog);
        else
        {
          sin = new StepData_SelectInt;
          val = sin;
          sin->SetLogical(slog);
        }
      }
      else
      {
        if (!sm.IsNull())
          sm->SetEnum(logic, str);
        else
        {
          sna = new StepData_SelectNamed;
          val = sna;
          sna->SetEnum(logic, str);
        }
      }
      return true;
    }
    case Interface_ParamLogical:
      break;
    case Interface_ParamText:
    {
      occ::handle<TCollection_HAsciiString> txt = new TCollection_HAsciiString(str);
      cleanText(txt);

      if (!val.IsNull())
      {
        DeclareAndCast(StepData_SelectMember, sm, val);
        sm->SetString(txt->ToCString());
        return true;
      }

      val = txt;
      return true;
    }
    case Interface_ParamSub:
    {
      int numsub = SubListNumber(num, nump, false);
      int nbp    = NbParams(numsub);
      if (nbp == 0)
        return false;
      const TCollection_AsciiString& rectyp = RecordType(numsub);
      if (nbp == 1 && rectyp.ToCString()[0] != '(')
      {

        DeclareAndCast(StepData_SelectArrReal, sma, val);
        if (!sma.IsNull())
        {
          int numsub2 = SubListNumber(numsub, 1, false);
          int nbp2    = NbParams(numsub2);
          if (nbp2 > 1)
          {
            if (Param(numsub2, 1).ParamType() == Interface_ParamReal)
            {
              if (!sma->SetName(rectyp.ToCString()))
                return false;
              occ::handle<NCollection_HSequence<double>> aSeq = new NCollection_HSequence<double>;
              for (int i = 1; i <= nbp2; i++)
              {
                if (Param(numsub2, i).ParamType() != Interface_ParamReal)
                  continue;
                occ::handle<Standard_Transient> asr = new StepData_SelectReal;
                if (!ReadAny(numsub2, i, mess, ach, descr, asr))
                  continue;
                occ::handle<StepData_SelectReal> sm1 = occ::down_cast<StepData_SelectReal>(asr);
                if (!sm1.IsNull())
                  aSeq->Append(sm1->Real());
              }
              occ::handle<NCollection_HArray1<double>> anArr =
                new NCollection_HArray1<double>(1, aSeq->Length());
              for (int nr = 1; nr <= aSeq->Length(); nr++)
              {
                anArr->SetValue(nr, aSeq->Value(nr));
              }
              sma->SetArrReal(anArr);
              return true;
            }
          }
        }
        DeclareAndCast(StepData_SelectMember, sm, val);
        if (sm.IsNull())
        {
          sm  = new StepData_SelectNamed;
          val = sm;
        }
        if (!sm->SetName(rectyp.ToCString()))
          return false;
        return ReadAny(numsub, 1, mess, ach, descr, val);
      }
    }
    default:
      break;
  }
  return false;
}

bool StepData_StepReaderData::ReadXY(const int                     num,
                                     const int                     nump,
                                     const char*                   mess,
                                     occ::handle<Interface_Check>& ach,
                                     double&                       X,
                                     double&                       Y) const
{
  char        txtmes[200];
  const char* errmess = nullptr;
  int         numsub  = SubListNumber(num, nump, false);
  if (numsub != 0)
  {
    if (NbParams(numsub) == 2)
    {
      const Interface_FileParameter& FPX = Param(numsub, 1);
      if (FPX.ParamType() == Interface_ParamReal)
        X = Interface_FileReaderData::Fastof(FPX.CValue());
      else
        errmess = "Parameter n0.%d (%s) : (X,Y) X not a Real";

      const Interface_FileParameter& FPY = Param(numsub, 2);
      if (FPY.ParamType() == Interface_ParamReal)
        Y = Interface_FileReaderData::Fastof(FPY.CValue());
      else
        errmess = "Parameter n0.%d (%s) : (X,Y) Y not a Real";
    }
    else
      errmess = "Parameter n0.%d (%s) : (X,Y) has not 2 params";
  }
  else
    errmess = "Parameter n0.%d (%s) : (X,Y) not a SubList";

  if (errmess == nullptr)
    return true;

  Sprintf(txtmes, errmess, nump, mess);
  ach->AddFail(txtmes, errmess);
  return false;
}

bool StepData_StepReaderData::ReadXYZ(const int                     num,
                                      const int                     nump,
                                      const char*                   mess,
                                      occ::handle<Interface_Check>& ach,
                                      double&                       X,
                                      double&                       Y,
                                      double&                       Z) const
{
  char        txtmes[200];
  const char* errmess = nullptr;
  int         numsub  = SubListNumber(num, nump, false);
  if (numsub != 0)
  {
    if (NbParams(numsub) == 3)
    {
      const Interface_FileParameter& FPX = Param(numsub, 1);
      if (FPX.ParamType() == Interface_ParamReal)
        X = Interface_FileReaderData::Fastof(FPX.CValue());
      else
        errmess = "Parameter n0.%d (%s) : (X,Y,Z) X not a Real";

      const Interface_FileParameter& FPY = Param(numsub, 2);
      if (FPY.ParamType() == Interface_ParamReal)
        Y = Interface_FileReaderData::Fastof(FPY.CValue());
      else
        errmess = "Parameter n0.%d (%s) : (X,Y,Z) Y not a Real";

      const Interface_FileParameter& FPZ = Param(numsub, 3);
      if (FPZ.ParamType() == Interface_ParamReal)
        Z = Interface_FileReaderData::Fastof(FPZ.CValue());
      else
        errmess = "Parameter n0.%d (%s) : (X,Y,Z) Z not a Real";
    }
    else
      errmess = "Parameter n0.%d (%s) : (X,Y,Z) has not 3 params";
  }
  else
    errmess = "Parameter n0.%d (%s) : (X,Y,Z) not a SubList";

  if (errmess == nullptr)
    return true;

  Sprintf(txtmes, errmess, nump, mess);
  ach->AddFail(txtmes, errmess);
  return false;
}

bool StepData_StepReaderData::ReadReal(const int                     num,
                                       const int                     nump,
                                       const char*                   mess,
                                       occ::handle<Interface_Check>& ach,
                                       double&                       val) const
{
  char        txtmes[200];
  const char* errmess = nullptr;
  if (nump > 0 && nump <= NbParams(num))
  {
    const Interface_FileParameter& FP = Param(num, nump);
    if (FP.ParamType() == Interface_ParamReal || FP.ParamType() == Interface_ParamInteger)
      val = Interface_FileReaderData::Fastof(FP.CValue());
    else
      errmess = "Parameter n0.%d (%s) not a Real";
  }
  else
    errmess = "Parameter n0.%d (%s) absent";

  if (errmess == nullptr)
    return true;

  Sprintf(txtmes, errmess, nump, mess);
  ach->AddFail(txtmes, errmess);
  return false;
}

bool StepData_StepReaderData::ReadEntity(const int                         num,
                                         const int                         nump,
                                         const char*                       mess,
                                         occ::handle<Interface_Check>&     ach,
                                         const occ::handle<Standard_Type>& atype,
                                         occ::handle<Standard_Transient>&  ent) const
{
  char        txtmes[200];
  const char* errmess = nullptr;
  if (nump > 0 && nump <= NbParams(num))
  {
    const Interface_FileParameter& FP   = Param(num, nump);
    int                            nent = FP.EntityNumber();
    if (FP.ParamType() == Interface_ParamIdent)
    {
      if (nent > 0)
      {
        occ::handle<Standard_Transient> entent = BoundEntity(nent);
        if (entent.IsNull() || !entent->IsKind(atype))
        {
          errmess = "Parameter n0.%d (%s) : Entity has illegal type";
          if (!entent.IsNull() && entent->IsKind(STANDARD_TYPE(StepData_UndefinedEntity)))
            ent = entent;
        }
        else
          ent = entent;
      }
      else
        errmess = "Parameter n0.%d (%s) : Unresolved reference";
    }
    else
    {
      errmess = "Parameter n0.%d (%s) not an Entity";
    }
  }
  else
  {
    errmess = "Parameter n0.%d (%s) absent";
  }

  if (errmess == nullptr)
    return true;

  Sprintf(txtmes, errmess, nump, mess);
  ach->AddFail(txtmes, errmess);
  return false;
}

bool StepData_StepReaderData::ReadEntity(const int                     num,
                                         const int                     nump,
                                         const char*                   mess,
                                         occ::handle<Interface_Check>& ach,
                                         StepData_SelectType&          sel) const
{
  char        txtmes[200];
  const char* errmess = nullptr;
  if (nump > 0 && nump <= NbParams(num))
  {
    const Interface_FileParameter& FP   = Param(num, nump);
    int                            nent = FP.EntityNumber();
    if (FP.ParamType() == Interface_ParamIdent)
    {
      if (nent > 0)
      {
        occ::handle<Standard_Transient> entent = BoundEntity(nent);
        if (!sel.Matches(entent))
        {
          errmess = "Parameter n0.%d (%s) : Entity has illegal type";

          if (!entent.IsNull() && entent->IsKind(STANDARD_TYPE(StepData_UndefinedEntity)))
            sel.SetValue(entent);
        }
        else
          sel.SetValue(entent);
      }
      else
        errmess = "Parameter n0.%d (%s) : Unresolved reference";
    }
    else if (FP.ParamType() == Interface_ParamVoid)
    {
      errmess = "Parameter n0.%d (%s) not an Entity";
    }
    else
    {

      occ::handle<Standard_Transient> sm = sel.NewMember();

      if (!ReadAny(num, nump, mess, ach, sel.Description(), sm))
        errmess = "Parameter n0.%d (%s) : could not be read";
      if (!sel.Matches(sm))
        errmess = "Parameter n0.%d (%s) : illegal parameter type";
      else
        sel.SetValue(sm);
    }
  }
  else
  {
    errmess = "Parameter n0.%d (%s) absent";
  }

  if (errmess == nullptr)
    return true;

  Sprintf(txtmes, errmess, nump, mess);
  ach->AddFail(txtmes, errmess);
  return false;
}

bool StepData_StepReaderData::ReadInteger(const int                     num,
                                          const int                     nump,
                                          const char*                   mess,
                                          occ::handle<Interface_Check>& ach,
                                          int&                          val) const
{
  char        txtmes[200];
  const char* errmess = nullptr;
  if (nump > 0 && nump <= NbParams(num))
  {
    const Interface_FileParameter& FP = Param(num, nump);
    if (FP.ParamType() == Interface_ParamInteger)
      val = atoi(FP.CValue());
    else if (FP.ParamType() == Interface_ParamReal)
    {
      val     = static_cast<int>(std::round(Interface_FileReaderData::Fastof(FP.CValue())));
      errmess = "Parameter n0.%d (%s) was rounded";
    }
    if (FP.ParamType() != Interface_ParamInteger && FP.ParamType() != Interface_ParamReal)
      errmess = "Parameter n0.%d (%s) not an Integer";
  }
  else
    errmess = "Parameter n0.%d (%s) absent";

  if (errmess == nullptr)
    return true;

  Sprintf(txtmes, errmess, nump, mess);
  ach->AddFail(txtmes, errmess);
  return false;
}

bool StepData_StepReaderData::ReadBoolean(const int                     num,
                                          const int                     nump,
                                          const char*                   mess,
                                          occ::handle<Interface_Check>& ach,
                                          bool&                         flag) const
{
  char txtmes[200];
  flag                = true;
  const char* errmess = nullptr;
  if (nump > 0 && nump <= NbParams(num))
  {
    const Interface_FileParameter& FP = Param(num, nump);
    if (FP.ParamType() == Interface_ParamEnum)
    {
      const char* txt = FP.CValue();
      if (!strcmp(txt, ".T."))
        flag = true;
      else if (!strcmp(txt, ".F."))
        flag = false;
      else
        errmess = "Parameter n0.%d (%s) : Incorrect Boolean Value. It was set to true";
    }
    else
      errmess = "Parameter n0.%d (%s) not a Boolean. It was set to true";
  }
  else
    errmess = "Parameter n0.%d (%s) absent.It was set to true";

  if (errmess == nullptr)
    return true;

  Sprintf(txtmes, errmess, nump, mess);
  ach->AddFail(txtmes, errmess);
  return false;
}

bool StepData_StepReaderData::ReadLogical(const int                     num,
                                          const int                     nump,
                                          const char*                   mess,
                                          occ::handle<Interface_Check>& ach,
                                          StepData_Logical&             flag) const
{
  char        txtmes[200];
  const char* errmess = nullptr;
  if (nump > 0 && nump <= NbParams(num))
  {
    const Interface_FileParameter& FP = Param(num, nump);
    if (FP.ParamType() == Interface_ParamEnum)
    {
      const char* txt = FP.CValue();
      if (!strcmp(txt, ".T."))
        flag = StepData_LTrue;
      else if (!strcmp(txt, ".F."))
        flag = StepData_LFalse;
      else if (!strcmp(txt, ".U."))
        flag = StepData_LUnknown;
      else
        errmess = "Parameter n0.%d (%s) : Incorrect Logical Value";
    }
    else
      errmess = "Parameter n0.%d (%s) not a Logical";
  }
  else
    errmess = "Parameter n0.%d (%s) absent";

  if (errmess == nullptr)
    return true;

  Sprintf(txtmes, errmess, nump, mess);
  ach->AddFail(txtmes, errmess);
  return false;
}

bool StepData_StepReaderData::ReadString(const int                              num,
                                         const int                              nump,
                                         const char*                            mess,
                                         occ::handle<Interface_Check>&          ach,
                                         occ::handle<TCollection_HAsciiString>& val) const
{
  char        txtmes[200];
  const char* errmess = nullptr;
  if (nump > 0 && nump <= NbParams(num))
  {
    const Interface_FileParameter& FP = Param(num, nump);
    if (FP.ParamType() == Interface_ParamText)
    {

      val = new TCollection_HAsciiString(FP.CValue());
      cleanText(val);
    }
    else
    {
      errmess = "Parameter n0.%d (%s) not a quoted String";
    }
  }
  else
    errmess = "Parameter n0.%d (%s) absent";

  if (errmess == nullptr)
    return true;

  Sprintf(txtmes, errmess, nump, mess);
  ach->AddFail(txtmes, errmess);
  return false;
}

bool StepData_StepReaderData::ReadEnumParam(const int                     num,
                                            const int                     nump,
                                            const char*                   mess,
                                            occ::handle<Interface_Check>& ach,
                                            const char*&                  text) const
{
  char        txtmes[200];
  const char* errmess = nullptr;
  if (nump > 0 && nump <= NbParams(num))
  {
    const Interface_FileParameter& FP = Param(num, nump);
    if (FP.ParamType() == Interface_ParamEnum)
    {
      text = FP.CValue();
    }
    else if (FP.ParamType() == Interface_ParamVoid)
    {
      errmess = "Parameter n0.%d (%s) : Undefined Enumeration not allowed";
    }
    else
      errmess = "Parameter n0.%d (%s) not an Enumeration";
  }
  else
    errmess = "Parameter n0.%d (%s) absent";

  if (errmess == nullptr)
    return true;

  Sprintf(txtmes, errmess, nump, mess);
  ach->AddFail(txtmes, errmess);
  return false;
}

void StepData_StepReaderData::FailEnumValue(const int,
                                            const int                     nump,
                                            const char*                   mess,
                                            occ::handle<Interface_Check>& ach) const
{
  char        txtmes[200];
  const char* errmess = "Parameter n0.%d (%s) : Incorrect Enumeration Value";
  Sprintf(txtmes, errmess, nump, mess);
  ach->AddFail(txtmes, errmess);
}

bool StepData_StepReaderData::ReadEnum(const int                     num,
                                       const int                     nump,
                                       const char*                   mess,
                                       occ::handle<Interface_Check>& ach,
                                       const StepData_EnumTool&      enumtool,
                                       int&                          val) const
{

  char        txtmes[200];
  const char* errmess = nullptr;
  if (nump > 0 && nump <= NbParams(num))
  {
    const Interface_FileParameter& FP = Param(num, nump);
    if (FP.ParamType() == Interface_ParamEnum)
    {
      val = enumtool.Value(FP.CValue());
      if (val >= 0)
        return true;
      else
        errmess = "Parameter n0.%d (%s) : Incorrect Enumeration Value";
    }
    else if (FP.ParamType() == Interface_ParamVoid)
    {
      val = enumtool.NullValue();
      if (val < 0)
        errmess = "Parameter n0.%d (%s) : Undefined Enumeration not allowed";
    }
    else
      errmess = "Parameter n0.%d (%s) not an Enumeration";
  }
  else
    errmess = "Parameter n0.%d (%s) absent";

  if (errmess == nullptr)
    return true;

  Sprintf(txtmes, errmess, nump, mess);
  ach->AddFail(txtmes, errmess);
  return false;
}

bool StepData_StepReaderData::ReadTypedParam(const int                     num,
                                             const int                     nump,
                                             const bool                    mustbetyped,
                                             const char*                   mess,
                                             occ::handle<Interface_Check>& ach,
                                             int&                          numr,
                                             int&                          numrp,
                                             TCollection_AsciiString&      typ) const
{
  char        txtmes[200];
  const char* errmess = nullptr;
  if (nump > 0 && nump <= NbParams(num))
  {
    const Interface_FileParameter& FP = Param(num, nump);
    if (FP.ParamType() != Interface_ParamSub)
    {

      numr  = num;
      numrp = nump;
      typ.Clear();
      if (mustbetyped)
      {
        errmess = "Parameter n0.%d (%s) : single, not typed";
        Sprintf(txtmes, errmess, nump, mess);
        ach->AddFail(txtmes, errmess);
        return false;
      }
      return true;
    }
    numr  = FP.EntityNumber();
    numrp = 1;
    if (NbParams(numr) != 1)
      errmess = "Parameter n0.%d (%s) : SubList, not typed";
    typ = RecordType(numr);
  }
  else
    errmess = "Parameter n0.%d (%s) absent";

  if (errmess == nullptr)
    return true;
  Sprintf(txtmes, errmess, nump, mess);
  ach->AddFail(txtmes, errmess);
  return false;
}

bool StepData_StepReaderData::CheckDerived(const int                     num,
                                           const int                     nump,
                                           const char*                   mess,
                                           occ::handle<Interface_Check>& ach,
                                           const bool                    errstat) const
{
  char        txtmes[200];
  const char* errmess = nullptr;
  bool        warn    = !errstat;
  if (nump > 0 && nump <= NbParams(num))
  {
    if (!strcmp(Param(num, nump).CValue(), "*"))
      return true;
    else
      errmess = "Parameter n0.%d (%s) not Derived";
  }
  else
    errmess = "Parameter n0.%d (%s) absent";

  if (errmess == nullptr)
    return true;

  Sprintf(txtmes, errmess, nump, mess);
  if (warn)
    ach->AddWarning(txtmes, errmess);
  else
    ach->AddFail(txtmes, errmess);
  return false;
}

int StepData_StepReaderData::NbEntities() const
{
  return thenbents;
}

int StepData_StepReaderData::FindNextRecord(const int num) const
{

  if (num < 0)
    return 0;
  int num1 = num + 1;
  if (num == 0)
    num1 = thenbhead + 1;
  int max = NbRecords();

  while (num1 <= max)
  {
    if (theidents(num1) > 0)
      return num1;

    num1++;
  }
  return 0;
}

int StepData_StepReaderData::FindEntityNumber(const int num, const int id) const
{

  if (num == 0)
    return 0;
  int nb = NbParams(num);
  for (int i = 1; i <= nb; i++)
  {
    const Interface_FileParameter& FP = Param(num, i);
    if (FP.ParamType() != Interface_ParamIdent)
      continue;
    int ixp = atoi(&FP.CValue()[1]);
    if (ixp == id)
      return FP.EntityNumber();
  }
  return 0;
}

void StepData_StepReaderData::SetEntityNumbers(const bool withmap)
{
  Message_Messenger::StreamBuffer sout = Message::SendTrace();

  int                                   nbdirec = NbRecords();
  occ::handle<NCollection_IncAllocator> anAlloc =
    new NCollection_IncAllocator(NCollection_IncAllocator::THE_MINIMUM_BLOCK_SIZE);
  NCollection_Array1<int> subn(0, thelastn);

  bool                        pbmap = false;
  int                         nbmap = 0;
  NCollection_IndexedMap<int> imap(thenbents, anAlloc);
  NCollection_Array1<int>     indm(0, nbdirec);

  int num;
  for (num = 1; num <= nbdirec; num++)
  {
    int ident = theidents(num);
    if (ident > 0)
    {

      int indmap = imap.Add(ident);
      if (indmap <= nbmap)
      {
        indmap       = imap.FindIndex(ident);
        indm(indmap) = -1;
        pbmap        = true;
      }
      else
      {
        nbmap        = indmap;
        indm(indmap) = num;
      }
    }
  }

  for (num = 1; num <= nbdirec; num++)
  {
    int ident = theidents(num);
    if (ident < -2)
      subn(-(ident + 2)) = num;

    int nba = NbParams(num);
    int nda = (num == 1 ? 0 : ParamFirstRank(num - 1));

    for (int na = nba; na > 0; na--)
    {

      Interface_FileParameter& FP = ChangeParameter(nda + na);

      Interface_ParamType letype = FP.ParamType();
      if (letype == Interface_ParamSub)
      {
        int numsub = FP.EntityNumber();
        if (numsub > thelastn)
        {
          Message::SendInfo() << "Bad Sub.N0, Record " << num << " Param " << na << ":$" << numsub
                              << std::endl;
          continue;
        }
        FP.SetEntityNumber(subn(numsub));
      }
      else if (letype == Interface_ParamIdent)
      {
        int id     = FP.EntityNumber();
        int indmap = imap.FindIndex(id);
        if (indmap > 0)
        {
          int num0 = indm(indmap);
          if (num0 > 0)
            FP.SetEntityNumber(num0);
          else
            FP.SetEntityNumber(-id);
        }
        else
        {
          if (pbmap)
          {
            FP.SetEntityNumber(-id);
            continue;
          }
          char failmess[100];

          Sprintf(failmess, "Unresolved Reference, Ent.Id.#%d Param.n0 %d (Id.#%d)", ident, na, id);
          thecheck->AddFail(failmess, "Unresolved Reference");

          sout << "*** ERR StepReaderData *** Entite #" << ident << "\n    Type:" << RecordType(num)
               << "  Param.n0 " << na << ": #" << id << " Not found" << std::endl;
        }
      }
    }
  }

  if (!pbmap)
  {
    return;
  }
  sout << " --  2nd pass required --";

  int                                   nbseq = thenbents + 2 * thenbscop;
  NCollection_Array1<int>               inds(0, nbseq);
  NCollection_Array1<int>               indi(0, nbseq);
  NCollection_Array1<int>               indr(0, nbdirec);
  occ::handle<NCollection_HArray1<int>> indx;

  imap.Clear();
  anAlloc->Reset();
  bool iamap = withmap;
  nbmap      = 0;

  NCollection_Sequence<int> scopile(anAlloc);
  int                       nr = 0;
  for (num = 1; num <= nbdirec; num++)
  {
    int ident = theidents(num);
    if (ident < -2)
    {
      indr(num) = nr + 1;
    }
    else if (ident >= 0)
    {
      nr++;
      inds(nr)  = num;
      indi(nr)  = ident;
      indr(num) = nr;
      if (ident > 0)
      {

        int indmap = imap.Add(ident);
        if (indmap <= nbmap)
        {
          bool errorscope = false;
          indmap          = imap.FindIndex(ident);
          pbmap           = true;
          if (thenbscop == 0)
            errorscope = true;

          else
          {

            int fromscope = nr;
            int toscope   = indm(indmap);
            if (toscope < 0)
              toscope = -toscope;
            for (;;)
            {
              fromscope--;
              if (fromscope <= toscope)
              {
                errorscope = true;
                break;
              }
              int idtest = indi(fromscope);
              if (idtest >= 0)
                continue;
              if (idtest == -1)
                break;
              if (idtest == -3)
              {
                fromscope = inds(fromscope);
                if (fromscope < toscope)
                  break;
              }
            }
          }
          if (errorscope)
          {

            char ligne[80];
            Sprintf(ligne, "Ident defined SEVERAL TIMES : #%d", ident);
            thecheck->AddFail(ligne, "Ident defined SEVERAL TIMES : #%d");
            sout << "StepReaderData : SetEntityNumbers, " << ligne << std::endl;
          }
          if (indm(indmap) > 0)
            indm(indmap) = -indm(indmap);
        }
        else
        {
          nbmap        = indmap;
          indm(indmap) = nr;
        }
      }
    }
    else if (ident == -1)
    {
      nr++;
      inds(nr)  = num;
      indi(nr)  = -1;
      indr(num) = 0;
      scopile.Append(nr);
    }
    else if (ident == -2)
    {
      int nscop = scopile.Last();
      scopile.Remove(scopile.Length());
      nr++;
      inds(nr)    = nscop;
      indi(nr)    = -3;
      indr(num)   = 0;
      inds(nscop) = nr;
      if (NbParams(num) > 0)
      {

        if (indx.IsNull())
        {
          indx = new NCollection_HArray1<int>(0, nbseq);
          for (int ixp = 0; ixp <= nbseq; ixp++)
            indx->ChangeValue(ixp) = 0;
        }
        indx->ChangeValue(nr)    = num;
        indx->ChangeValue(nscop) = num;
      }
    }
    else if (ident == 0)
    {
      indr(num) = 0;
    }
  }

  if ((!iamap || pbmap) && !indx.IsNull())
  {
    for (nr = 0; nr <= nbseq; nr++)
    {
      if (indx->Value(nr) == 0 && indi(nr) != -3)
        continue;
      num     = indx->Value(nr);
      int nba = NbParams(num);
      for (int na = 1; na <= nba; na++)
      {
        Interface_FileParameter& FP = ChangeParam(num, na);
        if (FP.ParamType() != Interface_ParamIdent)
          continue;
        int id = -FP.EntityNumber();
        if (id < 0)
          continue;

        int n0 = nr - 1;
        if (indi(n0) == -3)
          n0--;
        while (n0 > 0)
        {
          int irec = indi(n0);
          if (irec == id)
          {
            FP.SetEntityNumber(inds(n0));
            break;
          }
          if (irec == -1)
            break;
          if (irec == -3)
          {

            int nok = FindEntityNumber(indx->Value(n0), id);
            if (nok > 0)
            {
              FP.SetEntityNumber(nok);
              break;
            }
            n0 = inds(n0);
          }
          n0--;
        }
      }
    }
  }

  int                                   maxsubpil = 30;
  occ::handle<NCollection_HArray1<int>> subpile   = new NCollection_HArray1<int>(1, maxsubpil);
  int                                   nbsubpil  = 0;

  for (num = 1; num <= nbdirec; num++)
  {
    nr = indr(num);
    if (nr == 0)
      continue;
    int nba = NbParams(num);
    for (int na = nba; na > 0; na--)
    {

      Interface_FileParameter& FP     = ChangeParam(num, na);
      Interface_ParamType      letype = FP.ParamType();
      if (letype == Interface_ParamSub)
      {

        FP.SetEntityNumber(subpile->Value(nbsubpil));
        nbsubpil--;
      }
      else if (letype == Interface_ParamIdent)
      {

        int id = -FP.EntityNumber();
        if (id < 0)
          continue;

        int pass, sens, nok, n0, irec;
        pass = sens = nok = 0;
        if (!iamap)
          pass = 1;
        while (pass < 3)
        {
          pass++;

          if (pass == 1)
          {
            int indmap = imap.FindIndex(id);
            if (indmap > 0)
            {
              nok = indm(indmap);
              if (nok < 0)
                continue;
              break;
            }
            else
              continue;
          }

          if (sens == 0 && nr > 1)
          {
            n0 = nr - 1;
            if (indi(n0) == -3)
              n0--;
            while (n0 > 0)
            {
              irec = indi(n0);
              if (irec == id)
              {
                nok = n0;
                break;
              }

              if (irec == -3)
              {
                if (indx.IsNull())
                  n0 = inds(n0);
                else
                {

                  nok = FindEntityNumber(indx->Value(n0), id);
                  if (nok > 0)
                    break;
                  n0 = inds(n0);
                }
              }
              n0--;
            }
          }
          else if (nr < nbseq)
          {
            n0 = nr + 1;
            while (n0 <= nbseq)
            {
              irec = indi(n0);
              if (irec == id)
              {
                nok = n0;
                break;
              }

              if (irec == -1)
              {
                if (indx.IsNull())
                  n0 = inds(n0);
                else
                {

                  nok = FindEntityNumber(indx->Value(n0), id);
                  if (nok > 0)
                    break;
                  n0 = inds(n0);
                }
              }
              n0++;
            }
          }
          if (nok > 0)
            break;
          sens = 1 - sens;
        }

        if (nok > 0)
        {
          int num0 = inds(nok);
          FP.SetEntityNumber(num0);
        }
        else
        {

          char failmess[100];
          int  nument = 0;
          int  n0ent;
          for (n0ent = 1; n0ent <= nr; n0ent++)
          {
            if (indi(n0ent) > 0)
              nument++;
          }
          int ident = RecordIdent(num);
          if (ident < 0)
          {
            for (n0ent = num + 1; n0ent <= nbdirec; n0ent++)
            {
              ident = RecordIdent(n0ent);
              if (ident > 0)
                break;
            }
          }

          Sprintf(failmess,
                  "Unresolved Reference, Ent.n0 %d (Id.#%d) Param.n0 %d (Id.#%d)",
                  nument,
                  ident,
                  na,
                  id);
          thecheck->AddFail(failmess, "Unresolved Reference");

          sout << "*** ERR StepReaderData *** Entite " << nument << ", a " << (nr * 100) / nbseq
               << "% de DATA : #" << ident << "\n    Type:" << RecordType(num) << "  Param.n0 "
               << na << ": #" << id << " Not found" << std::endl;

          FP.SetEntityNumber(0);
        }
      }
    }

    if (inds(nr) != num)
    {
      if (nbsubpil >= maxsubpil)
      {
        maxsubpil = maxsubpil + 30;
        occ::handle<NCollection_HArray1<int>> newsubpil =
          new NCollection_HArray1<int>(1, maxsubpil);
        for (int bidpil = 1; bidpil <= maxsubpil - 30; bidpil++)
          newsubpil->SetValue(bidpil, subpile->Value(bidpil));
        subpile = newsubpil;
      }
      nbsubpil++;
      subpile->SetValue(nbsubpil, num);
    }
  }
}

int StepData_StepReaderData::FindNextHeaderRecord(const int num) const
{

  if (num < 0)
    return 0;
  int num1 = num + 1;
  int max  = thenbhead;

  while (num1 <= max)
  {

    if (RecordIdent(num1) >= 0)
      return num1;
    num1++;
  }
  return 0;
}

void StepData_StepReaderData::PrepareHeader() {}

const occ::handle<Interface_Check> StepData_StepReaderData::GlobalCheck() const
{
  return thecheck;
}
