#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_HSequence.hpp>
class IFSelect_Editor;
class Interface_InterfaceModel;
class IFSelect_ListEditor;
class TCollection_HAsciiString;

class IFSelect_EditForm : public Standard_Transient
{
public:
  Standard_EXPORT IFSelect_EditForm(const occ::handle<IFSelect_Editor>& editor,
                                    const bool                          readonly,
                                    const bool                          undoable,
                                    const char*                         label = "");

  Standard_EXPORT IFSelect_EditForm(const occ::handle<IFSelect_Editor>& editor,
                                    const NCollection_Sequence<int>&    nums,
                                    const bool                          readonly,
                                    const bool                          undoable,
                                    const char*                         label = "");

  Standard_EXPORT bool& EditKeepStatus();

  Standard_EXPORT const char* Label() const;

  Standard_EXPORT bool IsLoaded() const;

  Standard_EXPORT void ClearData();

  Standard_EXPORT void SetData(const occ::handle<Standard_Transient>&       ent,
                               const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT void SetEntity(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void SetModel(const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT occ::handle<Standard_Transient> Entity() const;

  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model() const;

  Standard_EXPORT occ::handle<IFSelect_Editor> Editor() const;

  Standard_EXPORT bool IsComplete() const;

  Standard_EXPORT int NbValues(const bool editable) const;

  Standard_EXPORT int NumberFromRank(const int rank) const;

  Standard_EXPORT int RankFromNumber(const int number) const;

  Standard_EXPORT int NameNumber(const char* name) const;

  Standard_EXPORT int NameRank(const char* name) const;

  Standard_EXPORT void LoadDefault();

  Standard_EXPORT virtual bool LoadData(const occ::handle<Standard_Transient>&       ent,
                                        const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT bool LoadEntity(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT bool LoadModel(const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT bool LoadData();

  Standard_EXPORT occ::handle<IFSelect_ListEditor> ListEditor(const int num) const;

  Standard_EXPORT void LoadValue(const int num, const occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT void LoadList(
    const int                                                                        num,
    const occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>& list);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> OriginalValue(const int num) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
                  OriginalList(const int num) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> EditedValue(const int num) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
                  EditedList(const int num) const;

  Standard_EXPORT bool IsModified(const int num) const;

  Standard_EXPORT bool IsTouched(const int num) const;

  Standard_EXPORT bool Modify(const int                                    num,
                              const occ::handle<TCollection_HAsciiString>& newval,
                              const bool                                   enforce = false);

  Standard_EXPORT bool ModifyList(const int                               num,
                                  const occ::handle<IFSelect_ListEditor>& edited,
                                  const bool                              enforce = false);

  Standard_EXPORT bool ModifyListValue(
    const int                                                                        num,
    const occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>& list,
    const bool enforce = false);

  Standard_EXPORT bool Touch(const int num, const occ::handle<TCollection_HAsciiString>& newval);

  Standard_EXPORT bool TouchList(
    const int                                                                        num,
    const occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>& newlist);

  Standard_EXPORT int NbTouched() const;

  Standard_EXPORT void ClearEdit(const int num = 0);

  Standard_EXPORT void PrintDefs(Standard_OStream& S) const;

  Standard_EXPORT void PrintValues(Standard_OStream& S,
                                   const int         what,
                                   const bool        names,
                                   const bool        alsolist = false) const;

  Standard_EXPORT bool Apply();

  Standard_EXPORT virtual bool Recognize() const;

  Standard_EXPORT virtual bool ApplyData(const occ::handle<Standard_Transient>&       ent,
                                         const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT bool Undo();

  DEFINE_STANDARD_RTTIEXT(IFSelect_EditForm, Standard_Transient)

private:
  bool                                                thecomplete;
  bool                                                theloaded;
  bool                                                thekeepst;
  TCollection_AsciiString                             thelabel;
  NCollection_Array1<int>                             thenums;
  NCollection_Array1<occ::handle<Standard_Transient>> theorigs;
  NCollection_Array1<occ::handle<Standard_Transient>> themodifs;
  NCollection_Array1<int>                             thestatus;
  occ::handle<IFSelect_Editor>                        theeditor;
  occ::handle<Standard_Transient>                     theent;
  occ::handle<Interface_InterfaceModel>               themodel;
  int                                                 thetouched;
};
