#include <IGESGraph_LineFontDefPattern.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGraph_LineFontDefPattern, IGESData_LineFontEntity)

IGESGraph_LineFontDefPattern::IGESGraph_LineFontDefPattern() = default;

void IGESGraph_LineFontDefPattern::Init(
  const occ::handle<NCollection_HArray1<double>>& allSegLength,
  const occ::handle<TCollection_HAsciiString>&    aPattern)
{
  if (allSegLength->Lower() != 1)
    throw Standard_DimensionMismatch("IGESGraph_LineFontDefPattern : Init");
  theSegmentLengths = allSegLength;
  theDisplayPattern = aPattern;
  InitTypeAndForm(304, 2);
}

int IGESGraph_LineFontDefPattern::NbSegments() const
{
  return theSegmentLengths->Length();
}

double IGESGraph_LineFontDefPattern::Length(const int Index) const
{
  return theSegmentLengths->Value(Index);
}

occ::handle<TCollection_HAsciiString> IGESGraph_LineFontDefPattern::DisplayPattern() const
{
  return theDisplayPattern;
}

bool IGESGraph_LineFontDefPattern::IsVisible(const int Index) const
{
  int nbSegs = theSegmentLengths->Length();
  if (Index <= 0 || Index > nbSegs)
    return false;

  char tempStr[2];
  int  length = theDisplayPattern->Length();
  tempStr[0]  = theDisplayPattern->Value(length - ((nbSegs - Index) / 4));
  tempStr[1]  = 0;
  int tempVal = (int)strtol(tempStr, (char**)nullptr, 16);

  int mask = 0x01;
  mask <<= ((nbSegs - Index) % 4);
  return ((tempVal & mask) != 0);
}
