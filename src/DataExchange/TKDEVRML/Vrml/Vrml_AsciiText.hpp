#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

enum Vrml_AsciiTextJustification
{
  Vrml_LEFT,
  Vrml_CENTER,
  Vrml_RIGHT
};

#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>

class Vrml_AsciiText : public Standard_Transient
{

public:
  Standard_EXPORT Vrml_AsciiText();

  Standard_EXPORT Vrml_AsciiText(
    const occ::handle<NCollection_HArray1<TCollection_AsciiString>>& aString,
    const double                                                     aSpacing,
    const Vrml_AsciiTextJustification                                aJustification,
    const double                                                     aWidth);

  Standard_EXPORT void SetString(
    const occ::handle<NCollection_HArray1<TCollection_AsciiString>>& aString);

  Standard_EXPORT occ::handle<NCollection_HArray1<TCollection_AsciiString>> String() const;

  Standard_EXPORT void SetSpacing(const double aSpacing);

  Standard_EXPORT double Spacing() const;

  Standard_EXPORT void SetJustification(const Vrml_AsciiTextJustification aJustification);

  Standard_EXPORT Vrml_AsciiTextJustification Justification() const;

  Standard_EXPORT void SetWidth(const double aWidth);

  Standard_EXPORT double Width() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

  DEFINE_STANDARD_RTTIEXT(Vrml_AsciiText, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<TCollection_AsciiString>> myString;
  double                                                    mySpacing;
  Vrml_AsciiTextJustification                               myJustification;
  double                                                    myWidth;
};
