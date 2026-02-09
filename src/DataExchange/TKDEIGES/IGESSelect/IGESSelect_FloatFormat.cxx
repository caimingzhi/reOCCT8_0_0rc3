

#include <IFSelect_ContextWrite.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESSelect_FloatFormat.hpp>
#include <Interface_FloatWriter.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_FloatFormat, IGESSelect_FileModifier)

IGESSelect_FloatFormat::IGESSelect_FloatFormat()
    : thezerosup(true),
      themainform("%E"),
      theformrange("%f"),
      therangemin(0.1),
      therangemax(1000.)
{
}

void IGESSelect_FloatFormat::SetDefault(const int digits)
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

void IGESSelect_FloatFormat::SetZeroSuppress(const bool mode)
{
  thezerosup = mode;
}

void IGESSelect_FloatFormat::SetFormat(const char* format)
{
  themainform.Clear();
  themainform.AssignCat(format);
}

void IGESSelect_FloatFormat::SetFormatForRange(const char* form, const double R1, const double R2)
{
  theformrange.Clear();
  theformrange.AssignCat(form);
  therangemin = R1;
  therangemax = R2;
}

void IGESSelect_FloatFormat::Format(bool&                    zerosup,
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

void IGESSelect_FloatFormat::Perform(IFSelect_ContextWrite&, IGESData_IGESWriter& writer) const
{
  writer.FloatWriter().SetFormat(themainform.ToCString());
  writer.FloatWriter().SetZeroSuppress(thezerosup);
  if (theformrange.Length() > 0)
    writer.FloatWriter().SetFormatForRange(theformrange.ToCString(), therangemin, therangemax);
}

TCollection_AsciiString IGESSelect_FloatFormat::Label() const
{
  TCollection_AsciiString lab("Float Format ");
  if (thezerosup)
    lab.AssignCat(" ZeroSup ");
  lab.AssignCat(themainform);
  if (theformrange.Length() > 0)
  {
    char mess[30];

    lab.AssignCat(", in range ");
    int convlen       = Interface_FloatWriter::Convert(therangemin,
                                                 mess,
                                                 true,
                                                 therangemin / 2.,
                                                 therangemax * 2.,
                                                 "%f",
                                                 "%f");
    mess[convlen]     = ' ';
    mess[convlen + 1] = '\0';
    lab.AssignCat(mess);
    convlen           = Interface_FloatWriter::Convert(therangemax,
                                             mess,
                                             true,
                                             therangemin / 2.,
                                             therangemax * 2.,
                                             "%f",
                                             "%f");
    mess[convlen]     = ':';
    mess[convlen + 1] = '\0';
    lab.AssignCat(mess);
    lab.AssignCat(theformrange.ToCString());
  }
  return lab;
}
