

#include <Interface_FileParameter.hpp>
#include <TCollection_AsciiString.hpp>

Interface_FileParameter::Interface_FileParameter()
{
  thetype = Interface_ParamMisc;
  thenum  = 0;
}

void Interface_FileParameter::Init(const TCollection_AsciiString& val,
                                   const Interface_ParamType      typ)
{
  theval = new char[val.Length() + 1];
  strcpy(theval, val.ToCString());
  thetype = typ;
  thenum  = 0;
}

void Interface_FileParameter::Init(const char* val, const Interface_ParamType typ)
{
  theval  = (Standard_PCharacter)val;
  thetype = typ;
  thenum  = 0;
}

const char* Interface_FileParameter::CValue() const
{
  return theval;
}

Interface_ParamType Interface_FileParameter::ParamType() const
{
  return thetype;
}

void Interface_FileParameter::SetEntityNumber(const int num)
{
  thenum = num;
}

int Interface_FileParameter::EntityNumber() const
{
  return thenum;
}

void Interface_FileParameter::Clear()
{
  theval = nullptr;
}

void Interface_FileParameter::Destroy() {}
