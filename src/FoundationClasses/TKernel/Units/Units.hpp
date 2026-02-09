#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_CString.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
class Units_UnitsDictionary;
class Units_Quantity;
class Units_Lexicon;
class Units_Dimensions;

class Units
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void UnitsFile(const char* afile);

  Standard_EXPORT static void LexiconFile(const char* afile);

  Standard_EXPORT static occ::handle<Units_UnitsDictionary> DictionaryOfUnits(
    const bool amode = false);

  Standard_EXPORT static occ::handle<Units_Quantity> Quantity(const char* aquantity);

  Standard_EXPORT static const char* FirstQuantity(const char* aunit);

  Standard_EXPORT static occ::handle<Units_Lexicon> LexiconUnits(const bool amode = true);

  Standard_EXPORT static occ::handle<Units_Lexicon> LexiconFormula();

  Standard_EXPORT static occ::handle<Units_Dimensions> NullDimensions();

  Standard_EXPORT static double Convert(const double avalue,
                                        const char*  afirstunit,
                                        const char*  asecondunit);

  Standard_EXPORT static double ToSI(const double aData, const char* aUnit);

  Standard_EXPORT static double ToSI(const double                   aData,
                                     const char*                    aUnit,
                                     occ::handle<Units_Dimensions>& aDim);

  Standard_EXPORT static double FromSI(const double aData, const char* aUnit);

  Standard_EXPORT static double FromSI(const double                   aData,
                                       const char*                    aUnit,
                                       occ::handle<Units_Dimensions>& aDim);

  Standard_EXPORT static occ::handle<Units_Dimensions> Dimensions(const char* aType);
};
