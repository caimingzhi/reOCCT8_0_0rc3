#pragma once


#include <Standard_CString.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>
#include <Standard_IStream.hpp>
#include <Standard_OStream.hpp>
#include <Draw_Interpretor.hpp>

class Draw_Display;

class Draw_Drawable3D : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Draw_Drawable3D, Standard_Transient)
public:
  //! Function type for restoring drawable from stream.
  typedef occ::handle<Draw_Drawable3D> (*FactoryFunction_t)(Standard_IStream& theStream);

  //! Register factory for restoring drawable from stream (opposite to Draw_Drawable3D::Save()).
  //! @param[in] theType  class name
  //! @param[in] theFactory  factory function
  Standard_EXPORT static void RegisterFactory(const char*              theType,
                                              const FactoryFunction_t& theFactory);

  //! Restore drawable from stream (opposite to Draw_Drawable3D::Save()).
  //! @param[in] theType  class name
  //! @param[in] theStream  input stream
  //! @return restored drawable or NULL if factory is undefined for specified class
  Standard_EXPORT static occ::handle<Draw_Drawable3D> Restore(const char*       theType,
                                                              Standard_IStream& theStream);

//! @def Draw_Drawable3D_FACTORY
//! Auxiliary macros defining Draw_Drawable3D restoration API to sub-class.
#define Draw_Drawable3D_FACTORY                                                                    \
  static void RegisterFactory() { Draw_Drawable3D::RegisterFactory(get_type_name(), &Restore); }   \
  Standard_EXPORT static occ::handle<Draw_Drawable3D> Restore(Standard_IStream& theStream);

public:
  Standard_EXPORT virtual void DrawOn(Draw_Display& dis) const = 0;

  //! Returns True if the pick is outside the box
  Standard_EXPORT virtual bool PickReject(const double X, const double Y, const double Prec) const;

  //! For variable copy.
  Standard_EXPORT virtual occ::handle<Draw_Drawable3D> Copy() const;

  //! For variable dump.
  Standard_EXPORT virtual void Dump(Standard_OStream& S) const;

  //! Save drawable into stream; default implementation raises Standard_NotImplemented exception.
  Standard_EXPORT virtual void Save(Standard_OStream& theStream) const;

  //! For variable whatis command. Set as a result the type of the variable.
  Standard_EXPORT virtual void Whatis(Draw_Interpretor& I) const;

  //! Is a 3D object. (Default True).
  virtual bool Is3D() const { return true; }

  //! Return TRUE if object can be displayed.
  virtual bool IsDisplayable() const { return true; }

  void SetBounds(const double theXMin,
                 const double theXMax,
                 const double theYMin,
                 const double theYMax)
  {
    myXmin = theXMin;
    myXmax = theXMax;
    myYmin = theYMin;
    myYmax = theYMax;
  }

  void Bounds(double& theXMin, double& theXMax, double& theYMin, double& theYMax) const
  {
    theXMin = myXmin;
    theXMax = myXmax;
    theYMin = myYmin;
    theYMax = myYmax;
  }

  bool Visible() const { return isVisible; }

  void Visible(const bool V) { isVisible = V; }

  bool Protected() const { return isProtected; }

  void Protected(const bool P) { isProtected = P; }

  const char* Name() const { return myName; }

  virtual void Name(const char* N) { myName = N; }

protected:
  Standard_EXPORT Draw_Drawable3D();

private:
  double      myXmin;
  double      myXmax;
  double      myYmin;
  double      myYmax;
  const char* myName;
  bool        isVisible;
  bool        isProtected;
};

