#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Trsf.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>

class TopLoc_Datum3D : public Standard_Transient
{

public:
  Standard_EXPORT TopLoc_Datum3D();

  Standard_EXPORT TopLoc_Datum3D(const gp_Trsf& T);

  const gp_Trsf& Transformation() const { return myTrsf; }

  const gp_Trsf& Trsf() const { return myTrsf; }

  gp_TrsfForm Form() const { return myTrsf.Form(); }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  Standard_EXPORT void ShallowDump(Standard_OStream& S) const;

  DEFINE_STANDARD_RTTIEXT(TopLoc_Datum3D, Standard_Transient)

private:
  gp_Trsf myTrsf;
};

inline void ShallowDump(const occ::handle<TopLoc_Datum3D>& me, Standard_OStream& S)
{
  me->ShallowDump(S);
}
