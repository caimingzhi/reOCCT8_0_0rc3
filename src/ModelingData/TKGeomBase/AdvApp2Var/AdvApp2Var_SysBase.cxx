

#include <cassert>
#include <cmath>
#include <NCollection_Array1.hpp>
#include <cstring>
#include <AdvApp2Var_SysBase.hpp>
#include <AdvApp2Var_Data.hpp>
#include <Standard.hpp>

static int __i__len();

static int __s__cmp();

static int macrbrk_();

static int macrclw_(intptr_t* iadfld, intptr_t* iadflf, integer* nalloc);
static int macrerr_(intptr_t* iad, intptr_t* nalloc);
static int macrgfl_(intptr_t* iadfld, intptr_t* iadflf, integer* iphase, integer* iznuti);
static int macrmsg_(const char* crout,
                    integer*    num,
                    integer*    it,
                    doublereal* xt,
                    const char* ct,
                    ftnlen      crout_len,
                    ftnlen      ct_len);

static int macrstw_(intptr_t* iadfld, intptr_t* iadflf, integer* nalloc);

static int madbtbk_(integer* indice);

static int magtlog_(const char* cnmlog,
                    const char* chaine,
                    integer*    long__,
                    integer*    iercod,
                    ftnlen      cnmlog_len,
                    ftnlen      chaine_len);

static int mamdlng_(char* cmdlng, ftnlen cmdlng_len);

static int maostrb_();

static int maostrd_();

static int maoverf_(integer* nbentr, doublereal* dtable);

static int matrlog_(const char* cnmlog,
                    const char* chaine,
                    integer*    length,
                    integer*    iercod,
                    ftnlen      cnmlog_len,
                    ftnlen      chaine_len);

static int matrsym_(const char* cnmsym,
                    const char* chaine,
                    integer*    length,
                    integer*    iercod,
                    ftnlen      cnmsym_len,
                    ftnlen      chaine_len);

static int mcrcomm_(integer* kop, integer* noct, intptr_t* iadr, integer* ier);

static int mcrfree_(integer* ibyte, intptr_t iadr, integer* ier);

static int mcrgetv_(integer* sz, intptr_t* iad, integer* ier);

static struct
{
  integer lec, imp, keyb, mae, jscrn, itblt, ibb;
} mblank__;

#define mcrfill_ABS(a) (((a) < 0) ? (-(a)) : (a))

AdvApp2Var_SysBase::AdvApp2Var_SysBase()
{
  mainial_();
  memset(&mcrstac_, 0, sizeof(mcrstac_));
}

AdvApp2Var_SysBase::~AdvApp2Var_SysBase()
{
  assert(mcrgene_.ncore == 0);
}

int AdvApp2Var_SysBase::macinit_(integer* imode, integer* ival)

{

  if (*imode == 0)
  {
    mblank__.imp = 6;
    mblank__.ibb = 0;
    mblank__.lec = 5;
  }
  else if (*imode == 1)
  {
    mblank__.imp = *ival;
  }
  else if (*imode == 2)
  {
    mblank__.ibb = *ival;
  }
  else if (*imode == 3)
  {
    mblank__.lec = *ival;
  }

  return 0;
}

int AdvApp2Var_SysBase::macrai4_(integer*  nbelem,
                                 integer*  maxelm,
                                 integer*  itablo,
                                 intptr_t* iofset,
                                 integer*  iercod)

{

  integer iunit;

  iunit = sizeof(integer);

  if (*nbelem > *maxelm)
  {
    mcrrqst_(&iunit, nbelem, itablo, iofset, iercod);
  }
  else
  {
    *iercod = 0;
    *iofset = 0;
  }
  return 0;
}

int AdvApp2Var_SysBase::macrar8_(integer*    nbelem,
                                 integer*    maxelm,
                                 doublereal* xtablo,
                                 intptr_t*   iofset,
                                 integer*    iercod)

{
  integer c__8 = 8;

  if (*nbelem > *maxelm)
  {
    mcrrqst_(&c__8, nbelem, xtablo, iofset, iercod);
  }
  else
  {
    *iercod = 0;
    *iofset = 0;
  }
  return 0;
}

int macrbrk_()
{
  return 0;
}

int AdvApp2Var_SysBase::macrchk_()
{

  integer i__1;

  integer i__, j;

  i__1 = mcrgene_.ncore;
  for (i__ = 0; i__ < i__1; ++i__)
  {

    intptr_t* p = &mcrgene_.icore[i__].startaddr;
    for (j = 0; j <= 1; ++j)
    {
      intptr_t* pp = p + j;
      if (*pp != -1)
      {

        double* t = reinterpret_cast<double*>(*pp);
        if (*t != -134744073.)
        {

          macrerr_(pp, p + 2);

          maostrb_();

          *pp = -1;
        }
      }
    }
  }
  return 0;
}

int macrclw_(intptr_t*, intptr_t*, integer*)

{
  return 0;
}

int AdvApp2Var_SysBase::macrdi4_(integer* nbelem,
                                 integer*,
                                 integer*  itablo,
                                 intptr_t* iofset,
                                 integer*  iercod)

{

  integer iunit;

  iunit = sizeof(integer);

  if (*iofset != 0)
  {
    AdvApp2Var_SysBase::mcrdelt_(&iunit, nbelem, itablo, iofset, iercod);
  }
  else
  {
    *iercod = 0;
  }
  return 0;
}

int AdvApp2Var_SysBase::macrdr8_(integer* nbelem,
                                 integer*,
                                 doublereal* xtablo,
                                 intptr_t*   iofset,
                                 integer*    iercod)

{
  integer c__8 = 8;

  if (*iofset != 0)
  {
    AdvApp2Var_SysBase::mcrdelt_(&c__8, nbelem, xtablo, iofset, iercod);
  }
  else
  {
    *iercod = 0;
  }
  return 0;
}

int macrerr_(intptr_t*, intptr_t*)

{

  return 0;
}

int macrgfl_(intptr_t* iadfld, intptr_t* iadflf, integer* iphase, integer* iznuti)

{

  integer ifois = 1;

  char    cbid[1] = {};
  integer ibid, ienr;
  integer novfl = 0;

  if (ifois == 0)
  {
    matrsym_("NO_OVERFLOW", cbid, &novfl, &ibid, 11L, 1L);
    ifois = 1;
  }

  double* t = reinterpret_cast<double*>(*iadfld);

  if (*iphase == 1 && novfl == 0)
  {
    ienr = *iznuti / 8;
    maoverf_(&ienr, &t[1]);
  }

  *t = -134744073.;

  macrbrk_();

  t  = reinterpret_cast<double*>(*iadflf);
  *t = -134744073.;

  macrbrk_();

  return 0;
}

int macrmsg_(const char*,
             integer*,
             integer*    it,
             doublereal* xt,
             const char* ct,
             ftnlen,
             ftnlen ct_len)

{

  integer inum;
  char    cln[3];

  ct -= ct_len;
  (void)ct;
  (void)xt;
  (void)it;

  mamdlng_(cln, 3L);

  inum = -1;

  if (inum == 0)
  {
  }
  else if (inum == 1)
  {
  }
  else
  {
  }

  return 0;
}

int macrstw_(intptr_t*, intptr_t*, integer*)

{
  return 0;
}

int madbtbk_(integer* indice)
{
  *indice = 0;
  return 0;
}

int AdvApp2Var_SysBase::maermsg_(const char*, integer*, ftnlen)

{
  return 0;
}

int magtlog_(const char* cnmlog,
             const char*,
             integer* long__,
             integer* iercod,
             ftnlen   cnmlog_len,
             ftnlen)

{

  char    cbid[255];
  integer ibid, ier;

  *long__ = 0;
  *iercod = 0;

  matrlog_(cnmlog, cbid, &ibid, &ier, cnmlog_len, 255L);
  if (ier == 1)
  {
    goto L9500;
  }
  if (ier == 2)
  {
    goto L9700;
  }

  if (ibid > __i__len())
  {
    goto L9600;
  }

  *long__ = ibid;

  goto L9999;

L9500:
  *iercod = 5;

  goto L9999;

L9600:
  *iercod = 6;

  goto L9999;

L9700:
  *iercod = 7;

L9999:
  return 0;
}

int AdvApp2Var_SysBase::mainial_()
{
  mcrgene_.ncore = 0;
  mcrgene_.lprot = 0;
  return 0;
}

int AdvApp2Var_SysBase::maitbr8_(integer* itaill, doublereal* xtab, doublereal* xval)

{
  integer c__504 = 504;

  doublereal buff0[63] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
                          0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
                          0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
                          0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};

  integer i__1;

  integer    i__;
  doublereal buffx[63];
  integer    nbfois, noffst, nreste, nufois;

  --xtab;

  nbfois = *itaill / 63;
  noffst = nbfois * 63;
  nreste = *itaill - noffst;

  if (*xval == 0.)
  {
    if (nbfois >= 1)
    {
      i__1 = nbfois;
      for (nufois = 1; nufois <= i__1; ++nufois)
      {
        AdvApp2Var_SysBase::mcrfill_(&c__504, buff0, &xtab[(nufois - 1) * 63 + 1]);
      }
    }

    if (nreste >= 1)
    {
      i__1 = nreste << 3;
      AdvApp2Var_SysBase::mcrfill_(&i__1, buff0, &xtab[noffst + 1]);
    }
  }
  else
  {
    for (i__ = 1; i__ <= 63; ++i__)
    {
      buffx[i__ - 1] = *xval;
    }
    if (nbfois >= 1)
    {
      i__1 = nbfois;
      for (nufois = 1; nufois <= i__1; ++nufois)
      {
        AdvApp2Var_SysBase::mcrfill_(&c__504, buffx, &xtab[(nufois - 1) * 63 + 1]);
      }
    }

    if (nreste >= 1)
    {
      i__1 = nreste << 3;
      AdvApp2Var_SysBase::mcrfill_(&i__1, buffx, &xtab[noffst + 1]);
    }
  }

  return 0;
}

int mamdlng_(char*, ftnlen)

{

  return 0;
}

int maostrb_()
{
  return 0;
}

int maostrd_()
{
  integer imod;

  madbtbk_(&imod);
  if (imod == 1)
  {
    maostrb_();
  }
  return 0;
}

int maoverf_(integer* nbentr, doublereal* dtable)

{

  integer ifois = 0;

  integer i__1;

  integer    ibid;
  doublereal buff[63];
  integer    ioct, indic, nrest, icompt;

  --dtable;

  if (ifois == 0)
  {
    for (icompt = 1; icompt <= 63; ++icompt)
    {
      buff[icompt - 1] = maovpar_.r8ovr;
    }
    ifois = 1;
  }

  if (*nbentr < 63)
  {
    nrest = *nbentr << 3;
    AdvApp2Var_SysBase::mcrfill_(&nrest, buff, &dtable[1]);
  }
  else
  {

    ioct = 504;
    AdvApp2Var_SysBase::mcrfill_(&ioct, buff, &dtable[1]);
    indic = 63;

    i__1 = (integer)(std::log((real)(*nbentr) / (float)63.) / std::log((float)2.));
    for (ibid = 1; ibid <= i__1; ++ibid)
    {

      AdvApp2Var_SysBase::mcrfill_(&ioct, &dtable[1], &dtable[indic + 1]);
      ioct += ioct;
      indic += indic;
    }

    nrest = (*nbentr - indic) << 3;

    if (nrest > 0)
    {
      AdvApp2Var_SysBase::mcrfill_(&nrest, &dtable[1], &dtable[indic + 1]);
    }
  }
  return 0;
}

int AdvApp2Var_SysBase::maovsr8_(integer* ivalcs)
{
  *ivalcs = maovpar_.r8ncs;
  return 0;
}

int matrlog_(const char*, const char*, integer* length, integer* iercod, ftnlen, ftnlen)

{
  *iercod = 1;
  *length = 0;

  return 0;
}

int matrsym_(const char* cnmsym,
             const char*,
             integer* length,
             integer* iercod,
             ftnlen   cnmsym_len,
             ftnlen)

{

  char chainx[255] = {};

  magtlog_(cnmsym, chainx, length, iercod, cnmsym_len, 255L);

  if (*iercod == 5)
  {
    *iercod = 1;
  }

  if (*iercod >= 2)
  {
    *iercod = 2;
  }

  if (__s__cmp() == 0)
  {

    *length = 0;
  }

  return 0;
}

int mcrcomm_(integer* kop, integer* noct, intptr_t* iadr, integer* ier)

{

  integer ntab = 0;

  integer i__1, i__2;

  intptr_t                       ideb;
  NCollection_Array1<doublereal> dtab(0, 32000 - 1);
  NCollection_Array1<intptr_t>   itab(0, 160 - 1);
  intptr_t                       ipre;
  integer                        i__, j, k;

  *ier = 0;

  if (*kop == 1)
  {
    *iadr = 0;
    if (*noct < 1)
    {
      *ier = 1;
      goto L9900;
    }
    if (ntab >= 40)
    {
      *ier = 2;
      goto L9900;
    }

    i__1 = ntab + 1;
    for (i__ = 1; i__ <= i__1; ++i__)
    {
      if (i__ <= 1)
      {
        ipre = 1;
      }
      else
      {
        ipre = itab[((i__ - 1) << 2) - 3] + itab[((i__ - 1) << 2) - 4];
      }
      if (i__ <= ntab)
      {
        ideb = itab[(i__ << 2) - 3];
      }
      else
      {
        ideb = 32001;
      }
      if ((ideb - ipre) << 3 >= *noct)
      {

        i__2 = i__;
        for (j = ntab; j >= i__2; --j)
        {
          for (k = 1; k <= 4; ++k)
          {
            itab[k + ((j + 1) << 2) - 5] = itab[k + (j << 2) - 5];
          }
        }
        ++ntab;
        itab[(i__ << 2) - 4] = *noct / 8 + 1;
        itab[(i__ << 2) - 3] = ipre;
        itab[(i__ << 2) - 2] = *noct;
        *iadr                = reinterpret_cast<intptr_t>(&dtab[static_cast<int>(ipre) - 1]);
        itab[(i__ << 2) - 1] = *iadr;
        goto L9900;
      }
    }

    *ier = 3;
    goto L9900;
  }
  else
  {
    i__1 = ntab;
    for (i__ = 1; i__ <= i__1; ++i__)
    {
      if (*noct != itab[(i__ << 2) - 2])
      {
        goto L2001;
      }
      if (*iadr != itab[(i__ << 2) - 1])
      {
        goto L2001;
      }

      i__2 = ntab;
      for (j = i__ + 1; j <= i__2; ++j)
      {
        for (k = 1; k <= 4; ++k)
        {
          itab[k + ((j - 1) << 2) - 5] = itab[k + (j << 2) - 5];
        }
      }
      --ntab;
      goto L9900;
    L2001:;
    }

    *ier = 4;
  }

L9900:
  return 0;
}

int AdvApp2Var_SysBase::mcrdelt_(integer*  iunit,
                                 integer*  isize,
                                 void*     t,
                                 intptr_t* iofset,
                                 integer*  iercod)

{
  integer    ibid;
  doublereal xbid;
  integer    noct, iver, ksys, i__, n, nrang, ibyte, ier;
  intptr_t   iadfd, iadff, iaddr, loc;
  integer    kop;

  *iercod = 0;

  n   = -1;
  loc = reinterpret_cast<intptr_t>(t);

  for (i__ = mcrgene_.ncore - 1; i__ >= 0; --i__)
  {
    if (*iunit == mcrgene_.icore[i__].unit && *isize == mcrgene_.icore[i__].reqsize
        && loc == mcrgene_.icore[i__].loc && *iofset == mcrgene_.icore[i__].offset)
    {
      n = i__;
      goto L1100;
    }
  }
L1100:

  if (n < 0)
  {
    goto L9003;
  }

  ksys  = mcrgene_.icore[n].alloctype;
  ibyte = mcrgene_.icore[n].size;
  iaddr = mcrgene_.icore[n].addr;
  iadfd = mcrgene_.icore[n].startaddr;
  iadff = mcrgene_.icore[n].endaddr;
  nrang = mcrgene_.icore[n].rank;

  madbtbk_(&iver);
  if (iver == 1)
  {
    macrchk_();
  }

  if (ksys == static_allocation)
  {

    kop = 2;
    mcrcomm_(&kop, &ibyte, &iaddr, &ier);
    if (ier != 0)
    {
      goto L9001;
    }
  }
  else
  {

    mcrfree_(&ibyte, iaddr, &ier);
    if (ier != 0)
    {
      goto L9002;
    }
  }

  macrclw_(&iadfd, &iadff, &nrang);

  ++mcrstac_.ndelt[ksys];
  mcrstac_.nbyte[ksys] -= mcrgene_.icore[n].unit * mcrgene_.icore[n].reqsize;

  if (n < MAX_ALLOC_NB - 1)
  {
    noct = (mcrgene_.ncore - (n + 1)) * sizeof(mcrgene_.icore[0]);
    AdvApp2Var_SysBase::mcrfill_(&noct, &mcrgene_.icore[n + 1], &mcrgene_.icore[n]);
  }
  --mcrgene_.ncore;

  {

    const size_t shift = sizeof(*iofset) * 8 - 1;
    *iofset            = (uintptr_t(1) << shift) - 1;
  }
  goto L9900;

L9001:

  *iercod = 1;
  AdvApp2Var_SysBase::maermsg_("MCRDELT", iercod, 7L);
  maostrd_();
  goto L9900;

L9002:
  *iercod = 2;
  AdvApp2Var_SysBase::maermsg_("MCRDELT", iercod, 7L);
  macrmsg_("MCRDELT", iercod, &ibid, &xbid, " ", 7L, 1L);
  maostrd_();
  goto L9900;

L9003:
  *iercod = 3;
  AdvApp2Var_SysBase::maermsg_("MCRDELT", iercod, 7L);
  maostrd_();
  goto L9900;

L9900:

  return 0;
}

int AdvApp2Var_SysBase::mcrfill_(integer* size, void* tin, void* tout)

{
  char* jmin  = static_cast<char*>(tin);
  char* jmout = static_cast<char*>(tout);
  if (mcrfill_ABS(jmout - jmin) >= *size)
    memcpy(tout, tin, *size);
  else if (tin > tout)
  {
    integer n = *size;
    while (n-- > 0)
      *jmout++ = *jmin++;
  }
  else
  {
    integer n = *size;
    jmin += n;
    jmout += n;
    while (n-- > 0)
      *--jmout = *--jmin;
  }
  return 0;
}

int mcrfree_(integer*, intptr_t iadr, integer* ier)

{
  *ier = 0;
  Standard::Free((void*)iadr);
  return 0;
}

int mcrgetv_(integer* sz, intptr_t* iad, integer* ier)

{

  *ier = 0;
  *iad = (intptr_t)Standard::Allocate(*sz);
  if (!*iad)
    *ier = 1;
  return 0;
}

int AdvApp2Var_SysBase::mcrlist_(integer* ier) const

{

  integer i__1;

  char       cfmt[1]{};
  doublereal dfmt;
  integer    ifmt, i__, nufmt, ntotal;
  char       subrou[7];

  *ier = 0;

  nufmt = 1;
  ifmt  = mcrgene_.ncore;
  macrmsg_(subrou, &nufmt, &ifmt, &dfmt, cfmt, 7L, 1L);

  ntotal = 0;

  i__1 = mcrgene_.ncore;
  for (i__ = 0; i__ < i__1; ++i__)
  {
    nufmt = 2;
    ifmt  = mcrgene_.icore[i__].unit * mcrgene_.icore[i__].reqsize;
    macrmsg_(subrou, &nufmt, &ifmt, &dfmt, cfmt, 7L, 1L);
    ntotal += ifmt;
  }

  nufmt = 3;
  ifmt  = ntotal;
  macrmsg_(subrou, &nufmt, &ifmt, &dfmt, cfmt, 7L, 1L);

  return 0;
}

int AdvApp2Var_SysBase::mcrrqst_(integer*  iunit,
                                 integer*  isize,
                                 void*     t,
                                 intptr_t* iofset,
                                 integer*  iercod)

{

  integer i__1, i__2;

  doublereal dfmt;
  integer    ifmt, iver;
  char       subr[7];
  integer    ksys, ibyte, irest, ier;
  intptr_t   iadfd, iadff, iaddr, lofset, loc;
  integer    izu;

  *iercod = 0;

  if (mcrgene_.ncore >= MAX_ALLOC_NB)
  {
    goto L9001;
  }
  if (*iunit != 1 && *iunit != 2 && *iunit != 4 && *iunit != 8)
  {
    goto L9002;
  }

  ibyte = *iunit * *isize;

  madbtbk_(&iver);

  if (iver == 1)
  {

    if (ibyte == 0)
    {

      maostrb_();
    }
    else if (ibyte >= 4096000)
    {

      maostrb_();
    }
  }

  loc   = reinterpret_cast<intptr_t>(t);
  izu   = ibyte + loc % *iunit;
  irest = izu % 8;
  if (irest != 0)
  {
    izu = izu + 8 - irest;
  }

  ibyte = izu + 24;

  ksys = heap_allocation;
  mcrgetv_(&ibyte, &iaddr, &ier);
  if (ier != 0)
  {
    goto L9003;
  }

  iadfd = iaddr + 8 - iaddr % 8;
  iadff = iadfd + 8 + izu;

  lofset  = iadfd + 8 + loc % *iunit - loc;
  *iofset = lofset / *iunit;

  if (iver == 1)
  {
    macrchk_();
  }

  macrgfl_(&iadfd, &iadff, &iver, &izu);

  mcrgene_.icore[mcrgene_.ncore].prot      = mcrgene_.lprot;
  mcrgene_.icore[mcrgene_.ncore].unit      = (unsigned char)(*iunit);
  mcrgene_.icore[mcrgene_.ncore].reqsize   = *isize;
  mcrgene_.icore[mcrgene_.ncore].loc       = loc;
  mcrgene_.icore[mcrgene_.ncore].offset    = *iofset;
  mcrgene_.icore[mcrgene_.ncore].alloctype = (unsigned char)ksys;
  mcrgene_.icore[mcrgene_.ncore].size      = ibyte;
  mcrgene_.icore[mcrgene_.ncore].addr      = iaddr;
  mcrgene_.icore[mcrgene_.ncore].userzone  = mcrgene_.ncore;
  mcrgene_.icore[mcrgene_.ncore].startaddr = iadfd;
  mcrgene_.icore[mcrgene_.ncore].endaddr   = iadff;
  mcrgene_.icore[mcrgene_.ncore].rank      = mcrgene_.ncore + 1;
  ++mcrgene_.ncore;

  mcrgene_.lprot = 0;

  macrstw_(&iadfd, &iadff, &mcrgene_.ncore);

  ++mcrstac_.nrqst[ksys];
  mcrstac_.nbyte[ksys] +=
    mcrgene_.icore[mcrgene_.ncore - 1].unit * mcrgene_.icore[mcrgene_.ncore - 1].reqsize;

  i__1 = mcrstac_.mbyte[ksys], i__2 = mcrstac_.nbyte[ksys];
  mcrstac_.mbyte[ksys] = advapp_max(i__1, i__2);

  goto L9900;

L9001:
  *iercod = 1;
  ifmt    = MAX_ALLOC_NB;

  macrmsg_(subr, iercod, &ifmt, &dfmt, " ", 7L, 1L);
  maostrd_();
  goto L9900;

L9002:
  *iercod = 2;
  ifmt    = *iunit;

  macrmsg_(subr, iercod, &ifmt, &dfmt, " ", 7L, 1L);
  goto L9900;

L9003:
  *iercod = 3;
  ifmt    = ibyte;

  macrmsg_(subr, iercod, &ifmt, &dfmt, " ", 7L, 1L);
  maostrd_();
  mcrlist_(&ier);
  goto L9900;

L9900:
  mcrgene_.lprot = 0;
  return 0;
}

int AdvApp2Var_SysBase::mgenmsg_(const char*, ftnlen)

{
  return 0;
}

int AdvApp2Var_SysBase::mgsomsg_(const char*, ftnlen)

{
  return 0;
}

void AdvApp2Var_SysBase::miraz_(integer* taille, void* adt)

{
  memset(adt, '\0', *taille);
}

integer AdvApp2Var_SysBase::mnfndeb_()
{
  integer ret_val;
  ret_val = 0;
  return ret_val;
}

int AdvApp2Var_SysBase::msifill_(integer* nbintg, integer* ivecin, integer* ivecou)
{
  integer nocte;

  --ivecou;
  --ivecin;

  nocte = *nbintg * sizeof(integer);
  AdvApp2Var_SysBase::mcrfill_(&nocte, &ivecin[1], &ivecou[1]);
  return 0;
}

int AdvApp2Var_SysBase::msrfill_(integer* nbreel, doublereal* vecent, doublereal* vecsor)
{
  integer nocte;

  --vecsor;
  --vecent;

  nocte = *nbreel * sizeof(doublereal);
  AdvApp2Var_SysBase::mcrfill_(&nocte, &vecent[1], &vecsor[1]);
  return 0;
}

int AdvApp2Var_SysBase::mswrdbg_(const char*, ftnlen)

{

  if (AdvApp2Var_SysBase::mnfndeb_() >= 1)
  {
  }
  return 0;
}

int __i__len()
{
  return 0;
}

int __s__cmp()
{
  return 0;
}

int AdvApp2Var_SysBase::do__fio()
{
  return 0;
}

int AdvApp2Var_SysBase::do__lio()
{
  return 0;
}

void AdvApp2Var_SysBase::mvriraz_(integer* taille, void* adt)

{
  integer offset;
  offset = *taille * 8;

  memset(adt, '\0', offset);
}
