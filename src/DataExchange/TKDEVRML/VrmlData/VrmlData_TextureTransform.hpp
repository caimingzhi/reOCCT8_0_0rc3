#pragma once

#include <VrmlData_Node.hpp>
#include <gp_XY.hpp>

class VrmlData_TextureTransform : public VrmlData_Node
{
public:
  inline VrmlData_TextureTransform()
      : myRotation(0.0)
  {
  }

  inline VrmlData_TextureTransform(const VrmlData_Scene& theScene, const char* theName)
      : VrmlData_Node(theScene, theName),
        myRotation(0.)
  {
  }

  inline const gp_XY& Center() const { return myCenter; }

  inline double Rotation() const { return myRotation; }

  inline const gp_XY& Scale() const { return myScale; }

  inline const gp_XY& Translation() const { return myTranslation; }

  inline void SetCenter(const gp_XY& V) { myCenter = V; }

  inline void SetRotation(const double V) { myRotation = V; }

  inline void SetScale(const gp_XY& V) { myScale = V; }

  inline void SetTranslation(const gp_XY& V) { myTranslation = V; }

private:
  gp_XY  myCenter;
  double myRotation;
  gp_XY  myScale;
  gp_XY  myTranslation;

public:
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_TextureTransform, VrmlData_Node)
};
