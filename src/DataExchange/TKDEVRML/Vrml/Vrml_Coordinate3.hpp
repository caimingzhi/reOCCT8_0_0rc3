#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Vec.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>

//! defines a Coordinate3 node of VRML specifying
//! properties of geometry and its appearance.
//! This node defines a set of 3D coordinates to be used by a subsequent IndexedFaceSet,
//! IndexedLineSet, or PointSet node. This node does not produce a visible result
//! during rendering; it simply replaces the current coordinates in the rendering
//! state for subsequent nodes to use.
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
