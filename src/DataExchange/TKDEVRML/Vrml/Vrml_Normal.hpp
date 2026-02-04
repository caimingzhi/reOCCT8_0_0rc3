#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Vec.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>

//! defines a Normal node of VRML specifying properties of geometry
//! and its appearance.
//! This node defines a set of 3D surface normal vectors to be used by vertex-based shape
//! nodes (IndexedFaceSet, IndexedLineSet, PointSet) that follow it in the scene graph. This
//! node does not produce a visible result during rendering; it simply replaces the current
//! normals in the rendering state for subsequent nodes to use. This node contains one
//! multiple-valued field that contains the normal vectors.
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

