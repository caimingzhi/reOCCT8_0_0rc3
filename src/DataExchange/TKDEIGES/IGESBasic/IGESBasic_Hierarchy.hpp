#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>

class IGESBasic_Hierarchy : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_Hierarchy();

  Standard_EXPORT void Init(const int nbPropVal,
                            const int aLineFont,
                            const int aView,
                            const int anEntityLevel,
                            const int aBlankStatus,
                            const int aLineWt,
                            const int aColorNum);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT int NewLineFont() const;

  Standard_EXPORT int NewView() const;

  Standard_EXPORT int NewEntityLevel() const;

  Standard_EXPORT int NewBlankStatus() const;

  Standard_EXPORT int NewLineWeight() const;

  Standard_EXPORT int NewColorNum() const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_Hierarchy, IGESData_IGESEntity)

private:
  int theNbPropertyValues;
  int theLineFont;
  int theView;
  int theEntityLevel;
  int theBlankStatus;
  int theLineWeight;
  int theColorNum;
};
