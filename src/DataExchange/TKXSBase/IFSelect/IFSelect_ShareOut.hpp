#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Dispatch.hpp>
#include <NCollection_Sequence.hpp>
#include <IFSelect_GeneralModifier.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class IFSelect_Dispatch;
class IFSelect_GeneralModifier;
class IFSelect_Modifier;
class TCollection_AsciiString;

class IFSelect_ShareOut : public Standard_Transient
{

public:
  Standard_EXPORT IFSelect_ShareOut();

  Standard_EXPORT void Clear(const bool onlydisp);

  Standard_EXPORT void ClearResult(const bool alsoname);

  Standard_EXPORT bool RemoveItem(const occ::handle<Standard_Transient>& item);

  Standard_EXPORT int LastRun() const;

  Standard_EXPORT void SetLastRun(const int last);

  Standard_EXPORT int NbDispatches() const;

  Standard_EXPORT int DispatchRank(const occ::handle<IFSelect_Dispatch>& disp) const;

  Standard_EXPORT const occ::handle<IFSelect_Dispatch>& Dispatch(const int num) const;

  Standard_EXPORT void AddDispatch(const occ::handle<IFSelect_Dispatch>& disp);

  Standard_EXPORT bool RemoveDispatch(const int rank);

  Standard_EXPORT void AddModifier(const occ::handle<IFSelect_GeneralModifier>& modifier,
                                   const int                                    atnum);

  Standard_EXPORT void AddModifier(const occ::handle<IFSelect_GeneralModifier>& modifier,
                                   const int                                    dispnum,
                                   const int                                    atnum);

  Standard_EXPORT void AddModif(const occ::handle<IFSelect_GeneralModifier>& modifier,
                                const bool                                   formodel,
                                const int                                    atnum = 0);

  Standard_EXPORT int NbModifiers(const bool formodel) const;

  Standard_EXPORT occ::handle<IFSelect_GeneralModifier> GeneralModifier(const bool formodel,
                                                                        const int  num) const;

  Standard_EXPORT occ::handle<IFSelect_Modifier> ModelModifier(const int num) const;

  Standard_EXPORT int ModifierRank(const occ::handle<IFSelect_GeneralModifier>& modifier) const;

  Standard_EXPORT bool RemoveModifier(const bool formodel, const int num);

  Standard_EXPORT bool ChangeModifierRank(const bool formodel, const int befor, const int after);

  Standard_EXPORT bool SetRootName(const int                                    num,
                                   const occ::handle<TCollection_HAsciiString>& name);

  Standard_EXPORT bool HasRootName(const int num) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> RootName(const int num) const;

  Standard_EXPORT int RootNumber(const occ::handle<TCollection_HAsciiString>& name) const;

  Standard_EXPORT void SetPrefix(const occ::handle<TCollection_HAsciiString>& pref);

  Standard_EXPORT bool SetDefaultRootName(const occ::handle<TCollection_HAsciiString>& defrt);

  Standard_EXPORT void SetExtension(const occ::handle<TCollection_HAsciiString>& ext);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Prefix() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> DefaultRootName() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Extension() const;

  Standard_EXPORT TCollection_AsciiString FileName(const int dnum,
                                                   const int pnum,
                                                   const int nbpack = 0);

  DEFINE_STANDARD_RTTIEXT(IFSelect_ShareOut, Standard_Transient)

private:
  NCollection_Sequence<occ::handle<IFSelect_Dispatch>>        thedisps;
  NCollection_Sequence<occ::handle<IFSelect_GeneralModifier>> themodelmodifiers;
  NCollection_Sequence<occ::handle<IFSelect_GeneralModifier>> thefilemodifiers;
  occ::handle<TCollection_HAsciiString>                       thepref;
  occ::handle<TCollection_HAsciiString>                       thedefrt;
  occ::handle<TCollection_HAsciiString>                       theext;
  int                                                         thenbdefs;
  int                                                         thelastrun;
};
