#include <BRepBlend_AppSurf.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>
#include <Blend_AppFunction.hpp>
#include <BRepBlend_Line.hpp>

#define TheSectionGenerator Blend_AppFunction
#define TheSectionGenerator_hxx <Blend_AppFunction.hpp>
#define Handle_TheLine occ::handle<BRepBlend_Line>
#define TheLine BRepBlend_Line
#define TheLine_hxx <BRepBlend_Line.hpp>
#define AppBlend_AppSurf BRepBlend_AppSurf
#define AppBlend_AppSurf_hxx <BRepBlend_AppSurf.hpp>
#include <AppBlend_AppSurf.hpp>
