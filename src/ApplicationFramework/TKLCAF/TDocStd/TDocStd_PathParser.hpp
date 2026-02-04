#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_ExtendedString.hpp>

//! parse an OS path
class TDocStd_PathParser
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TDocStd_PathParser(const TCollection_ExtendedString& path);

  Standard_EXPORT void Parse();

  Standard_EXPORT TCollection_ExtendedString Trek() const;

  Standard_EXPORT TCollection_ExtendedString Name() const;

  Standard_EXPORT TCollection_ExtendedString Extension() const;

  Standard_EXPORT TCollection_ExtendedString Path() const;

  Standard_EXPORT int Length() const;

private:
  TCollection_ExtendedString myPath;
  TCollection_ExtendedString myExtension;
  TCollection_ExtendedString myTrek;
  TCollection_ExtendedString myName;
};

