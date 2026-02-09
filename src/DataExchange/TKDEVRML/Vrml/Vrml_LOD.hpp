#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Vec.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>

class Vrml_LOD : public Standard_Transient
{

public:
  Standard_EXPORT Vrml_LOD();

  Standard_EXPORT Vrml_LOD(const occ::handle<NCollection_HArray1<double>>& aRange,
                           const gp_Vec&                                   aCenter);

  Standard_EXPORT void SetRange(const occ::handle<NCollection_HArray1<double>>& aRange);

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> Range() const;

  Standard_EXPORT void SetCenter(const gp_Vec& aCenter);

  Standard_EXPORT gp_Vec Center() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

  DEFINE_STANDARD_RTTIEXT(Vrml_LOD, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<double>> myRange;
  gp_Vec                                   myCenter;
  bool                                     myRangeFlag;
};
