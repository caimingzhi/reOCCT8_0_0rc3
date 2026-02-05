#pragma once

#include <Standard.hpp>

#include <gp_Ax3.hpp>
#include <V3d_ViewerPointer.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
#include <Aspect_RectangularGrid.hpp>
class Graphic3d_Structure;
class Graphic3d_Group;

class V3d_RectangularGrid : public Aspect_RectangularGrid
{
  DEFINE_STANDARD_RTTIEXT(V3d_RectangularGrid, Aspect_RectangularGrid)
public:
  Standard_EXPORT V3d_RectangularGrid(const V3d_ViewerPointer& aViewer,
                                      const Quantity_Color&    aColor,
                                      const Quantity_Color&    aTenthColor);

  Standard_EXPORT ~V3d_RectangularGrid() override;

  Standard_EXPORT void SetColors(const Quantity_Color& aColor,
                                 const Quantity_Color& aTenthColor) override;

  Standard_EXPORT void Display() override;

  Standard_EXPORT void Erase() const override;

  Standard_EXPORT bool IsDisplayed() const override;

  Standard_EXPORT void GraphicValues(double& XSize, double& YSize, double& OffSet) const;

  Standard_EXPORT void SetGraphicValues(const double XSize,
                                        const double YSize,
                                        const double OffSet);

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  Standard_EXPORT void UpdateDisplay() override;

private:
  Standard_EXPORT void DefineLines();

  Standard_EXPORT void DefinePoints();

private:
  //! Custom Graphic3d_Structure implementation.
  class RectangularGridStructure;

private:
  occ::handle<Graphic3d_Structure> myStructure;
  occ::handle<Graphic3d_Group>     myGroup;
  gp_Ax3                           myCurViewPlane;
  V3d_ViewerPointer                myViewer;
  bool                             myCurAreDefined;
  bool                             myToComputePrs;
  Aspect_GridDrawMode              myCurDrawMode;
  double                           myCurXo;
  double                           myCurYo;
  double                           myCurAngle;
  double                           myCurXStep;
  double                           myCurYStep;
  double                           myXSize;
  double                           myYSize;
  double                           myOffSet;
};
