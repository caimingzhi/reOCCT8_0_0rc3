#pragma once

#include <Image_PixMap.hpp>
#include <math_BullardGenerator.hpp>
#include <NCollection_Map.hpp>
#include <StdSelect_TypeOfSelectionImage.hpp>

class SelectMgr_ViewerSelector;

class SelectMgr_SelectionImageFiller : public Standard_Transient
{
public:
  static occ::handle<SelectMgr_SelectionImageFiller> CreateFiller(
    Image_PixMap&                  thePixMap,
    SelectMgr_ViewerSelector*      theSelector,
    StdSelect_TypeOfSelectionImage theType);

public:
  SelectMgr_SelectionImageFiller(Image_PixMap& thePixMap, SelectMgr_ViewerSelector* theSelector)
      : myImage(&thePixMap),
        myMainSel(theSelector)
  {
  }

  virtual void Fill(const int theCol, const int theRow, const int thePicked) = 0;

  virtual void Flush() {}

protected:
  void randomPastelColor(Quantity_Color& theColor)
  {
    for (;;)
    {
      nextRandomPastelColor(theColor);
      if (myUniqueColors.Add(theColor))
      {
        return;
      }
    }
  }

  void nextRandomPastelColor(Quantity_Color& theColor)
  {
    theColor = Quantity_Color(double(myBullardGenerator.NextInt() % 256) / 255.0,
                              double(myBullardGenerator.NextInt() % 256) / 255.0,
                              double(myBullardGenerator.NextInt() % 256) / 255.0,
                              Quantity_TOC_sRGB);
  }

protected:
  Image_PixMap*                   myImage;
  SelectMgr_ViewerSelector*       myMainSel;
  math_BullardGenerator           myBullardGenerator;
  NCollection_Map<Quantity_Color> myUniqueColors;
};
