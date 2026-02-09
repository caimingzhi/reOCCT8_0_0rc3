#pragma once

enum Aspect_HatchStyle
{
  Aspect_HS_SOLID              = 0,
  Aspect_HS_HORIZONTAL         = 7,
  Aspect_HS_HORIZONTAL_WIDE    = 11,
  Aspect_HS_VERTICAL           = 8,
  Aspect_HS_VERTICAL_WIDE      = 12,
  Aspect_HS_DIAGONAL_45        = 5,
  Aspect_HS_DIAGONAL_45_WIDE   = 9,
  Aspect_HS_DIAGONAL_135       = 6,
  Aspect_HS_DIAGONAL_135_WIDE  = 10,
  Aspect_HS_GRID               = 3,
  Aspect_HS_GRID_WIDE          = 4,
  Aspect_HS_GRID_DIAGONAL      = 1,
  Aspect_HS_GRID_DIAGONAL_WIDE = 2,
  Aspect_HS_NB                 = 13,
};

#include <Image_PixMap.hpp>
#include <NCollection_Buffer.hpp>

class Graphic3d_HatchStyle : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_HatchStyle, Standard_Transient)

public:
  Standard_EXPORT Graphic3d_HatchStyle(const occ::handle<Image_PixMap>& thePattern);

  Graphic3d_HatchStyle(const Aspect_HatchStyle theType)
      : myHatchType(theType)
  {
  }

  Standard_EXPORT const uint8_t* Pattern() const;

  int HatchType() const { return myHatchType; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  occ::handle<NCollection_Buffer> myPattern;
  int                             myHatchType;
};
