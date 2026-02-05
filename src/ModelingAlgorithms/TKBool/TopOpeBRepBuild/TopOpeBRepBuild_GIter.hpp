#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <TopAbs_State.hpp>
#include <Standard_OStream.hpp>
class TopOpeBRepBuild_GTopo;

class TopOpeBRepBuild_GIter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_GIter();

  Standard_EXPORT TopOpeBRepBuild_GIter(const TopOpeBRepBuild_GTopo& G);

  Standard_EXPORT void Init();

  Standard_EXPORT void Init(const TopOpeBRepBuild_GTopo& G);

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT void Current(TopAbs_State& s1, TopAbs_State& s2) const;

  Standard_EXPORT void Dump(Standard_OStream& OS) const;

private:
  Standard_EXPORT void Find();

  int   myII;
  void* mypG;
};
