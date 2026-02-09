#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <gp_XYZ.hpp>
#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>

class gp_Ax1;
class gp_Ax2;
class gp_Trsf;
class gp_Vec;

class gp_Pnt
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Pnt() noexcept

    = default;

  constexpr gp_Pnt(const gp_XYZ& theCoord) noexcept
      : coord(theCoord)
  {
  }

  constexpr gp_Pnt(const double theXp, const double theYp, const double theZp) noexcept
      : coord(theXp, theYp, theZp)
  {
  }

  constexpr void SetCoord(const int theIndex, const double theXi)
  {
    coord.SetCoord(theIndex, theXi);
  }

  constexpr void SetCoord(const double theXp, const double theYp, const double theZp) noexcept
  {
    coord.SetCoord(theXp, theYp, theZp);
  }

  constexpr void SetX(const double theX) noexcept { coord.SetX(theX); }

  constexpr void SetY(const double theY) noexcept { coord.SetY(theY); }

  constexpr void SetZ(const double theZ) noexcept { coord.SetZ(theZ); }

  constexpr void SetXYZ(const gp_XYZ& theCoord) noexcept { coord = theCoord; }

  constexpr double Coord(const int theIndex) const { return coord.Coord(theIndex); }

  constexpr void Coord(double& theXp, double& theYp, double& theZp) const noexcept
  {
    coord.Coord(theXp, theYp, theZp);
  }

  constexpr double X() const noexcept { return coord.X(); }

  constexpr double Y() const noexcept { return coord.Y(); }

  constexpr double Z() const noexcept { return coord.Z(); }

  constexpr const gp_XYZ& XYZ() const noexcept { return coord; }

  constexpr const gp_XYZ& Coord() const noexcept { return coord; }

  constexpr gp_XYZ& ChangeCoord() noexcept { return coord; }

  constexpr void BaryCenter(const double theAlpha, const gp_Pnt& theP, const double theBeta)
  {
    coord.SetLinearForm(theAlpha, coord, theBeta, theP.coord);
    coord.Divide(theAlpha + theBeta);
  }

  bool IsEqual(const gp_Pnt& theOther, const double theLinearTolerance) const
  {
    return Distance(theOther) <= theLinearTolerance;
  }

  double Distance(const gp_Pnt& theOther) const;

  constexpr double SquareDistance(const gp_Pnt& theOther) const noexcept;

  Standard_EXPORT void Mirror(const gp_Pnt& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Pnt Mirrored(const gp_Pnt& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax1& theA1) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Pnt Mirrored(const gp_Ax1& theA1) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2& theA2) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Pnt Mirrored(const gp_Ax2& theA2) const noexcept;

  void Rotate(const gp_Ax1& theA1, const double theAng);

  [[nodiscard]] gp_Pnt Rotated(const gp_Ax1& theA1, const double theAng) const
  {
    gp_Pnt aP = *this;
    aP.Rotate(theA1, theAng);
    return aP;
  }

  constexpr void Scale(const gp_Pnt& theP, const double theS) noexcept;

  [[nodiscard]] constexpr gp_Pnt Scaled(const gp_Pnt& theP, const double theS) const noexcept
  {
    gp_Pnt aPres = *this;
    aPres.Scale(theP, theS);
    return aPres;
  }

  Standard_EXPORT void Transform(const gp_Trsf& theT);

  [[nodiscard]] gp_Pnt Transformed(const gp_Trsf& theT) const
  {
    gp_Pnt aP = *this;
    aP.Transform(theT);
    return aP;
  }

  constexpr void Translate(const gp_Vec& theV) noexcept;

  [[nodiscard]] constexpr gp_Pnt Translated(const gp_Vec& theV) const noexcept;

  constexpr void Translate(const gp_Pnt& theP1, const gp_Pnt& theP2) noexcept
  {
    coord.Add(theP2.coord);
    coord.Subtract(theP1.coord);
  }

  [[nodiscard]] constexpr gp_Pnt Translated(const gp_Pnt& theP1, const gp_Pnt& theP2) const noexcept
  {
    gp_Pnt aP = *this;
    aP.Translate(theP1, theP2);
    return aP;
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  Standard_EXPORT bool InitFromJson(const Standard_SStream& theSStream, int& theStreamPos);

private:
  gp_XYZ coord;
};

namespace std
{
  template <>
  struct hash<gp_Pnt>
  {
    size_t operator()(const gp_Pnt& thePnt) const noexcept
    {
      union
      {
        double R[3];
        int    I[6];
      } U;

      thePnt.Coord(U.R[0], U.R[1], U.R[2]);

      return std::hash<double>{}(U.I[0] / 23 + U.I[1] / 19 + U.I[2] / 17 + U.I[3] / 13 + U.I[4] / 11
                                 + U.I[5] / 7);
    }
  };

  template <>
  struct equal_to<gp_Pnt>
  {
    bool operator()(const gp_Pnt& thePnt1, const gp_Pnt& thePnt2) const noexcept
    {
      if (std::abs(thePnt1.X() - thePnt2.X()) > Epsilon(thePnt2.X()))
        return false;
      if (std::abs(thePnt1.Y() - thePnt2.Y()) > Epsilon(thePnt2.Y()))
        return false;
      if (std::abs(thePnt1.Z() - thePnt2.Z()) > Epsilon(thePnt2.Z()))
        return false;
      return true;
    }
  };
} // namespace std

#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>

inline double gp_Pnt::Distance(const gp_Pnt& theOther) const
{
  return sqrt(SquareDistance(theOther));
}

inline constexpr double gp_Pnt::SquareDistance(const gp_Pnt& theOther) const noexcept
{
  const gp_XYZ& aXYZ = theOther.coord;
  const double  aDx  = coord.X() - aXYZ.X();
  const double  aDy  = coord.Y() - aXYZ.Y();
  const double  aDz  = coord.Z() - aXYZ.Z();
  return aDx * aDx + aDy * aDy + aDz * aDz;
}

inline void gp_Pnt::Rotate(const gp_Ax1& theA1, const double theAng)
{
  gp_Trsf aT;
  aT.SetRotation(theA1, theAng);
  aT.Transforms(coord);
}

inline constexpr void gp_Pnt::Scale(const gp_Pnt& theP, const double theS) noexcept
{
  gp_XYZ aXYZ = theP.coord;
  aXYZ.Multiply(1.0 - theS);
  coord.Multiply(theS);
  coord.Add(aXYZ);
}

inline constexpr void gp_Pnt::Translate(const gp_Vec& theV) noexcept
{
  coord.Add(theV.XYZ());
}

inline constexpr gp_Pnt gp_Pnt::Translated(const gp_Vec& theV) const noexcept
{
  gp_Pnt aP = *this;
  aP.coord.Add(theV.XYZ());
  return aP;
}
