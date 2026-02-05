#pragma once

#include <Quantity_Color.hpp>

struct MeshVS_TwoColors
{
  unsigned int r1 : 8;
  unsigned int g1 : 8;
  unsigned int b1 : 8;
  unsigned int r2 : 8;
  unsigned int g2 : 8;
  unsigned int b2 : 8;

  bool operator==(const MeshVS_TwoColors& TwoColors) const
  {
    return (((r1 * 256 + g1) * 256 + b1)
              == ((TwoColors.r1 * 256 + TwoColors.g1) * 256 + TwoColors.b1)
            && ((r2 * 256 + g2) * 256 + b2)
                 == ((TwoColors.r2 * 256 + TwoColors.g2) * 256 + TwoColors.b2));
  }
};

namespace std
{
  template <>
  struct hash<MeshVS_TwoColors>
  {
    size_t operator()(const MeshVS_TwoColors& TwoColors) const noexcept
    {
      unsigned int aHash = 0;
      meshprsHashByte(aHash, TwoColors.r1);
      meshprsHashByte(aHash, TwoColors.g1);
      meshprsHashByte(aHash, TwoColors.b1);
      meshprsHashByte(aHash, TwoColors.r2);
      meshprsHashByte(aHash, TwoColors.g2);
      meshprsHashByte(aHash, TwoColors.b2);
      return std::hash<unsigned int>{}(aHash);
    }

  private:
    void meshprsHashByte(unsigned int& theHash, const unsigned int theValues) const noexcept
    {
      theHash += (theValues);
      theHash += (theHash << 10);
      theHash ^= (theHash >> 6);
    }
  };
} // namespace std

Standard_EXPORT MeshVS_TwoColors BindTwoColors(const Quantity_Color&, const Quantity_Color&);
Standard_EXPORT Quantity_Color   ExtractColor(MeshVS_TwoColors&, const int);
Standard_EXPORT void             ExtractColors(MeshVS_TwoColors&, Quantity_Color&, Quantity_Color&);
