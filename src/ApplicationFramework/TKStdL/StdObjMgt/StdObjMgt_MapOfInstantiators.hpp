#pragma once


#include <StdObjMgt_Persistent.hpp>
#include <NCollection_DataMap.hpp>
#include <TCollection_AsciiString.hpp>

class StdObjMgt_MapOfInstantiators
    : public NCollection_DataMap<TCollection_AsciiString, StdObjMgt_Persistent::Instantiator>
{
public:
  template <class Persistent>
  void Bind(const TCollection_AsciiString& theTypeName)
  {
    NCollection_DataMap<TCollection_AsciiString, StdObjMgt_Persistent::Instantiator>::Bind(
      theTypeName,
      Persistent::template Instantiate<Persistent>);
  }

  DEFINE_STANDARD_ALLOC
};

