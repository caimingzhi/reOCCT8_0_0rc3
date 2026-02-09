#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>

class Interface_FloatWriter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Interface_FloatWriter(const int chars = 0);

  Standard_EXPORT void SetFormat(const char* form, const bool reset = true);

  Standard_EXPORT void SetFormatForRange(const char* form, const double R1, const double R2);

  Standard_EXPORT void SetZeroSuppress(const bool mode);

  Standard_EXPORT void SetDefaults(const int chars = 0);

  Standard_EXPORT void Options(bool& zerosup, bool& range, double& R1, double& R2) const;

  Standard_EXPORT const char* MainFormat() const;

  Standard_EXPORT const char* FormatForRange() const;

  Standard_EXPORT int Write(const double val, const char* text) const;

  Standard_EXPORT static int Convert(const double val,
                                     const char*  text,
                                     const bool   zerosup,
                                     const double Range1,
                                     const double Range2,
                                     const char*  mainform,
                                     const char*  rangeform);

private:
  char   themainform[12];
  double therange1;
  double therange2;
  char   therangeform[12];
  bool   thezerosup;
};
