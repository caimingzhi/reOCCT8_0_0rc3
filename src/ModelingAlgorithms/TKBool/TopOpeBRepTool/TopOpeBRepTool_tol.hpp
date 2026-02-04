#pragma once


#include <Bnd_Box.hpp>
#include <BRepAdaptor_Surface.hpp>

Standard_EXPORT void FTOL_FaceTolerances(const Bnd_Box&             B1,
                                         const Bnd_Box&             B2,
                                         const TopoDS_Face&         myFace1,
                                         const TopoDS_Face&         myFace2,
                                         const BRepAdaptor_Surface& mySurface1,
                                         const BRepAdaptor_Surface& mySurface2,
                                         double&                    myTol1,
                                         double&                    myTol2,
                                         double&                    Deflection,
                                         double&                    MaxUV);

Standard_EXPORT void FTOL_FaceTolerances3d(const TopoDS_Face& myFace1,
                                           const TopoDS_Face& myFace2,
                                           double&            Tol);

Standard_EXPORT void FTOL_FaceTolerances3d(const Bnd_Box&             B1,
                                           const Bnd_Box&             B2,
                                           const TopoDS_Face&         myFace1,
                                           const TopoDS_Face&         myFace2,
                                           const BRepAdaptor_Surface& mySurface1,
                                           const BRepAdaptor_Surface& mySurface2,
                                           double&                    myTol1,
                                           double&                    myTol2,
                                           double&                    Deflection,
                                           double&                    MaxUV);

Standard_EXPORT void FTOL_FaceTolerances2d(const Bnd_Box&             B1,
                                           const Bnd_Box&             B2,
                                           const TopoDS_Face&         myFace1,
                                           const TopoDS_Face&         myFace2,
                                           const BRepAdaptor_Surface& mySurface1,
                                           const BRepAdaptor_Surface& mySurface2,
                                           double&                    myTol1,
                                           double&                    myTol2);

