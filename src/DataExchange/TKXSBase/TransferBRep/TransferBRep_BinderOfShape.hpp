#pragma once

#include <Standard.hpp>

#include <TopoDS_Shape.hpp>
#include <Transfer_Binder.hpp>
#include <Standard_Type.hpp>
#include <Standard_CString.hpp>

class TransferBRep_BinderOfShape : public Transfer_Binder
{

public:
  Standard_EXPORT TransferBRep_BinderOfShape();

  Standard_EXPORT TransferBRep_BinderOfShape(const TopoDS_Shape& res);

  Standard_EXPORT occ::handle<Standard_Type> ResultType() const override;

  Standard_EXPORT const char* ResultTypeName() const override;

  Standard_EXPORT void SetResult(const TopoDS_Shape& res);

  Standard_EXPORT const TopoDS_Shape& Result() const;

  Standard_EXPORT TopoDS_Shape& CResult();

  DEFINE_STANDARD_RTTIEXT(TransferBRep_BinderOfShape, Transfer_Binder)

private:
  TopoDS_Shape theres;
};
