#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Editor.hpp>
#include <Standard_Integer.hpp>
class TCollection_AsciiString;
class IFSelect_EditForm;
class TCollection_HAsciiString;
class Standard_Transient;
class Interface_InterfaceModel;

//! EditSDR is an Editor fit for a Shape Definition Representation
//! which designates a Product Definition
class STEPEdit_EditSDR : public IFSelect_Editor
{

public:
  Standard_EXPORT STEPEdit_EditSDR();

  Standard_EXPORT TCollection_AsciiString Label() const override;

  Standard_EXPORT bool Recognize(const occ::handle<IFSelect_EditForm>& form) const override;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> StringValue(
    const occ::handle<IFSelect_EditForm>& form,
    const int                             num) const override;

  Standard_EXPORT bool Apply(const occ::handle<IFSelect_EditForm>&        form,
                             const occ::handle<Standard_Transient>&       ent,
                             const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT bool Load(const occ::handle<IFSelect_EditForm>&        form,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  DEFINE_STANDARD_RTTIEXT(STEPEdit_EditSDR, IFSelect_Editor)
};

