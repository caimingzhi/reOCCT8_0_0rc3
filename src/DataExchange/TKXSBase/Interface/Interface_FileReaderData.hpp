#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_CString.hpp>
#include <Interface_ParamType.hpp>
class Interface_ParamSet;
class TCollection_AsciiString;
class Interface_FileParameter;
class Interface_ParamList;

class Interface_FileReaderData : public Standard_Transient
{

public:
  Standard_EXPORT virtual int NbRecords() const;

  Standard_EXPORT virtual int NbEntities() const;

  Standard_EXPORT virtual int FindNextRecord(const int num) const = 0;

  Standard_EXPORT void InitParams(const int num);

  Standard_EXPORT void AddParam(const int                 num,
                                const char*               aval,
                                const Interface_ParamType atype,
                                const int                 nument = 0);

  Standard_EXPORT void AddParam(const int                      num,
                                const TCollection_AsciiString& aval,
                                const Interface_ParamType      atype,
                                const int                      nument = 0);

  Standard_EXPORT void AddParam(const int num, const Interface_FileParameter& FP);

  Standard_EXPORT void SetParam(const int num, const int nump, const Interface_FileParameter& FP);

  Standard_EXPORT int NbParams(const int num) const;

  Standard_EXPORT occ::handle<Interface_ParamList> Params(const int num) const;

  Standard_EXPORT const Interface_FileParameter& Param(const int num, const int nump) const;

  Standard_EXPORT Interface_FileParameter& ChangeParam(const int num, const int nump);

  Standard_EXPORT Interface_ParamType ParamType(const int num, const int nump) const;

  Standard_EXPORT const char* ParamCValue(const int num, const int nump) const;

  Standard_EXPORT bool IsParamDefined(const int num, const int nump) const;

  Standard_EXPORT int ParamNumber(const int num, const int nump) const;

  Standard_EXPORT const occ::handle<Standard_Transient>& ParamEntity(const int num,
                                                                     const int nump) const;

  Standard_EXPORT int ParamFirstRank(const int num) const;

  Standard_EXPORT const occ::handle<Standard_Transient>& BoundEntity(const int num) const;

  Standard_EXPORT void BindEntity(const int num, const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void SetErrorLoad(const bool val);

  Standard_EXPORT bool IsErrorLoad() const;

  Standard_EXPORT bool ResetErrorLoad();

  Standard_EXPORT void Destroy();

  ~Interface_FileReaderData() override { Destroy(); }

  Standard_EXPORT static double Fastof(const char* str);

  DEFINE_STANDARD_RTTIEXT(Interface_FileReaderData, Standard_Transient)

protected:
  Standard_EXPORT Interface_FileReaderData(const int nbr, const int npar);

  Standard_EXPORT Interface_FileParameter& ChangeParameter(const int numpar);

  Standard_EXPORT void ParamPosition(const int numpar, int& num, int& nump) const;

private:
  int                                                 thenum0;
  int                                                 therrload;
  occ::handle<Interface_ParamSet>                     theparams;
  NCollection_Array1<int>                             thenumpar;
  NCollection_Array1<occ::handle<Standard_Transient>> theents;
};
