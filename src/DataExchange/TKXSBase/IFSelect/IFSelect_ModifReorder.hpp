#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Modifier.hpp>
class IFSelect_ContextModif;
class Interface_InterfaceModel;
class Interface_Protocol;
class Interface_CopyTool;
class TCollection_AsciiString;

//! This modifier reorders a whole model from its roots, i.e.
//! according to <rootlast> status, it considers each of its
//! roots, then it orders all its shared entities at any level,
//! the result begins by the lower level entities ... ends by
//! the roots.
class IFSelect_ModifReorder : public IFSelect_Modifier
{

public:
  //! Creates a ModifReorder. It may change the graph (it does !)
  //! If <rootlast> is True (D), roots are set at the end of packets
  //! Else, they are set at beginning (as done by AddWithRefs)
  Standard_EXPORT IFSelect_ModifReorder(const bool rootlast = true);

  //! Acts by computing orders (by method All from ShareTool) then
  //! forcing them in the model. Remark that selection is ignored :
  //! ALL the model is processed in once
  Standard_EXPORT void Perform(IFSelect_ContextModif&                       ctx,
                               const occ::handle<Interface_InterfaceModel>& target,
                               const occ::handle<Interface_Protocol>&       protocol,
                               Interface_CopyTool&                          TC) const override;

  //! Returns Label as "Reorder, Roots (last or first)"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_ModifReorder, IFSelect_Modifier)

private:
  bool thertl;
};

