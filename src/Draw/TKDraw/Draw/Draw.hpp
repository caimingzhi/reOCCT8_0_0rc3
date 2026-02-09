#pragma once

#include <Draw_Interpretor.hpp>
#include <NCollection_Map.hpp>
#include <Quantity_ColorRGBA.hpp>
#include <Standard_Handle.hpp>

class Draw_Drawable3D;
class Draw_ProgressIndicator;

class Draw
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Load(Draw_Interpretor&              theDI,
                                   const TCollection_AsciiString& theKey,
                                   const TCollection_AsciiString& theResourceFileName,
                                   const TCollection_AsciiString& theDefaultsDirectory,
                                   const TCollection_AsciiString& theUserDefaultsDirectory,
                                   const bool                     theIsVerbose = false);

public:
  Standard_EXPORT static void Set(const char*                         Name,
                                  const occ::handle<Draw_Drawable3D>& D,
                                  const bool                          Disp);

  Standard_EXPORT static void Set(const char* Name, const occ::handle<Draw_Drawable3D>& D);

  Standard_EXPORT static void Set(const char* Name, const double val);

  Standard_EXPORT static Draw_Interpretor& GetInterpretor();

  static occ::handle<Draw_Drawable3D> Get(const char*& theName)
  {
    return getDrawable(theName, true);
  }

  static occ::handle<Draw_Drawable3D> GetExisting(const char*& theName)
  {
    const char* aName = theName;
    return getDrawable(aName, false);
  }

  Standard_EXPORT static bool Get(const char* Name, double& val);

  Standard_EXPORT static void Set(const char* Name, const char* val);

  Standard_EXPORT static const NCollection_Map<occ::handle<Draw_Drawable3D>>& Drawables();

public:
  Standard_EXPORT static double Atof(const char* Name);

  Standard_EXPORT static bool ParseReal(const char* theExpressionString,
                                        double&     theParsedRealValue);

  Standard_EXPORT static int Atoi(const char* Name);

  Standard_EXPORT static bool ParseInteger(const char* theExpressionString,
                                           int&        theParsedIntegerValue);

  static int ParseColor(const int                theArgNb,
                        const char* const* const theArgVec,
                        Quantity_ColorRGBA&      theColor)
  {
    return parseColor(theArgNb, theArgVec, theColor, true);
  }

  static int ParseColor(const int                theArgNb,
                        const char* const* const theArgVec,
                        Quantity_Color&          theColor)
  {
    Quantity_ColorRGBA anRgba;
    const int          aNbParsed = parseColor(theArgNb, theArgVec, anRgba, false);
    if (aNbParsed != 0)
    {
      theColor = anRgba.GetRGB();
    }
    return aNbParsed;
  }

  Standard_EXPORT static bool ParseOnOff(const char* theArg, bool& theIsOn);

  Standard_EXPORT static bool ParseOnOffIterator(int          theArgsNb,
                                                 const char** theArgVec,
                                                 int&         theArgIter);

  Standard_EXPORT static bool ParseOnOffNoIterator(int          theArgsNb,
                                                   const char** theArgVec,
                                                   int&         theArgIter);

public:
  Standard_EXPORT static void LastPick(int& view, int& X, int& Y, int& button);

  Standard_EXPORT static void Repaint();

  Standard_EXPORT static void SetProgressBar(
    const occ::handle<Draw_ProgressIndicator>& theProgress);

  Standard_EXPORT static occ::handle<Draw_ProgressIndicator> GetProgressBar();

public:
  Standard_EXPORT static void Commands(Draw_Interpretor& I);

  Standard_EXPORT static void BasicCommands(Draw_Interpretor& I);

  Standard_EXPORT static void MessageCommands(Draw_Interpretor& I);

  Standard_EXPORT static void VariableCommands(Draw_Interpretor& I);

  Standard_EXPORT static void GraphicCommands(Draw_Interpretor& I);

  Standard_EXPORT static void PloadCommands(Draw_Interpretor& I);

  Standard_EXPORT static void UnitCommands(Draw_Interpretor& I);

protected:
  Standard_EXPORT static occ::handle<Draw_Drawable3D> getDrawable(const char*& theName,
                                                                  bool         theToAllowPick);

  Standard_EXPORT static int parseColor(int                 theArgNb,
                                        const char* const*  theArgVec,
                                        Quantity_ColorRGBA& theColor,
                                        bool                theToParseAlpha);
};
