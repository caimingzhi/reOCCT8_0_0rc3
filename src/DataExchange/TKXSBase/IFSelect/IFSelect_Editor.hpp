#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Array1.hpp>
#include <TCollection_AsciiString.hpp>

enum IFSelect_EditValue
{
  IFSelect_Optional,
  IFSelect_Editable,
  IFSelect_EditProtected,
  IFSelect_EditComputed,
  IFSelect_EditRead,
  IFSelect_EditDynamic
};

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <NCollection_DataMap.hpp>
class Interface_TypedValue;
class IFSelect_EditForm;
class TCollection_HAsciiString;
class IFSelect_ListEditor;
class Interface_InterfaceModel;

class IFSelect_Editor : public Standard_Transient
{

public:
  Standard_EXPORT void SetValue(const int                                num,
                                const occ::handle<Interface_TypedValue>& typval,
                                const char*                              shortname = "",
                                const IFSelect_EditValue accessmode = IFSelect_Editable);

  Standard_EXPORT void SetList(const int num, const int max = 0);

  Standard_EXPORT int NbValues() const;

  Standard_EXPORT occ::handle<Interface_TypedValue> TypedValue(const int num) const;

  Standard_EXPORT bool IsList(const int num) const;

  Standard_EXPORT int MaxList(const int num) const;

  Standard_EXPORT const char* Name(const int num, const bool isshort = false) const;

  Standard_EXPORT IFSelect_EditValue EditMode(const int num) const;

  Standard_EXPORT int NameNumber(const char* name) const;

  Standard_EXPORT void PrintNames(Standard_OStream& S) const;

  Standard_EXPORT void PrintDefs(Standard_OStream& S, const bool labels = false) const;

  Standard_EXPORT int MaxNameLength(const int what) const;

  Standard_EXPORT virtual TCollection_AsciiString Label() const = 0;

  Standard_EXPORT virtual occ::handle<IFSelect_EditForm> Form(const bool readonly,
                                                              const bool undoable = true) const;

  Standard_EXPORT virtual bool Recognize(const occ::handle<IFSelect_EditForm>& form) const = 0;

  Standard_EXPORT virtual occ::handle<TCollection_HAsciiString> StringValue(
    const occ::handle<IFSelect_EditForm>& form,
    const int                             num) const = 0;

  Standard_EXPORT virtual occ::handle<IFSelect_ListEditor> ListEditor(const int num) const;

  Standard_EXPORT virtual occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
    ListValue(const occ::handle<IFSelect_EditForm>& form, const int num) const;

  Standard_EXPORT virtual bool Load(const occ::handle<IFSelect_EditForm>&        form,
                                    const occ::handle<Standard_Transient>&       ent,
                                    const occ::handle<Interface_InterfaceModel>& model) const = 0;

  Standard_EXPORT virtual bool Update(const occ::handle<IFSelect_EditForm>&        form,
                                      const int                                    num,
                                      const occ::handle<TCollection_HAsciiString>& newval,
                                      const bool                                   enforce) const;

  Standard_EXPORT virtual bool UpdateList(
    const occ::handle<IFSelect_EditForm>&                                            form,
    const int                                                                        num,
    const occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>& newlist,
    const bool                                                                       enforce) const;

  Standard_EXPORT virtual bool Apply(const occ::handle<IFSelect_EditForm>&        form,
                                     const occ::handle<Standard_Transient>&       ent,
                                     const occ::handle<Interface_InterfaceModel>& model) const = 0;

  DEFINE_STANDARD_RTTIEXT(IFSelect_Editor, Standard_Transient)

protected:
  Standard_EXPORT IFSelect_Editor(const int nbval);

  Standard_EXPORT void SetNbValues(const int nbval);

private:
  int                                                 thenbval;
  int                                                 themaxsh;
  int                                                 themaxco;
  int                                                 themaxla;
  NCollection_DataMap<TCollection_AsciiString, int>   thenames;
  NCollection_Array1<occ::handle<Standard_Transient>> thevalues;
  NCollection_Array1<TCollection_AsciiString>         theshorts;
  NCollection_Array1<int>                             themodes;
  NCollection_Array1<int>                             thelists;
};
