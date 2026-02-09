#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Vec.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>

class Vrml_Coordinate3 : public Standard_Transient
{

public:
  Standard_EXPORT Vrml_Coordinate3(const occ::handle<NCollection_HArray1<gp_Vec>>& aPoint);

  Standard_EXPORT Vrml_Coordinate3();

  Standard_EXPORT void SetPoint(const occ::handle<NCollection_HArray1<gp_Vec>>& aPoint);

  Standard_EXPORT occ::handle<NCollection_HArray1<gp_Vec>> Point() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

  DEFINE_STANDARD_RTTIEXT(Vrml_Coordinate3, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<gp_Vec>> myPoint;
};
