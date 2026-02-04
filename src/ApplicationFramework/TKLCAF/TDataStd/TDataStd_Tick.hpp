#pragma once


#include <TDataStd_GenericEmpty.hpp>
#include <Standard_OStream.hpp>
class Standard_GUID;
class TDF_Label;

//! Defines a boolean attribute.
//! If it exists at a label - true,
//! Otherwise - false.
class TDataStd_Tick : public TDataStd_GenericEmpty
{

public:
  //! Static methods
  //! ==============
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Find, or create, a Tick attribute.
  //! Tick methods
  //! ============
  Standard_EXPORT static occ::handle<TDataStd_Tick> Set(const TDF_Label& label);

  Standard_EXPORT TDataStd_Tick();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataStd_Tick, TDataStd_GenericEmpty)
};

