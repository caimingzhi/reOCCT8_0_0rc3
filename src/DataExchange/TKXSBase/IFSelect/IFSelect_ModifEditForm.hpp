#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Modifier.hpp>
class IFSelect_EditForm;
class IFSelect_ContextModif;
class Interface_InterfaceModel;
class Interface_Protocol;
class Interface_CopyTool;
class TCollection_AsciiString;

//! This modifier applies an EditForm on the entities selected
class IFSelect_ModifEditForm : public IFSelect_Modifier
{

public:
  //! Creates a ModifEditForm. It may not change the graph
  Standard_EXPORT IFSelect_ModifEditForm(const occ::handle<IFSelect_EditForm>& editform);

  //! Returns the EditForm
  Standard_EXPORT occ::handle<IFSelect_EditForm> EditForm() const;

  //! Acts by applying an EditForm to entities, selected or all model
  Standard_EXPORT void Perform(IFSelect_ContextModif&                       ctx,
                               const occ::handle<Interface_InterfaceModel>& target,
                               const occ::handle<Interface_Protocol>&       protocol,
                               Interface_CopyTool&                          TC) const override;

  //! Returns Label as "Apply EditForm <+ label of EditForm>"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_ModifEditForm, IFSelect_Modifier)

private:
  occ::handle<IFSelect_EditForm> theedit;
};
