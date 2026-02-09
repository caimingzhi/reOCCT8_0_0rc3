#include <Quantity_ColorRGBA.hpp>

#include <NCollection_Vec4.hpp>
#include <Standard_Dump.hpp>

#include <algorithm>

namespace
{

  typedef unsigned int ColorInteger;

  enum HexColorLength
  {
    HexColorLength_ShortRGB  = 3,
    HexColorLength_ShortRGBA = 4,
    HexColorLength_RGB       = 6,
    HexColorLength_RGBA      = 8
  };

  static constexpr ColorInteger HEX_BASE                     = 16;
  static constexpr int          HEX_BITS_PER_COMPONENT       = 8;
  static constexpr int          HEX_BITS_PER_COMPONENT_SHORT = 4;
  static constexpr int          RGB_COMPONENT_LAST_INDEX     = 2;

  static float takeColorComponentFromInteger(ColorInteger&      theColorInteger,
                                             const ColorInteger theColorComponentBase)
  {
    Standard_ASSERT_RETURN(theColorComponentBase >= 2,
                           "'theColorComponentBase' must be greater than 1.",
                           0.0f);
    const ColorInteger aColorComponentMaxValue  = theColorComponentBase - 1;
    const ColorInteger aColorComponentAsInteger = theColorInteger % theColorComponentBase;
    const float        aColorComponent = aColorComponentAsInteger * 1.0f / aColorComponentMaxValue;
    theColorInteger /= theColorComponentBase;
    return aColorComponent;
  }

  static bool convertIntegerToColorRGBA(ColorInteger        theColorInteger,
                                        const ColorInteger  theColorComponentBase,
                                        const bool          hasAlphaComponent,
                                        Quantity_ColorRGBA& theColor)
  {
    Standard_ASSERT_RETURN(theColorComponentBase >= 2,
                           "'theColorComponentBase' must be greater than 1.",
                           0.0f);
    NCollection_Vec4<float> aColor(1.0f);
    if (hasAlphaComponent)
    {
      const float anAlphaComponent =
        takeColorComponentFromInteger(theColorInteger, theColorComponentBase);
      aColor.a() = anAlphaComponent;
    }
    for (int aColorComponentIndex = RGB_COMPONENT_LAST_INDEX; aColorComponentIndex >= 0;
         --aColorComponentIndex)
    {
      const float aColorComponent =
        takeColorComponentFromInteger(theColorInteger, theColorComponentBase);
      aColor[aColorComponentIndex] = Quantity_Color::Convert_sRGB_To_LinearRGB(aColorComponent);
    }
    if (theColorInteger != 0)
    {
      return false;
    }
    theColor = Quantity_ColorRGBA(aColor);
    return true;
  }

  template <typename TheNumber>
  static bool convertStringToInteger(const char* const theString,
                                     TheNumber&        theNumber,
                                     const TheNumber   theBase = 10)
  {
    std::stringstream aConversionStringStream;
    aConversionStringStream << std::setbase(theBase) << theString;
    if (aConversionStringStream.fail())
    {
      return false;
    }
    aConversionStringStream >> theNumber;
    return !aConversionStringStream.fail();
  }

  static bool isHexDigit(const char theCharacter)
  {
    return std::isxdigit(static_cast<unsigned char>(theCharacter)) != 0;
  }

  static bool isHexString(const char* const theString, const std::size_t theLength)
  {
    if (theLength == 0)
    {
      return false;
    }

    return std::count_if(theString, theString + theLength, isHexDigit)
           == static_cast<std::ptrdiff_t>(theLength);
  }

} // namespace

bool Quantity_ColorRGBA::ColorFromHex(const char* const   theHexColorString,
                                      Quantity_ColorRGBA& theColor,
                                      const bool          theAlphaComponentIsOff)
{
  std::size_t aHexColorStringLength = std::strlen(theHexColorString);
  if (aHexColorStringLength == 0)
  {
    return false;
  }

  const bool        hasPrefix       = (theHexColorString[0] == '#');
  const std::size_t aPrefixLength   = hasPrefix ? 1 : 0;
  const char* const aHexColorString = theHexColorString + aPrefixLength;
  aHexColorStringLength -= aPrefixLength;
  if (!isHexString(aHexColorString, aHexColorStringLength))
  {
    return false;
  }

  ColorInteger aHexColorInteger;
  if (!convertStringToInteger(aHexColorString, aHexColorInteger, HEX_BASE))
  {
    return false;
  }

  bool hasAlphaComponent = false;
  bool isShort           = false;
  switch (static_cast<HexColorLength>(aHexColorStringLength))
  {
    case HexColorLength_ShortRGBA:
      hasAlphaComponent = true;
      [[fallthrough]];
    case HexColorLength_ShortRGB:
      isShort = true;
      break;
    case HexColorLength_RGBA:
      hasAlphaComponent = true;
      break;
    case HexColorLength_RGB:
      break;
    default:
      return false;
  }
  if (theAlphaComponentIsOff && hasAlphaComponent)
  {
    return false;
  }

  if (isShort && !hasAlphaComponent && !hasPrefix)
  {
    return false;
  }

  const ColorInteger THE_HEX_COLOR_COMPONENT_BASE       = 1 << HEX_BITS_PER_COMPONENT;
  const ColorInteger THE_HEX_COLOR_COMPONENT_SHORT_BASE = 1 << HEX_BITS_PER_COMPONENT_SHORT;
  const ColorInteger aColorComponentBase =
    isShort ? THE_HEX_COLOR_COMPONENT_SHORT_BASE : THE_HEX_COLOR_COMPONENT_BASE;
  return convertIntegerToColorRGBA(aHexColorInteger,
                                   aColorComponentBase,
                                   hasAlphaComponent,
                                   theColor);
}

void Quantity_ColorRGBA::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_FIELD_VALUES_NUMERICAL(theOStream,
                                   "RGBA",
                                   4,
                                   myRgb.Red(),
                                   myRgb.Green(),
                                   myRgb.Blue(),
                                   myAlpha)
}

bool Quantity_ColorRGBA::InitFromJson(const Standard_SStream& theSStream, int& theStreamPos)
{
  int aPos = theStreamPos;

  double aRed, aGreen, aBlue, anAlpha;
  OCCT_INIT_VECTOR_CLASS(Standard_Dump::Text(theSStream),
                         "RGBA",
                         aPos,
                         4,
                         &aRed,
                         &aGreen,
                         &aBlue,
                         &anAlpha)

  SetValues((float)aRed, (float)aGreen, (float)aBlue, (float)anAlpha);
  return true;
}
