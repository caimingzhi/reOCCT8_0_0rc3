#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Real.hpp>
class TCollection_HAsciiString;

class MoniTool_Stat
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT MoniTool_Stat(const char* title = "");

  Standard_EXPORT MoniTool_Stat(const MoniTool_Stat& other);

  Standard_EXPORT static MoniTool_Stat& Current();

  Standard_EXPORT int Open(const int nb = 100);

  Standard_EXPORT void OpenMore(const int id, const int nb);

  Standard_EXPORT void Add(const int nb = 1);

  Standard_EXPORT void AddSub(const int nb = 1);

  Standard_EXPORT void AddEnd();

  Standard_EXPORT void Close(const int id);

  Standard_EXPORT int Level() const;

  Standard_EXPORT double Percent(const int fromlev = 0) const;

private:
  occ::handle<TCollection_HAsciiString> thetit;
  int                                   thelev;
  occ::handle<NCollection_HArray1<int>> thetot;
  occ::handle<NCollection_HArray1<int>> thedone;
  occ::handle<NCollection_HArray1<int>> thecurr;
};
