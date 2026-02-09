

#include <IFSelect_IntParam.hpp>
#include <Interface_Static.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_IntParam, Standard_Transient)

IFSelect_IntParam::IFSelect_IntParam()
{
  theval = 0;
}

void IFSelect_IntParam::SetStaticName(const char* statname)
{
  thestn.Clear();
  thestn.AssignCat(statname);
}

int IFSelect_IntParam::Value() const
{
  if (thestn.Length() == 0)
    return theval;
  if (!Interface_Static::IsSet(thestn.ToCString()))
    return theval;
  return Interface_Static::IVal(thestn.ToCString());
}

void IFSelect_IntParam::SetValue(const int val)
{
  theval = val;
  if (thestn.Length() == 0)
    return;
  if (!Interface_Static::IsPresent(thestn.ToCString()))
    return;
  Interface_Static::SetIVal(thestn.ToCString(), theval);
}
