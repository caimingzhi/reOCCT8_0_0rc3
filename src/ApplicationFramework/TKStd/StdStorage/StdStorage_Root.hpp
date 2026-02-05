#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
class StdObjMgt_Persistent;

//! Describes a named persistent root
class StdStorage_Root : public Standard_Transient
{
  friend class StdStorage_RootData;

public:
  DEFINE_STANDARD_RTTIEXT(StdStorage_Root, Standard_Transient)

  //! Creates an empty root
  Standard_EXPORT StdStorage_Root();

  //! Creates a root for writing
  Standard_EXPORT StdStorage_Root(const TCollection_AsciiString&           theName,
                                  const occ::handle<StdObjMgt_Persistent>& theObject);

  //! Returns a name of the root
  Standard_EXPORT TCollection_AsciiString Name() const;

  //! Sets a name to the root object
  Standard_EXPORT void SetName(const TCollection_AsciiString& theName);

  //! Returns a root's persistent object
  Standard_EXPORT occ::handle<StdObjMgt_Persistent> Object() const;

  //! Sets a root's persistent object
  Standard_EXPORT void SetObject(const occ::handle<StdObjMgt_Persistent>& anObject);

  //! Returns a root's persistent type
  Standard_EXPORT TCollection_AsciiString Type() const;

  //! Sets a root's persistent type
  Standard_EXPORT void SetType(const TCollection_AsciiString& aType);

  //! Returns root's position in the root data section
  Standard_EXPORT int Reference() const;

private:
  Standard_EXPORT StdStorage_Root(const TCollection_AsciiString& theName,
                                  const int                      theRef,
                                  const TCollection_AsciiString& theType);

  Standard_EXPORT void SetReference(const int aRef);

  TCollection_AsciiString           myName;
  TCollection_AsciiString           myType;
  occ::handle<StdObjMgt_Persistent> myObject;
  int                               myRef;
};
