#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Vec.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>

class Vrml_Normal : public Standard_Transient
{

public:
  Standard_EXPORT Vrml_Normal(const occ::handle<NCollection_HArray1<gp_Vec>>& aVector);

  Standard_EXPORT Vrml_Normal();

  Standard_EXPORT void SetVector(const occ::handle<NCollection_HArray1<gp_Vec>>& aVector);

  Standard_EXPORT occ::handle<NCollection_HArray1<gp_Vec>> Vector() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

  DEFINE_STANDARD_RTTIEXT(Vrml_Normal, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<gp_Vec>> myVector;
};
