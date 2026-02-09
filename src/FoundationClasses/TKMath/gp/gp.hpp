#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Real.hpp>

class gp_Pnt;
class gp_Dir;
class gp_Ax1;
class gp_Ax2;
class gp_Pnt2d;
class gp_Dir2d;
class gp_Ax2d;

class gp
{
private:
  gp()                     = delete;
  gp(const gp&)            = delete;
  gp& operator=(const gp&) = delete;

public:
  static constexpr double Resolution() { return RealSmall(); }

  Standard_EXPORT static const gp_Pnt& Origin() noexcept;

  Standard_EXPORT static const gp_Dir& DX() noexcept;

  Standard_EXPORT static const gp_Dir& DY() noexcept;

  Standard_EXPORT static const gp_Dir& DZ() noexcept;

  Standard_EXPORT static const gp_Ax1& OX() noexcept;

  Standard_EXPORT static const gp_Ax1& OY() noexcept;

  Standard_EXPORT static const gp_Ax1& OZ() noexcept;

  Standard_EXPORT static const gp_Ax2& XOY() noexcept;

  Standard_EXPORT static const gp_Ax2& ZOX() noexcept;

  Standard_EXPORT static const gp_Ax2& YOZ() noexcept;

  Standard_EXPORT static const gp_Pnt2d& Origin2d() noexcept;

  Standard_EXPORT static const gp_Dir2d& DX2d() noexcept;

  Standard_EXPORT static const gp_Dir2d& DY2d() noexcept;

  Standard_EXPORT static const gp_Ax2d& OX2d() noexcept;

  Standard_EXPORT static const gp_Ax2d& OY2d() noexcept;
};
