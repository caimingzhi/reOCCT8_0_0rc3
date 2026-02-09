#include <MeshVS_TwoColors.hpp>

MeshVS_TwoColors BindTwoColors(const Quantity_Color& theCol1, const Quantity_Color& theCol2)
{
  MeshVS_TwoColors         aRes;
  NCollection_Vec3<double> aColor_sRGB;
  theCol1.Values(aColor_sRGB.r(), aColor_sRGB.g(), aColor_sRGB.b(), Quantity_TOC_sRGB);
  aRes.r1 = unsigned(aColor_sRGB.r() * 255.0);
  aRes.g1 = unsigned(aColor_sRGB.g() * 255.0);
  aRes.b1 = unsigned(aColor_sRGB.b() * 255.0);
  theCol2.Values(aColor_sRGB.r(), aColor_sRGB.g(), aColor_sRGB.b(), Quantity_TOC_sRGB);
  aRes.r2 = unsigned(aColor_sRGB.r() * 255.0);
  aRes.g2 = unsigned(aColor_sRGB.g() * 255.0);
  aRes.b2 = unsigned(aColor_sRGB.b() * 255.0);

  return aRes;
}

Quantity_Color ExtractColor(MeshVS_TwoColors& theTwoColors, const int Index)
{
  Quantity_Color aRes;
  double         max = 255.0;

  if (Index == 1)
    aRes.SetValues(double(theTwoColors.r1) / max,
                   double(theTwoColors.g1) / max,
                   double(theTwoColors.b1) / max,
                   Quantity_TOC_sRGB);
  else if (Index == 2)
    aRes.SetValues(double(theTwoColors.r2) / max,
                   double(theTwoColors.g2) / max,
                   double(theTwoColors.b2) / max,
                   Quantity_TOC_sRGB);

  return aRes;
}

void ExtractColors(MeshVS_TwoColors& theTwoColors, Quantity_Color& theCol1, Quantity_Color& theCol2)
{
  double max = 255.0;
  theCol1.SetValues(double(theTwoColors.r1) / max,
                    double(theTwoColors.g1) / max,
                    double(theTwoColors.b1) / max,
                    Quantity_TOC_sRGB);
  theCol2.SetValues(double(theTwoColors.r2) / max,
                    double(theTwoColors.g2) / max,
                    double(theTwoColors.b2) / max,
                    Quantity_TOC_sRGB);
}
