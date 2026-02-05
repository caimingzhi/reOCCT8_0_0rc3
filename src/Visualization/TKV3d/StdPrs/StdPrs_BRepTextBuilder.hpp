#pragma once

#include <Font_BRepFont.hpp>
#include <Font_TextFormatter.hpp>
#include <gp_Ax3.hpp>

//! Represents class for applying text formatting.
class StdPrs_BRepTextBuilder
{
public:
  //! Render text as BRep shape.
  //! @param theFormatter formatter which defines aligned text
  //! @param thePenLoc start position and orientation on the baseline
  //! @return result shape with pen transformation applied as shape location
  Standard_EXPORT TopoDS_Shape Perform(StdPrs_BRepFont&                       theFont,
                                       const occ::handle<Font_TextFormatter>& theFormatter,
                                       const gp_Ax3&                          thePenLoc = gp_Ax3());
  //! Render text as BRep shape.
  //! @param theString text in UTF-8 encoding
  //! @param thePenLoc start position and orientation on the baseline
  //! @param theHAlign horizontal alignment of the text
  //! @param theVAlign vertical alignment of the text
  //! @return result shape with pen transformation applied as shape location
  Standard_EXPORT TopoDS_Shape
    Perform(StdPrs_BRepFont&                        theFont,
            const NCollection_String&               theString,
            const gp_Ax3&                           thePenLoc = gp_Ax3(),
            const Graphic3d_HorizontalTextAlignment theHAlign = Graphic3d_HTA_LEFT,
            const Graphic3d_VerticalTextAlignment   theVAlign = Graphic3d_VTA_BOTTOM);

protected:
  BRep_Builder myBuilder;
};
