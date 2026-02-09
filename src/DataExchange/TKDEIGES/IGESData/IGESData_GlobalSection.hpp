#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
class TCollection_HAsciiString;
class Interface_ParamSet;
class Interface_Check;
class gp_XYZ;

class IGESData_GlobalSection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESData_GlobalSection();

  Standard_EXPORT void Init(const occ::handle<Interface_ParamSet>& params,
                            occ::handle<Interface_Check>&          ach);

  Standard_EXPORT void CopyRefs();

  Standard_EXPORT occ::handle<Interface_ParamSet> Params() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> TranslatedFromHollerith(
    const occ::handle<TCollection_HAsciiString>& astr) const;

  Standard_EXPORT char Separator() const;

  Standard_EXPORT char EndMark() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> SendName() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> FileName() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> SystemId() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> InterfaceVersion() const;

  Standard_EXPORT int IntegerBits() const;

  Standard_EXPORT int MaxPower10Single() const;

  Standard_EXPORT int MaxDigitsSingle() const;

  Standard_EXPORT int MaxPower10Double() const;

  Standard_EXPORT int MaxDigitsDouble() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ReceiveName() const;

  Standard_EXPORT double Scale() const;

  Standard_EXPORT double CascadeUnit() const;

  Standard_EXPORT int UnitFlag() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> UnitName() const;

  Standard_EXPORT int LineWeightGrad() const;

  Standard_EXPORT double MaxLineWeight() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Date() const;

  Standard_EXPORT double Resolution() const;

  Standard_EXPORT double MaxCoord() const;

  Standard_EXPORT bool HasMaxCoord() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> AuthorName() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> CompanyName() const;

  Standard_EXPORT int IGESVersion() const;

  Standard_EXPORT int DraftingStandard() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> LastChangeDate() const;

  Standard_EXPORT bool HasLastChangeDate() const;

  Standard_EXPORT void SetLastChangeDate();

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ApplicationProtocol() const;

  Standard_EXPORT bool HasApplicationProtocol() const;

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> NewDateString(const int year,
                                                                             const int month,
                                                                             const int day,
                                                                             const int hour,
                                                                             const int minut,
                                                                             const int second,
                                                                             const int mode = -1);

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> NewDateString(
    const occ::handle<TCollection_HAsciiString>& date,
    const int                                    mode = 1);

  Standard_EXPORT double UnitValue() const;

  Standard_EXPORT void SetSeparator(const char val);

  Standard_EXPORT void SetEndMark(const char val);

  Standard_EXPORT void SetSendName(const occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT void SetFileName(const occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT void SetSystemId(const occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT void SetInterfaceVersion(const occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT void SetIntegerBits(const int val);

  Standard_EXPORT void SetMaxPower10Single(const int val);

  Standard_EXPORT void SetMaxDigitsSingle(const int val);

  Standard_EXPORT void SetMaxPower10Double(const int val);

  Standard_EXPORT void SetMaxDigitsDouble(const int val);

  Standard_EXPORT void SetReceiveName(const occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT void SetCascadeUnit(const double theUnit);

  Standard_EXPORT void SetScale(const double val);

  Standard_EXPORT void SetUnitFlag(const int val);

  Standard_EXPORT void SetUnitName(const occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT void SetLineWeightGrad(const int val);

  Standard_EXPORT void SetMaxLineWeight(const double val);

  Standard_EXPORT void SetDate(const occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT void SetResolution(const double val);

  Standard_EXPORT void SetMaxCoord(const double val = 0.0);

  Standard_EXPORT void MaxMaxCoord(const double val = 0.0);

  Standard_EXPORT void MaxMaxCoords(const gp_XYZ& xyz);

  Standard_EXPORT void SetAuthorName(const occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT void SetCompanyName(const occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT void SetIGESVersion(const int val);

  Standard_EXPORT void SetDraftingStandard(const int val);

  Standard_EXPORT void SetLastChangeDate(const occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT void SetApplicationProtocol(const occ::handle<TCollection_HAsciiString>& val);

private:
  char                                  theSeparator;
  char                                  theEndMark;
  occ::handle<TCollection_HAsciiString> theSendName;
  occ::handle<TCollection_HAsciiString> theFileName;
  occ::handle<TCollection_HAsciiString> theSystemId;
  occ::handle<TCollection_HAsciiString> theInterfaceVersion;
  int                                   theIntegerBits;
  int                                   theMaxPower10Single;
  int                                   theMaxDigitsSingle;
  int                                   theMaxPower10Double;
  int                                   theMaxDigitsDouble;
  occ::handle<TCollection_HAsciiString> theReceiveName;
  double                                theScale;
  double                                theCascadeUnit;
  int                                   theUnitFlag;
  occ::handle<TCollection_HAsciiString> theUnitName;
  int                                   theLineWeightGrad;
  double                                theMaxLineWeight;
  occ::handle<TCollection_HAsciiString> theDate;
  double                                theResolution;
  double                                theMaxCoord;
  bool                                  hasMaxCoord;
  occ::handle<TCollection_HAsciiString> theAuthorName;
  occ::handle<TCollection_HAsciiString> theCompanyName;
  int                                   theIGESVersion;
  int                                   theDraftingStandard;
  occ::handle<TCollection_HAsciiString> theLastChangeDate;
  occ::handle<TCollection_HAsciiString> theAppliProtocol;
};
