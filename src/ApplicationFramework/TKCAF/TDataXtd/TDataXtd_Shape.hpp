#pragma once


#include <TDataStd_GenericEmpty.hpp>
class TopoDS_Shape;
class TDF_DataSet;

//! A Shape is associated in the framework with :
//! a NamedShape attribute
class TDataXtd_Shape : public TDataStd_GenericEmpty
{

public:
  //! class methods
  //! =============
  //! try to retrieve a Shape attribute at <current> label
  //! or in fathers label of <current>. Returns True if
  //! found and set <S>.
  Standard_EXPORT static bool Find(const TDF_Label& current, occ::handle<TDataXtd_Shape>& S);

  //! Find, or create, a Shape attribute. the Shape attribute
  //! is returned. Raises if <label> has attribute.
  Standard_EXPORT static occ::handle<TDataXtd_Shape> New(const TDF_Label& label);

  //! Create or update associated NamedShape attribute. the
  //! Shape attribute is returned.
  Standard_EXPORT static occ::handle<TDataXtd_Shape> Set(const TDF_Label&    label,
                                                         const TopoDS_Shape& shape);

  //! the Shape from associated NamedShape attribute
  //! is returned.
  Standard_EXPORT static TopoDS_Shape Get(const TDF_Label& label);

  //! Shape methods
  //! =============
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TDataXtd_Shape();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& DS) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataXtd_Shape, TDataStd_GenericEmpty)
};

