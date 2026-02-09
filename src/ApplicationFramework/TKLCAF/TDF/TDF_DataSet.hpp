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

class TDF_DataSet : public Standard_Transient
{

public:
  Standard_EXPORT TDF_DataSet();

  Standard_EXPORT void Clear();

  bool IsEmpty() const;

  void AddLabel(const TDF_Label& aLabel);

  bool ContainsLabel(const TDF_Label& aLabel) const;

  NCollection_Map<TDF_Label>& Labels();

  void AddAttribute(const occ::handle<TDF_Attribute>& anAttribute);

  bool ContainsAttribute(const occ::handle<TDF_Attribute>& anAttribute) const;

  NCollection_Map<occ::handle<TDF_Attribute>>& Attributes();

  void AddRoot(const TDF_Label& aLabel);

  NCollection_List<TDF_Label>& Roots();

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

inline bool TDF_DataSet::IsEmpty() const
{
  return (myLabelMap.IsEmpty() && myAttributeMap.IsEmpty());
}

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

inline void TDF_DataSet::AddRoot(const TDF_Label& aLabel)
{
  if (ContainsLabel(aLabel))
    myRootLabels.Append(aLabel);
}

inline NCollection_List<TDF_Label>& TDF_DataSet::Roots()
{
  return myRootLabels;
}
