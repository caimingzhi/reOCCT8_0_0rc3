#pragma once


#include <VrmlData_Node.hpp>
#include <gp_XY.hpp>

///  Implementation of the TextureTransform node

class VrmlData_TextureTransform : public VrmlData_Node
{
public:
  // ---------- PUBLIC METHODS ----------

  /**
   * Empty constructor
   */
  inline VrmlData_TextureTransform()
      : myRotation(0.0)
  {
  }

  /**
   * Constructor
   */
  inline VrmlData_TextureTransform(const VrmlData_Scene& theScene, const char* theName)
      : VrmlData_Node(theScene, theName),
        myRotation(0.)
  {
  }

  /**
   * Query the Center
   */
  inline const gp_XY& Center() const { return myCenter; }

  /**
   * Query the Rotation
   */
  inline double Rotation() const { return myRotation; }

  /**
   * Query the Scale
   */
  inline const gp_XY& Scale() const { return myScale; }

  /**
   * Query the Translation
   */
  inline const gp_XY& Translation() const { return myTranslation; }

  /**
   * Set the Center
   */
  inline void SetCenter(const gp_XY& V) { myCenter = V; }

  /**
   * Set the Rotation
   */
  inline void SetRotation(const double V) { myRotation = V; }

  /**
   * Set the Scale
   */
  inline void SetScale(const gp_XY& V) { myScale = V; }

  /**
   * Set the Translation
   */
  inline void SetTranslation(const gp_XY& V) { myTranslation = V; }

private:
  // ---------- PRIVATE FIELDS ----------

  gp_XY  myCenter;
  double myRotation;
  gp_XY  myScale;
  gp_XY  myTranslation;

public:
  // Declaration of CASCADE RTTI
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_TextureTransform, VrmlData_Node)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp
