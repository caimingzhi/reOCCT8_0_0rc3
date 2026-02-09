#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <Draw_MarkerShape.hpp>
class Draw_Color;
class gp_Pnt;
class gp_Pnt2d;
class gp_Circ;
class gp_Circ2d;

class Draw_Display
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Draw_Display();

  Standard_EXPORT void SetColor(const Draw_Color& col) const;

  Standard_EXPORT void SetMode(const int M) const;

  Standard_EXPORT void Flush() const;

  Standard_EXPORT void MoveTo(const gp_Pnt& pt);

  Standard_EXPORT void DrawTo(const gp_Pnt& pt);

  Standard_EXPORT void MoveTo(const gp_Pnt2d& pt);

  Standard_EXPORT void DrawTo(const gp_Pnt2d& pt);

  Standard_EXPORT void Draw(const gp_Pnt& p1, const gp_Pnt& p2);

  Standard_EXPORT void Draw(const gp_Pnt2d& p1, const gp_Pnt2d& p2);

  Standard_EXPORT void Draw(const gp_Circ& C,
                            const double   A1,
                            const double   A2,
                            const bool     ModifyWithZoom = true);

  Standard_EXPORT void Draw(const gp_Circ2d& C,
                            const double     A1,
                            const double     A2,
                            const bool       ModifyWithZoom = true);

  Standard_EXPORT void DrawMarker(const gp_Pnt& pt, const Draw_MarkerShape S, const int Size = 5);

  Standard_EXPORT void DrawMarker(const gp_Pnt2d& pt, const Draw_MarkerShape S, const int Size = 5);

  Standard_EXPORT void DrawMarker(const gp_Pnt& pt, const Draw_MarkerShape S, const double Size);

  Standard_EXPORT void DrawMarker(const gp_Pnt2d& pt, const Draw_MarkerShape S, const double Size);

  Standard_EXPORT void DrawString(const gp_Pnt& pt, const char* S);

  Standard_EXPORT void DrawString(const gp_Pnt2d& pt, const char* S);

  Standard_EXPORT void DrawString(const gp_Pnt& pt,
                                  const char*   S,
                                  const double  moveX,
                                  const double  moveY);

  Standard_EXPORT void DrawString(const gp_Pnt2d& pt,
                                  const char*     S,
                                  const double    moveX,
                                  const double    moveY);

  Standard_EXPORT gp_Pnt2d Project(const gp_Pnt& pt) const;

  Standard_EXPORT void Project(const gp_Pnt& pt, gp_Pnt2d& pt2d) const;

  Standard_EXPORT double Zoom() const;

  Standard_EXPORT int ViewId() const;

  Standard_EXPORT bool HasPicked() const;
};
