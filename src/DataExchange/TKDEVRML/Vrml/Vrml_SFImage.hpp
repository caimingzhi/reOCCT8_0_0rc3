#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>

enum Vrml_SFImageNumber
{
  Vrml_NULL,
  Vrml_ONE,
  Vrml_TWO,
  Vrml_THREE,
  Vrml_FOUR
};

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>

//! defines SFImage type of VRML field types.
class Vrml_SFImage : public Standard_Transient
{

public:
  Standard_EXPORT Vrml_SFImage();

  Standard_EXPORT Vrml_SFImage(const int                                    aWidth,
                               const int                                    aHeight,
                               const Vrml_SFImageNumber                     aNumber,
                               const occ::handle<NCollection_HArray1<int>>& anArray);

  Standard_EXPORT void SetWidth(const int aWidth);

  Standard_EXPORT int Width() const;

  Standard_EXPORT void SetHeight(const int aHeight);

  Standard_EXPORT int Height() const;

  Standard_EXPORT void SetNumber(const Vrml_SFImageNumber aNumber);

  Standard_EXPORT Vrml_SFImageNumber Number() const;

  Standard_EXPORT void SetArray(const occ::handle<NCollection_HArray1<int>>& anArray);

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> Array() const;

  Standard_EXPORT bool ArrayFlag() const;

  DEFINE_STANDARD_RTTIEXT(Vrml_SFImage, Standard_Transient)

private:
  int                                   myWidth;
  int                                   myHeight;
  Vrml_SFImageNumber                    myNumber;
  occ::handle<NCollection_HArray1<int>> myArray;
  bool                                  myArrayFlag;
};
