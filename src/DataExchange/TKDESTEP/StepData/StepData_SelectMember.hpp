#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <Interface_ParamType.hpp>
#include <StepData_Logical.hpp>

class StepData_SelectMember : public Standard_Transient
{

public:
  Standard_EXPORT StepData_SelectMember();

  Standard_EXPORT virtual bool HasName() const;

  Standard_EXPORT virtual const char* Name() const;

  Standard_EXPORT virtual bool SetName(const char* name);

  Standard_EXPORT virtual bool Matches(const char* name) const;

  Standard_EXPORT virtual int Kind() const;

  Standard_EXPORT virtual void SetKind(const int kind);

  Standard_EXPORT Interface_ParamType ParamType() const;

  Standard_EXPORT virtual int Int() const;

  Standard_EXPORT virtual void SetInt(const int val);

  Standard_EXPORT int Integer() const;

  Standard_EXPORT void SetInteger(const int val);

  Standard_EXPORT bool Boolean() const;

  Standard_EXPORT void SetBoolean(const bool val);

  Standard_EXPORT StepData_Logical Logical() const;

  Standard_EXPORT void SetLogical(const StepData_Logical val);

  Standard_EXPORT virtual double Real() const;

  Standard_EXPORT virtual void SetReal(const double val);

  Standard_EXPORT virtual const char* String() const;

  Standard_EXPORT virtual void SetString(const char* val);

  Standard_EXPORT int Enum() const;

  Standard_EXPORT virtual const char* EnumText() const;

  Standard_EXPORT void SetEnum(const int val, const char* text = "");

  Standard_EXPORT virtual void SetEnumText(const int val, const char* text);

  DEFINE_STANDARD_RTTIEXT(StepData_SelectMember, Standard_Transient)
};
