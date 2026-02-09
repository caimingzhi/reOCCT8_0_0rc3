#pragma once

#include <Standard.hpp>

#include <IFSelect_SelectFlag.hpp>

class IFSelect_SelectIncorrectEntities : public IFSelect_SelectFlag
{

public:
  Standard_EXPORT IFSelect_SelectIncorrectEntities();

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectIncorrectEntities, IFSelect_SelectFlag)
};
