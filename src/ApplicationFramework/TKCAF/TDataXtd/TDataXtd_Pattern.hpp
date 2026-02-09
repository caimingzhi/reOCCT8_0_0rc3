#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDF_Attribute.hpp>
#include <Standard_Integer.hpp>
#include <gp_Trsf.hpp>
#include <NCollection_Array1.hpp>
class Standard_GUID;

class TDataXtd_Pattern : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT virtual const Standard_GUID& PatternID() const = 0;

  Standard_EXPORT virtual int NbTrsfs() const = 0;

  Standard_EXPORT virtual void ComputeTrsfs(NCollection_Array1<gp_Trsf>& Trsfs) const = 0;

  DEFINE_STANDARD_RTTIEXT(TDataXtd_Pattern, TDF_Attribute)
};
