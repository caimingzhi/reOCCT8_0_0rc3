#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_ParamType.hpp>
#include <Standard_PCharacter.hpp>
class TCollection_AsciiString;

class Interface_FileParameter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Interface_FileParameter();

  Standard_EXPORT void Init(const TCollection_AsciiString& val, const Interface_ParamType typ);

  Standard_EXPORT void Init(const char* val, const Interface_ParamType typ);

  Standard_EXPORT const char* CValue() const;

  Standard_EXPORT Interface_ParamType ParamType() const;

  Standard_EXPORT void SetEntityNumber(const int num);

  Standard_EXPORT int EntityNumber() const;

  Standard_EXPORT void Clear();

  Standard_EXPORT void Destroy();

  ~Interface_FileParameter() { Destroy(); }

private:
  Interface_ParamType thetype;
  Standard_PCharacter theval;
  int                 thenum;
};
