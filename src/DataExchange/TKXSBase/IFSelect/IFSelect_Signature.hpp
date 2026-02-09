#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Interface_SignType.hpp>
class Standard_Transient;
class Interface_InterfaceModel;

class IFSelect_Signature : public Interface_SignType
{

public:
  Standard_EXPORT void SetIntCase(const bool hasmin,
                                  const int  valmin,
                                  const bool hasmax,
                                  const int  valmax);

  Standard_EXPORT bool IsIntCase(bool& hasmin, int& valmin, bool& hasmax, int& valmax) const;

  Standard_EXPORT void AddCase(const char* acase);

  Standard_EXPORT occ::handle<NCollection_HSequence<TCollection_AsciiString>> CaseList() const;

  Standard_EXPORT const char* Name() const override;

  Standard_EXPORT TCollection_AsciiString Label() const;

  Standard_EXPORT virtual bool Matches(const occ::handle<Standard_Transient>&       ent,
                                       const occ::handle<Interface_InterfaceModel>& model,
                                       const TCollection_AsciiString&               text,
                                       const bool                                   exact) const;

  Standard_EXPORT static bool MatchValue(const char*                    val,
                                         const TCollection_AsciiString& text,
                                         const bool                     exact);

  Standard_EXPORT static const char* IntValue(const int val);

  DEFINE_STANDARD_RTTIEXT(IFSelect_Signature, Interface_SignType)

protected:
  Standard_EXPORT IFSelect_Signature(const char* name);

  TCollection_AsciiString thename;

private:
  int                                                         thecasi[3];
  occ::handle<NCollection_HSequence<TCollection_AsciiString>> thecasl;
};
