

#include <Interface_FileParameter.hpp>
#include <Interface_FileReaderData.hpp>
#include <Interface_ParamList.hpp>
#include <Interface_ParamSet.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Interface_FileReaderData, Standard_Transient)

static int thefic = 0;
static int thenm0 = -1;
static int thenp0 = -1;

Interface_FileReaderData::Interface_FileReaderData(const int nbr, const int npar)
    : therrload(0),
      thenumpar(0, nbr),
      theents(0, nbr)
{
  theparams = new Interface_ParamSet(npar);
  thenumpar.Init(0);
  thenm0  = -1;
  thenum0 = ++thefic;
}

int Interface_FileReaderData::NbRecords() const
{
  return thenumpar.Upper();
}

int Interface_FileReaderData::NbEntities() const
{
  int nb  = 0;
  int num = 0;
  while ((num = FindNextRecord(num)) > 0)
    nb++;
  return nb;
}

void Interface_FileReaderData::InitParams(const int num)
{
  thenumpar.SetValue(num, theparams->NbParams());
}

void Interface_FileReaderData::AddParam(const int,
                                        const char*               aval,
                                        const Interface_ParamType atype,
                                        const int                 nument)
{
  theparams->Append(aval, -1, atype, nument);
}

void Interface_FileReaderData::AddParam(const int,
                                        const TCollection_AsciiString& aval,
                                        const Interface_ParamType      atype,
                                        const int                      nument)
{
  theparams->Append(aval.ToCString(), aval.Length(), atype, nument);
}

void Interface_FileReaderData::AddParam(const int, const Interface_FileParameter& FP)
{
  theparams->Append(FP);
}

void Interface_FileReaderData::SetParam(const int                      num,
                                        const int                      nump,
                                        const Interface_FileParameter& FP)
{
  theparams->SetParam(thenumpar(num - 1) + nump, FP);
}

int Interface_FileReaderData::NbParams(const int num) const
{
  if (num > 1)
    return (thenumpar(num) - thenumpar(num - 1));
  else if (num == 1)
    return thenumpar(num);
  else
    return theparams->NbParams();
}

occ::handle<Interface_ParamList> Interface_FileReaderData::Params(const int num) const
{
  if (num == 0)
    return theparams->Params(0, 0);
  else if (num == 1)
    return theparams->Params(0, thenumpar(1));
  else
    return theparams->Params(thenumpar(num - 1) + 1, (thenumpar(num) - thenumpar(num - 1)));
}

const Interface_FileParameter& Interface_FileReaderData::Param(const int num, const int nump) const
{
  if (thefic != thenum0)
    return theparams->Param(thenumpar(num - 1) + nump);
  if (thenm0 != num)
  {
    thenp0 = thenumpar(num - 1);
    thenm0 = num;
  }
  return theparams->Param(thenp0 + nump);
}

Interface_FileParameter& Interface_FileReaderData::ChangeParam(const int num, const int nump)
{
  if (thefic != thenum0)
    return theparams->ChangeParam(thenumpar(num - 1) + nump);
  if (thenm0 != num)
  {
    thenp0 = thenumpar(num - 1);
    thenm0 = num;
  }
  return theparams->ChangeParam(thenp0 + nump);
}

Interface_ParamType Interface_FileReaderData::ParamType(const int num, const int nump) const
{
  return Param(num, nump).ParamType();
}

const char* Interface_FileReaderData::ParamCValue(const int num, const int nump) const
{
  return Param(num, nump).CValue();
}

bool Interface_FileReaderData::IsParamDefined(const int num, const int nump) const
{
  return (Param(num, nump).ParamType() != Interface_ParamVoid);
}

int Interface_FileReaderData::ParamNumber(const int num, const int nump) const
{
  return Param(num, nump).EntityNumber();
}

const occ::handle<Standard_Transient>& Interface_FileReaderData::ParamEntity(const int num,
                                                                             const int nump) const
{
  return BoundEntity(Param(num, nump).EntityNumber());
}

Interface_FileParameter& Interface_FileReaderData::ChangeParameter(const int numpar)
{
  return theparams->ChangeParam(numpar);
}

void Interface_FileReaderData::ParamPosition(const int numpar, int& num, int& nump) const
{
  int nbe = thenumpar.Upper();
  if (numpar <= 0)
  {
    num = nump = 0;
    return;
  }
  for (int i = 1; i <= nbe; i++)
  {
    if (thenumpar(i) > numpar)
    {
      num  = i;
      nump = numpar - thenumpar(i) + 1;
      return;
    }
  }
  num  = nbe;
  nump = numpar - thenumpar(nbe) + 1;
}

int Interface_FileReaderData::ParamFirstRank(const int num) const
{
  return thenumpar(num);
}

void Interface_FileReaderData::SetErrorLoad(const bool val)
{
  therrload = (val ? 1 : -1);
}

bool Interface_FileReaderData::IsErrorLoad() const
{
  return (therrload != 0);
}

bool Interface_FileReaderData::ResetErrorLoad()
{
  bool res  = (therrload > 0);
  therrload = 0;
  return res;
}

const occ::handle<Standard_Transient>& Interface_FileReaderData::BoundEntity(const int num) const

{
  if (num >= theents.Lower() && num <= theents.Upper())
  {
    return theents(num);
  }
  else
  {
    static occ::handle<Standard_Transient> dummy;
    return dummy;
  }
}

void Interface_FileReaderData::BindEntity(const int num, const occ::handle<Standard_Transient>& ent)

{

  theents.SetValue(num, ent);
}

void Interface_FileReaderData::Destroy() {}

double Interface_FileReaderData::Fastof(const char* ligne)
{
  return Strtod(ligne, nullptr);
}
