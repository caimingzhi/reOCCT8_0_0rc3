#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Ax2.hpp>
#include <HelixGeom_BuilderHelixGen.hpp>
class gp_Ax2;

//! Upper level class for geometrical algorithm of building
//! helix curves using arbitrary axis
class HelixGeom_BuilderHelix : public HelixGeom_BuilderHelixGen
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT HelixGeom_BuilderHelix();
  Standard_EXPORT ~HelixGeom_BuilderHelix() override;

  //! Sets coordinate axes for helix
  Standard_EXPORT void SetPosition(const gp_Ax2& aAx2);

  //! Gets coordinate axes for helix
  Standard_EXPORT const gp_Ax2& Position() const;

  //! Performs calculations
  Standard_EXPORT void Perform() override;

protected:
  gp_Ax2 myPosition;
};

