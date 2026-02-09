#pragma once

enum Graphic3d_CubeMapSide
{
  Graphic3d_CMS_POS_X,
  Graphic3d_CMS_NEG_X,
  Graphic3d_CMS_POS_Y,
  Graphic3d_CMS_NEG_Y,
  Graphic3d_CMS_POS_Z,
  Graphic3d_CMS_NEG_Z,
};

#include <Standard_Macro.hpp>

class Graphic3d_ValidatedCubeMapOrder;

class Graphic3d_CubeMapOrder
{

public:
  Standard_EXPORT Graphic3d_CubeMapOrder();

  Standard_EXPORT Graphic3d_CubeMapOrder(unsigned char thePosXLocation,
                                         unsigned char theNegXLocation,
                                         unsigned char thePosYLocation,
                                         unsigned char theNegYLocation,
                                         unsigned char thePosZLocation,
                                         unsigned char theNegZLocation);

  Standard_EXPORT Graphic3d_CubeMapOrder(const Graphic3d_ValidatedCubeMapOrder& theOrder);

  Standard_EXPORT Graphic3d_CubeMapOrder& Set(const Graphic3d_CubeMapOrder& theOrder);

  Standard_EXPORT Graphic3d_ValidatedCubeMapOrder Validated() const;

public:
  Standard_EXPORT Graphic3d_CubeMapOrder& Set(Graphic3d_CubeMapSide theCubeMapSide,
                                              unsigned char         theValue);

  Standard_EXPORT Graphic3d_CubeMapOrder& SetDefault();

  Standard_EXPORT Graphic3d_CubeMapOrder& Permute(const Graphic3d_ValidatedCubeMapOrder& anOrder);

  Standard_EXPORT Graphic3d_CubeMapOrder
    Permuted(const Graphic3d_ValidatedCubeMapOrder& anOrder) const;

  Standard_EXPORT Graphic3d_CubeMapOrder& Swap(Graphic3d_CubeMapSide theFirstSide,
                                               Graphic3d_CubeMapSide theSecondSide);

  Standard_EXPORT Graphic3d_CubeMapOrder Swapped(Graphic3d_CubeMapSide theFirstSide,
                                                 Graphic3d_CubeMapSide theSecondSide) const;

  Standard_EXPORT unsigned char Get(Graphic3d_CubeMapSide theCubeMapSide) const;

  Standard_EXPORT unsigned char operator[](Graphic3d_CubeMapSide theCubeMapSide) const;

  Standard_EXPORT Graphic3d_CubeMapOrder& Clear();

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT bool HasRepetitions() const;

  Standard_EXPORT bool HasOverflows() const;

  Standard_EXPORT bool IsValid() const;

public:
  Standard_EXPORT static const Graphic3d_ValidatedCubeMapOrder& Default();

private:
  unsigned char get(unsigned char theCubeMapSide) const;

  void set(unsigned char theCubeMapSide, unsigned char theValue);

  void set(Graphic3d_CubeMapSide theCubeMapSide, unsigned char theValue);

private:
  unsigned int myConvolution;
  bool         myHasOverflows;
};

class Graphic3d_ValidatedCubeMapOrder
{

public:
  friend class Graphic3d_CubeMapOrder;

  const Graphic3d_CubeMapOrder* operator->() const { return &Order; }

  Graphic3d_ValidatedCubeMapOrder(const Graphic3d_ValidatedCubeMapOrder& theOther)

    = default;

public:
  const Graphic3d_CubeMapOrder Order;

private:
  Graphic3d_ValidatedCubeMapOrder(const Graphic3d_CubeMapOrder theOrder)
      : Order(theOrder)
  {
  }

  Graphic3d_ValidatedCubeMapOrder& operator=(const Graphic3d_ValidatedCubeMapOrder&) = delete;
};
