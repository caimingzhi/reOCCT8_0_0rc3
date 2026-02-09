#pragma once

#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
#include <TopOpeBRepDS_Kind.hpp>
#include <TopOpeBRepBuild_Loop.hpp>

class TopOpeBRepBuild_Pave : public TopOpeBRepBuild_Loop
{

public:
  Standard_EXPORT TopOpeBRepBuild_Pave(const TopoDS_Shape& V, const double P, const bool bound);

  Standard_EXPORT void HasSameDomain(const bool b);

  Standard_EXPORT void SameDomain(const TopoDS_Shape& VSD);

  Standard_EXPORT bool HasSameDomain() const;

  Standard_EXPORT const TopoDS_Shape& SameDomain() const;

  Standard_EXPORT const TopoDS_Shape& Vertex() const;

  Standard_EXPORT TopoDS_Shape& ChangeVertex();

  Standard_EXPORT double Parameter() const;

  Standard_EXPORT void Parameter(const double Par);

  Standard_EXPORT TopOpeBRepDS_Kind& InterferenceType();

  Standard_EXPORT bool IsShape() const override;

  Standard_EXPORT const TopoDS_Shape& Shape() const override;

  Standard_EXPORT void Dump() const override;

  DEFINE_STANDARD_RTTIEXT(TopOpeBRepBuild_Pave, TopOpeBRepBuild_Loop)

private:
  TopoDS_Shape      myVertex;
  double            myParam;
  bool              myIsShape;
  bool              myHasSameDomain;
  TopoDS_Shape      mySameDomain;
  TopOpeBRepDS_Kind myIntType;
};
