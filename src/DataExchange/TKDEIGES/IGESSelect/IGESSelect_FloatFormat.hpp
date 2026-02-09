#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <IGESSelect_FileModifier.hpp>
#include <Standard_Integer.hpp>
class IFSelect_ContextWrite;
class IGESData_IGESWriter;

class IGESSelect_FloatFormat : public IGESSelect_FileModifier
{

public:
  Standard_EXPORT IGESSelect_FloatFormat();

  Standard_EXPORT void SetDefault(const int digits = 0);

  Standard_EXPORT void SetZeroSuppress(const bool mode);

  Standard_EXPORT void SetFormat(const char* format = "%E");

  Standard_EXPORT void SetFormatForRange(const char*  format = "%f",
                                         const double Rmin   = 0.1,
                                         const double Rmax   = 1000.0);

  Standard_EXPORT void Format(bool&                    zerosup,
                              TCollection_AsciiString& mainform,
                              bool&                    hasrange,
                              TCollection_AsciiString& forminrange,
                              double&                  rangemin,
                              double&                  rangemax) const;

  Standard_EXPORT void Perform(IFSelect_ContextWrite& ctx,
                               IGESData_IGESWriter&   writer) const override;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_FloatFormat, IGESSelect_FileModifier)

private:
  bool                    thezerosup;
  TCollection_AsciiString themainform;
  TCollection_AsciiString theformrange;
  double                  therangemin;
  double                  therangemax;
};
