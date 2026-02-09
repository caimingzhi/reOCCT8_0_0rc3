

#include <IFSelect_ContextWrite.hpp>
#include <Standard_Type.hpp>
#include <StepData_StepWriter.hpp>
#include <StepSelect_FloatFormat.hpp>
#include <TCollection_AsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(StepSelect_FloatFormat, StepSelect_FileModifier)

StepSelect_FloatFormat::StepSelect_FloatFormat()
    : thezerosup(true),
      themainform("%E"),
      theformrange("%f"),
      therangemin(0.1),
      therangemax(1000.)
{
}

void StepSelect_FloatFormat::SetDefault(const int digits)
{
  themainform.Clear();
  theformrange.Clear();
  if (digits <= 0)
  {
    themainform.AssignCat("%E");
    theformrange.AssignCat("%f");
  }
  else
  {
    char format[20];
    char pourcent = '%';
    char point    = '.';
    Sprintf(format, "%c%d%c%dE", pourcent, digits + 2, point, digits);
    themainform.AssignCat(format);
    Sprintf(format, "%c%d%c%df", pourcent, digits + 2, point, digits);
    theformrange.AssignCat(format);
  }
  therangemin = 0.1;
  therangemax = 1000.;
  thezerosup  = true;
}

void StepSelect_FloatFormat::SetZeroSuppress(const bool mode)
{
  thezerosup = mode;
}

void StepSelect_FloatFormat::SetFormat(const char* format)
{
  themainform.Clear();
  themainform.AssignCat(format);
}

void StepSelect_FloatFormat::SetFormatForRange(const char* form, const double R1, const double R2)
{
  theformrange.Clear();
  theformrange.AssignCat(form);
  therangemin = R1;
  therangemax = R2;
}

void StepSelect_FloatFormat::Format(bool&                    zerosup,
                                    TCollection_AsciiString& mainform,
                                    bool&                    hasrange,
                                    TCollection_AsciiString& formrange,
                                    double&                  rangemin,
                                    double&                  rangemax) const
{
  zerosup   = thezerosup;
  mainform  = themainform;
  hasrange  = (theformrange.Length() > 0);
  formrange = theformrange;
  rangemin  = therangemin;
  rangemax  = therangemax;
}

void StepSelect_FloatFormat::Perform(IFSelect_ContextWrite&, StepData_StepWriter& writer) const
{
  writer.FloatWriter().SetFormat(themainform.ToCString());
  writer.FloatWriter().SetZeroSuppress(thezerosup);
  if (theformrange.Length() > 0)
    writer.FloatWriter().SetFormatForRange(theformrange.ToCString(), therangemin, therangemax);
}

TCollection_AsciiString StepSelect_FloatFormat::Label() const
{
  TCollection_AsciiString lab("Float Format ");
  if (thezerosup)
    lab.AssignCat(" ZeroSuppress");
  lab.AssignCat(themainform);
  if (theformrange.Length() > 0)
  {
    char mess[30];
    Sprintf(mess, ", in range %f %f %s", therangemin, therangemax, theformrange.ToCString());
    lab.AssignCat(mess);
  }
  return lab;
}
