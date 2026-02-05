#pragma once

#include <BRepLib_ToolTriangulatedShape.hpp>
#include <gp_Dir.hpp>
#include <NCollection_Array1.hpp>

class TopoDS_Shape;
class Prs3d_Drawer;

class StdPrs_ToolTriangulatedShape : public BRepLib_ToolTriangulatedShape
{
public:
  //! Similar to BRepTools::Triangulation() but without extra checks.
  //! @return true if all faces within shape are triangulated.
  Standard_EXPORT static bool IsTriangulated(const TopoDS_Shape& theShape);

  //! Checks back faces visibility for specified shape (to activate back-face culling).
  //! @return true if shape is closed manifold Solid or compound of such Solids.
  Standard_EXPORT static bool IsClosed(const TopoDS_Shape& theShape);

  //! Computes the absolute deflection value depending on the type of deflection in theDrawer:
  //! <ul>
  //! <li><b>Aspect_TOD_RELATIVE</b>: the absolute deflection is computed using the relative
  //! deviation coefficient from theDrawer and the shape's bounding box;</li>
  //! <li><b>Aspect_TOD_ABSOLUTE</b>: the maximal chordial deviation from theDrawer is
  //! returned.</li>
  //! </ul>
  //! In case of the type of deflection in theDrawer computed relative deflection for shape is
  //! stored as absolute deflection. It is necessary to use it later on for sub-shapes. This
  //! function should always be used to compute the deflection value for building discrete
  //! representations of the shape (triangulation, wireframe) to avoid inconsistencies between
  //! different representations of the shape and undesirable visual artifacts.
  Standard_EXPORT static double GetDeflection(const TopoDS_Shape&              theShape,
                                              const occ::handle<Prs3d_Drawer>& theDrawer);

  //! Checks whether the shape is properly triangulated for a given display settings.
  //! @param[in] theShape  the shape.
  //! @param[in] theDrawer  the display settings.
  Standard_EXPORT static bool IsTessellated(const TopoDS_Shape&              theShape,
                                            const occ::handle<Prs3d_Drawer>& theDrawer);

  //! Validates triangulation within the shape and performs tessellation if necessary.
  //! @param[in] theShape  the shape.
  //! @param[in] theDrawer  the display settings.
  //! @return true if tessellation was recomputed and false otherwise.
  Standard_EXPORT static bool Tessellate(const TopoDS_Shape&              theShape,
                                         const occ::handle<Prs3d_Drawer>& theDrawer);

  //! If presentation has own deviation coefficient and IsAutoTriangulation() is true,
  //! function will compare actual coefficients with previous values and will clear triangulation on
  //! their change (regardless actual tessellation quality). Function is placed here for
  //! compatibility reasons - new code should avoid using IsAutoTriangulation().
  //! @param[in] theShape   the shape
  //! @param[in] theDrawer  the display settings
  //! @param[in] theToResetCoeff  updates coefficients in theDrawer to actual state to avoid
  //! redundant recomputations
  Standard_EXPORT static void ClearOnOwnDeflectionChange(const TopoDS_Shape&              theShape,
                                                         const occ::handle<Prs3d_Drawer>& theDrawer,
                                                         const bool theToResetCoeff);
};
