#pragma once

#include <TDataStd_GenericEmpty.hpp>
class TDF_Label;
class gp_Lin;

//! The basis to define an axis attribute.
//!
//! Warning: Use TDataXtd_Geometry attribute to retrieve the
//! gp_Lin of the Axis attribute
class TDataXtd_Axis : public TDataStd_GenericEmpty
{

public:
  //! class methods
  //! =============
  //! Returns the GUID for an axis.
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Finds or creates an axis attribute defined by the label.
  //! In the case of a creation of an axis, a compatible
  //! named shape should already be associated with label.
  //! Exceptions
  //! Standard_NullObject if no compatible named shape is
  //! associated with the label.
  Standard_EXPORT static occ::handle<TDataXtd_Axis> Set(const TDF_Label& label);

  //! Find, or create, an Axis attribute and set <P> as
  //! generated in the associated NamedShape.

  //! Axis methods
  //! ============
  Standard_EXPORT static occ::handle<TDataXtd_Axis> Set(const TDF_Label& label, const gp_Lin& L);

  Standard_EXPORT TDataXtd_Axis();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataXtd_Axis, TDataStd_GenericEmpty)
};
