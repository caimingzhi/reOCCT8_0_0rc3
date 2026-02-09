

#include <Standard_Type.hpp>
#include <Vrml_SFImage.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Vrml_SFImage, Standard_Transient)

Vrml_SFImage::Vrml_SFImage()
{
  myArray     = new NCollection_HArray1<int>(1, 1);
  myArrayFlag = false;
}

Vrml_SFImage::Vrml_SFImage(const int                                    aWidth,
                           const int                                    aHeight,
                           const Vrml_SFImageNumber                     aNumber,
                           const occ::handle<NCollection_HArray1<int>>& anArray)
{
  int size = aWidth * aHeight;
  if (anArray->Length() != size)
  {
    throw Standard_Failure("The size of Array is no equal (aWidth*aHeight)");
  }
  myWidth     = aWidth;
  myHeight    = aHeight;
  myNumber    = aNumber;
  myArray     = anArray;
  myArrayFlag = true;
}

void Vrml_SFImage::SetWidth(const int aWidth)
{
  myWidth = aWidth;
}

int Vrml_SFImage::Width() const
{
  return myWidth;
}

void Vrml_SFImage::SetHeight(const int aHeight)
{
  myHeight = aHeight;
}

int Vrml_SFImage::Height() const
{
  return myHeight;
}

void Vrml_SFImage::SetNumber(const Vrml_SFImageNumber aNumber)
{
  myNumber = aNumber;
}

Vrml_SFImageNumber Vrml_SFImage::Number() const
{
  return myNumber;
}

void Vrml_SFImage::SetArray(const occ::handle<NCollection_HArray1<int>>& anArray)
{
  int size = myWidth * myHeight;
  if (anArray->Length() != size)
  {
    throw Standard_Failure("The size of Array is no equal (aWidth*aHeight)");
  }
  myArray     = anArray;
  myArrayFlag = true;
}

bool Vrml_SFImage::ArrayFlag() const
{
  return myArrayFlag;
}

occ::handle<NCollection_HArray1<int>> Vrml_SFImage::Array() const
{
  return myArray;
}
