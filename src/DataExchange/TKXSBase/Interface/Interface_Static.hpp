#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>

#include <TCollection_HAsciiString.hpp>

typedef bool (*Interface_StaticSatisfies)(const occ::handle<TCollection_HAsciiString>& val);

#include <Interface_TypedValue.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class TCollection_HAsciiString;

class Interface_Static : public Interface_TypedValue
{

public:
  Standard_EXPORT Interface_Static(const char*               family,
                                   const char*               name,
                                   const Interface_ParamType type = Interface_ParamText,
                                   const char*               init = "");

  Standard_EXPORT Interface_Static(const char*                          family,
                                   const char*                          name,
                                   const occ::handle<Interface_Static>& other);

  Standard_EXPORT void PrintStatic(Standard_OStream& S) const;

  Standard_EXPORT const char* Family() const;

  Standard_EXPORT void SetWild(const occ::handle<Interface_Static>& wildcard);

  Standard_EXPORT occ::handle<Interface_Static> Wild() const;

  Standard_EXPORT void SetUptodate();

  Standard_EXPORT bool UpdatedStatus() const;

  Standard_EXPORT static bool Init(const char*               family,
                                   const char*               name,
                                   const Interface_ParamType type,
                                   const char*               init = "");

  Standard_EXPORT static bool Init(const char* family,
                                   const char* name,
                                   const char  type,
                                   const char* init = "");

  Standard_EXPORT static occ::handle<Interface_Static> Static(const char* name);

  Standard_EXPORT static bool IsPresent(const char* name);

  Standard_EXPORT static const char* CDef(const char* name, const char* part);

  Standard_EXPORT static int IDef(const char* name, const char* part);

  Standard_EXPORT static bool IsSet(const char* name, const bool proper = true);

  Standard_EXPORT static const char* CVal(const char* name);

  Standard_EXPORT static int IVal(const char* name);

  Standard_EXPORT static double RVal(const char* name);

  Standard_EXPORT static bool SetCVal(const char* name, const char* val);

  Standard_EXPORT static bool SetIVal(const char* name, const int val);

  Standard_EXPORT static bool SetRVal(const char* name, const double val);

  Standard_EXPORT static bool Update(const char* name);

  Standard_EXPORT static bool IsUpdated(const char* name);

  Standard_EXPORT static occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
    Items(const int mode = 0, const char* criter = "");

  Standard_EXPORT static void Standards();

  Standard_EXPORT static void FillMap(
    NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString>& theMap);

  DEFINE_STANDARD_RTTIEXT(Interface_Static, Interface_TypedValue)

private:
  TCollection_AsciiString                                   thefamily;
  TCollection_AsciiString                                   thename;
  TCollection_AsciiString                                   thelabel;
  Interface_ParamType                                       thetype;
  occ::handle<Standard_Type>                                theotyp;
  occ::handle<Interface_Static>                             thewild;
  int                                                       thelims;
  int                                                       theintlow;
  int                                                       theintup;
  double                                                    therealow;
  double                                                    therealup;
  TCollection_AsciiString                                   theunidef;
  occ::handle<NCollection_HArray1<TCollection_AsciiString>> theenums;
  NCollection_DataMap<TCollection_AsciiString, int>         theeadds;
  Interface_StaticSatisfies                                 thesatisf;
  TCollection_AsciiString                                   thesatisn;
  bool                                                      theupdate;
  int                                                       theival;
  occ::handle<TCollection_HAsciiString>                     thehval;
  occ::handle<Standard_Transient>                           theoval;
};
