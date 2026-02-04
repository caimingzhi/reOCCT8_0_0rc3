#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Pnt.hpp>
#include <TDF_Attribute.hpp>
class TDF_Label;
class Standard_GUID;
class TDF_RelocationTable;

//! Position of a Label
class TDataXtd_Position : public TDF_Attribute
{

public:
  //! Create if not found the TDataXtd_Position attribute set its position to <aPos>
  Standard_EXPORT static void Set(const TDF_Label& aLabel, const gp_Pnt& aPos);

  //! Find an existing, or create an empty, Position.
  //! the Position attribute is returned.
  Standard_EXPORT static occ::handle<TDataXtd_Position> Set(const TDF_Label& aLabel);

  //! Search label <aLabel) for the TDataXtd_Position attribute and get its position
  //! if found returns True
  Standard_EXPORT static bool Get(const TDF_Label& aLabel, gp_Pnt& aPos);

  Standard_EXPORT TDataXtd_Position();

  //! Returns the ID of the attribute.
  Standard_EXPORT const Standard_GUID& ID() const override;

  //! Returns the ID of the attribute.
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Restores the contents from <anAttribute> into this
  //! one. It is used when aborting a transaction.
  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& anAttribute) override;

  //! Returns an new empty attribute from the good end
  //! type. It is used by the copy algorithm.
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  //! This method is different from the "Copy" one,
  //! because it is used when copying an attribute from
  //! a source structure into a target structure. This
  //! method pastes the current attribute to the label
  //! corresponding to the insertor. The pasted
  //! attribute may be a brand new one or a new version
  //! of the previous one.
  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&       intoAttribute,
    const occ::handle<TDF_RelocationTable>& aRelocTationable) const override;

  Standard_EXPORT const gp_Pnt& GetPosition() const;

  Standard_EXPORT void SetPosition(const gp_Pnt& aPos);

  DEFINE_STANDARD_RTTIEXT(TDataXtd_Position, TDF_Attribute)

private:
  gp_Pnt myPosition;
};

