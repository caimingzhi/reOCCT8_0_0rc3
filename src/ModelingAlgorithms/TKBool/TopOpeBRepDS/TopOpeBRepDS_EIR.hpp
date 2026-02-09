#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class TopOpeBRepDS_HDataStructure;

class TopOpeBRepDS_EIR
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_EIR(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

  Standard_EXPORT void ProcessEdgeInterferences();

  Standard_EXPORT void ProcessEdgeInterferences(const int I);

private:
  occ::handle<TopOpeBRepDS_HDataStructure> myHDS;
};
