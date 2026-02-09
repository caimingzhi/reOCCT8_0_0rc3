#pragma once

#include <Standard.hpp>

#include <NCollection_Vector.hpp>
#include <Interface_FileParameter.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class Interface_FileParameter;

class Interface_ParamList : public Standard_Transient
{

public:
  Standard_EXPORT Interface_ParamList(const int theIncrement = 256);

  int Length() const;

  int Lower() const;

  int Upper() const;

  Standard_EXPORT void SetValue(const int Index, const Interface_FileParameter& Value);

  Standard_EXPORT const Interface_FileParameter& Value(const int Index) const;

  const Interface_FileParameter& operator()(const int Index) const { return Value(Index); }

  Standard_EXPORT Interface_FileParameter& ChangeValue(const int Index);

  Interface_FileParameter& operator()(const int Index) { return ChangeValue(Index); }

  Standard_EXPORT void Clear();

  DEFINE_STANDARD_RTTIEXT(Interface_ParamList, Standard_Transient)

private:
  NCollection_Vector<Interface_FileParameter> myVector;
};

inline int Interface_ParamList::Length() const
{
  return myVector.Length();
}

inline int Interface_ParamList::Lower() const
{
  return 1;
}

inline int Interface_ParamList::Upper() const
{
  return (myVector.Length());
}
