#pragma once


#include <Standard.hpp>

#include <DBRep_DrawableShape.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
class Draw_Text3D;
class TopoDS_Shape;
class gp_Pnt;
class Draw_Display;

class BOPTest_DrawableShape : public DBRep_DrawableShape
{

public:
  Standard_EXPORT BOPTest_DrawableShape(const TopoDS_Shape& S,
                                        const Draw_Color&   FreeCol,
                                        const Draw_Color&   ConnCol,
                                        const Draw_Color&   EdgeCol,
                                        const Draw_Color&   IsosCol,
                                        const double        size,
                                        const int           nbisos,
                                        const int           discret,
                                        const char*         Text,
                                        const Draw_Color&   TextColor);

  Standard_EXPORT BOPTest_DrawableShape(const TopoDS_Shape& S,
                                        const char*         Text,
                                        const Draw_Color&   TextColor);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  DEFINE_STANDARD_RTTIEXT(BOPTest_DrawableShape, DBRep_DrawableShape)

private:
  Standard_EXPORT gp_Pnt Pnt() const;

  occ::handle<Draw_Text3D> myText;
  Draw_Color               myTextColor;
};

