#pragma once


#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>

//! defines required type for ViewKind in directory part
//! that is, Single view or Multiple view
//! An effective ViewKind entity must inherit it and define
//! IsSingle (True for Single, False for List of Views),
//! NbViews and ViewItem (especially for a List)
class IGESData_ViewKindEntity : public IGESData_IGESEntity
{

public:
  //! says if "me" is a Single View (True) or a List of Views (False)
  Standard_EXPORT virtual bool IsSingle() const = 0;

  //! Returns the count of Views for a List of Views. For a Single
  //! View, may return simply 1
  Standard_EXPORT virtual int NbViews() const = 0;

  //! Returns the View n0. <num> for a List of Views. For a Single
  //! Views, may return <me> itself
  Standard_EXPORT virtual occ::handle<IGESData_ViewKindEntity> ViewItem(const int num) const = 0;

  DEFINE_STANDARD_RTTIEXT(IGESData_ViewKindEntity, IGESData_IGESEntity)
};

