#pragma once

#include <Standard.hpp>

#include <TDocStd_Document.hpp>
#include <NCollection_Sequence.hpp>
#include <TCollection_ExtendedString.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>

class TDocStd_ApplicationDelta : public Standard_Transient
{

public:
  Standard_EXPORT TDocStd_ApplicationDelta();

  NCollection_Sequence<occ::handle<TDocStd_Document>>& GetDocuments();

  const TCollection_ExtendedString& GetName() const;

  void SetName(const TCollection_ExtendedString& theName);

  Standard_EXPORT void Dump(Standard_OStream& anOS) const;

  DEFINE_STANDARD_RTTIEXT(TDocStd_ApplicationDelta, Standard_Transient)

private:
  NCollection_Sequence<occ::handle<TDocStd_Document>> myDocuments;
  TCollection_ExtendedString                          myName;
};

inline NCollection_Sequence<occ::handle<TDocStd_Document>>& TDocStd_ApplicationDelta::GetDocuments()
{
  return myDocuments;
}

//=================================================================================================

inline const TCollection_ExtendedString& TDocStd_ApplicationDelta::GetName() const
{
  return myName;
}

//=================================================================================================

inline void TDocStd_ApplicationDelta::SetName(const TCollection_ExtendedString& theName)
{
  myName = theName;
}
