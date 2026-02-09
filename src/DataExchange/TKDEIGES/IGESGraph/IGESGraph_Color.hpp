#pragma once

#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <IGESData_ColorEntity.hpp>
class TCollection_HAsciiString;

class IGESGraph_Color : public IGESData_ColorEntity
{

public:
  Standard_EXPORT IGESGraph_Color();

  Standard_EXPORT void Init(const double                                 red,
                            const double                                 green,
                            const double                                 blue,
                            const occ::handle<TCollection_HAsciiString>& aColorName);

  Standard_EXPORT void RGBIntensity(double& Red, double& Green, double& Blue) const;

  Standard_EXPORT void CMYIntensity(double& Cyan, double& Magenta, double& Yellow) const;

  Standard_EXPORT void HLSPercentage(double& Hue, double& Lightness, double& Saturation) const;

  Standard_EXPORT bool HasColorName() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ColorName() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_Color, IGESData_ColorEntity)

private:
  double                                theRed;
  double                                theGreen;
  double                                theBlue;
  occ::handle<TCollection_HAsciiString> theColorName;
};
