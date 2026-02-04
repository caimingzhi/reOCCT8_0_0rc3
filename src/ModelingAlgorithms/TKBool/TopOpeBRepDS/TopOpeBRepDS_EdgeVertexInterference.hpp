#pragma once


#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <TopOpeBRepDS_ShapeShapeInterference.hpp>
#include <TopOpeBRepDS_Kind.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <TopOpeBRepDS_Config.hpp>
#include <Standard_OStream.hpp>
class TopOpeBRepDS_Transition;

//! An interference with a parameter (ShapeShapeInterference).
class TopOpeBRepDS_EdgeVertexInterference : public TopOpeBRepDS_ShapeShapeInterference
{

public:
  //! Create an interference of VERTEX <G> on a crossed EDGE E.
  //!
  //! if support type <ST> == EDGE : <S> is edge E
  //! FACE : <S> is the face with bound E.
  //! <T> is the transition along the edge, crossing the crossed edge.
  //! E is the crossed edge.
  //! <GIsBound> indicates if <G> is a bound of the edge.
  //! <P> is the parameter of <G> on the edge.
  //!
  //! interference is stored in the list of interfs of the edge.
  Standard_EXPORT TopOpeBRepDS_EdgeVertexInterference(const TopOpeBRepDS_Transition& T,
                                                      const TopOpeBRepDS_Kind        ST,
                                                      const int                      S,
                                                      const int                      G,
                                                      const bool                     GIsBound,
                                                      const TopOpeBRepDS_Config      C,
                                                      const double                   P);

  //! Create an interference of VERTEX <G> on crossed EDGE <S>.
  //!
  //! <T> is the transition along the edge, crossing the crossed edge.
  //! <S> is the crossed edge.
  //! <GIsBound> indicates if <G> is a bound of the edge.
  //! <C> indicates the geometric configuration between
  //! the edge and the crossed edge.
  //! <P> is the parameter of <G> on the edge.
  //!
  //! interference is stored in the list of interfs of the edge.
  Standard_EXPORT TopOpeBRepDS_EdgeVertexInterference(const TopOpeBRepDS_Transition& T,
                                                      const int                      S,
                                                      const int                      G,
                                                      const bool                     GIsBound,
                                                      const TopOpeBRepDS_Config      C,
                                                      const double                   P);

  Standard_EXPORT double Parameter() const;

  Standard_EXPORT void Parameter(const double P);

  DEFINE_STANDARD_RTTIEXT(TopOpeBRepDS_EdgeVertexInterference, TopOpeBRepDS_ShapeShapeInterference)

private:
  double myParam;
};

