#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Trsf.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>

//! Describes a coordinate transformation, i.e. a change
//! to an elementary 3D coordinate system, or position in 3D space.
//! A Datum3D is always described relative to the default datum.
//! The default datum is described relative to itself: its
//! origin is (0,0,0), and its axes are (1,0,0) (0,1,0) (0,0,1).
class TopLoc_Datum3D : public Standard_Transient
{

public:
  //! Constructs a default Datum3D.
  Standard_EXPORT TopLoc_Datum3D();

  //! Constructs a Datum3D form a Trsf from gp. An error is
  //! raised if the Trsf is not a rigid transformation.
  Standard_EXPORT TopLoc_Datum3D(const gp_Trsf& T);

  //! Returns a gp_Trsf which, when applied to this datum, produces the default datum.
  const gp_Trsf& Transformation() const { return myTrsf; }

  //! Returns a gp_Trsf which, when applied to this datum, produces the default datum.
  const gp_Trsf& Trsf() const { return myTrsf; }

  //! Return transformation form.
  gp_TrsfForm Form() const { return myTrsf.Form(); }

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  //! Writes the contents of this Datum3D to the stream S.
  Standard_EXPORT void ShallowDump(Standard_OStream& S) const;

  DEFINE_STANDARD_RTTIEXT(TopLoc_Datum3D, Standard_Transient)

private:
  gp_Trsf myTrsf;
};

inline void ShallowDump(const occ::handle<TopLoc_Datum3D>& me, Standard_OStream& S)
{
  me->ShallowDump(S);
}
