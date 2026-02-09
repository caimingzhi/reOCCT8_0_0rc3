#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Transient.hpp>
class Interface_TypedValue;
class Interface_InterfaceModel;
class TCollection_HAsciiString;

class IFSelect_ListEditor : public Standard_Transient
{

public:
  Standard_EXPORT IFSelect_ListEditor();

  Standard_EXPORT IFSelect_ListEditor(const occ::handle<Interface_TypedValue>& def,
                                      const int                                max = 0);

  Standard_EXPORT void LoadModel(const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT void LoadValues(
    const occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>& vals);

  Standard_EXPORT void SetTouched();

  Standard_EXPORT void ClearEdit();

  Standard_EXPORT virtual bool LoadEdited(
    const occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>& list);

  Standard_EXPORT virtual bool SetValue(const int                                    num,
                                        const occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT virtual bool AddValue(const occ::handle<TCollection_HAsciiString>& val,
                                        const int                                    atnum = 0);

  Standard_EXPORT virtual bool Remove(const int num = 0, const int howmany = 1);

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
                  OriginalValues() const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
                  EditedValues() const;

  Standard_EXPORT int NbValues(const bool edited = true) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Value(const int  num,
                                                              const bool edited = true) const;

  Standard_EXPORT bool IsChanged(const int num) const;

  Standard_EXPORT bool IsModified(const int num) const;

  Standard_EXPORT bool IsAdded(const int num) const;

  Standard_EXPORT bool IsTouched() const;

  DEFINE_STANDARD_RTTIEXT(IFSelect_ListEditor, Standard_Transient)

private:
  int                                                                       themax;
  occ::handle<Interface_TypedValue>                                         thedef;
  int                                                                       thetouc;
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> theorig;
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> theedit;
  occ::handle<NCollection_HSequence<int>>                                   thestat;
  occ::handle<Interface_InterfaceModel>                                     themodl;
};
