#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopAbs_ShapeEnum.hpp>
#include <Standard_OStream.hpp>
class TopOpeBRepBuild_GTopo;

class TopOpeBRepBuild_GTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static TopOpeBRepBuild_GTopo GFusUnsh(const TopAbs_ShapeEnum s1,
                                                        const TopAbs_ShapeEnum s2);

  Standard_EXPORT static TopOpeBRepBuild_GTopo GFusSame(const TopAbs_ShapeEnum s1,
                                                        const TopAbs_ShapeEnum s2);

  Standard_EXPORT static TopOpeBRepBuild_GTopo GFusDiff(const TopAbs_ShapeEnum s1,
                                                        const TopAbs_ShapeEnum s2);

  Standard_EXPORT static TopOpeBRepBuild_GTopo GCutUnsh(const TopAbs_ShapeEnum s1,
                                                        const TopAbs_ShapeEnum s2);

  Standard_EXPORT static TopOpeBRepBuild_GTopo GCutSame(const TopAbs_ShapeEnum s1,
                                                        const TopAbs_ShapeEnum s2);

  Standard_EXPORT static TopOpeBRepBuild_GTopo GCutDiff(const TopAbs_ShapeEnum s1,
                                                        const TopAbs_ShapeEnum s2);

  Standard_EXPORT static TopOpeBRepBuild_GTopo GComUnsh(const TopAbs_ShapeEnum s1,
                                                        const TopAbs_ShapeEnum s2);

  Standard_EXPORT static TopOpeBRepBuild_GTopo GComSame(const TopAbs_ShapeEnum s1,
                                                        const TopAbs_ShapeEnum s2);

  Standard_EXPORT static TopOpeBRepBuild_GTopo GComDiff(const TopAbs_ShapeEnum s1,
                                                        const TopAbs_ShapeEnum s2);

  Standard_EXPORT static void Dump(Standard_OStream& OS);
};

