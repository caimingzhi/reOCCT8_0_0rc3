#pragma once

#include <Standard.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_LineFontEntity.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
class TCollection_HAsciiString;

class IGESGraph_LineFontDefPattern : public IGESData_LineFontEntity
{

public:
  Standard_EXPORT IGESGraph_LineFontDefPattern();

  Standard_EXPORT void Init(const occ::handle<NCollection_HArray1<double>>& allSegLength,
                            const occ::handle<TCollection_HAsciiString>&    aPattern);

  Standard_EXPORT int NbSegments() const;

  Standard_EXPORT double Length(const int Index) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> DisplayPattern() const;

  Standard_EXPORT bool IsVisible(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_LineFontDefPattern, IGESData_LineFontEntity)

private:
  occ::handle<NCollection_HArray1<double>> theSegmentLengths;
  occ::handle<TCollection_HAsciiString>    theDisplayPattern;
};
