#pragma once

#include <gp_Ax2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_Vec2d.hpp>

class gp_Ax22d
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Ax22d() noexcept
      : vydir(gp_Dir2d::D::Y)

  {
  }

  constexpr gp_Ax22d(const gp_Pnt2d& theP, const gp_Dir2d& theVx, const gp_Dir2d& theVy)
      : point(theP),
        vydir(theVy),
        vxdir(theVx)
  {
    const double aValue = theVx.Crossed(theVy);
    if (aValue >= 0.0)
    {
      vydir.SetCoord(-vxdir.Y(), vxdir.X());
    }
    else
    {
      vydir.SetCoord(vxdir.Y(), -vxdir.X());
    }
  }

  constexpr gp_Ax22d(const gp_Pnt2d& theP, const gp_Dir2d& theV, const bool theIsSense = true)
      : point(theP),
        vxdir(theV)
  {
    if (theIsSense)
    {
      vydir.SetCoord(-theV.Y(), theV.X());
    }
    else
    {
      vydir.SetCoord(theV.Y(), -theV.X());
    }
  }

  constexpr gp_Ax22d(const gp_Ax2d& theA, const bool theIsSense = true)
      : point(theA.Location()),
        vxdir(theA.Direction())
  {
    if (theIsSense)
    {
      vydir.SetCoord(-vxdir.Y(), vxdir.X());
    }
    else
    {
      vydir.SetCoord(vxdir.Y(), -vxdir.X());
    }
  }

  constexpr void SetAxis(const gp_Ax22d& theA1) noexcept
  {
    point = theA1.Location();
    vxdir = theA1.XDirection();
    vydir = theA1.YDirection();
  }

  constexpr void SetXAxis(const gp_Ax2d& theA1);

  constexpr void SetYAxis(const gp_Ax2d& theA1);

  constexpr void SetLocation(const gp_Pnt2d& theP) noexcept { point = theP; }

  constexpr void SetXDirection(const gp_Dir2d& theVx);

  constexpr void SetYDirection(const gp_Dir2d& theVy);

  gp_Ax2d XAxis() const { return gp_Ax2d(point, vxdir); }

  gp_Ax2d YAxis() const { return gp_Ax2d(point, vydir); }

  constexpr const gp_Pnt2d& Location() const noexcept { return point; }

  constexpr const gp_Dir2d& XDirection() const noexcept { return vxdir; }

  constexpr const gp_Dir2d& YDirection() const noexcept { return vydir; }

  Standard_EXPORT void Mirror(const gp_Pnt2d& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Ax22d Mirrored(const gp_Pnt2d& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2d& theA) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Ax22d Mirrored(const gp_Ax2d& theA) const noexcept;

  void Rotate(const gp_Pnt2d& theP, const double theAng);

  [[nodiscard]] gp_Ax22d Rotated(const gp_Pnt2d& theP, const double theAng) const
  {
    gp_Ax22d aTemp = *this;
    aTemp.Rotate(theP, theAng);
    return aTemp;
  }

  void Scale(const gp_Pnt2d& theP, const double theS);

  [[nodiscard]] gp_Ax22d Scaled(const gp_Pnt2d& theP, const double theS) const
  {
    gp_Ax22d aTemp = *this;
    aTemp.Scale(theP, theS);
    return aTemp;
  }

  void Transform(const gp_Trsf2d& theT) noexcept;

  [[nodiscard]] gp_Ax22d Transformed(const gp_Trsf2d& theT) const
  {
    gp_Ax22d aTemp = *this;
    aTemp.Transform(theT);
    return aTemp;
  }

  constexpr void Translate(const gp_Vec2d& theV) noexcept { point.Translate(theV); }

  [[nodiscard]] constexpr gp_Ax22d Translated(const gp_Vec2d& theV) const noexcept
  {
    gp_Ax22d aTemp = *this;
    aTemp.Translate(theV);
    return aTemp;
  }

  constexpr void Translate(const gp_Pnt2d& theP1, const gp_Pnt2d& theP2) noexcept
  {
    point.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Ax22d Translated(const gp_Pnt2d& theP1,
                                              const gp_Pnt2d& theP2) const noexcept
  {
    gp_Ax22d aTemp = *this;
    aTemp.Translate(theP1, theP2);
    return aTemp;
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  gp_Pnt2d point;
  gp_Dir2d vydir;
  gp_Dir2d vxdir;
};

inline constexpr void gp_Ax22d::SetXAxis(const gp_Ax2d& theA1)
{
  const bool isSign = (vxdir.Crossed(vydir)) >= 0.0;
  point             = theA1.Location();
  vxdir             = theA1.Direction();
  if (isSign)
  {
    vydir.SetCoord(-vxdir.Y(), vxdir.X());
  }
  else
  {
    vydir.SetCoord(vxdir.Y(), -vxdir.X());
  }
}

inline constexpr void gp_Ax22d::SetYAxis(const gp_Ax2d& theA1)
{
  const bool isSign = (vxdir.Crossed(vydir)) >= 0.0;
  point             = theA1.Location();
  vydir             = theA1.Direction();
  if (isSign)
  {
    vxdir.SetCoord(vydir.Y(), -vydir.X());
  }
  else
  {
    vxdir.SetCoord(-vydir.Y(), vydir.X());
  }
}

inline constexpr void gp_Ax22d::SetXDirection(const gp_Dir2d& theVx)
{
  const bool isSign = (vxdir.Crossed(vydir)) >= 0.0;
  vxdir             = theVx;
  if (isSign)
  {
    vydir.SetCoord(-theVx.Y(), theVx.X());
  }
  else
  {
    vydir.SetCoord(theVx.Y(), -theVx.X());
  }
}

inline constexpr void gp_Ax22d::SetYDirection(const gp_Dir2d& theVy)
{
  const bool isSign = (vxdir.Crossed(vydir)) >= 0.0;
  vydir             = theVy;
  if (isSign)
  {
    vxdir.SetCoord(theVy.Y(), -theVy.X());
  }
  else
  {
    vxdir.SetCoord(-theVy.Y(), theVy.X());
  }
}

inline void gp_Ax22d::Rotate(const gp_Pnt2d& theP, const double theAng)
{
  gp_Pnt2d aTemp = point;
  aTemp.Rotate(theP, theAng);
  point = aTemp;
  vxdir.Rotate(theAng);
  vydir.Rotate(theAng);
}

inline void gp_Ax22d::Scale(const gp_Pnt2d& theP, const double theS)
{
  gp_Pnt2d aTemp = point;
  aTemp.Scale(theP, theS);
  point = aTemp;
  if (theS < 0.0)
  {
    vxdir.Reverse();
    vydir.Reverse();
  }
}

inline void gp_Ax22d::Transform(const gp_Trsf2d& theT) noexcept
{
  gp_Pnt2d aTemp = point;
  aTemp.Transform(theT);
  point = aTemp;
  vxdir.Transform(theT);
  vydir.Transform(theT);
}
