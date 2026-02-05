#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Vec.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>

//! defines a LOD (level of detailization) node of VRML specifying properties
//! of geometry and its appearance.
//! This group node is used to allow applications to switch between
//! various representations of objects automatically. The children of this
//! node typically represent the same object or objects at the varying
//! of Levels Of Detail (LOD), from highest detail to lowest.
//!
//! The specified center point of the LOD is transformed by current
//! transformation into world space, and the distance from the transformed
//! center to the world-space eye point is calculated.
//! If thedistance is less than the first value in the ranges array,
//! than the first child of the LOD group is drawn. If between
//! the first and second values in the range array, the second child
//! is drawn, etc.
//! If there are N values in the range array, the LOD group should
//! have N+1 children.
//! Specifying too few children will result in the last child being
//! used repeatedly for the lowest levels of detail; if too many children
//! are specified, the extra children will be ignored.
//! Each value in the ranges array should be greater than the previous
//! value, otherwise results are undefined.
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
