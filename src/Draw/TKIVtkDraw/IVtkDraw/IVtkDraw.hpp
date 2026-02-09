#pragma once

#include <Standard_Transient.hpp>
#include <Standard.hpp>
#include <Standard_Macro.hpp>

class Draw_Interpretor;
class WNT_WClass;

class IVtkDraw
{
public:
  DEFINE_STANDARD_ALLOC

  struct IVtkWinParams
  {
    NCollection_Vec2<int> TopLeft;
    NCollection_Vec2<int> Size;
    int                   NbMsaaSample;
    bool                  UseSRGBColorSpace;

    IVtkWinParams()
        : NbMsaaSample(0),
          UseSRGBColorSpace(false)
    {
    }
  };

public:
  Standard_EXPORT static void ViewerInit(const IVtkWinParams& theParams);

  static void ViewerInit(int thePxLeft, int thePxTop, int thePxWidth, int thePxHeight)
  {
    IVtkWinParams aParams;
    aParams.TopLeft.SetValues(thePxLeft, thePxTop);
    aParams.Size.SetValues(thePxWidth, thePxHeight);
    ViewerInit(aParams);
  }

  Standard_EXPORT static void Factory(Draw_Interpretor& theDI);
  Standard_EXPORT static void Commands(Draw_Interpretor& theCommands);

private:
  Standard_EXPORT static const occ::handle<WNT_WClass>& WClass();
};
