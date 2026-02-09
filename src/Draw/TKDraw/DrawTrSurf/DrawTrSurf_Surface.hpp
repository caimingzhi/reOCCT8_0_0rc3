#pragma once

#include <Draw_Color.hpp>
#include <DrawTrSurf_Drawable.hpp>
#include <Draw_Interpretor.hpp>

class Geom_Surface;

class DrawTrSurf_Surface : public DrawTrSurf_Drawable
{
  DEFINE_STANDARD_RTTIEXT(DrawTrSurf_Surface, DrawTrSurf_Drawable)
  Draw_Drawable3D_FACTORY
public:
  Standard_EXPORT DrawTrSurf_Surface(const occ::handle<Geom_Surface>& S);

  Standard_EXPORT DrawTrSurf_Surface(const occ::handle<Geom_Surface>& S,
                                     const int                        Nu,
                                     const int                        Nv,
                                     const Draw_Color&                BoundsColor,
                                     const Draw_Color&                IsosColor,
                                     const int                        Discret,
                                     const double                     Deflection,
                                     const int                        DrawMode);

  Draw_Color BoundsColor() const { return boundsLook; }

  Standard_EXPORT virtual void ClearIsos();

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  Standard_EXPORT void DrawOn(Draw_Display& dis, const bool Iso) const;

  occ::handle<Geom_Surface> GetSurface() const { return surf; }

  Draw_Color IsosColor() const { return isosLook; }

  void NbIsos(int& theNU, int& theNV) const
  {
    theNU = nbUIsos;
    theNV = nbVIsos;
  }

  void SetBoundsColor(const Draw_Color& theColor) { boundsLook = theColor; }

  void SetIsosColor(const Draw_Color& theColor) { isosLook = theColor; }

  virtual void ShowIsos(const int theNu, const int theNv)
  {
    nbUIsos = std::abs(theNu);
    nbVIsos = std::abs(theNv);
  }

  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  Standard_EXPORT void Save(Standard_OStream& theStream) const override;

  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

protected:
  occ::handle<Geom_Surface> surf;
  Draw_Color                boundsLook;
  Draw_Color                isosLook;
  int                       nbUIsos;
  int                       nbVIsos;
};
