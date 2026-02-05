#include <GeomFill_AppSurf.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>
#include <GeomFill_SectionGenerator.hpp>
#include <GeomFill_Line.hpp>

#define TheSectionGenerator GeomFill_SectionGenerator
#define TheSectionGenerator_hxx <GeomFill_SectionGenerator.hpp>
#define Handle_TheLine occ::handle<GeomFill_Line>
#define TheLine GeomFill_Line
#define TheLine_hxx <GeomFill_Line.hpp>
#define AppBlend_AppSurf GeomFill_AppSurf
#define AppBlend_AppSurf_hxx <GeomFill_AppSurf.hpp>
#include <AppBlend_AppSurf.hpp>
