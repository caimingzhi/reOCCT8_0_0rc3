#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Trsf.hpp>
#include <Standard_OStream.hpp>

class Vrml_MatrixTransform
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_MatrixTransform();

  Standard_EXPORT Vrml_MatrixTransform(const gp_Trsf& aMatrix);

  Standard_EXPORT void SetMatrix(const gp_Trsf& aMatrix);

  Standard_EXPORT gp_Trsf Matrix() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  gp_Trsf myMatrix;
};
