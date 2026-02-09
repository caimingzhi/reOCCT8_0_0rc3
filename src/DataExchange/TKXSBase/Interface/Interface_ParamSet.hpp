#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_PCharacter.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <Interface_ParamType.hpp>
class Interface_ParamList;
class Interface_FileParameter;

class Interface_ParamSet : public Standard_Transient
{

public:
  Standard_EXPORT Interface_ParamSet(const int nres, const int nst = 1);

  Standard_EXPORT int Append(const char*               val,
                             const int                 lnval,
                             const Interface_ParamType typ,
                             const int                 nument);

  Standard_EXPORT int Append(const Interface_FileParameter& FP);

  Standard_EXPORT int NbParams() const;

  Standard_EXPORT const Interface_FileParameter& Param(const int num) const;

  Standard_EXPORT Interface_FileParameter& ChangeParam(const int num);

  Standard_EXPORT void SetParam(const int num, const Interface_FileParameter& FP);

  Standard_EXPORT occ::handle<Interface_ParamList> Params(const int num, const int nb) const;

  Standard_EXPORT void Destroy();

  ~Interface_ParamSet() override { Destroy(); }

  DEFINE_STANDARD_RTTIEXT(Interface_ParamSet, Standard_Transient)

private:
  Standard_PCharacter              theval;
  int                              thelnval;
  int                              thelnres;
  int                              thenbpar;
  int                              themxpar;
  occ::handle<Interface_ParamList> thelist;
  occ::handle<Interface_ParamSet>  thenext;
};
