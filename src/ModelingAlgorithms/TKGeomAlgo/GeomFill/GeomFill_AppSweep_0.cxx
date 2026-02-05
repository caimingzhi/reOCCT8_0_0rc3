#include <GeomFill_AppSweep.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>
#include <GeomFill_SweepSectionGenerator.hpp>
#include <GeomFill_Line.hpp>

#define TheSectionGenerator GeomFill_SweepSectionGenerator
#define TheSectionGenerator_hxx <GeomFill_SweepSectionGenerator.hpp>
#define Handle_TheLine occ::handle<GeomFill_Line>
#define TheLine GeomFill_Line
#define TheLine_hxx <GeomFill_Line.hpp>
#define AppBlend_AppSurf GeomFill_AppSweep
#define AppBlend_AppSurf_hxx <GeomFill_AppSweep.hpp>
#include <AppBlend_AppSurf.hpp>
