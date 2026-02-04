#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Vec2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>

//! defines a TextureCoordinate2 node of VRML specifying properties of geometry
//! and its appearance.
//! This node defines a set of 2D coordinates to be used to map textures
//! to the vertices of subsequent PointSet, IndexedLineSet, or IndexedFaceSet
//! objects. It replaces the current texture coordinates in the rendering
//! state for the shapes to use.
//! Texture coordinates range from 0 to 1 across the texture.
//! The horizontal coordinate, called S, is specified first, followed
//! by vertical coordinate, T.
//! By default:
//! myPoint (0 0)
class Vrml_TextureCoordinate2 : public Standard_Transient
{

public:
  Standard_EXPORT Vrml_TextureCoordinate2();

  Standard_EXPORT Vrml_TextureCoordinate2(const occ::handle<NCollection_HArray1<gp_Vec2d>>& aPoint);

  Standard_EXPORT void SetPoint(const occ::handle<NCollection_HArray1<gp_Vec2d>>& aPoint);

  Standard_EXPORT occ::handle<NCollection_HArray1<gp_Vec2d>> Point() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

  DEFINE_STANDARD_RTTIEXT(Vrml_TextureCoordinate2, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<gp_Vec2d>> myPoint;
};

