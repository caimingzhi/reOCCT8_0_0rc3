#pragma once

#include <TDataStd_GenericEmpty.hpp>
class TDF_Label;
class gp_Pln;

//! The basis to define a plane attribute.
//! Warning: Use TDataXtd_Geometry attribute to retrieve the
//! gp_Pln of the Plane attribute
class TDataXtd_Plane : public TDataStd_GenericEmpty
{

public:
  //! class methods
  //! =============
  //!
  //! Returns the GUID for plane attributes.
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Finds or creates the plane attribute defined by
  //! the label label.
  //! Warning
  //! If you are creating the attribute with this syntax, a
  //! planar face should already be associated with label.
  Standard_EXPORT static occ::handle<TDataXtd_Plane> Set(const TDF_Label& label);

  //! Finds, or creates, a Plane attribute and sets <P> as
  //! generated the associated NamedShape.
  //! Plane methods
  //! =============
  Standard_EXPORT static occ::handle<TDataXtd_Plane> Set(const TDF_Label& label, const gp_Pln& P);

  Standard_EXPORT TDataXtd_Plane();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataXtd_Plane, TDataStd_GenericEmpty)
};
