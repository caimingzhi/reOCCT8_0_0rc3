

#include <Interface_FileParameter.hpp>
#include <Interface_ParamList.hpp>
#include <Interface_ParamSet.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Interface_ParamSet, Standard_Transient)

Interface_ParamSet::Interface_ParamSet(const int nres, const int)
{
  thelist  = new Interface_ParamList;
  themxpar = nres;
  thenbpar = 0;
  thelnval = 0;
  thelnres = 100;
  theval   = new char[thelnres];
}

int Interface_ParamSet::Append(const char*               val,
                               const int                 lnval,
                               const Interface_ParamType typ,
                               const int                 nument)
{

  thenbpar++;
  if (thenbpar > themxpar)
  {
    thenext = new Interface_ParamSet(themxpar, 1);
    return (thenbpar + thenext->Append(val, lnval, typ, nument));
  }
  else if (lnval < 0)
  {

    Interface_FileParameter& FP = thelist->ChangeValue(thenbpar);
    FP.Init(val, typ);
    if (nument != 0)
      FP.SetEntityNumber(nument);
  }
  else
  {

    int i;
    if (thelnval + lnval + 1 > thelnres)
    {

      int   newres = (int)(thelnres * 2 + lnval);
      char* newval = new char[newres];
      for (i = 0; i < thelnval; i++)
        newval[i] = theval[i];

      char* poldVal = &theval[0];
      char* pnewVal = &newval[0];
      for (i = 1; i < thenbpar; i++)
      {
        Interface_FileParameter& OFP   = thelist->ChangeValue(i);
        Interface_ParamType      otyp  = OFP.ParamType();
        char*                    oval  = (char*)OFP.CValue();
        int                      delta = (int)(oval - poldVal);

        int onum = OFP.EntityNumber();
        OFP.Init(pnewVal + delta, otyp);
        if (onum != 0)
          OFP.SetEntityNumber(onum);
      }

      delete[] theval;
      theval   = newval;
      thelnres = newres;
    }

    for (i = 0; i < lnval; i++)
      theval[thelnval + i] = val[i];
    theval[thelnval + lnval] = '\0';

    Interface_FileParameter& FP = thelist->ChangeValue(thenbpar);
    FP.Init(&theval[thelnval], typ);
    if (nument != 0)
      FP.SetEntityNumber(nument);
    thelnval += (int)(lnval + 1);
  }
  return thenbpar;
}

int Interface_ParamSet::Append(const Interface_FileParameter& FP)
{

  thenbpar++;
  if (thenbpar > themxpar)
  {
    thenext = new Interface_ParamSet(themxpar, 1);
    return thenbpar + thenext->Append(FP);
  }
  thelist->SetValue(thenbpar, FP);
  return thenbpar;
}

int Interface_ParamSet::NbParams() const
{
  return thenbpar;
}

const Interface_FileParameter& Interface_ParamSet::Param(const int num) const
{
  if (num > themxpar)
    return thenext->Param(num - themxpar);
  else
    return thelist->Value(num);
}

Interface_FileParameter& Interface_ParamSet::ChangeParam(const int num)
{
  if (num > themxpar)
    return thenext->ChangeParam(num - themxpar);
  else
    return thelist->ChangeValue(num);
}

void Interface_ParamSet::SetParam(const int num, const Interface_FileParameter& FP)
{
  if (num > themxpar)
    thenext->SetParam(num - themxpar, FP);
  else
    thelist->SetValue(num, FP);
}

occ::handle<Interface_ParamList> Interface_ParamSet::Params(const int num, const int nb) const
{
  int i, n0 = num - 1, nbp = nb;
  if (num > themxpar)
    return thenext->Params(num - themxpar, nb);
  if (num == 0 && nb == 0)
  {
    n0  = 0;
    nbp = thenbpar;
    if (thenbpar <= themxpar)
      return thelist;
  }
  occ::handle<Interface_ParamList> list = new Interface_ParamList;
  if (nb == 0)
    return list;

  for (i = 1; i <= nbp; i++)
    list->SetValue(i, Param(n0 + i));
  return list;
}

void Interface_ParamSet::Destroy()
{

  thenext.Nullify();

  if (theval)
    delete[] theval;
  theval = nullptr;
  thelist->Clear();
  thelist.Nullify();
}
