#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_PCharacter.hpp>
#include <Standard_Real.hpp>
#include <Standard_IStream.hpp>
#include <Standard_OStream.hpp>

class Interface_MSG
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Interface_MSG(const char* key);

  Standard_EXPORT Interface_MSG(const char* key, const int i1);

  Standard_EXPORT Interface_MSG(const char* key, const int i1, const int i2);

  Standard_EXPORT Interface_MSG(const char* key, const double r1, const int intervals = -1);

  Standard_EXPORT Interface_MSG(const char* key, const char* str);

  Standard_EXPORT Interface_MSG(const char* key, const int ival, const char* str);

  Standard_EXPORT void Destroy();

  ~Interface_MSG() { Destroy(); }

  Standard_EXPORT const char* Value() const;
  operator const char*() const;

  Standard_EXPORT static int Read(Standard_IStream& S);

  Standard_EXPORT static int Read(const char* file);

  Standard_EXPORT static int Write(Standard_OStream& S, const char* rootkey = "");

  Standard_EXPORT static bool IsKey(const char* mess);

  Standard_EXPORT static const char* Translated(const char* key);

  Standard_EXPORT static void Record(const char* key, const char* item);

  Standard_EXPORT static void SetTrace(const bool toprint, const bool torecord);

  Standard_EXPORT static void SetMode(const bool running, const bool raising);

  Standard_EXPORT static void PrintTrace(Standard_OStream& S);

  Standard_EXPORT static double Intervalled(const double val,
                                            const int    order = 3,
                                            const bool   upper = false);

  Standard_EXPORT static void TDate(const char* text,
                                    const int   yy,
                                    const int   mm,
                                    const int   dd,
                                    const int   hh,
                                    const int   mn,
                                    const int   ss,
                                    const char* format = "");

  Standard_EXPORT static bool NDate(const char* text,
                                    int&        yy,
                                    int&        mm,
                                    int&        dd,
                                    int&        hh,
                                    int&        mn,
                                    int&        ss);

  Standard_EXPORT static int CDate(const char* text1, const char* text2);

  Standard_EXPORT static const char* Blanks(const int val, const int max);

  Standard_EXPORT static const char* Blanks(const char* val, const int max);

  Standard_EXPORT static const char* Blanks(const int count);

  Standard_EXPORT static void Print(Standard_OStream& S,
                                    const char*       val,
                                    const int         max,
                                    const int         just = -1);

private:
  const char*         thekey;
  Standard_PCharacter theval;
};
