#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Wire.hpp>
#include <TopoDS_Face.hpp>

class TopOpeBRepTool_face
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepTool_face();

  Standard_EXPORT bool Init(const TopoDS_Wire& W, const TopoDS_Face& Fref);

  Standard_EXPORT const TopoDS_Wire& W() const;

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool Finite() const;

  Standard_EXPORT const TopoDS_Face& Ffinite() const;

  Standard_EXPORT TopoDS_Face RealF() const;

private:
  TopoDS_Wire myW;
  bool        myfinite;
  TopoDS_Face myFfinite;
};
