

#include <IFSelect_EditForm.hpp>
#include <IFSelect_ParamEditor.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Static.hpp>
#include <Interface_TypedValue.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_ParamEditor, IFSelect_Editor)

IFSelect_ParamEditor::IFSelect_ParamEditor(const int nbmax, const char* label)
    : IFSelect_Editor(nbmax),
      thelabel(label)
{
  SetNbValues(0);
  if (thelabel.Length() == 0)
    thelabel.AssignCat("Param Editor");
}

void IFSelect_ParamEditor::AddValue(const occ::handle<Interface_TypedValue>& val,
                                    const char*                              shortname)
{
  SetNbValues(NbValues() + 1);
  SetValue(NbValues(), val, shortname);
}

void IFSelect_ParamEditor::AddConstantText(const char* val,
                                           const char* shortname,
                                           const char* longname)
{
  occ::handle<Interface_TypedValue> tv =
    new Interface_TypedValue(longname[0] == '\0' ? shortname : longname);
  tv->SetCStringValue(val);
  SetNbValues(NbValues() + 1);
  SetValue(NbValues(), tv, shortname, IFSelect_EditRead);
}

TCollection_AsciiString IFSelect_ParamEditor::Label() const
{
  return thelabel;
}

bool IFSelect_ParamEditor::Recognize(const occ::handle<IFSelect_EditForm>&) const
{
  return true;
}

occ::handle<TCollection_HAsciiString> IFSelect_ParamEditor::StringValue(
  const occ::handle<IFSelect_EditForm>&,
  const int num) const
{
  return TypedValue(num)->HStringValue();
}

bool IFSelect_ParamEditor::Load(const occ::handle<IFSelect_EditForm>& form,
                                const occ::handle<Standard_Transient>&,
                                const occ::handle<Interface_InterfaceModel>&) const
{
  int i, nb = NbValues();
  for (i = 1; i <= nb; i++)
    form->LoadValue(i, TypedValue(i)->HStringValue());

  return true;
}

bool IFSelect_ParamEditor::Apply(const occ::handle<IFSelect_EditForm>& form,
                                 const occ::handle<Standard_Transient>&,
                                 const occ::handle<Interface_InterfaceModel>&) const
{
  int i, nb = NbValues();
  for (i = 1; i <= nb; i++)
    if (form->IsModified(i))
      TypedValue(i)->SetHStringValue(form->EditedValue(i));

  return true;
}

occ::handle<IFSelect_ParamEditor> IFSelect_ParamEditor::StaticEditor(
  const occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>& list,
  const char*                                                                      label)
{
  occ::handle<IFSelect_ParamEditor> editor;
  if (list.IsNull())
    return editor;
  int i, nb = list->Length();

  editor = new IFSelect_ParamEditor(nb + 10, label);
  for (i = 1; i <= nb; i++)
  {
    occ::handle<Interface_Static> val = Interface_Static::Static(list->Value(i)->ToCString());
    if (!val.IsNull())
      editor->AddValue(val);
  }
  return editor;
}
