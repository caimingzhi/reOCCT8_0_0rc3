#pragma once

#include <TDataStd_GenericEmpty.hpp>
class TopoDS_Shape;
class TDF_DataSet;

class TDataXtd_Shape : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT static bool Find(const TDF_Label& current, occ::handle<TDataXtd_Shape>& S);

  Standard_EXPORT static occ::handle<TDataXtd_Shape> New(const TDF_Label& label);

  Standard_EXPORT static occ::handle<TDataXtd_Shape> Set(const TDF_Label&    label,
                                                         const TopoDS_Shape& shape);

  Standard_EXPORT static TopoDS_Shape Get(const TDF_Label& label);

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TDataXtd_Shape();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& DS) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataXtd_Shape, TDataStd_GenericEmpty)
};
