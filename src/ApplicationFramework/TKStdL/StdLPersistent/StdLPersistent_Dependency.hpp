#pragma once

#include <StdObjMgt_Attribute.hpp>
#include <StdLPersistent_HString.hpp>
#include <StdLPersistent_HArray1.hpp>

#include <TDataStd_Relation.hpp>

class StdLPersistent_Dependency
{
  template <class AttribClass>
  class instance : public StdObjMgt_Attribute<AttribClass>
  {
  public:
    inline void Read(StdObjMgt_ReadData& theReadData) { theReadData >> myName >> myVariables; }

    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myName << myVariables;
    }

    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
    {
      theChildren.Append(myName);
      theChildren.Append(myVariables);
    }

    const char* PName() const;

    void Import(const occ::handle<AttribClass>& theAttribute) const;

  private:
    Handle(StdLPersistent_HString::Extended)   myName;
    Handle(StdLPersistent_HArray1::Persistent) myVariables;
  };

public:
  typedef instance<TDataStd_Expression> Expression;
  typedef instance<TDataStd_Relation>   Relation;
};

template <>
inline const char* StdLPersistent_Dependency::instance<TDataStd_Expression>::PName() const
{
  return "PDataStd_Expression";
}

template <>
inline const char* StdLPersistent_Dependency::instance<TDataStd_Relation>::PName() const
{
  return "PDataStd_Relation";
}
