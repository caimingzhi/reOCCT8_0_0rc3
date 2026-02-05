#pragma once

#include <Standard.hpp>

#include <IGESData_ViewKindEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESData_IGESEntity;

//! Defines IGESViewsVisible, Type <402>, Form <3>
//! in package IGESDraw
//!
//! If an entity is to be displayed in more than one views,
//! this class instance is used, which contains the Visible
//! views and the associated entity Displays.
class IGESDraw_ViewsVisible : public IGESData_ViewKindEntity
{

public:
  Standard_EXPORT IGESDraw_ViewsVisible();

  //! This method is used to set the fields of the class
  //! ViewsVisible
  //! - allViewEntities  : All View kind entities
  //! - allDisplayEntity : All entities whose display is specified
  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>>& allViewEntities,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&     allDisplayEntity);

  //! Changes only the list of Displayed Entities (Null allowed)
  Standard_EXPORT void InitImplied(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allDisplayEntity);

  //! Returns False (for a complex view)
  Standard_EXPORT bool IsSingle() const override;

  //! returns the Number of views visible
  Standard_EXPORT int NbViews() const override;

  //! returns the number of entities displayed in the Views or zero if
  //! no Entities specified in these Views
  Standard_EXPORT int NbDisplayedEntities() const;

  //! returns the Index'th ViewKindEntity Entity
  //! raises exception if Index <= 0 or Index > NbViewsVisible()
  Standard_EXPORT occ::handle<IGESData_ViewKindEntity> ViewItem(const int Index) const override;

  //! returns the Index'th entity whose display is being specified by
  //! this associativity instance
  //! raises exception if Index <= 0 or Index > NbEntityDisplayed()
  Standard_EXPORT occ::handle<IGESData_IGESEntity> DisplayedEntity(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_ViewsVisible, IGESData_ViewKindEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>> theViewEntities;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>     theDisplayEntity;
};
