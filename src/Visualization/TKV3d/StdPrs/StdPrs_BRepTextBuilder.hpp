#pragma once

#include <Font_BRepFont.hpp>
#include <Font_TextFormatter.hpp>
#include <gp_Ax3.hpp>

class StdPrs_BRepTextBuilder
{
public:
  Standard_EXPORT TopoDS_Shape Perform(StdPrs_BRepFont&                       theFont,
                                       const occ::handle<Font_TextFormatter>& theFormatter,
                                       const gp_Ax3&                          thePenLoc = gp_Ax3());

  Standard_EXPORT TopoDS_Shape
    Perform(StdPrs_BRepFont&                        theFont,
            const NCollection_String&               theString,
            const gp_Ax3&                           thePenLoc = gp_Ax3(),
            const Graphic3d_HorizontalTextAlignment theHAlign = Graphic3d_HTA_LEFT,
            const Graphic3d_VerticalTextAlignment   theVAlign = Graphic3d_VTA_BOTTOM);

protected:
  BRep_Builder myBuilder;
};
