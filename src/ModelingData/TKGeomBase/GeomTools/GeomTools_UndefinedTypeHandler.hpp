#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>
#include <Standard_IStream.hpp>
#include <Standard_Integer.hpp>
class Geom_Curve;
class Geom2d_Curve;
class Geom_Surface;

class GeomTools_UndefinedTypeHandler : public Standard_Transient
{

public:
  Standard_EXPORT GeomTools_UndefinedTypeHandler();

  Standard_EXPORT virtual void PrintCurve(const occ::handle<Geom_Curve>& C,
                                          Standard_OStream&              OS,
                                          const bool                     compact = false) const;

  Standard_EXPORT virtual Standard_IStream& ReadCurve(const int                ctype,
                                                      Standard_IStream&        IS,
                                                      occ::handle<Geom_Curve>& C) const;

  Standard_EXPORT virtual void PrintCurve2d(const occ::handle<Geom2d_Curve>& C,
                                            Standard_OStream&                OS,
                                            const bool                       compact = false) const;

  Standard_EXPORT virtual Standard_IStream& ReadCurve2d(const int                  ctype,
                                                        Standard_IStream&          IS,
                                                        occ::handle<Geom2d_Curve>& C) const;

  Standard_EXPORT virtual void PrintSurface(const occ::handle<Geom_Surface>& S,
                                            Standard_OStream&                OS,
                                            const bool                       compact = false) const;

  Standard_EXPORT virtual Standard_IStream& ReadSurface(const int                  ctype,
                                                        Standard_IStream&          IS,
                                                        occ::handle<Geom_Surface>& S) const;

  DEFINE_STANDARD_RTTIEXT(GeomTools_UndefinedTypeHandler, Standard_Transient)
};
