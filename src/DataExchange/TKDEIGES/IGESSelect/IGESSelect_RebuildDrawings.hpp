#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESSelect_ModelModifier.hpp>
class IFSelect_ContextModif;
class IGESData_IGESModel;
class Interface_CopyTool;
class TCollection_AsciiString;

//! Rebuilds Drawings which were bypassed to produce new models.
//! If a set of entities, all put into a same IGESModel, were
//! attached to a same Drawing in the starting Model, this Modifier
//! rebuilds the original Drawing, but only with the transferred
//! entities. This includes that all its views are kept too, but
//! empty; and annotations are not kept. Drawing Name is renewed.
//!
//! If the Input Selection is present, tries to rebuild Drawings
//! only for the selected entities. Else, tries to rebuild
//! Drawings for all the transferred entities.
class IGESSelect_RebuildDrawings : public IGESSelect_ModelModifier
{

public:
  //! Creates an RebuildDrawings, which uses the system Date
  Standard_EXPORT IGESSelect_RebuildDrawings();

  //! Specific action : Rebuilds the original Drawings
  Standard_EXPORT void Performing(IFSelect_ContextModif&                 ctx,
                                  const occ::handle<IGESData_IGESModel>& target,
                                  Interface_CopyTool&                    TC) const override;

  //! Returns a text which is
  //! "Rebuild Drawings"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_RebuildDrawings, IGESSelect_ModelModifier)
};

