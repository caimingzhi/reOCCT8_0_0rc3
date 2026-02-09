#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <IFSelect_Editor.hpp>
#include <Standard_Integer.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class Interface_TypedValue;
class IFSelect_EditForm;
class TCollection_HAsciiString;
class Standard_Transient;
class Interface_InterfaceModel;

class IFSelect_ParamEditor : public IFSelect_Editor
{

public:
  Standard_EXPORT IFSelect_ParamEditor(const int nbmax = 100, const char* label = "");

  Standard_EXPORT void AddValue(const occ::handle<Interface_TypedValue>& val,
                                const char*                              shortname = "");

  Standard_EXPORT void AddConstantText(const char* val,
                                       const char* shortname,
                                       const char* completename = "");

  Standard_EXPORT TCollection_AsciiString Label() const override;

  Standard_EXPORT bool Recognize(const occ::handle<IFSelect_EditForm>& form) const override;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> StringValue(
    const occ::handle<IFSelect_EditForm>& form,
    const int                             num) const override;

  Standard_EXPORT bool Load(const occ::handle<IFSelect_EditForm>&        form,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT bool Apply(const occ::handle<IFSelect_EditForm>&        form,
                             const occ::handle<Standard_Transient>&       ent,
                             const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT static occ::handle<IFSelect_ParamEditor> StaticEditor(
    const occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>& list,
    const char*                                                                      label = "");

  DEFINE_STANDARD_RTTIEXT(IFSelect_ParamEditor, IFSelect_Editor)

private:
  TCollection_AsciiString thelabel;
};
