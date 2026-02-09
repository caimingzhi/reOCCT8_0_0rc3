#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <IGESData_IGESEntity.hpp>

class IGESAppli_LineWidening : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_LineWidening();

  Standard_EXPORT void Init(const int    nbPropVal,
                            const double aWidth,
                            const int    aCornering,
                            const int    aExtnFlag,
                            const int    aJustifFlag,
                            const double aExtnVal);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT double WidthOfMetalization() const;

  Standard_EXPORT int CorneringCode() const;

  Standard_EXPORT int ExtensionFlag() const;

  Standard_EXPORT int JustificationFlag() const;

  Standard_EXPORT double ExtensionValue() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_LineWidening, IGESData_IGESEntity)

private:
  int    theNbPropertyValues;
  double theWidth;
  int    theCorneringCode;
  int    theExtensionFlag;
  int    theJustificationFlag;
  double theExtensionValue;
};
