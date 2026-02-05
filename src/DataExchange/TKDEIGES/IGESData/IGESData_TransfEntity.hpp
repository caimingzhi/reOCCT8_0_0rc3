#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
class gp_GTrsf;

//! defines required type for Transf in directory part
//! an effective Transf entity must inherits it
class IGESData_TransfEntity : public IGESData_IGESEntity
{

public:
  //! gives value of the transformation, as a GTrsf
  //! To be defined by an effective class of Transformation Entity
  //! Warning : Must take in account Composition : if a TransfEntity has in
  //! its Directory Part, a Transf, this means that it is Compound,
  //! Value must return the global result
  Standard_EXPORT virtual gp_GTrsf Value() const = 0;

  DEFINE_STANDARD_RTTIEXT(IGESData_TransfEntity, IGESData_IGESEntity)
};
