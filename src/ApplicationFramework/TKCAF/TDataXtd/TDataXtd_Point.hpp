#pragma once


#include <TDataStd_GenericEmpty.hpp>
class TDF_Label;
class gp_Pnt;

//! The basis to define a point attribute.
//! The topological attribute must contain a vertex.
//! You use this class to create reference points in a design.
//!
//! Warning: Use TDataXtd_Geometry attribute to retrieve the
//! gp_Pnt of the Point attribute
class TDataXtd_Point : public TDataStd_GenericEmpty
{

public:
  //! class methods
  //! =============
  //!
  //! Returns the GUID for point attributes.
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Sets the label Label as a point attribute.
  //! If no object is found, a point attribute is created.
  Standard_EXPORT static occ::handle<TDataXtd_Point> Set(const TDF_Label& label);

  //! Sets the label Label as a point attribute containing the point P.
  //! If no object is found, a point attribute is created.
  //! Point methods
  //! =============
  Standard_EXPORT static occ::handle<TDataXtd_Point> Set(const TDF_Label& label, const gp_Pnt& P);

  Standard_EXPORT TDataXtd_Point();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataXtd_Point, TDataStd_GenericEmpty)
};

