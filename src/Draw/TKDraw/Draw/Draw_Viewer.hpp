#pragma once

#include <gp_Trsf.hpp>
#include <gp_Ax1.hpp>
#include <Draw_Drawable3D.hpp>
#include <NCollection_Sequence.hpp>
#include <Draw_Color.hpp>

#ifdef _WIN32
  #include <windows.h>
#endif

const int MAXVIEW = 30;

class Draw_View;

class Draw_Viewer
{

public:
  Standard_EXPORT      Draw_Viewer();
  Standard_EXPORT bool DefineColor(const int i, const char* colname);
  Standard_EXPORT void MakeView(const int   id,
                                const char* typ,
                                const int   X,
                                const int   Y,
                                const int   W,
                                const int   H);

#ifdef _WIN32
  Standard_EXPORT void MakeView(const int   id,
                                const char* typ,
                                const int   X,
                                const int   Y,
                                const int   W,
                                const int   H,
                                HWND        win,
                                const bool  useBuffer = false);
#endif
  Standard_EXPORT void   MakeView(const int id, const char* typ, const char* window);
  Standard_EXPORT void   SetTitle(const int id, const char* name);
  Standard_EXPORT void   ResetView(const int id);
  Standard_EXPORT void   SetZoom(const int id, const double z);
  Standard_EXPORT void   RotateView(const int id, const gp_Dir2d&, const double);
  Standard_EXPORT void   RotateView(const int id, const gp_Pnt&, const gp_Dir&, const double);
  Standard_EXPORT void   SetFocal(const int id, const double FocalDist);
  Standard_EXPORT char*  GetType(const int id) const;
  Standard_EXPORT double Zoom(const int id) const;
  Standard_EXPORT double Focal(const int id) const;
  Standard_EXPORT void   SetTrsf(const int id, gp_Trsf& T);
  Standard_EXPORT void   GetTrsf(const int id, gp_Trsf& T) const;
  Standard_EXPORT void   GetPosSize(const int id, int& X, int& Y, int& W, int& H);
  Standard_EXPORT bool   Is3D(const int id) const;
  Standard_EXPORT void   GetFrame(const int id, int& xmin, int& ymin, int& xmax, int& ymax);
  Standard_EXPORT void   FitView(const int id, const int frame);
  Standard_EXPORT void   PanView(const int id, const int DX, const int DY);
  Standard_EXPORT void   SetPan(const int id, const int DX, const int DY);
  Standard_EXPORT void   GetPan(const int id, int& DX, int& DY);
  Standard_EXPORT bool   HasView(const int id) const;
  Standard_EXPORT void   DisplayView(const int id) const;
  Standard_EXPORT void   HideView(const int id) const;
  Standard_EXPORT void   ClearView(const int id) const;
  Standard_EXPORT void   RemoveView(const int id);
  Standard_EXPORT void   RepaintView(const int id) const;
#ifdef _WIN32
  Standard_EXPORT void ResizeView(const int id) const;
  Standard_EXPORT void UpdateView(const int id, const bool forced = false) const;
#endif
  Standard_EXPORT void ConfigView(const int id) const;
  Standard_EXPORT void PostScriptView(const int     id,
                                      const int     VXmin,
                                      const int     VYmin,
                                      const int     VXmax,
                                      const int     VYmax,
                                      const int     PXmin,
                                      const int     PYmin,
                                      const int     PXmax,
                                      const int     PYmax,
                                      std::ostream& sortie) const;
  Standard_EXPORT void PostColor(const int icol, const int width, const double gray);
  Standard_EXPORT bool SaveView(const int id, const char* filename);
  Standard_EXPORT void RepaintAll() const;
  Standard_EXPORT void Repaint2D() const;
  Standard_EXPORT void Repaint3D() const;
  Standard_EXPORT void DeleteView(const int id);
  Standard_EXPORT void Clear();
  Standard_EXPORT void Clear2D();
  Standard_EXPORT void Clear3D();
  Standard_EXPORT void Flush();

  Standard_EXPORT void DrawOnView(const int id, const occ::handle<Draw_Drawable3D>& D) const;
  Standard_EXPORT void HighlightOnView(const int                           id,
                                       const occ::handle<Draw_Drawable3D>& D,
                                       const Draw_ColorKind                C = Draw_blanc) const;
  Standard_EXPORT void AddDrawable(const occ::handle<Draw_Drawable3D>& D);
  Standard_EXPORT void RemoveDrawable(const occ::handle<Draw_Drawable3D>& D);
  Standard_EXPORT Draw_Display MakeDisplay(const int id) const;

  Standard_EXPORT void Select(int& id, int& X, int& Y, int& Button, bool waitclick = true);

  Standard_EXPORT int Pick(const int                     id,
                           const int                     X,
                           const int                     Y,
                           const int                     Prec,
                           occ::handle<Draw_Drawable3D>& D,
                           const int                     First = 0) const;

  Standard_EXPORT void LastPick(gp_Pnt& P1, gp_Pnt& P2, double& Param);

  Standard_EXPORT ~Draw_Viewer();
  Standard_EXPORT Draw_Viewer& operator<<(const occ::handle<Draw_Drawable3D>&);
  Standard_EXPORT const NCollection_Sequence<occ::handle<Draw_Drawable3D>>& GetDrawables();

private:
  Draw_View*                                         myViews[MAXVIEW];
  NCollection_Sequence<occ::handle<Draw_Drawable3D>> myDrawables;
};
