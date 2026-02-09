#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TCollection_HAsciiString.hpp>
#include <Interface_EntityList.hpp>
#include <Standard_Transient.hpp>
#include <Interface_ParamType.hpp>
class TCollection_HAsciiString;
class Interface_CopyTool;

class Interface_UndefinedContent : public Standard_Transient
{

public:
  Standard_EXPORT Interface_UndefinedContent();

  Standard_EXPORT int NbParams() const;

  Standard_EXPORT int NbLiterals() const;

  Standard_EXPORT bool ParamData(const int                              num,
                                 Interface_ParamType&                   ptype,
                                 occ::handle<Standard_Transient>&       ent,
                                 occ::handle<TCollection_HAsciiString>& val) const;

  Standard_EXPORT Interface_ParamType ParamType(const int num) const;

  Standard_EXPORT bool IsParamEntity(const int num) const;

  Standard_EXPORT occ::handle<Standard_Transient> ParamEntity(const int num) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ParamValue(const int num) const;

  Standard_EXPORT void Reservate(const int nb, const int nblit);

  Standard_EXPORT void AddLiteral(const Interface_ParamType                    ptype,
                                  const occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT void AddEntity(const Interface_ParamType              ptype,
                                 const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void RemoveParam(const int num);

  Standard_EXPORT void SetLiteral(const int                                    num,
                                  const Interface_ParamType                    ptype,
                                  const occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT void SetEntity(const int                              num,
                                 const Interface_ParamType              ptype,
                                 const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void SetEntity(const int num, const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT Interface_EntityList EntityList() const;

  Standard_EXPORT void GetFromAnother(const occ::handle<Interface_UndefinedContent>& other,
                                      Interface_CopyTool&                            TC);

  DEFINE_STANDARD_RTTIEXT(Interface_UndefinedContent, Standard_Transient)

private:
  int                                                                     thenbparams;
  int                                                                     thenbstr;
  occ::handle<NCollection_HArray1<int>>                                   theparams;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> thevalues;
  Interface_EntityList                                                    theentities;
};
