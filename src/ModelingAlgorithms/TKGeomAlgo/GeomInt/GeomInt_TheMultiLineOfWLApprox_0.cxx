#include <GeomInt_TheMultiLineOfWLApprox.hpp>

#include <IntPatch_WLine.hpp>
#include <ApproxInt_SvSurfaces.hpp>

#define Handle_TheLine occ::handle<IntPatch_WLine>
#define TheLine IntPatch_WLine
#define TheLine_hxx <IntPatch_WLine.hpp>
#define TheSvSurfaces ApproxInt_SvSurfaces
#define TheSvSurfaces_hxx <ApproxInt_SvSurfaces.hpp>
#define ApproxInt_MultiLine GeomInt_TheMultiLineOfWLApprox
#define ApproxInt_MultiLine_hxx <GeomInt_TheMultiLineOfWLApprox.hpp>
#include <ApproxInt_MultiLine.hpp>
