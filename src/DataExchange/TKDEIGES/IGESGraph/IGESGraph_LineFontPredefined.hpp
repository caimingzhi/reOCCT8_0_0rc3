#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>

class IGESGraph_LineFontPredefined : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_LineFontPredefined();

  Standard_EXPORT void Init(const int nbProps, const int aLineFontPatternCode);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT int LineFontPatternCode() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_LineFontPredefined, IGESData_IGESEntity)

private:
  int theNbPropertyValues;
  int theLineFontPatternCode;
};
