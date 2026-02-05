#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopOpeBRepDS_Config.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <TopOpeBRepDS_Kind.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
class TopOpeBRepDS_Transition;

//! Interference
class TopOpeBRepDS_ShapeShapeInterference : public TopOpeBRepDS_Interference
{

public:
  //! a shape interferes on shape <G> with shape <S>.
  //! examples :
  //! create a ShapeShapeInterference describing :
  //! vertex V of edge E1 found on edge E2 :
  //! ST,S,GT,G = TopOpeBRepDS_EDGE,E2,TopOpeBRepDS_VERTEX,V
  //!
  //! create a ShapeShapeInterference describing
  //! vertex V of edge E found on face F :
  //! ST,S,GT,G = TopOpeBRepDS_FACE,F,TopOpeBRepDS_VERTEX,V
  //!
  //! <GBound> indicates if shape <G> is a bound of shape <S>.
  //!
  //! <SCC> :
  //! UNSH_GEOMETRY :
  //! <S> and <Ancestor> have any types,
  //! <S> and <Ancestor> don't share the same geometry
  //! SAME_ORIENTED :
  //! <S> and <Ancestor> have identical types,
  //! <S> and <Ancestor> orientations are IDENTICAL.
  //! DIFF_ORIENTED :
  //! <S> and <Ancestor> have identical types,
  //! <S> and <Ancestor> orientations are DIFFERENT.
  Standard_EXPORT TopOpeBRepDS_ShapeShapeInterference(const TopOpeBRepDS_Transition& T,
                                                      const TopOpeBRepDS_Kind        ST,
                                                      const int                      S,
                                                      const TopOpeBRepDS_Kind        GT,
                                                      const int                      G,
                                                      const bool                     GBound,
                                                      const TopOpeBRepDS_Config      C);

  Standard_EXPORT TopOpeBRepDS_Config Config() const;

  Standard_EXPORT bool GBound() const;

  Standard_EXPORT void SetGBound(const bool b);

  DEFINE_STANDARD_RTTIEXT(TopOpeBRepDS_ShapeShapeInterference, TopOpeBRepDS_Interference)

private:
  bool                myGBound;
  TopOpeBRepDS_Config myC;
};
