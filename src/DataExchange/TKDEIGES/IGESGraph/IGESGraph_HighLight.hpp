#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>

//! defines IGESHighLight, Type <406> Form <20>
//! in package IGESGraph
//!
//! Attaches information that an entity is to be
//! displayed in some system dependent manner
class IGESGraph_HighLight : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_HighLight();

  //! This method is used to set the fields of the class
  //! HighLight
  //! - nbProps          : Number of property values (NP = 1)
  //! - aHighLightStatus : HighLight Flag
  Standard_EXPORT void Init(const int nbProps, const int aHighLightStatus);

  //! returns the number of property values in <me>
  Standard_EXPORT int NbPropertyValues() const;

  //! returns 0 if <me> is not highlighted(default),
  //! 1 if <me> is highlighted
  Standard_EXPORT int HighLightStatus() const;

  //! returns True if entity is highlighted
  Standard_EXPORT bool IsHighLighted() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_HighLight, IGESData_IGESEntity)

private:
  int theNbPropertyValues;
  int theHighLight;
};

