#pragma once

#include <Standard.hpp>

#include <TDF_Label.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Map.hpp>
#include <Standard_Handle.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_OStream.hpp>
class TDF_Label;
class TDF_Attribute;

//! This class is a set of TDF information like labels and attributes.
class TDF_DataSet : public Standard_Transient
{

public:
  //! Creates an empty DataSet object.
  Standard_EXPORT TDF_DataSet();

  //! Clears all information.
  Standard_EXPORT void Clear();

  //! Returns true if there is at least one label or one
  //! attribute.
  bool IsEmpty() const;

  //! Adds <aLabel> in the current data set.
  void AddLabel(const TDF_Label& aLabel);

  //! Returns true if the label <alabel> is in the data set.
  bool ContainsLabel(const TDF_Label& aLabel) const;

  //! Returns the map of labels in this data set.
  //! This map can be used directly, or updated.
  NCollection_Map<TDF_Label>& Labels();

  //! Adds <anAttribute> into the current data set.
  void AddAttribute(const occ::handle<TDF_Attribute>& anAttribute);

  //! Returns true if <anAttribute> is in the data set.
  bool ContainsAttribute(const occ::handle<TDF_Attribute>& anAttribute) const;

  //! Returns the map of attributes in the current data set.
  //! This map can be used directly, or updated.
  NCollection_Map<occ::handle<TDF_Attribute>>& Attributes();

  //! Adds a root label to <myRootLabels>.
  void AddRoot(const TDF_Label& aLabel);

  //! Returns <myRootLabels> to be used or updated.
  NCollection_List<TDF_Label>& Roots();

  //! Dumps the minimum information about <me> on
  //! <aStream>.
  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const;

  Standard_OStream& operator<<(Standard_OStream& anOS) const { return Dump(anOS); }

  DEFINE_STANDARD_RTTIEXT(TDF_DataSet, Standard_Transient)

private:
  NCollection_List<TDF_Label>                 myRootLabels;
  NCollection_Map<TDF_Label>                  myLabelMap;
  NCollection_Map<occ::handle<TDF_Attribute>> myAttributeMap;
};

#include <TDF_Label.hpp>
#include <TDF_Attribute.hpp>

// IsEmpty
//=========
inline bool TDF_DataSet::IsEmpty() const
{
  return (myLabelMap.IsEmpty() && myAttributeMap.IsEmpty());
}

// Labels
//========
inline void TDF_DataSet::AddLabel(const TDF_Label& aLabel)
{
  if (!aLabel.IsNull())
    myLabelMap.Add(aLabel);
}

inline bool TDF_DataSet::ContainsLabel(const TDF_Label& aLabel) const
{
  return myLabelMap.Contains(aLabel);
}

inline NCollection_Map<TDF_Label>& TDF_DataSet::Labels()
{
  return myLabelMap;
}

// Attributes
//============

inline void TDF_DataSet::AddAttribute(const occ::handle<TDF_Attribute>& anAttribute)
{
  if (!anAttribute.IsNull())
    myAttributeMap.Add(anAttribute);
}

inline bool TDF_DataSet::ContainsAttribute(const occ::handle<TDF_Attribute>& anAttribute) const
{
  return myAttributeMap.Contains(anAttribute);
}

inline NCollection_Map<occ::handle<TDF_Attribute>>& TDF_DataSet::Attributes()
{
  return myAttributeMap;
}

// Root labels
//=============

inline void TDF_DataSet::AddRoot(const TDF_Label& aLabel)
{
  if (ContainsLabel(aLabel))
    myRootLabels.Append(aLabel);
}

inline NCollection_List<TDF_Label>& TDF_DataSet::Roots()
{
  return myRootLabels;
}
