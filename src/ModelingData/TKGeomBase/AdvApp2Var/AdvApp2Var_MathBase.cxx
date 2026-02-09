

#include <cmath>
#include <AdvApp2Var_SysBase.hpp>
#include <AdvApp2Var_Data_f2c.hpp>
#include <AdvApp2Var_MathBase.hpp>
#include <AdvApp2Var_Data.hpp>
#include <NCollection_Array1.hpp>

static int mmchole_(integer*    mxcoef,
                    integer*    dimens,
                    doublereal* amatri,
                    integer*    aposit,
                    integer*    posuiv,
                    doublereal* chomat,
                    integer*    iercod);

static int mmrslss_(integer*    mxcoef,
                    integer*    dimens,
                    doublereal* smatri,
                    integer*    sposit,
                    integer*    posuiv,
                    doublereal* mscnmbr,
                    doublereal* soluti,
                    integer*    iercod);

static int mfac_(doublereal* f, integer* n);

static int mmaper0_(integer*    ncofmx,
                    integer*    ndimen,
                    integer*    ncoeff,
                    doublereal* crvlgd,
                    integer*    ncfnew,
                    doublereal* ycvmax,
                    doublereal* errmax);
static int mmaper2_(integer*    ncofmx,
                    integer*    ndimen,
                    integer*    ncoeff,
                    doublereal* crvjac,
                    integer*    ncfnew,
                    doublereal* ycvmax,
                    doublereal* errmax);

static int mmaper4_(integer*    ncofmx,
                    integer*    ndimen,
                    integer*    ncoeff,
                    doublereal* crvjac,
                    integer*    ncfnew,
                    doublereal* ycvmax,
                    doublereal* errmax);

static int mmaper6_(integer*    ncofmx,
                    integer*    ndimen,
                    integer*    ncoeff,
                    doublereal* crvjac,
                    integer*    ncfnew,
                    doublereal* ycvmax,
                    doublereal* errmax);

static int mmarc41_(integer*    ndimax,
                    integer*    ndimen,
                    integer*    ncoeff,
                    doublereal* crvold,
                    doublereal* upara0,
                    doublereal* upara1,
                    doublereal* crvnew,
                    integer*    iercod);

static int mmatvec_(integer*    nligne,
                    integer*    ncolon,
                    integer*    gposit,
                    integer*    gnstoc,
                    doublereal* gmatri,
                    doublereal* vecin,
                    integer*    deblig,
                    doublereal* vecout,
                    integer*    iercod);

static int mmcvstd_(integer*    ncofmx,
                    integer*    ndimax,
                    integer*    ncoeff,
                    integer*    ndimen,
                    doublereal* crvcan,
                    doublereal* courbe);

static int mmdrvcb_(integer*    ideriv,
                    integer*    ndim,
                    integer*    ncoeff,
                    doublereal* courbe,
                    doublereal* tparam,
                    doublereal* tabpnt,
                    integer*    iercod);

static int mmexthi_(integer* ndegre, NCollection_Array1<doublereal>& hwgaus);

static int mmextrl_(integer* ndegre, NCollection_Array1<doublereal>& rootlg);

static int mmherm0_(doublereal* debfin, integer* iercod);

static int mmherm1_(doublereal* debfin,
                    integer*    ordrmx,
                    integer*    iordre,
                    doublereal* hermit,
                    integer*    iercod);
static int mmloncv_(integer*    ndimax,
                    integer*    ndimen,
                    integer*    ncoeff,
                    doublereal* courbe,
                    doublereal* tdebut,
                    doublereal* tfinal,
                    doublereal* xlongc,
                    integer*    iercod);
static int mmpojac_(doublereal*                     tparam,
                    integer*                        iordre,
                    integer*                        ncoeff,
                    integer*                        nderiv,
                    NCollection_Array1<doublereal>& valjac,
                    integer*                        iercod);

static int mmrslw_(integer*    normax,
                   integer*    nordre,
                   integer*    ndimen,
                   doublereal* epspiv,
                   doublereal* abmatr,
                   doublereal* xmatri,
                   integer*    iercod);
static int mmtmave_(integer*    nligne,
                    integer*    ncolon,
                    integer*    gposit,
                    integer*    gnstoc,
                    doublereal* gmatri,
                    doublereal* vecin,
                    doublereal* vecout,
                    integer*    iercod);
static int mmtrpj0_(integer*    ncofmx,
                    integer*    ndimen,
                    integer*    ncoeff,
                    doublereal* epsi3d,
                    doublereal* crvlgd,
                    doublereal* ycvmax,
                    doublereal* epstrc,
                    integer*    ncfnew);
static int mmtrpj2_(integer*    ncofmx,
                    integer*    ndimen,
                    integer*    ncoeff,
                    doublereal* epsi3d,
                    doublereal* crvlgd,
                    doublereal* ycvmax,
                    doublereal* epstrc,
                    integer*    ncfnew);

static int     mmtrpj4_(integer*    ncofmx,
                        integer*    ndimen,
                        integer*    ncoeff,
                        doublereal* epsi3d,
                        doublereal* crvlgd,
                        doublereal* ycvmax,
                        doublereal* epstrc,
                        integer*    ncfnew);
static int     mmtrpj6_(integer*    ncofmx,
                        integer*    ndimen,
                        integer*    ncoeff,
                        doublereal* epsi3d,
                        doublereal* crvlgd,
                        doublereal* ycvmax,
                        doublereal* epstrc,
                        integer*    ncfnew);
static integer pow__ii(integer* x, integer* n);

static int mvcvin2_(integer* ncoeff, doublereal* crvold, doublereal* crvnew, integer* iercod);

static int mvcvinv_(integer* ncoeff, doublereal* crvold, doublereal* crvnew, integer* iercod);

static int mvgaus0_(integer*    kindic,
                    doublereal* urootl,
                    doublereal* hiltab,
                    integer*    nbrval,
                    integer*    iercod);
static int mvpscr2_(integer* ncoeff, doublereal* curve2, doublereal* tparam, doublereal* pntcrb);

static int mvpscr3_(integer* ncoeff, doublereal* curve2, doublereal* tparam, doublereal* pntcrb);

static struct
{
  doublereal eps1, eps2, eps3, eps4;
  integer    niterm, niterr;
} mmprcsn_;

static struct
{
  doublereal tdebut, tfinal, verifi, cmherm[576];
} mmcmher_;

int AdvApp2Var_MathBase::mdsptpt_(integer*    ndimen,
                                  doublereal* point1,
                                  doublereal* point2,
                                  doublereal* distan)

{
  integer c__8 = 8;

  integer    i__1;
  doublereal d__1;

  integer     i__;
  doublereal* differ = nullptr;
  integer     ier;
  intptr_t    iofset, j;

  --point2;
  --point1;

  iofset = 0;
  ier    = 0;

  AdvApp2Var_SysBase anAdvApp2Var_SysBase;
  if (*ndimen > 100)
  {
    anAdvApp2Var_SysBase.mcrrqst_(&c__8, ndimen, differ, &iofset, &ier);
  }

  if (ier > 0)
  {

    *distan = 0.;
    i__1    = *ndimen;
    for (i__ = 1; i__ <= i__1; ++i__)
    {

      d__1 = point1[i__] - point2[i__];
      *distan += d__1 * d__1;
    }
    *distan = sqrt(*distan);
  }
  else
  {
    i__1 = *ndimen;
    for (i__ = 1; i__ <= i__1; ++i__)
    {
      j         = iofset + i__ - 1;
      differ[j] = point2[i__] - point1[i__];
    }

    *distan = AdvApp2Var_MathBase::mzsnorm_(ndimen, &differ[iofset]);
  }

  if (iofset != 0)
  {
    anAdvApp2Var_SysBase.mcrdelt_(&c__8, ndimen, differ, &iofset, &ier);
  }

  return 0;
}

int mfac_(doublereal* f, integer* n)

{

  integer i__1;

  integer i__;

  --f;

  f[1] = (float)1.;
  i__1 = *n;
  for (i__ = 2; i__ <= i__1; ++i__)
  {

    f[i__] = i__ * f[i__ - 1];
  }
  return 0;
}

int AdvApp2Var_MathBase::mmapcmp_(integer*    ndim,
                                  integer*    ncofmx,
                                  integer*    ncoeff,
                                  doublereal* crvold,
                                  doublereal* crvnew)

{

  integer crvold_dim1, crvold_offset, crvnew_dim1, crvnew_offset, i__1, i__2;

  integer ipair, nd, ndegre, impair, ibb, idg;

  crvold_dim1   = *ncofmx;
  crvold_offset = crvold_dim1;
  crvold -= crvold_offset;
  crvnew_dim1   = (*ncoeff - 1) / 2 + 1;
  crvnew_offset = crvnew_dim1 << 1;
  crvnew -= crvnew_offset;

  ibb = AdvApp2Var_SysBase::mnfndeb_();
  if (ibb >= 3)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMAPCMP", 7L);
  }

  ndegre = *ncoeff - 1;
  i__1   = *ndim;
  for (nd = 1; nd <= i__1; ++nd)
  {
    ipair = 0;
    i__2  = ndegre / 2;
    for (idg = 0; idg <= i__2; ++idg)
    {
      crvnew[idg + (nd << 1) * crvnew_dim1] = crvold[ipair + nd * crvold_dim1];
      ipair += 2;
    }
    if (ndegre < 1)
    {
      goto L400;
    }
    impair = 1;
    i__2   = (ndegre - 1) / 2;
    for (idg = 0; idg <= i__2; ++idg)
    {
      crvnew[idg + ((nd << 1) + 1) * crvnew_dim1] = crvold[impair + nd * crvold_dim1];
      impair += 2;
    }

  L400:

    ;
  }

  if (ibb >= 3)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMAPCMP", 7L);
  }
  return 0;
}

int mmaper0_(integer*    ncofmx,
             integer*    ndimen,
             integer*    ncoeff,
             doublereal* crvlgd,
             integer*    ncfnew,
             doublereal* ycvmax,
             doublereal* errmax)

{

  integer    crvlgd_dim1, crvlgd_offset, i__1, i__2;
  doublereal d__1;

  integer    ncut;
  doublereal bidon;
  integer    ii, nd;

  --ycvmax;
  crvlgd_dim1   = *ncofmx;
  crvlgd_offset = crvlgd_dim1 + 1;
  crvlgd -= crvlgd_offset;

  i__1 = *ndimen;
  for (ii = 1; ii <= i__1; ++ii)
  {
    ycvmax[ii] = 0.;
  }

  ncut = 1;
  if (*ncfnew + 1 > ncut)
  {
    ncut = *ncfnew + 1;
  }

  i__1 = *ncoeff;
  for (ii = ncut; ii <= i__1; ++ii)
  {

    bidon = ((ii - 1) * 2. + 1.) / 2.;
    bidon = sqrt(bidon);

    i__2 = *ndimen;
    for (nd = 1; nd <= i__2; ++nd)
    {
      ycvmax[nd] += (d__1 = crvlgd[ii + nd * crvlgd_dim1], advapp_abs(d__1)) * bidon;
    }
  }

  *errmax = AdvApp2Var_MathBase::mzsnorm_(ndimen, &ycvmax[1]);

  return 0;
}

int mmaper2_(integer*    ncofmx,
             integer*    ndimen,
             integer*    ncoeff,
             doublereal* crvjac,
             integer*    ncfnew,
             doublereal* ycvmax,
             doublereal* errmax)

{

  static doublereal xmaxj[57] = {
    .9682458365518542212948163499456,   .986013297183269340427888048593603,
    1.07810420343739860362585159028115, 1.17325804490920057010925920756025,
    1.26476561266905634732910520370741, 1.35169950227289626684434056681946,
    1.43424378958284137759129885012494, 1.51281316274895465689402798226634,
    1.5878364329591908800533936587012,  1.65970112228228167018443636171226,
    1.72874345388622461848433443013543, 1.7952515611463877544077632304216,
    1.85947199025328260370244491818047, 1.92161634324190018916351663207101,
    1.98186713586472025397859895825157, 2.04038269834980146276967984252188,
    2.09730119173852573441223706382076, 2.15274387655763462685970799663412,
    2.20681777186342079455059961912859, 2.25961782459354604684402726624239,
    2.31122868752403808176824020121524, 2.36172618435386566570998793688131,
    2.41117852396114589446497298177554, 2.45964731268663657873849811095449,
    2.50718840313973523778244737914028, 2.55385260994795361951813645784034,
    2.59968631659221867834697883938297, 2.64473199258285846332860663371298,
    2.68902863641518586789566216064557, 2.73261215675199397407027673053895,
    2.77551570192374483822124304745691, 2.8177699459714315371037628127545,
    2.85940333797200948896046563785957, 2.90044232019793636101516293333324,
    2.94091151970640874812265419871976, 2.98083391718088702956696303389061,
    3.02023099621926980436221568258656, 3.05912287574998661724731962377847,
    3.09752842783622025614245706196447, 3.13546538278134559341444834866301,
    3.17295042316122606504398054547289, 3.2099992681699613513775259670214,
    3.24662674946606137764916854570219, 3.28284687953866689817670991319787,
    3.31867291347259485044591136879087, 3.35411740487202127264475726990106,
    3.38919225660177218727305224515862, 3.42390876691942143189170489271753,
    3.45827767149820230182596660024454, 3.49230918177808483937957161007792,
    3.5260130200285724149540352829756,  3.55939845146044235497103883695448,
    3.59247431368364585025958062194665, 3.62524904377393592090180712976368,
    3.65773070318071087226169680450936, 3.68992700068237648299565823810245,
    3.72184531357268220291630708234186};

  integer    crvjac_dim1, crvjac_offset, i__1, i__2;
  doublereal d__1;

  integer    idec, ncut;
  doublereal bidon;
  integer    ii, nd;

  --ycvmax;
  crvjac_dim1   = *ncofmx;
  crvjac_offset = crvjac_dim1 + 1;
  crvjac -= crvjac_offset;

  i__1 = *ndimen;
  for (ii = 1; ii <= i__1; ++ii)
  {
    ycvmax[ii] = 0.;
  }

  idec = 3;

  i__1 = idec, i__2 = *ncfnew + 1;
  ncut = advapp_max(i__1, i__2);

  i__1 = *ncoeff;
  for (ii = ncut; ii <= i__1; ++ii)
  {

    bidon = xmaxj[ii - idec];
    i__2  = *ndimen;
    for (nd = 1; nd <= i__2; ++nd)
    {
      ycvmax[nd] += (d__1 = crvjac[ii + nd * crvjac_dim1], advapp_abs(d__1)) * bidon;
    }
  }

  *errmax = AdvApp2Var_MathBase::mzsnorm_(ndimen, &ycvmax[1]);

  return 0;
}

int mmaper4_(integer*    ncofmx,
             integer*    ndimen,
             integer*    ncoeff,
             doublereal* crvjac,
             integer*    ncfnew,
             doublereal* ycvmax,
             doublereal* errmax)
{

  static doublereal xmaxj[55] = {
    1.1092649593311780079813740546678,  1.05299572648705464724876659688996,
    1.0949715351434178709281698645813,  1.15078388379719068145021100764647,
    1.2094863084718701596278219811869,  1.26806623151369531323304177532868,
    1.32549784426476978866302826176202, 1.38142537365039019558329304432581,
    1.43575531950773585146867625840552, 1.48850442653629641402403231015299,
    1.53973611681876234549146350844736, 1.58953193485272191557448229046492,
    1.63797820416306624705258190017418, 1.68515974143594899185621942934906,
    1.73115699602477936547107755854868, 1.77604489805513552087086912113251,
    1.81989256661534438347398400420601, 1.86276344480103110090865609776681,
    1.90471563564740808542244678597105, 1.94580231994751044968731427898046,
    1.98607219357764450634552790950067, 2.02556989246317857340333585562678,
    2.06433638992049685189059517340452, 2.10240936014742726236706004607473,
    2.13982350649113222745523925190532, 2.17661085564771614285379929798896,
    2.21280102016879766322589373557048, 2.2484214321456956597803794333791,
    2.28349755104077956674135810027654, 2.31805304852593774867640120860446,
    2.35210997297725685169643559615022, 2.38568889602346315560143377261814,
    2.41880904328694215730192284109322, 2.45148841120796359750021227795539,
    2.48374387161372199992570528025315, 2.5155912654873773953959098501893,
    2.54704548720896557684101746505398, 2.57812056037881628390134077704127,
    2.60882970619319538196517982945269, 2.63918540521920497868347679257107,
    2.66919945330942891495458446613851, 2.69888301230439621709803756505788,
    2.72824665609081486737132853370048, 2.75730041251405791603760003778285,
    2.78605380158311346185098508516203, 2.81451587035387403267676338931454,
    2.84269522483114290814009184272637, 2.87060005919012917988363332454033,
    2.89823818258367657739520912946934, 2.92561704377132528239806135133273,
    2.95274375377994262301217318010209, 2.97962510678256471794289060402033,
    3.00626759936182712291041810228171, 3.03267744830655121818899164295959,
    3.05886060707437081434964933864149};

  integer    crvjac_dim1, crvjac_offset, i__1, i__2;
  doublereal d__1;

  integer    idec, ncut;
  doublereal bidon;
  integer    ii, nd;

  --ycvmax;
  crvjac_dim1   = *ncofmx;
  crvjac_offset = crvjac_dim1 + 1;
  crvjac -= crvjac_offset;

  i__1 = *ndimen;
  for (ii = 1; ii <= i__1; ++ii)
  {
    ycvmax[ii] = 0.;
  }

  idec = 5;

  i__1 = idec, i__2 = *ncfnew + 1;
  ncut = advapp_max(i__1, i__2);

  i__1 = *ncoeff;
  for (ii = ncut; ii <= i__1; ++ii)
  {

    bidon = xmaxj[ii - idec];
    i__2  = *ndimen;
    for (nd = 1; nd <= i__2; ++nd)
    {
      ycvmax[nd] += (d__1 = crvjac[ii + nd * crvjac_dim1], advapp_abs(d__1)) * bidon;
    }
  }

  *errmax = AdvApp2Var_MathBase::mzsnorm_(ndimen, &ycvmax[1]);

  return 0;
}

int mmaper6_(integer*    ncofmx,
             integer*    ndimen,
             integer*    ncoeff,
             doublereal* crvjac,
             integer*    ncfnew,
             doublereal* ycvmax,
             doublereal* errmax)

{

  static doublereal xmaxj[53] = {
    1.21091229812484768570102219548814, 1.11626917091567929907256116528817,
    1.1327140810290884106278510474203,  1.1679452722668028753522098022171,
    1.20910611986279066645602153641334, 1.25228283758701572089625983127043,
    1.29591971597287895911380446311508, 1.3393138157481884258308028584917,
    1.3821288728999671920677617491385,  1.42420414683357356104823573391816,
    1.46546895108549501306970087318319, 1.50590085198398789708599726315869,
    1.54550385142820987194251585145013, 1.58429644271680300005206185490937,
    1.62230484071440103826322971668038, 1.65955905239130512405565733793667,
    1.69609056468292429853775667485212, 1.73193098017228915881592458573809,
    1.7671112206990325429863426635397,  1.80166107681586964987277458875667,
    1.83560897003644959204940535551721, 1.86898184653271388435058371983316,
    1.90180515174518670797686768515502, 1.93410285411785808749237200054739,
    1.96589749778987993293150856865539, 1.99721027139062501070081653790635,
    2.02806108474738744005306947877164, 2.05846864831762572089033752595401,
    2.08845055210580131460156962214748, 2.11802334209486194329576724042253,
    2.14720259305166593214642386780469, 2.17600297710595096918495785742803,
    2.20443832785205516555772788192013, 2.2325216999457379530416998244706,
    2.2602654243075083168599953074345,  2.28768115912702794202525264301585,
    2.3147799369092684021274946755348,  2.34157220782483457076721300512406,
    2.36806787963276257263034969490066, 2.39427635443992520016789041085844,
    2.42020656255081863955040620243062, 2.44586699364757383088888037359254,
    2.47126572552427660024678584642791, 2.49641045058324178349347438430311,
    2.52130850028451113942299097584818, 2.54596686772399937214920135190177,
    2.5703922285006754089328998222275,  2.59459096001908861492582631591134,
    2.61856915936049852435394597597773, 2.64233265984385295286445444361827,
    2.66588704638685848486056711408168, 2.68923766976735295746679957665724,
    2.71238965987606292679677228666411};

  integer    crvjac_dim1, crvjac_offset, i__1, i__2;
  doublereal d__1;

  integer    idec, ncut;
  doublereal bidon;
  integer    ii, nd;

  --ycvmax;
  crvjac_dim1   = *ncofmx;
  crvjac_offset = crvjac_dim1 + 1;
  crvjac -= crvjac_offset;

  i__1 = *ndimen;
  for (ii = 1; ii <= i__1; ++ii)
  {
    ycvmax[ii] = 0.;
  }

  idec = 7;

  i__1 = idec, i__2 = *ncfnew + 1;
  ncut = advapp_max(i__1, i__2);

  i__1 = *ncoeff;
  for (ii = ncut; ii <= i__1; ++ii)
  {

    bidon = xmaxj[ii - idec];
    i__2  = *ndimen;
    for (nd = 1; nd <= i__2; ++nd)
    {
      ycvmax[nd] += (d__1 = crvjac[ii + nd * crvjac_dim1], advapp_abs(d__1)) * bidon;
    }
  }

  *errmax = AdvApp2Var_MathBase::mzsnorm_(ndimen, &ycvmax[1]);

  return 0;
}

int AdvApp2Var_MathBase::mmaperx_(integer*    ncofmx,
                                  integer*    ndimen,
                                  integer*    ncoeff,
                                  integer*    iordre,
                                  doublereal* crvjac,
                                  integer*    ncfnew,
                                  doublereal* ycvmax,
                                  doublereal* errmax,
                                  integer*    iercod)

{

  integer crvjac_dim1, crvjac_offset;

  integer jord;

  --ycvmax;
  crvjac_dim1   = *ncofmx;
  crvjac_offset = crvjac_dim1 + 1;
  crvjac -= crvjac_offset;

  *iercod = 0;

  jord = (*iordre + 1) << 1;

  if (jord == 0)
  {
    mmaper0_(ncofmx, ndimen, ncoeff, &crvjac[crvjac_offset], ncfnew, &ycvmax[1], errmax);
  }
  else if (jord == 2)
  {
    mmaper2_(ncofmx, ndimen, ncoeff, &crvjac[crvjac_offset], ncfnew, &ycvmax[1], errmax);
  }
  else if (jord == 4)
  {
    mmaper4_(ncofmx, ndimen, ncoeff, &crvjac[crvjac_offset], ncfnew, &ycvmax[1], errmax);
  }
  else if (jord == 6)
  {
    mmaper6_(ncofmx, ndimen, ncoeff, &crvjac[crvjac_offset], ncfnew, &ycvmax[1], errmax);
  }
  else
  {
    *iercod = 1;
  }

  return 0;
}

int mmarc41_(integer*    ndimax,
             integer*    ndimen,
             integer*    ncoeff,
             doublereal* crvold,
             doublereal* upara0,
             doublereal* upara1,
             doublereal* crvnew,
             integer*    iercod)

{

  integer crvold_dim1, crvold_offset, crvnew_dim1, crvnew_offset, i__1, i__2, i__3;

  integer    nboct;
  doublereal tbaux[61];
  integer    nd;
  doublereal bid;
  integer    ncf, ncj;

  crvnew_dim1   = *ndimax;
  crvnew_offset = crvnew_dim1 + 1;
  crvnew -= crvnew_offset;
  crvold_dim1   = *ndimax;
  crvold_offset = crvold_dim1 + 1;
  crvold -= crvold_offset;

  *iercod = 0;

  if (*ncoeff > 61 || *ncoeff < 1)
  {
    *iercod = 10;
    goto L9999;
  }

  if (*ndimen == *ndimax && *upara0 == 0. && *upara1 == 1.)
  {
    nboct = (*ndimax << 3) * *ncoeff;
    AdvApp2Var_SysBase::mcrfill_(&nboct, &crvold[crvold_offset], &crvnew[crvnew_offset]);
    goto L9999;
  }

  if (*upara0 == 1. && *upara1 == 0.)
  {
    if (*ndimen == 3 && *ndimax == 3 && *ncoeff <= 21)
    {
      mvcvinv_(ncoeff, &crvold[crvold_offset], &crvnew[crvnew_offset], iercod);
      goto L9999;
    }

    if (*ndimen == 2 && *ndimax == 2 && *ncoeff <= 21)
    {
      mvcvin2_(ncoeff, &crvold[crvold_offset], &crvnew[crvnew_offset], iercod);
      goto L9999;
    }
  }

  i__1 = *ndimen;
  for (nd = 1; nd <= i__1; ++nd)
  {
    crvnew[nd + crvnew_dim1] = crvold[nd + crvold_dim1];
  }
  if (*ncoeff == 1)
  {
    goto L9999;
  }
  tbaux[0] = *upara0;
  tbaux[1] = *upara1 - *upara0;

  i__1 = *ncoeff - 1;
  for (ncf = 2; ncf <= i__1; ++ncf)
  {

    i__2 = ncf - 1;
    for (ncj = 1; ncj <= i__2; ++ncj)
    {
      bid  = tbaux[ncj - 1];
      i__3 = *ndimen;
      for (nd = 1; nd <= i__3; ++nd)
      {
        crvnew[nd + ncj * crvnew_dim1] += crvold[nd + ncf * crvold_dim1] * bid;
      }
    }

    bid  = tbaux[ncf - 1];
    i__2 = *ndimen;
    for (nd = 1; nd <= i__2; ++nd)
    {
      crvnew[nd + ncf * crvnew_dim1] = crvold[nd + ncf * crvold_dim1] * bid;
    }

    bid        = *upara1 - *upara0;
    tbaux[ncf] = tbaux[ncf - 1] * bid;
    for (ncj = ncf; ncj >= 2; --ncj)
    {
      tbaux[ncj - 1] = tbaux[ncj - 1] * *upara0 + tbaux[ncj - 2] * bid;
    }
    tbaux[0] *= *upara0;
  }

  i__1 = *ncoeff - 1;
  for (ncj = 1; ncj <= i__1; ++ncj)
  {
    bid  = tbaux[ncj - 1];
    i__2 = *ndimen;
    for (nd = 1; nd <= i__2; ++nd)
    {
      crvnew[nd + ncj * crvnew_dim1] += crvold[nd + *ncoeff * crvold_dim1] * bid;
    }
  }
  i__1 = *ndimen;
  for (nd = 1; nd <= i__1; ++nd)
  {
    crvnew[nd + *ncoeff * crvnew_dim1] = crvold[nd + *ncoeff * crvold_dim1] * tbaux[*ncoeff - 1];
  }

L9999:
  if (*iercod != 0)
  {
    AdvApp2Var_SysBase::maermsg_("MMARC41", iercod, 7L);
  }

  return 0;
}

int AdvApp2Var_MathBase::mmarcin_(integer*    ndimax,
                                  integer*    ndim,
                                  integer*    ncoeff,
                                  doublereal* crvold,
                                  doublereal* u0,
                                  doublereal* u1,
                                  doublereal* crvnew,
                                  integer*    iercod)

{

  integer    crvold_dim1, crvold_offset, crvnew_dim1, crvnew_offset, i__1, i__2, i__3;
  doublereal d__1;

  doublereal x0, x1;
  integer    nd;
  doublereal tabaux[61];
  integer    ibb;
  doublereal bid;
  integer    ncf;
  integer    ncj;
  doublereal eps3;

  crvnew_dim1   = *ndimax;
  crvnew_offset = crvnew_dim1 + 1;
  crvnew -= crvnew_offset;
  crvold_dim1   = *ncoeff;
  crvold_offset = crvold_dim1 + 1;
  crvold -= crvold_offset;

  ibb = AdvApp2Var_SysBase::mnfndeb_();
  if (ibb >= 2)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMARCIN", 7L);
  }

  AdvApp2Var_MathBase::mmveps3_(&eps3);
  if ((d__1 = *u1 - *u0, advapp_abs(d__1)) < eps3)
  {
    *iercod = 13;
    goto L9999;
  }
  *iercod = 0;

  if (*ncoeff > 61 || *ncoeff < 1)
  {
    *iercod = 10;
    goto L9999;
  }

  if (*ndim == *ndimax && *u0 == -1. && *u1 == 1.)
  {
    AdvApp2Var_MathBase::mmcvinv_(ndim,
                                  ncoeff,
                                  ndim,
                                  &crvold[crvold_offset],
                                  &crvnew[crvnew_offset]);
    goto L9999;
  }

  if (*u0 == 0. && *u1 == 1.)
  {
    mmcvstd_(ncoeff, ndimax, ncoeff, ndim, &crvold[crvold_offset], &crvnew[crvnew_offset]);
    goto L9999;
  }

  x0   = -(*u1 + *u0) / (*u1 - *u0);
  x1   = 2. / (*u1 - *u0);
  i__1 = *ndim;
  for (nd = 1; nd <= i__1; ++nd)
  {
    crvnew[nd + crvnew_dim1] = crvold[nd * crvold_dim1 + 1];
  }
  if (*ncoeff == 1)
  {
    goto L9999;
  }
  tabaux[0] = x0;
  tabaux[1] = x1;

  i__1 = *ncoeff - 1;
  for (ncf = 2; ncf <= i__1; ++ncf)
  {

    i__2 = ncf - 1;
    for (ncj = 1; ncj <= i__2; ++ncj)
    {
      bid  = tabaux[ncj - 1];
      i__3 = *ndim;
      for (nd = 1; nd <= i__3; ++nd)
      {
        crvnew[nd + ncj * crvnew_dim1] += crvold[ncf + nd * crvold_dim1] * bid;
      }
    }

    bid  = tabaux[ncf - 1];
    i__2 = *ndim;
    for (nd = 1; nd <= i__2; ++nd)
    {
      crvnew[nd + ncf * crvnew_dim1] = crvold[ncf + nd * crvold_dim1] * bid;
    }

    tabaux[ncf] = tabaux[ncf - 1] * x1;
    for (ncj = ncf; ncj >= 2; --ncj)
    {
      tabaux[ncj - 1] = tabaux[ncj - 1] * x0 + tabaux[ncj - 2] * x1;
    }
    tabaux[0] *= x0;
  }

  i__1 = *ncoeff - 1;
  for (ncj = 1; ncj <= i__1; ++ncj)
  {
    bid  = tabaux[ncj - 1];
    i__2 = *ndim;
    for (nd = 1; nd <= i__2; ++nd)
    {
      crvnew[nd + ncj * crvnew_dim1] += crvold[*ncoeff + nd * crvold_dim1] * bid;
    }
  }
  i__1 = *ndim;
  for (nd = 1; nd <= i__1; ++nd)
  {
    crvnew[nd + *ncoeff * crvnew_dim1] = crvold[*ncoeff + nd * crvold_dim1] * tabaux[*ncoeff - 1];
  }

L9999:
  if (*iercod > 0)
  {
    AdvApp2Var_SysBase::maermsg_("MMARCIN", iercod, 7L);
  }
  if (ibb >= 2)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMARCIN", 7L);
  }
  return 0;
}

int mmatvec_(integer* nligne,
             integer*,
             integer* gposit,
             integer*,
             doublereal* gmatri,
             doublereal* vecin,
             integer*    deblig,
             doublereal* vecout,
             integer*    iercod)

{

  integer i__1, i__2;

  logical    ldbg;
  integer    jmin, jmax, i__, j, k;
  doublereal somme;
  integer    aux;

  --vecout;
  gposit -= 4;
  --vecin;
  --gmatri;

  ldbg = AdvApp2Var_SysBase::mnfndeb_() >= 2;
  if (ldbg)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMATVEC", 7L);
  }
  *iercod = 0;

  AdvApp2Var_SysBase::mvriraz_(nligne, &vecout[1]);
  i__1 = *nligne;
  for (i__ = *deblig; i__ <= i__1; ++i__)
  {
    somme = 0.;
    jmin  = gposit[i__ * 3 + 3];
    jmax  = gposit[i__ * 3 + 1] + gposit[i__ * 3 + 3] - 1;
    aux   = gposit[i__ * 3 + 2] - gposit[i__ * 3 + 1] - jmin + 1;
    i__2  = jmax;
    for (j = jmin; j <= i__2; ++j)
    {
      k = j + aux;
      somme += gmatri[k] * vecin[j];
    }
    vecout[i__] = somme;
  }

  goto L9999;

L9999:

  AdvApp2Var_SysBase::maermsg_("MMATVEC", iercod, 7L);
  if (ldbg)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMATVEC", 7L);
  }

  return 0;
}

int AdvApp2Var_MathBase::mmbulld_(integer*    nbcoln,
                                  integer*    nblign,
                                  doublereal* dtabtr,
                                  integer*    numcle)

{

  integer dtabtr_dim1, dtabtr_offset, i__1, i__2;

  logical    ldbg;
  doublereal daux;
  integer    nite1, nite2, nchan, i1, i2;

  dtabtr_dim1   = *nblign;
  dtabtr_offset = dtabtr_dim1 + 1;
  dtabtr -= dtabtr_offset;

  ldbg = AdvApp2Var_SysBase::mnfndeb_() >= 2;
  if (ldbg)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMBULLD", 7L);
  }
  nchan = 1;
  nite1 = *nbcoln;
  nite2 = 2;

  while (nchan != 0)
  {

    nchan = 0;
    i__1  = nite1;
    for (i1 = nite2; i1 <= i__1; ++i1)
    {
      if (dtabtr[*numcle + i1 * dtabtr_dim1] < dtabtr[*numcle + (i1 - 1) * dtabtr_dim1])
      {
        i__2 = *nblign;
        for (i2 = 1; i2 <= i__2; ++i2)
        {
          daux                                = dtabtr[i2 + (i1 - 1) * dtabtr_dim1];
          dtabtr[i2 + (i1 - 1) * dtabtr_dim1] = dtabtr[i2 + i1 * dtabtr_dim1];
          dtabtr[i2 + i1 * dtabtr_dim1]       = daux;
        }
        if (nchan == 0)
        {
          nchan = 1;
        }
      }
    }
    --nite1;

    if (nchan != 0)
    {
      nchan = 0;
      i__1  = nite2;
      for (i1 = nite1; i1 >= i__1; --i1)
      {
        if (dtabtr[*numcle + i1 * dtabtr_dim1] < dtabtr[*numcle + (i1 - 1) * dtabtr_dim1])
        {
          i__2 = *nblign;
          for (i2 = 1; i2 <= i__2; ++i2)
          {
            daux                                = dtabtr[i2 + (i1 - 1) * dtabtr_dim1];
            dtabtr[i2 + (i1 - 1) * dtabtr_dim1] = dtabtr[i2 + i1 * dtabtr_dim1];
            dtabtr[i2 + i1 * dtabtr_dim1]       = daux;
          }
          if (nchan == 0)
          {
            nchan = 1;
          }
        }
      }
      ++nite2;
    }
  }

  goto L9999;

L9999:

  if (ldbg)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMBULLD", 7L);
  }

  return 0;
}

int AdvApp2Var_MathBase::mmcdriv_(integer*    ndimen,
                                  integer*    ncoeff,
                                  doublereal* courbe,
                                  integer*    ideriv,
                                  integer*    ncofdv,
                                  doublereal* crvdrv)

{

  integer courbe_dim1, courbe_offset, crvdrv_dim1, crvdrv_offset, i__1, i__2;

  integer    i__, j, k;
  doublereal mfactk, bid;

  crvdrv_dim1   = *ndimen;
  crvdrv_offset = crvdrv_dim1 + 1;
  crvdrv -= crvdrv_offset;
  courbe_dim1   = *ndimen;
  courbe_offset = courbe_dim1 + 1;
  courbe -= courbe_offset;

  if (*ideriv >= *ncoeff)
  {
    i__1 = *ndimen;
    for (i__ = 1; i__ <= i__1; ++i__)
    {
      crvdrv[i__ + crvdrv_dim1] = 0.;
    }
    *ncofdv = 1;
    goto L9999;
  }

  k      = *ideriv;
  mfactk = 1.;
  i__1   = k;
  for (i__ = 2; i__ <= i__1; ++i__)
  {
    mfactk *= i__;
  }

  i__1 = *ncoeff;
  for (j = k + 1; j <= i__1; ++j)
  {
    bid  = mmcmcnp_.cnp[j - 1 + k * 61] * mfactk;
    i__2 = *ndimen;
    for (i__ = 1; i__ <= i__2; ++i__)
    {
      crvdrv[i__ + (j - k) * crvdrv_dim1] = bid * courbe[i__ + j * courbe_dim1];
    }
  }

  *ncofdv = *ncoeff - *ideriv;

L9999:
  return 0;
}

int AdvApp2Var_MathBase::mmcglc1_(integer*    ndimax,
                                  integer*    ndimen,
                                  integer*    ncoeff,
                                  doublereal* courbe,
                                  doublereal* tdebut,
                                  doublereal* tfinal,
                                  doublereal* epsiln,
                                  doublereal* xlongc,
                                  doublereal* erreur,
                                  integer*    iercod)

{

  integer    courbe_dim1, courbe_offset, i__1;
  doublereal d__1;

  integer    ndec;
  doublereal tdeb, tfin;
  integer    iter;
  doublereal oldso = 0.;
  integer    itmax;
  doublereal sottc;
  integer    kk, ibb;
  doublereal dif, pas;
  doublereal som;

  courbe_dim1   = *ndimax;
  courbe_offset = courbe_dim1 + 1;
  courbe -= courbe_offset;

  ibb = AdvApp2Var_SysBase::mnfndeb_();
  if (ibb >= 2)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMCGLC1", 7L);
  }

  *iercod = 0;
  *xlongc = 0.;
  *erreur = 0.;

  if (*tdebut == *tfinal)
  {
    *iercod = 0;
    goto L9999;
  }

  if (*ndimen <= 0 || *ncoeff <= 0)
  {
    goto L9003;
  }

  ndec = 1;
  iter = 1;

  itmax = 13;

L5000:
  pas   = (*tfinal - *tdebut) / ndec;
  sottc = 0.;

  i__1 = ndec;
  for (kk = 1; kk <= i__1; ++kk)
  {

    tdeb = *tdebut + (kk - 1) * pas;
    tfin = tdeb + pas;
    mmloncv_(ndimax, ndimen, ncoeff, &courbe[courbe_offset], &tdeb, &tfin, &som, iercod);
    if (*iercod > 0)
    {
      goto L9002;
    }

    sottc += som;
  }

  if (iter == 1)
  {
    oldso = sottc;
    ndec <<= 1;
    ++iter;
    goto L5000;
  }
  else
  {

    ++iter;
    dif = (d__1 = sottc - oldso, advapp_abs(d__1));

    if (dif > *epsiln)
    {

      if (iter > itmax)
      {
        *iercod = 1;
        goto L9000;
      }
      else
      {

        oldso = sottc;
        ndec <<= 1;
        goto L5000;
      }
    }
  }

L9000:
  *xlongc = sottc;
  *erreur = dif;
  goto L9999;

L9002:
  *iercod = 2;
  goto L9999;

L9003:
  *iercod = 3;
  goto L9999;

L9999:
  if (*iercod > 0)
  {
    AdvApp2Var_SysBase::maermsg_("MMCGLC1", iercod, 7L);
  }
  if (ibb >= 2)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMCGLC1", 7L);
  }
  return 0;
}

int mmchole_(integer*,
             integer*    dimens,
             doublereal* amatri,
             integer*    aposit,
             integer*    posuiv,
             doublereal* chomat,
             integer*    iercod)

{

  integer    i__1, i__2, i__3;
  doublereal d__1;

  logical    ldbg;
  integer    kmin, i__, j, k;
  doublereal somme;
  integer    ptini, ptcou;

  --chomat;
  --posuiv;
  --amatri;
  aposit -= 3;

  ldbg = AdvApp2Var_SysBase::mnfndeb_() >= 4;
  if (ldbg)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMCHOLE", 7L);
  }
  *iercod = 0;

  i__1 = *dimens;
  for (j = 1; j <= i__1; ++j)
  {

    ptini = aposit[(j << 1) + 2];

    somme = 0.;
    i__2  = ptini - 1;
    for (k = ptini - aposit[(j << 1) + 1]; k <= i__2; ++k)
    {

      d__1 = chomat[k];
      somme += d__1 * d__1;
    }

    if (amatri[ptini] - somme < 1e-32)
    {
      goto L9101;
    }
    chomat[ptini] = sqrt(amatri[ptini] - somme);

    ptcou = ptini;

    while (posuiv[ptcou] > 0)
    {

      i__   = posuiv[ptcou];
      ptcou = aposit[(i__ << 1) + 2] - (i__ - j);

      somme = 0.;

      i__2 = i__ - aposit[(i__ << 1) + 1], i__3 = j - aposit[(j << 1) + 1];
      kmin = advapp_max(i__2, i__3);
      i__2 = j - 1;
      for (k = kmin; k <= i__2; ++k)
      {
        somme +=
          chomat[aposit[(i__ << 1) + 2] - (i__ - k)] * chomat[aposit[(j << 1) + 2] - (j - k)];
      }

      chomat[ptcou] = (amatri[ptcou] - somme) / chomat[ptini];
    }
  }

  goto L9999;

L9101:
  *iercod = 1;
  goto L9999;

L9999:

  AdvApp2Var_SysBase::maermsg_("MMCHOLE", iercod, 7L);
  if (ldbg)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMCHOLE", 7L);
  }

  return 0;
}

int AdvApp2Var_MathBase::mmcvctx_(integer*    ndimen,
                                  integer*    ncofmx,
                                  integer*    nderiv,
                                  doublereal* ctrtes,
                                  doublereal* crvres,
                                  doublereal* tabaux,
                                  doublereal* xmatri,
                                  integer*    iercod)

{

  integer ctrtes_dim1, ctrtes_offset, crvres_dim1, crvres_offset, xmatri_dim1, xmatri_offset,
    tabaux_dim1, tabaux_offset, i__1, i__2;

  integer    moup1, nordr;
  integer    nd;
  integer    ibb, ncf, ndv;
  doublereal eps1;

  crvres_dim1   = *ncofmx;
  crvres_offset = crvres_dim1 + 1;
  crvres -= crvres_offset;
  xmatri_dim1   = *nderiv + 1;
  xmatri_offset = xmatri_dim1 + 1;
  xmatri -= xmatri_offset;
  tabaux_dim1   = *nderiv + 1 + *ndimen;
  tabaux_offset = tabaux_dim1 + 1;
  tabaux -= tabaux_offset;
  ctrtes_dim1   = *ndimen;
  ctrtes_offset = ctrtes_dim1 * 3 + 1;
  ctrtes -= ctrtes_offset;

  ibb = AdvApp2Var_SysBase::mnfndeb_();
  if (ibb >= 3)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMCVCTX", 7L);
  }

  AdvApp2Var_MathBase::mmeps1_(&eps1);

  nordr = *nderiv + 1;
  i__1  = nordr;
  for (ncf = 1; ncf <= i__1; ++ncf)
  {
    tabaux[ncf + tabaux_dim1] = 1.;
  }

  i__1 = nordr;
  for (ndv = 2; ndv <= i__1; ++ndv)
  {
    i__2 = nordr;
    for (ncf = 1; ncf <= i__2; ++ncf)
    {
      tabaux[ncf + ndv * tabaux_dim1] =
        tabaux[ncf + (ndv - 1) * tabaux_dim1] * (doublereal)((ncf << 1) - ndv);
    }
  }

  moup1 = 1;
  i__1  = nordr;
  for (ndv = 1; ndv <= i__1; ++ndv)
  {
    i__2 = *ndimen;
    for (nd = 1; nd <= i__2; ++nd)
    {
      tabaux[nordr + nd + ndv * tabaux_dim1] =
        (ctrtes[nd + ((ndv << 1) + 2) * ctrtes_dim1]
         + moup1 * ctrtes[nd + ((ndv << 1) + 1) * ctrtes_dim1])
        / 2.;
    }
    moup1 = -moup1;
  }

  mmrslw_(&nordr, &nordr, ndimen, &eps1, &tabaux[tabaux_offset], &xmatri[xmatri_offset], iercod);
  if (*iercod > 0)
  {
    goto L9999;
  }
  i__1 = *ndimen;
  for (nd = 1; nd <= i__1; ++nd)
  {
    i__2 = nordr;
    for (ncf = 1; ncf <= i__2; ++ncf)
    {
      crvres[(ncf << 1) - 1 + nd * crvres_dim1] = xmatri[ncf + nd * xmatri_dim1];
    }
  }

  i__1 = nordr;
  for (ncf = 1; ncf <= i__1; ++ncf)
  {
    tabaux[ncf + tabaux_dim1] = 1.;
  }

  i__1 = nordr;
  for (ndv = 2; ndv <= i__1; ++ndv)
  {
    i__2 = nordr;
    for (ncf = 1; ncf <= i__2; ++ncf)
    {
      tabaux[ncf + ndv * tabaux_dim1] =
        tabaux[ncf + (ndv - 1) * tabaux_dim1] * (doublereal)((ncf << 1) - ndv + 1);
    }
  }

  moup1 = -1;
  i__1  = nordr;
  for (ndv = 1; ndv <= i__1; ++ndv)
  {
    i__2 = *ndimen;
    for (nd = 1; nd <= i__2; ++nd)
    {
      tabaux[nordr + nd + ndv * tabaux_dim1] =
        (ctrtes[nd + ((ndv << 1) + 2) * ctrtes_dim1]
         + moup1 * ctrtes[nd + ((ndv << 1) + 1) * ctrtes_dim1])
        / 2.;
    }
    moup1 = -moup1;
  }

  mmrslw_(&nordr, &nordr, ndimen, &eps1, &tabaux[tabaux_offset], &xmatri[xmatri_offset], iercod);
  if (*iercod > 0)
  {
    goto L9999;
  }
  i__1 = *ndimen;
  for (nd = 1; nd <= i__1; ++nd)
  {
    i__2 = nordr;
    for (ncf = 1; ncf <= i__2; ++ncf)
    {
      crvres[(ncf << 1) + nd * crvres_dim1] = xmatri[ncf + nd * xmatri_dim1];
    }
  }

L9999:
  if (*iercod != 0)
  {
    AdvApp2Var_SysBase::maermsg_("MMCVCTX", iercod, 7L);
  }
  if (ibb >= 3)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMCVCTX", 7L);
  }

  return 0;
}

int AdvApp2Var_MathBase::mmcvinv_(integer*    ndimax,
                                  integer*    ncoef,
                                  integer*    ndim,
                                  doublereal* curveo,
                                  doublereal* curve)

{

  static char nomprg[8 + 1] = "MMCVINV ";

  integer curve_dim1, curve_offset, curveo_dim1, curveo_offset, i__1, i__2;

  integer i__, nd, ibb;

  curve_dim1   = *ndimax;
  curve_offset = curve_dim1 + 1;
  curve -= curve_offset;
  curveo_dim1   = *ncoef;
  curveo_offset = curveo_dim1 + 1;
  curveo -= curveo_offset;

  ibb = AdvApp2Var_SysBase::mnfndeb_();
  if (ibb >= 2)
  {
    AdvApp2Var_SysBase::mgenmsg_(nomprg, 6L);
  }

  i__1 = *ncoef;
  for (i__ = 1; i__ <= i__1; ++i__)
  {
    i__2 = *ndim;
    for (nd = 1; nd <= i__2; ++nd)
    {
      curve[nd + i__ * curve_dim1] = curveo[i__ + nd * curveo_dim1];
    }
  }

  return 0;
}

int mmcvstd_(integer*    ncofmx,
             integer*    ndimax,
             integer*    ncoeff,
             integer*    ndimen,
             doublereal* crvcan,
             doublereal* courbe)

{

  integer courbe_dim1, crvcan_dim1, crvcan_offset, i__1, i__2, i__3;

  integer    ndeg, i__, j, j1, nd, ibb;
  doublereal bid;

  courbe_dim1 = *ndimax;
  --courbe;
  crvcan_dim1   = *ncofmx;
  crvcan_offset = crvcan_dim1;
  crvcan -= crvcan_offset;

  ibb = AdvApp2Var_SysBase::mnfndeb_();
  if (ibb >= 3)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMCVSTD", 7L);
  }
  ndeg = *ncoeff - 1;

  i__1 = *ndimen;
  for (nd = 1; nd <= i__1; ++nd)
  {
    i__2 = ndeg;
    for (j = 0; j <= i__2; ++j)
    {
      bid  = 0.;
      i__3 = ndeg;
      for (i__ = j; i__ <= i__3; i__ += 2)
      {
        bid += crvcan[i__ + nd * crvcan_dim1] * mmcmcnp_.cnp[i__ + j * 61];
      }
      courbe[nd + j * courbe_dim1] = bid;

      bid  = 0.;
      j1   = j + 1;
      i__3 = ndeg;
      for (i__ = j1; i__ <= i__3; i__ += 2)
      {
        bid += crvcan[i__ + nd * crvcan_dim1] * mmcmcnp_.cnp[i__ + j * 61];
      }
      courbe[nd + j * courbe_dim1] -= bid;
    }
  }

  bid  = 1.;
  i__1 = ndeg;
  for (i__ = 0; i__ <= i__1; ++i__)
  {
    i__2 = *ndimen;
    for (nd = 1; nd <= i__2; ++nd)
    {
      courbe[nd + i__ * courbe_dim1] *= bid;
    }
    bid *= 2.;
  }

  if (ibb >= 3)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMCVSTD", 7L);
  }
  return 0;
}

int AdvApp2Var_MathBase::mmdrc11_(integer*    iordre,
                                  integer*    ndimen,
                                  integer*    ncoeff,
                                  doublereal* courbe,
                                  doublereal* points,
                                  doublereal* mfactab)

{

  integer courbe_dim1, courbe_offset, points_dim2, points_offset, i__1, i__2;

  integer ndeg, i__, j, ndgcb, nd, ibb;

  points_dim2   = *iordre + 1;
  points_offset = (points_dim2 << 1) + 1;
  points -= points_offset;
  courbe_dim1   = *ncoeff;
  courbe_offset = courbe_dim1;
  courbe -= courbe_offset;

  ibb = AdvApp2Var_SysBase::mnfndeb_();
  if (ibb >= 2)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMDRC11", 7L);
  }

  if (*iordre < 0 || *ncoeff < 1)
  {
    goto L9999;
  }

  ndgcb = *ncoeff - 1;
  i__1  = *ndimen;
  for (nd = 1; nd <= i__1; ++nd)
  {
    points[(nd * points_dim2 << 1) + 1] = courbe[ndgcb + nd * courbe_dim1];
    points[(nd * points_dim2 << 1) + 2] = courbe[ndgcb + nd * courbe_dim1];
  }

  i__1 = *ndimen;
  for (nd = 1; nd <= i__1; ++nd)
  {
    i__2 = *iordre;
    for (j = 1; j <= i__2; ++j)
    {
      points[((j + nd * points_dim2) << 1) + 1] = 0.;
      points[((j + nd * points_dim2) << 1) + 2] = 0.;
    }
  }

  i__1 = *ndimen;
  for (nd = 1; nd <= i__1; ++nd)
  {
    i__2 = ndgcb;
    for (ndeg = 1; ndeg <= i__2; ++ndeg)
    {
      for (i__ = *iordre; i__ >= 1; --i__)
      {
        points[((i__ + nd * points_dim2) << 1) + 1] =
          -points[((i__ + nd * points_dim2) << 1) + 1]
          + points[((i__ - 1 + nd * points_dim2) << 1) + 1];
        points[((i__ + nd * points_dim2) << 1) + 2] +=
          points[((i__ - 1 + nd * points_dim2) << 1) + 2];
      }
      points[(nd * points_dim2 << 1) + 1] =
        -points[(nd * points_dim2 << 1) + 1] + courbe[ndgcb - ndeg + nd * courbe_dim1];
      points[(nd * points_dim2 << 1) + 2] += courbe[ndgcb - ndeg + nd * courbe_dim1];
    }
  }

  if (*iordre > 1)
  {
    mfac_(&mfactab[1], iordre);

    i__1 = *ndimen;
    for (nd = 1; nd <= i__1; ++nd)
    {
      i__2 = *iordre;
      for (i__ = 2; i__ <= i__2; ++i__)
      {
        points[((i__ + nd * points_dim2) << 1) + 1] =
          mfactab[i__] * points[((i__ + nd * points_dim2) << 1) + 1];
        points[((i__ + nd * points_dim2) << 1) + 2] =
          mfactab[i__] * points[((i__ + nd * points_dim2) << 1) + 2];
      }
    }
  }

L9999:
  if (ibb >= 2)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMDRC11", 7L);
  }
  return 0;
}

int mmdrvcb_(integer*    ideriv,
             integer*    ndim,
             integer*    ncoeff,
             doublereal* courbe,
             doublereal* tparam,
             doublereal* tabpnt,
             integer*    iercod)

{

  integer courbe_dim1, tabpnt_dim1, i__1, i__2, i__3;

  integer ndeg, i__, j, nd, ndgcrb, iptpnt, ibb;

  tabpnt_dim1 = *ndim;
  --tabpnt;
  courbe_dim1 = *ndim;
  --courbe;

  ibb = AdvApp2Var_SysBase::mnfndeb_();
  if (ibb >= 2)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMDRVCB", 7L);
  }

  if (*ideriv < 0 || *ncoeff < 1)
  {
    *iercod = 1;
    goto L9999;
  }
  *iercod = 0;

  ndgcrb = *ncoeff - 1;
  i__1   = *ndim;
  for (nd = 1; nd <= i__1; ++nd)
  {
    tabpnt[nd] = courbe[nd + ndgcrb * courbe_dim1];
  }

  if (*ideriv < 1)
  {
    goto L200;
  }
  iptpnt = *ndim * *ideriv;
  AdvApp2Var_SysBase::mvriraz_(&iptpnt, &tabpnt[tabpnt_dim1 + 1]);
L200:

  i__1 = ndgcrb;
  for (ndeg = 1; ndeg <= i__1; ++ndeg)
  {
    i__2 = *ndim;
    for (nd = 1; nd <= i__2; ++nd)
    {
      for (i__ = *ideriv; i__ >= 1; --i__)
      {
        tabpnt[nd + i__ * tabpnt_dim1] =
          tabpnt[nd + i__ * tabpnt_dim1] * *tparam + tabpnt[nd + (i__ - 1) * tabpnt_dim1];
      }
      tabpnt[nd] = tabpnt[nd] * *tparam + courbe[nd + (ndgcrb - ndeg) * courbe_dim1];
    }
  }

  i__1 = *ideriv;
  for (i__ = 2; i__ <= i__1; ++i__)
  {
    i__2 = i__;
    for (j = 2; j <= i__2; ++j)
    {
      i__3 = *ndim;
      for (nd = 1; nd <= i__3; ++nd)
      {
        tabpnt[nd + i__ * tabpnt_dim1] = (doublereal)j * tabpnt[nd + i__ * tabpnt_dim1];
      }
    }
  }

L9999:
  if (*iercod > 0)
  {
    AdvApp2Var_SysBase::maermsg_("MMDRVCB", iercod, 7L);
  }
  return 0;
}

int AdvApp2Var_MathBase::mmdrvck_(integer*    ncoeff,
                                  integer*    ndimen,
                                  doublereal* courbe,
                                  integer*    ideriv,
                                  doublereal* tparam,
                                  doublereal* pntcrb)

{

  static doublereal mmfack[21] = {1.,
                                  2.,
                                  6.,
                                  24.,
                                  120.,
                                  720.,
                                  5040.,
                                  40320.,
                                  362880.,
                                  3628800.,
                                  39916800.,
                                  479001600.,
                                  6227020800.,
                                  87178291200.,
                                  1.307674368e12,
                                  2.0922789888e13,
                                  3.55687428096e14,
                                  6.402373705728e15,
                                  1.21645100408832e17,
                                  2.43290200817664e18,
                                  5.109094217170944e19};

  integer courbe_dim1, courbe_offset, i__1, i__2;

  integer    i__, j, k, nd;
  doublereal mfactk, bid;

  --pntcrb;
  courbe_dim1   = *ndimen;
  courbe_offset = courbe_dim1 + 1;
  courbe -= courbe_offset;

  if (*ideriv >= *ncoeff)
  {
    i__1 = *ndimen;
    for (nd = 1; nd <= i__1; ++nd)
    {
      pntcrb[nd] = 0.;
    }
    goto L9999;
  }

  k = *ideriv;
  if (*ideriv <= 21 && *ideriv > 0)
  {
    mfactk = mmfack[k - 1];
  }
  else
  {
    mfactk = 1.;
    i__1   = k;
    for (i__ = 2; i__ <= i__1; ++i__)
    {
      mfactk *= i__;
    }
  }

  i__1 = *ndimen;
  for (nd = 1; nd <= i__1; ++nd)
  {
    pntcrb[nd] = courbe[nd + *ncoeff * courbe_dim1] * mmcmcnp_.cnp[*ncoeff - 1 + k * 61] * mfactk;
  }

  i__1 = k + 1;
  for (j = *ncoeff - 1; j >= i__1; --j)
  {
    bid  = mmcmcnp_.cnp[j - 1 + k * 61] * mfactk;
    i__2 = *ndimen;
    for (nd = 1; nd <= i__2; ++nd)
    {
      pntcrb[nd] = pntcrb[nd] * *tparam + courbe[nd + j * courbe_dim1] * bid;
    }
  }

L9999:

  return 0;
}

int AdvApp2Var_MathBase::mmeps1_(doublereal* epsilo)

{

  *epsilo = mmprcsn_.eps1;

  return 0;
}

int mmexthi_(integer* ndegre, NCollection_Array1<doublereal>& hwgaus)

{

  integer i__1;

  integer iadd, ideb, ndeg2, nmod2, ii, ibb;
  integer kpt;

  ibb = AdvApp2Var_SysBase::mnfndeb_();
  if (ibb >= 3)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMEXTHI", 7L);
  }

  ndeg2 = *ndegre / 2;
  nmod2 = *ndegre % 2;

  iadd = ndeg2 * (ndeg2 - 1) / 2 + 1;

  ideb = (*ndegre + 1) / 2 + 1;

  i__1 = *ndegre;
  for (ii = ideb; ii <= i__1; ++ii)
  {
    kpt        = iadd + ii - ideb;
    hwgaus(ii) = mlgdrtl_.hiltab[kpt + nmod2 * 465 - 1];
  }

  i__1 = ndeg2;
  for (ii = 1; ii <= i__1; ++ii)
  {
    hwgaus(ii) = hwgaus(*ndegre + 1 - ii);
  }

  if (nmod2 == 1)
  {
    hwgaus(ndeg2 + 1) = mlgdrtl_.hi0tab[ndeg2];
  }

  if (ibb >= 3)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMEXTHI", 7L);
  }
  return 0;
}

int mmextrl_(integer* ndegre, NCollection_Array1<doublereal>& rootlg)
{

  integer i__1;

  integer iadd, ideb, ndeg2, nmod2, ii, ibb;
  integer kpt;

  ibb = AdvApp2Var_SysBase::mnfndeb_();
  if (ibb >= 3)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMEXTRL", 7L);
  }

  ndeg2 = *ndegre / 2;
  nmod2 = *ndegre % 2;

  iadd = ndeg2 * (ndeg2 - 1) / 2 + 1;

  ideb = (*ndegre + 1) / 2 + 1;

  i__1 = *ndegre;
  for (ii = ideb; ii <= i__1; ++ii)
  {
    kpt        = iadd + ii - ideb;
    rootlg(ii) = mlgdrtl_.rootab[kpt + nmod2 * 465 - 1];
  }

  i__1 = ndeg2;
  for (ii = 1; ii <= i__1; ++ii)
  {
    rootlg(ii) = -rootlg(*ndegre + 1 - ii);
  }

  if (nmod2 == 1)
  {
    rootlg(ndeg2 + 1) = 0.;
  }

  if (ibb >= 3)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMEXTRL", 7L);
  }
  return 0;
}

int AdvApp2Var_MathBase::mmfmca8_(const integer* ndimen,
                                  const integer* ncoefu,
                                  const integer* ncoefv,
                                  const integer* ndimax,
                                  const integer* ncfumx,
                                  const integer*,
                                  doublereal* tabini,
                                  doublereal* tabres)

{

  integer tabini_dim1, tabini_dim2, tabini_offset, tabres_dim1, tabres_dim2, tabres_offset;

  integer i__, j, k, ilong;

  tabini_dim1   = *ndimen;
  tabini_dim2   = *ncoefu;
  tabini_offset = tabini_dim1 * (tabini_dim2 + 1) + 1;
  tabini -= tabini_offset;
  tabres_dim1   = *ndimax;
  tabres_dim2   = *ncfumx;
  tabres_offset = tabres_dim1 * (tabres_dim2 + 1) + 1;
  tabres -= tabres_offset;

  if (*ndimax == *ndimen)
  {
    goto L1000;
  }

  for (k = *ncoefv; k >= 1; --k)
  {
    for (j = *ncoefu; j >= 1; --j)
    {
      for (i__ = *ndimen; i__ >= 1; --i__)
      {
        tabres[i__ + (j + k * tabres_dim2) * tabres_dim1] =
          tabini[i__ + (j + k * tabini_dim2) * tabini_dim1];
      }
    }
  }
  goto L9999;

L1000:
  if (*ncoefu == *ncfumx)
  {
    goto L2000;
  }
  ilong = (*ndimen << 3) * *ncoefu;
  for (k = *ncoefv; k >= 1; --k)
  {
    AdvApp2Var_SysBase::mcrfill_(&ilong,
                                 &tabini[(k * tabini_dim2 + 1) * tabini_dim1 + 1],
                                 &tabres[(k * tabres_dim2 + 1) * tabres_dim1 + 1]);
  }
  goto L9999;

L2000:
  ilong = (*ndimen << 3) * *ncoefu * *ncoefv;
  AdvApp2Var_SysBase::mcrfill_(&ilong, &tabini[tabini_offset], &tabres[tabres_offset]);
  goto L9999;

L9999:
  return 0;
}

int AdvApp2Var_MathBase::mmfmca9_(integer* ndimax,
                                  integer* ncfumx,
                                  integer*,
                                  integer*    ndimen,
                                  integer*    ncoefu,
                                  integer*    ncoefv,
                                  doublereal* tabini,
                                  doublereal* tabres)

{

  integer tabini_dim1, tabini_dim2, tabini_offset, tabres_dim1, tabres_dim2, tabres_offset, i__1,
    i__2, i__3;

  integer i__, j, k, ilong;

  tabini_dim1   = *ndimax;
  tabini_dim2   = *ncfumx;
  tabini_offset = tabini_dim1 * (tabini_dim2 + 1) + 1;
  tabini -= tabini_offset;
  tabres_dim1   = *ndimen;
  tabres_dim2   = *ncoefu;
  tabres_offset = tabres_dim1 * (tabres_dim2 + 1) + 1;
  tabres -= tabres_offset;

  if (*ndimen == *ndimax)
  {
    goto L1000;
  }

  i__1 = *ncoefv;
  for (k = 1; k <= i__1; ++k)
  {
    i__2 = *ncoefu;
    for (j = 1; j <= i__2; ++j)
    {
      i__3 = *ndimen;
      for (i__ = 1; i__ <= i__3; ++i__)
      {
        tabres[i__ + (j + k * tabres_dim2) * tabres_dim1] =
          tabini[i__ + (j + k * tabini_dim2) * tabini_dim1];
      }
    }
  }
  goto L9999;

L1000:
  if (*ncoefu == *ncfumx)
  {
    goto L2000;
  }
  ilong = (*ndimen << 3) * *ncoefu;
  i__1  = *ncoefv;
  for (k = 1; k <= i__1; ++k)
  {
    AdvApp2Var_SysBase::mcrfill_(&ilong,
                                 &tabini[(k * tabini_dim2 + 1) * tabini_dim1 + 1],
                                 &tabres[(k * tabres_dim2 + 1) * tabres_dim1 + 1]);
  }
  goto L9999;

L2000:
  ilong = (*ndimen << 3) * *ncoefu * *ncoefv;
  AdvApp2Var_SysBase::mcrfill_(&ilong, &tabini[tabini_offset], &tabres[tabres_offset]);
  goto L9999;

L9999:
  return 0;
}

int AdvApp2Var_MathBase::mmfmcar_(integer*    ndimen,
                                  integer*    ncofmx,
                                  integer*    ncoefu,
                                  integer*    ncoefv,
                                  doublereal* patold,
                                  doublereal* upara1,
                                  doublereal* upara2,
                                  doublereal* vpara1,
                                  doublereal* vpara2,
                                  doublereal* patnew,
                                  integer*    iercod)

{
  integer c__8 = 8;

  integer patold_dim1, patold_dim2, patnew_dim1, patnew_dim2, i__1, patold_offset, patnew_offset;

  doublereal* tbaux = nullptr;
  integer     ksize, numax, kk;
  intptr_t    iofst;
  integer     ibb, ier;

  patnew_dim1   = *ndimen;
  patnew_dim2   = *ncofmx;
  patnew_offset = patnew_dim1 * (patnew_dim2 + 1) + 1;
  patnew -= patnew_offset;
  patold_dim1   = *ndimen;
  patold_dim2   = *ncofmx;
  patold_offset = patold_dim1 * (patold_dim2 + 1) + 1;
  patold -= patold_offset;

  ibb = AdvApp2Var_SysBase::mnfndeb_();
  if (ibb >= 2)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMFMCAR", 7L);
  }
  *iercod = 0;
  iofst   = 0;
  AdvApp2Var_SysBase anAdvApp2Var_SysBase;

  if (*ncofmx < *ncoefu)
  {
    *iercod = 10;
    goto L9999;
  }
  if (*ncoefu < 1 || *ncoefu > 61 || *ncoefv < 1 || *ncoefv > 61)
  {
    *iercod = 10;
    goto L9999;
  }

  if (*upara1 == 0. && *upara2 == 1. && *vpara1 == 0. && *vpara2 == 1.)
  {
    ksize = (*ndimen << 3) * *ncofmx * *ncoefv;
    AdvApp2Var_SysBase::mcrfill_(&ksize, &patold[patold_offset], &patnew[patnew_offset]);
    goto L9999;
  }

  if (*upara1 == 0. && *upara2 == 1.)
  {
    goto L2000;
  }
  i__1 = *ncoefv;
  for (kk = 1; kk <= i__1; ++kk)
  {
    mmarc41_(ndimen,
             ndimen,
             ncoefu,
             &patold[(kk * patold_dim2 + 1) * patold_dim1 + 1],
             upara1,
             upara2,
             &patnew[(kk * patnew_dim2 + 1) * patnew_dim1 + 1],
             iercod);
  }

L2000:
  if (*vpara1 == 0. && *vpara2 == 1.)
  {
    goto L9999;
  }

  numax = *ndimen * *ncoefu;
  if (*ncofmx != *ncoefu)
  {

    ksize = *ndimen * *ncoefu * *ncoefv;
    anAdvApp2Var_SysBase.mcrrqst_(&c__8, &ksize, tbaux, &iofst, &ier);
    if (ier > 0)
    {
      *iercod = 13;
      goto L9900;
    }

    if (*upara1 == 0. && *upara2 == 1.)
    {
      AdvApp2Var_MathBase::mmfmca9_(ndimen,
                                    ncofmx,
                                    ncoefv,
                                    ndimen,
                                    ncoefu,
                                    ncoefv,
                                    &patold[patold_offset],
                                    &tbaux[iofst]);
    }
    else
    {
      AdvApp2Var_MathBase::mmfmca9_(ndimen,
                                    ncofmx,
                                    ncoefv,
                                    ndimen,
                                    ncoefu,
                                    ncoefv,
                                    &patnew[patnew_offset],
                                    &tbaux[iofst]);
    }

    mmarc41_(&numax, &numax, ncoefv, &tbaux[iofst], vpara1, vpara2, &tbaux[iofst], iercod);

    AdvApp2Var_MathBase::mmfmca8_(ndimen,
                                  ncoefu,
                                  ncoefv,
                                  ndimen,
                                  ncofmx,
                                  ncoefv,
                                  &tbaux[iofst],
                                  &patnew[patnew_offset]);
    goto L9900;
  }
  else
  {
    if (*upara1 == 0. && *upara2 == 1.)
    {
      mmarc41_(&numax,
               &numax,
               ncoefv,
               &patold[patold_offset],
               vpara1,
               vpara2,
               &patnew[patnew_offset],
               iercod);
    }
    else
    {
      mmarc41_(&numax,
               &numax,
               ncoefv,
               &patnew[patnew_offset],
               vpara1,
               vpara2,
               &patnew[patnew_offset],
               iercod);
    }
    goto L9999;
  }

L9900:
  if (iofst != 0)
  {
    anAdvApp2Var_SysBase.mcrdelt_(&c__8, &ksize, tbaux, &iofst, &ier);
  }
  if (ier > 0)
  {
    *iercod = 13;
  }

L9999:
  if (*iercod > 0)
  {
    AdvApp2Var_SysBase::maermsg_("MMFMCAR", iercod, 7L);
  }
  if (ibb >= 2)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMFMCAR", 7L);
  }
  return 0;
}

int AdvApp2Var_MathBase::mmfmcb5_(integer*    isenmsc,
                                  integer*    ndimax,
                                  integer*    ncf1mx,
                                  doublereal* courb1,
                                  integer*    ncoeff,
                                  integer*    ncf2mx,
                                  integer*    ndimen,
                                  doublereal* courb2,
                                  integer*    iercod)

{

  integer courb1_dim1, courb1_offset, courb2_dim1, courb2_offset, i__1, i__2;

  integer i__, nboct, nd;

  courb1_dim1   = *ndimax;
  courb1_offset = courb1_dim1 + 1;
  courb1 -= courb1_offset;
  courb2_dim1   = *ncf2mx;
  courb2_offset = courb2_dim1 + 1;
  courb2 -= courb2_offset;

  if (*ndimen > *ndimax || *ncoeff > *ncf1mx || *ncoeff > *ncf2mx)
  {
    goto L9119;
  }

  if (*ndimen == 1 && *ncf1mx == *ncf2mx)
  {
    nboct = *ncf2mx << 3;
    if (*isenmsc == 1)
    {
      AdvApp2Var_SysBase::mcrfill_(&nboct, &courb1[courb1_offset], &courb2[courb2_offset]);
    }
    if (*isenmsc == -1)
    {
      AdvApp2Var_SysBase::mcrfill_(&nboct, &courb2[courb2_offset], &courb1[courb1_offset]);
    }
    *iercod = -3136;
    goto L9999;
  }

  *iercod = 0;
  if (*isenmsc == 1)
  {
    i__1 = *ndimen;
    for (nd = 1; nd <= i__1; ++nd)
    {
      i__2 = *ncoeff;
      for (i__ = 1; i__ <= i__2; ++i__)
      {
        courb2[i__ + nd * courb2_dim1] = courb1[nd + i__ * courb1_dim1];
      }
    }
  }
  else if (*isenmsc == -1)
  {
    i__1 = *ndimen;
    for (nd = 1; nd <= i__1; ++nd)
    {
      i__2 = *ncoeff;
      for (i__ = 1; i__ <= i__2; ++i__)
      {
        courb1[nd + i__ * courb1_dim1] = courb2[i__ + nd * courb2_dim1];
      }
    }
  }
  else
  {
    *iercod = 3164;
  }

  goto L9999;

L9119:
  *iercod = 3119;

L9999:
  if (*iercod != 0)
  {
    AdvApp2Var_SysBase::maermsg_("MMFMCB5", iercod, 7L);
  }
  return 0;
}

int AdvApp2Var_MathBase::mmfmtb1_(integer*    maxsz1,
                                  doublereal* table1,
                                  integer*    isize1,
                                  integer*    jsize1,
                                  integer*    maxsz2,
                                  doublereal* table2,
                                  integer*    isize2,
                                  integer*    jsize2,
                                  integer*    iercod)
{
  integer c__8 = 8;

  integer table1_dim1, table1_offset, table2_dim1, table2_offset, i__1, i__2;

  doublereal* work = nullptr;
  integer     ilong, isize, ii, jj, ier = 0;
  intptr_t    iofst = 0, iipt, jjpt;

  table1_dim1   = *maxsz1;
  table1_offset = table1_dim1 + 1;
  table1 -= table1_offset;
  table2_dim1   = *maxsz2;
  table2_offset = table2_dim1 + 1;
  table2 -= table2_offset;
  AdvApp2Var_SysBase anAdvApp2Var_SysBase;

  *iercod = 0;
  if (*isize1 > *maxsz1 || *jsize1 > *maxsz2)
  {
    goto L9100;
  }

  iofst = 0;
  isize = *maxsz2 * *isize1;
  anAdvApp2Var_SysBase.mcrrqst_(&c__8, &isize, work, &iofst, &ier);
  if (ier > 0)
  {
    goto L9200;
  }

  i__1 = *isize1;
  for (ii = 1; ii <= i__1; ++ii)
  {
    iipt = (ii - 1) * *maxsz2 + iofst;
    i__2 = *jsize1;
    for (jj = 1; jj <= i__2; ++jj)
    {
      jjpt       = iipt + (jj - 1);
      work[jjpt] = table1[ii + jj * table1_dim1];
    }
  }
  ilong = isize << 3;
  AdvApp2Var_SysBase::mcrfill_(&ilong, &work[iofst], &table2[table2_offset]);

  ii      = *isize1;
  *isize2 = *jsize1;
  *jsize2 = ii;

  goto L9999;

L9100:
  *iercod = 1;
  goto L9999;

L9200:
  *iercod = 2;
  goto L9999;

L9999:
  if (iofst != 0)
  {
    anAdvApp2Var_SysBase.mcrdelt_(&c__8, &isize, work, &iofst, &ier);
  }
  if (ier > 0)
  {
    *iercod = 2;
  }
  return 0;
}

int AdvApp2Var_MathBase::mmgaus1_(
  integer* ndimf,
  int (*bfunx)(integer* ninteg, doublereal* parame, doublereal* vfunj1, integer* iercod),

  integer*    k,
  doublereal* xd,
  doublereal* xf,
  doublereal* saux1,
  doublereal* saux2,
  doublereal* somme,
  integer*    niter,
  integer*    iercod)
{

  integer i__1, i__2;

  integer    ndeg;
  doublereal h__[20];
  integer    j;
  doublereal t, u[20], x;
  integer    idimf;
  doublereal c1x, c2x;

  --somme;
  --saux2;
  --saux1;

  AdvApp2Var_SysBase::mvriraz_(ndimf, &somme[1]);
  *iercod = 0;

  mvgaus0_(k, u, h__, &ndeg, iercod);
  if (*iercod > 0)
  {
    goto L9999;
  }

  c1x = (*xf + *xd) * .5;
  c2x = (*xf - *xd) * .5;

  i__1 = ndeg;
  for (j = 1; j <= i__1; ++j)
  {
    t = c2x * u[j - 1];

    x = c1x + t;
    (*bfunx)(ndimf, &x, &saux1[1], iercod);
    if (*iercod != 0)
    {
      goto L9999;
    }

    x = c1x - t;
    (*bfunx)(ndimf, &x, &saux2[1], iercod);
    if (*iercod != 0)
    {
      goto L9999;
    }

    i__2 = *ndimf;
    for (idimf = 1; idimf <= i__2; ++idimf)
    {
      somme[idimf] += h__[j - 1] * (saux1[idimf] + saux2[idimf]);
    }
  }

  *niter = ndeg << 1;
  i__1   = *ndimf;
  for (idimf = 1; idimf <= i__1; ++idimf)
  {
    somme[idimf] *= c2x;
  }

L9999:

  return 0;
}

int mmherm0_(doublereal* debfin, integer* iercod)
{
  integer c__576 = 576;
  integer c__6   = 6;

  integer    i__1, i__2;
  doublereal d__1;

  doublereal amat[36];
  integer    iord[2];
  doublereal prod;
  integer    iord1, iord2;
  doublereal miden[36];
  integer    ncmat;
  doublereal epspi, d1, d2;
  integer    ii, jj, pp, ncf;
  doublereal cof[6];
  integer    iof[2], ier;
  doublereal mat[36];
  integer    cot;
  doublereal abid[72];

  --debfin;

  d1 = advapp_abs(debfin[1]);
  if (d1 > (float)100.)
  {
    goto L9101;
  }

  d2 = advapp_abs(debfin[2]);
  if (d2 > (float)100.)
  {
    goto L9101;
  }

  d2 = d1 + d2;
  if (d2 < (float).01)
  {
    goto L9101;
  }

  d1 = (d__1 = debfin[2] - debfin[1], advapp_abs(d__1));
  if (d1 / d2 < (float).01)
  {
    goto L9101;
  }

  *iercod = 0;

  epspi = 1e-10;

  d1 = advapp_abs(debfin[1]) + advapp_abs(debfin[2]);
  d1 *= 16111959;

  if (debfin[1] != mmcmher_.tdebut)
  {
    goto L100;
  }
  if (debfin[2] != mmcmher_.tfinal)
  {
    goto L100;
  }
  if (d1 != mmcmher_.verifi)
  {
    goto L100;
  }

  goto L9001;

L100:

  ncmat = 36;
  AdvApp2Var_SysBase::mvriraz_(&ncmat, miden);

  for (ii = 1; ii <= 6; ++ii)
  {
    miden[ii + ii * 6 - 7] = 1.;
  }

  AdvApp2Var_SysBase::mvriraz_(&c__576, mmcmher_.cmherm);

  for (iord1 = -1; iord1 <= 2; ++iord1)
  {
    for (iord2 = -1; iord2 <= 2; ++iord2)
    {

      iord[0] = iord1;
      iord[1] = iord2;

      iof[0] = 0;
      iof[1] = iord[0] + 1;

      ncf = iord[0] + iord[1] + 2;

      for (cot = 1; cot <= 2; ++cot)
      {

        if (iord[cot - 1] > -1)
        {
          prod = 1.;
          i__1 = ncf;
          for (jj = 1; jj <= i__1; ++jj)
          {
            cof[jj - 1] = 1.;
          }
        }

        i__1 = iord[cot - 1] + 1;
        for (pp = 1; pp <= i__1; ++pp)
        {

          ii = pp + iof[cot - 1];

          prod = 1.;

          i__2 = pp - 1;
          for (jj = 1; jj <= i__2; ++jj)
          {
            mat[ii + jj * 6 - 7] = (float)0.;
          }

          i__2 = ncf;
          for (jj = pp; jj <= i__2; ++jj)
          {

            mat[ii + jj * 6 - 7] = cof[jj - 1] * prod;
            cof[jj - 1] *= jj - pp;
            prod *= debfin[cot];
          }
        }
      }

      if (ncf >= 1)
      {
        AdvApp2Var_MathBase::mmmrslwd_(&c__6, &ncf, &ncf, mat, miden, &epspi, abid, amat, &ier);
        if (ier > 0)
        {
          goto L9101;
        }
      }

      for (cot = 1; cot <= 2; ++cot)
      {
        i__1 = iord[cot - 1] + 1;
        for (pp = 1; pp <= i__1; ++pp)
        {
          i__2 = ncf;
          for (ii = 1; ii <= i__2; ++ii)
          {
            mmcmher_.cmherm[ii + (pp + (cot + ((iord1 + (iord2 << 2)) << 1)) * 3) * 6 + 155] =
              amat[ii + (pp + iof[cot - 1]) * 6 - 7];
          }
        }
      }
    }
  }

  mmcmher_.tdebut = debfin[1];
  mmcmher_.tfinal = debfin[2];

  d1              = advapp_abs(debfin[1]) + advapp_abs(debfin[2]);
  mmcmher_.verifi = d1 * 16111959;

  goto L9999;

L9101:
  *iercod = 1;
  goto L9999;

L9001:
  *iercod = -1;
  goto L9999;

L9999:

  AdvApp2Var_SysBase::maermsg_("MMHERM0", iercod, 7L);

  return 0;
}

int mmherm1_(doublereal* debfin,
             integer*    ordrmx,
             integer*    iordre,
             doublereal* hermit,
             integer*    iercod)
{

  integer hermit_dim1, hermit_dim2, hermit_offset;

  integer    nbval;
  doublereal d1;
  integer    cot;

  --debfin;
  hermit_dim1   = (*ordrmx << 1) + 2;
  hermit_dim2   = *ordrmx + 1;
  hermit_offset = hermit_dim1 * hermit_dim2 + 1;
  hermit -= hermit_offset;
  --iordre;

  *iercod = 0;

  if (*ordrmx != 2)
  {
    goto L9102;
  }

  for (cot = 1; cot <= 2; ++cot)
  {
    if (iordre[cot] < -1)
    {
      goto L9102;
    }
    if (iordre[cot] > *ordrmx)
    {
      goto L9102;
    }
  }

  d1 = advapp_abs(debfin[1]) + advapp_abs(debfin[2]);
  d1 *= 16111959;

  if (debfin[1] != mmcmher_.tdebut || debfin[2] != mmcmher_.tfinal || d1 != mmcmher_.verifi)
  {
    *iercod = -1;
    mmherm0_(&debfin[1], iercod);
    if (*iercod > 0)
    {
      goto L9101;
    }
  }

  nbval = 36;

  AdvApp2Var_SysBase::msrfill_(
    &nbval,
    &mmcmher_.cmherm[((((iordre[1] + (iordre[2] << 2)) << 1) + 1) * 3 + 1) * 6 + 156],
    &hermit[hermit_offset]);

  goto L9999;

L9101:
  *iercod = 1;
  goto L9999;

L9102:
  *iercod = 2;
  goto L9999;

L9999:

  AdvApp2Var_SysBase::maermsg_("MMHERM1", iercod, 7L);

  return 0;
}

int AdvApp2Var_MathBase::mmhjcan_(integer*    ndimen,
                                  integer*    ncourb,
                                  integer*    ncftab,
                                  integer*    orcont,
                                  integer*    ncflim,
                                  doublereal* tcbold,
                                  doublereal* tdecop,
                                  doublereal* tcbnew,
                                  integer*    iercod)

{
  integer c__2  = 2;
  integer c__21 = 21;

  integer tcbold_dim1, tcbold_dim2, tcbold_offset, tcbnew_dim1, tcbnew_dim2, tcbnew_offset, i__1,
    i__2, i__3, i__4, i__5;

  logical    ldbg;
  integer    ndeg;
  doublereal taux1[21];
  integer    d__, e, i__, k;
  doublereal mfact;
  integer    ncoeff;
  doublereal tjacap[21];
  integer    iordre[2];
  doublereal hermit[36], ctenor, bornes[2];
  integer    ier;
  integer    aux1, aux2;

  --ncftab;
  tcbnew_dim1   = *ndimen;
  tcbnew_dim2   = *ncflim;
  tcbnew_offset = tcbnew_dim1 * (tcbnew_dim2 + 1) + 1;
  tcbnew -= tcbnew_offset;
  tcbold_dim1   = *ndimen;
  tcbold_dim2   = *ncflim;
  tcbold_offset = tcbold_dim1 * (tcbold_dim2 + 1) + 1;
  tcbold -= tcbold_offset;

  ldbg = AdvApp2Var_SysBase::mnfndeb_() >= 2;
  if (ldbg)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMHJCAN", 7L);
  }
  *iercod = 0;

  bornes[0] = -1.;
  bornes[1] = 1.;

  if (*orcont > 2)
  {
    goto L9101;
  }
  if (*ncflim > 21)
  {
    goto L9101;
  }

  iordre[0] = *orcont;
  iordre[1] = *orcont;
  mmherm1_(bornes, &c__2, iordre, hermit, &ier);
  if (ier > 0)
  {
    goto L9102;
  }

  aux1 = *orcont + 1;
  aux2 = aux1 << 1;

  i__1 = *ncourb;
  for (e = 1; e <= i__1; ++e)
  {

    ctenor = (tdecop[e] - tdecop[e - 1]) / 2;
    ncoeff = ncftab[e];
    ndeg   = ncoeff - 1;
    if (ncoeff > 21)
    {
      goto L9101;
    }

    i__2 = *ndimen;
    for (d__ = 1; d__ <= i__2; ++d__)
    {

      AdvApp2Var_SysBase::mvriraz_(&ncoeff, taux1);

      i__3 = aux2;
      for (k = 1; k <= i__3; ++k)
      {
        i__4 = aux1;
        for (i__ = 1; i__ <= i__4; ++i__)
        {
          i__5  = i__ - 1;
          mfact = AdvApp2Var_MathBase::pow__di(&ctenor, &i__5);
          taux1[k - 1] +=
            (tcbold[d__ + (i__ + e * tcbold_dim2) * tcbold_dim1] * hermit[k + (i__ + 2) * 6 - 19]
             + tcbold[d__ + (i__ + aux1 + e * tcbold_dim2) * tcbold_dim1]
                 * hermit[k + (i__ + 5) * 6 - 19])
            * mfact;
        }
      }

      i__3 = ncoeff;
      for (i__ = aux2 + 1; i__ <= i__3; ++i__)
      {
        taux1[i__ - 1] = tcbold[d__ + (i__ + e * tcbold_dim2) * tcbold_dim1];
      }

      AdvApp2Var_MathBase::mmapcmp_(&minombr_.nbr[1], &c__21, &ncoeff, taux1, tjacap);
      AdvApp2Var_MathBase::mmjacan_(orcont, &ndeg, tjacap, taux1);

      i__3 = ncoeff;
      for (i__ = 1; i__ <= i__3; ++i__)
      {
        tcbnew[d__ + (i__ + e * tcbnew_dim2) * tcbnew_dim1] = taux1[i__ - 1];
      }
    }
  }

  goto L9999;

L9101:
  *iercod = 1;
  goto L9999;
L9102:
  *iercod = 2;
  goto L9999;

L9999:

  AdvApp2Var_SysBase::maermsg_("MMHJCAN", iercod, 7L);
  if (ldbg)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMHJCAN", 7L);
  }
  return 0;
}

int AdvApp2Var_MathBase::mminltt_(integer*    ncolmx,
                                  integer*    nlgnmx,
                                  doublereal* tabtri,
                                  integer*    nbrcol,
                                  integer*    nbrlgn,
                                  doublereal* ajoute,
                                  doublereal*,
                                  integer* iercod)
{

  integer tabtri_dim1, tabtri_offset, i__1, i__2;

  logical    idbg;
  integer    icol, ilgn, nlgn, noct, inser;
  doublereal epsega = 0.;
  integer    ibb;

  tabtri_dim1   = *ncolmx;
  tabtri_offset = tabtri_dim1 + 1;
  tabtri -= tabtri_offset;
  --ajoute;

  ibb  = AdvApp2Var_SysBase::mnfndeb_();
  idbg = ibb >= 3;
  if (idbg)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMINLTT", 7L);
  }

  if (*nbrlgn >= *nlgnmx)
  {
    goto L9001;
  }

  *iercod = 0;

  i__1 = *nbrlgn;
  for (ilgn = 1; ilgn <= i__1; ++ilgn)
  {
    if (tabtri[ilgn * tabtri_dim1 + 1] >= ajoute[1] - epsega)
    {
      if (tabtri[ilgn * tabtri_dim1 + 1] <= ajoute[1] + epsega)
      {
        i__2 = *nbrcol;
        for (icol = 1; icol <= i__2; ++icol)
        {
          if (tabtri[icol + ilgn * tabtri_dim1] < ajoute[icol] - epsega
              || tabtri[icol + ilgn * tabtri_dim1] > ajoute[icol] + epsega)
          {
            goto L20;
          }
        }
        goto L9999;
      }
      else
      {
        goto L30;
      }
    }
  L20:;
  }

L30:

  i__1 = *nbrlgn;
  for (ilgn = 1; ilgn <= i__1; ++ilgn)
  {
    i__2 = *nbrcol;
    for (icol = 1; icol <= i__2; ++icol)
    {
      if (tabtri[icol + ilgn * tabtri_dim1] < ajoute[icol])
      {
        goto L50;
      }
      if (tabtri[icol + ilgn * tabtri_dim1] > ajoute[icol])
      {
        goto L70;
      }
    }
  L50:;
  }

  ilgn = *nbrlgn + 1;

L70:

  inser = ilgn;
  ++(*nbrlgn);

  nlgn = *nbrlgn - inser;
  if (nlgn > 0)
  {
    noct = (*ncolmx << 3) * nlgn;
    AdvApp2Var_SysBase::mcrfill_(&noct,
                                 &tabtri[inser * tabtri_dim1 + 1],
                                 &tabtri[(inser + 1) * tabtri_dim1 + 1]);
  }

  noct = *nbrcol << 3;
  AdvApp2Var_SysBase::mcrfill_(&noct, &ajoute[1], &tabtri[inser * tabtri_dim1 + 1]);

  goto L9999;

L9001:
  *iercod = 1;

L9999:
  if (*iercod != 0)
  {
    AdvApp2Var_SysBase::maermsg_("MMINLTT", iercod, 7L);
  }
  if (idbg)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMINLTT", 7L);
  }
  return 0;
}

int AdvApp2Var_MathBase::mmjacan_(const integer* ideriv,
                                  integer*       ndeg,
                                  doublereal*    poljac,
                                  doublereal*    polcan)
{

  integer poljac_dim1, i__1, i__2;

  integer    iptt, i__, j, ibb;
  doublereal bid;

  poljac_dim1 = *ndeg / 2 + 1;

  ibb = AdvApp2Var_SysBase::mnfndeb_();
  if (ibb >= 5)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMJACAN", 7L);
  }

  i__1 = *ndeg / 2;
  for (i__ = 0; i__ <= i__1; ++i__)
  {
    bid  = 0.;
    iptt = i__ * 31 - (i__ + 1) * i__ / 2 + 1;
    i__2 = *ndeg / 2;
    for (j = i__; j <= i__2; ++j)
    {
      bid += mmjcobi_.plgcan[iptt + j + *ideriv * 992 + 991] * poljac[j];
    }
    polcan[i__ * 2] = bid;
  }

  if (*ndeg == 0)
  {
    goto L9999;
  }

  i__1 = (*ndeg - 1) / 2;
  for (i__ = 0; i__ <= i__1; ++i__)
  {
    bid  = 0.;
    iptt = i__ * 31 - (i__ + 1) * i__ / 2 + 1;
    i__2 = (*ndeg - 1) / 2;
    for (j = i__; j <= i__2; ++j)
    {
      bid += mmjcobi_.plgcan[iptt + j + ((*ideriv << 1) + 1) * 496 + 991] * poljac[j + poljac_dim1];
    }
    polcan[(i__ << 1) + 1] = bid;
  }

L9999:
  if (ibb >= 5)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMJACAN", 7L);
  }
  return 0;
}

int AdvApp2Var_MathBase::mmjaccv_(const integer*    ncoef,
                                  const integer*    ndim,
                                  const integer*    ider,
                                  const doublereal* crvlgd,
                                  doublereal*       polaux,
                                  doublereal*       crvcan)

{

  static char nomprg[8 + 1] = "MMJACCV ";

  integer crvlgd_dim1, crvlgd_offset, crvcan_dim1, crvcan_offset, polaux_dim1, i__1, i__2;

  integer ndeg, i__, nd, ii, ibb;

  polaux_dim1   = (*ncoef - 1) / 2 + 1;
  crvcan_dim1   = *ncoef - 1 + 1;
  crvcan_offset = crvcan_dim1;
  crvcan -= crvcan_offset;
  crvlgd_dim1   = *ncoef - 1 + 1;
  crvlgd_offset = crvlgd_dim1;
  crvlgd -= crvlgd_offset;

  ibb = AdvApp2Var_SysBase::mnfndeb_();
  if (ibb >= 3)
  {
    AdvApp2Var_SysBase::mgenmsg_(nomprg, 6L);
  }

  ndeg = *ncoef - 1;

  i__1 = *ndim;
  for (nd = 1; nd <= i__1; ++nd)
  {

    ii   = 0;
    i__2 = ndeg / 2;
    for (i__ = 0; i__ <= i__2; ++i__)
    {
      polaux[i__] = crvlgd[ii + nd * crvlgd_dim1];
      ii += 2;
    }

    ii = 1;
    if (ndeg >= 1)
    {
      i__2 = (ndeg - 1) / 2;
      for (i__ = 0; i__ <= i__2; ++i__)
      {
        polaux[i__ + polaux_dim1] = crvlgd[ii + nd * crvlgd_dim1];
        ii += 2;
      }
    }

    AdvApp2Var_MathBase::mmjacan_(ider, &ndeg, polaux, &crvcan[nd * crvcan_dim1]);
  }

  return 0;
}

int mmloncv_(integer*    ndimax,
             integer*    ndimen,
             integer*    ncoeff,
             doublereal* courbe,
             doublereal* tdebut,
             doublereal* tfinal,
             doublereal* xlongc,
             integer*    iercod)

{

  integer kgar = 0;

  integer courbe_dim1, courbe_offset, i__1, i__2;

  doublereal tran;
  integer    ngaus = 0;
  doublereal c1, c2, d1, d2, wgaus[20] = {0.}, uroot[20] = {0.}, x1, x2, dd;
  integer    ii, jj, kk;
  doublereal som;
  doublereal der1, der2;

  courbe_dim1   = *ndimax;
  courbe_offset = courbe_dim1 + 1;
  courbe -= courbe_offset;

  *iercod = 999999;
  *xlongc = 0.;

  if (*tdebut == *tfinal)
  {
    *iercod = 0;
    goto L9900;
  }

  if (*ndimen <= 0 || *ncoeff <= 0)
  {
    *iercod = 1;
    goto L9900;
  }

  kk = *ncoeff / 4 + 1;
  kk = advapp_min(kk, 10);

  if (kk != kgar)
  {
    mvgaus0_(&kk, uroot, wgaus, &ngaus, iercod);
    if (*iercod > 0)
    {
      kgar    = 0;
      *iercod = 2;
      goto L9900;
    }
    kgar = kk;
  }

  c1 = (*tfinal + *tdebut) * .5;
  c2 = (*tfinal - *tdebut) * .5;

  som = 0.;

  i__1 = ngaus;
  for (jj = 1; jj <= i__1; ++jj)
  {

    tran = c2 * uroot[jj - 1];
    x1   = c1 + tran;
    x2   = c1 - tran;

    der1 = 0.;
    der2 = 0.;
    i__2 = *ndimen;
    for (kk = 1; kk <= i__2; ++kk)
    {
      d1 = (*ncoeff - 1) * courbe[kk + *ncoeff * courbe_dim1];
      d2 = d1;
      for (ii = *ncoeff - 1; ii >= 2; --ii)
      {
        dd = (ii - 1) * courbe[kk + ii * courbe_dim1];
        d1 = d1 * x1 + dd;
        d2 = d2 * x2 + dd;
      }
      der1 += d1 * d1;
      der2 += d2 * d2;
    }

    som += wgaus[jj - 1] * c2 * (sqrt(der1) + sqrt(der2));
  }

  *xlongc = som;

  *iercod = 0;

L9900:

  if (*iercod != 0)
  {
    AdvApp2Var_SysBase::maermsg_("MMLONCV", iercod, 7L);
  }
  return 0;
}

int AdvApp2Var_MathBase::mmpobas_(doublereal* tparam,
                                  integer*    iordre,
                                  integer*    ncoeff,
                                  integer*    nderiv,
                                  doublereal* valbas,
                                  integer*    iercod)

{
  integer c__2 = 2;
  integer c__1 = 1;

  doublereal moin11[2] = {-1., 1.};

  integer valbas_dim1 = 0, i__1 = 0;

  doublereal                     vjacc[80] = {};
  doublereal                     herm[24]  = {};
  NCollection_Array1<doublereal> vjac(vjacc[0], 1, 80);
  integer                        iord[2] = {};
  doublereal                     wval[4] = {};
  integer                        nwcof = 0, iunit = 0;
  doublereal                     wpoly[7] = {};
  integer                        ii = 0, jj = 0, iorjac = 0;
  doublereal                     hermit[36] = {};
  integer                        kk1 = 0, kk2 = 0, kk3 = 0;
  integer                        khe = 0, ier = 0;

  valbas_dim1 = *ncoeff;
  --valbas;

  *iercod = 0;

  if (*nderiv > 3)
  {
    goto L9101;
  }
  if (*ncoeff > 20)
  {
    goto L9101;
  }
  if (*iordre > 2)
  {
    goto L9101;
  }

  iord[0] = *iordre;
  iord[1] = *iordre;
  iorjac  = (*iordre + 1) << 1;

  if (*iordre >= 0)
  {
    mmherm1_(moin11, &c__2, iord, hermit, &ier);
    if (ier > 0)
    {
      goto L9102;
    }
  }

  jj    = 1;
  iunit = *nderiv + 1;
  khe   = (*iordre + 1) * iunit;

  if (*nderiv > 0)
  {

    i__1 = *iordre;
    for (ii = 0; ii <= i__1; ++ii)
    {
      mmdrvcb_(nderiv, &c__1, &iorjac, &hermit[(ii + 3) * 6 - 18], tparam, &herm[jj - 1], &ier);
      if (ier > 0)
      {
        goto L9102;
      }

      mmdrvcb_(nderiv,
               &c__1,
               &iorjac,
               &hermit[(ii + 6) * 6 - 18],
               tparam,
               &herm[jj + khe - 1],
               &ier);
      if (ier > 0)
      {
        goto L9102;
      }
      jj += iunit;
    }
  }
  else
  {

    i__1 = *iordre;
    for (ii = 0; ii <= i__1; ++ii)
    {
      AdvApp2Var_MathBase::mmpocrb_(&c__1,
                                    &iorjac,
                                    &hermit[(ii + 3) * 6 - 18],
                                    &c__1,
                                    tparam,
                                    &herm[jj - 1]);

      AdvApp2Var_MathBase::mmpocrb_(&c__1,
                                    &iorjac,
                                    &hermit[(ii + 6) * 6 - 18],
                                    &c__1,
                                    tparam,
                                    &herm[jj + khe - 1]);
      jj += iunit;
    }
  }

  ii = *ncoeff - iorjac;

  mmpojac_(tparam, &iorjac, &ii, nderiv, vjac, &ier);
  if (ier > 0)
  {
    goto L9102;
  }

  i__1  = iorjac + 1;
  nwcof = advapp_max(i__1, 1);
  AdvApp2Var_SysBase::mvriraz_(&nwcof, wpoly);
  wpoly[0] = 1.;
  if (*iordre == 2)
  {
    wpoly[2] = -3.;
    wpoly[4] = 3.;
    wpoly[6] = -1.;
  }
  else if (*iordre == 1)
  {
    wpoly[2] = -2.;
    wpoly[4] = 1.;
  }
  else if (*iordre == 0)
  {
    wpoly[2] = -1.;
  }

  mmdrvcb_(nderiv, &c__1, &nwcof, wpoly, tparam, wval, &ier);
  if (ier > 0)
  {
    goto L9102;
  }

  kk1 = *ncoeff - iorjac;
  kk2 = kk1 << 1;
  kk3 = kk1 * 3;

  jj   = 1;
  i__1 = iorjac;
  for (ii = 1; ii <= i__1; ++ii)
  {
    valbas[ii] = herm[jj - 1];
    jj += iunit;
  }

  i__1 = kk1;
  for (ii = 1; ii <= i__1; ++ii)
  {
    valbas[ii + iorjac] = wval[0] * vjac(ii);
  }

  if (*nderiv >= 1)
  {
    jj   = 2;
    i__1 = iorjac;
    for (ii = 1; ii <= i__1; ++ii)
    {
      valbas[ii + valbas_dim1] = herm[jj - 1];
      jj += iunit;
    }

    i__1 = kk1;
    for (ii = 1; ii <= i__1; ++ii)
    {
      valbas[ii + iorjac + valbas_dim1] = wval[0] * vjac(ii + kk1) + wval[1] * vjac(ii);
    }
  }

  if (*nderiv >= 2)
  {
    jj   = 3;
    i__1 = iorjac;
    for (ii = 1; ii <= i__1; ++ii)
    {
      valbas[ii + (valbas_dim1 << 1)] = herm[jj - 1];
      jj += iunit;
    }

    i__1 = kk1;
    for (ii = 1; ii <= i__1; ++ii)
    {
      valbas[ii + iorjac + (valbas_dim1 << 1)] =
        wval[0] * vjac(ii + kk2) + wval[1] * 2 * vjac(ii + kk1) + wval[2] * vjac(ii);
    }
  }

  if (*nderiv >= 3)
  {
    jj   = 4;
    i__1 = iorjac;
    for (ii = 1; ii <= i__1; ++ii)
    {
      valbas[ii + valbas_dim1 * 3] = herm[jj - 1];
      jj += iunit;
    }

    i__1 = kk1;
    for (ii = 1; ii <= i__1; ++ii)
    {
      valbas[ii + iorjac + valbas_dim1 * 3] = wval[0] * vjac(ii + kk3)
                                              + wval[1] * 3 * vjac(ii + kk2)
                                              + wval[2] * 3 * vjac(ii + kk1) + wval[3] * vjac(ii);
    }
  }

  goto L9999;

L9101:
  *iercod = 1;
  goto L9999;

L9102:
  *iercod = 2;

L9999:

  if (*iercod > 0)
  {
    AdvApp2Var_SysBase::maermsg_("MMPOBAS", iercod, 7L);
  }
  return 0;
}

int AdvApp2Var_MathBase::mmpocrb_(integer*    ndimax,
                                  integer*    ncoeff,
                                  doublereal* courbe,
                                  integer*    ndim,
                                  doublereal* tparam,
                                  doublereal* pntcrb)

{

  integer courbe_dim1, courbe_offset, i__1, i__2;

  integer ncof2;
  integer isize, nd, kcf, ncf;

  courbe_dim1   = *ndimax;
  courbe_offset = courbe_dim1 + 1;
  courbe -= courbe_offset;
  --pntcrb;

  isize = *ndim << 3;
  AdvApp2Var_SysBase::miraz_(&isize, &pntcrb[1]);

  if (*ncoeff <= 0)
  {
    goto L9999;
  }

  if (*ndim == 3 && *ndimax == 3)
  {
    mvpscr3_(ncoeff, &courbe[courbe_offset], tparam, &pntcrb[1]);
  }
  else if (*ndim == 2 && *ndimax == 2)
  {
    mvpscr2_(ncoeff, &courbe[courbe_offset], tparam, &pntcrb[1]);
  }
  else if (*tparam == 0.)
  {
    i__1 = *ndim;
    for (nd = 1; nd <= i__1; ++nd)
    {
      pntcrb[nd] = courbe[nd + courbe_dim1];
    }
  }
  else if (*tparam == 1.)
  {
    i__1 = *ncoeff;
    for (ncf = 1; ncf <= i__1; ++ncf)
    {
      i__2 = *ndim;
      for (nd = 1; nd <= i__2; ++nd)
      {
        pntcrb[nd] += courbe[nd + ncf * courbe_dim1];
      }
    }
  }
  else
  {
    ncof2 = *ncoeff + 2;
    i__1  = *ndim;
    for (nd = 1; nd <= i__1; ++nd)
    {
      i__2 = *ncoeff;
      for (ncf = 2; ncf <= i__2; ++ncf)
      {
        kcf        = ncof2 - ncf;
        pntcrb[nd] = (pntcrb[nd] + courbe[nd + kcf * courbe_dim1]) * *tparam;
      }
      pntcrb[nd] += courbe[nd + courbe_dim1];
    }
  }

L9999:
  return 0;
}

int AdvApp2Var_MathBase::mmmpocur_(integer*    ncofmx,
                                   integer*    ndim,
                                   integer*    ndeg,
                                   doublereal* courbe,
                                   doublereal* tparam,
                                   doublereal* tabval)

{

  integer courbe_dim1, courbe_offset, i__1;

  integer    i__, nd;
  doublereal fu;

  --tabval;
  courbe_dim1   = *ncofmx;
  courbe_offset = courbe_dim1 + 1;
  courbe -= courbe_offset;

  if (*ndeg < 1)
  {
    i__1 = *ndim;
    for (nd = 1; nd <= i__1; ++nd)
    {
      tabval[nd] = 0.;
    }
  }
  else
  {
    i__1 = *ndim;
    for (nd = 1; nd <= i__1; ++nd)
    {
      fu = courbe[*ndeg + nd * courbe_dim1];
      for (i__ = *ndeg - 1; i__ >= 1; --i__)
      {
        fu = fu * *tparam + courbe[i__ + nd * courbe_dim1];
      }
      tabval[nd] = fu;
    }
  }
  return 0;
}

int mmpojac_(doublereal*                     tparam,
             integer*                        iordre,
             integer*                        ncoeff,
             integer*                        nderiv,
             NCollection_Array1<doublereal>& valjac,
             integer*                        iercod)

{
  integer c__2 = 2;

  integer valjac_dim1, i__1, i__2;

  doublereal cofa, cofb, denom, tnorm[100];
  integer    ii, jj, kk1, kk2;
  doublereal aux1, aux2;

  valjac_dim1 = *ncoeff;

  *iercod = 0;

  if (*nderiv > 3)
  {
    goto L9101;
  }
  if (*ncoeff > 100)
  {
    goto L9101;
  }

  i__1 = *ncoeff;
  for (ii = 1; ii <= i__1; ++ii)
  {
    kk1  = ii - 1;
    aux2 = 1.;
    i__2 = *iordre;
    for (jj = 1; jj <= i__2; ++jj)
    {
      aux2 = aux2 * (doublereal)(kk1 + *iordre + jj) / (doublereal)(kk1 + jj);
    }
    i__2          = (*iordre << 1) + 1;
    tnorm[ii - 1] = sqrt(aux2 * (kk1 * 2. + (*iordre << 1) + 1) / pow__ii(&c__2, &i__2));
  }

  valjac(1) = 1.;
  aux1      = (doublereal)(*iordre + 1);
  valjac(2) = aux1 * *tparam;

  if (*nderiv >= 1)
  {
    valjac(valjac_dim1 + 1) = 0.;
    valjac(valjac_dim1 + 2) = aux1;

    if (*nderiv >= 2)
    {
      valjac((valjac_dim1 << 1) + 1) = 0.;
      valjac((valjac_dim1 << 1) + 2) = 0.;

      if (*nderiv >= 3)
      {
        valjac(valjac_dim1 * 3 + 1) = 0.;
        valjac(valjac_dim1 * 3 + 2) = 0.;
      }
    }
  }

  i__1 = *ncoeff;
  for (ii = 3; ii <= i__1; ++ii)
  {

    kk1   = ii - 1;
    kk2   = ii - 2;
    aux1  = (doublereal)(*iordre + kk2);
    aux2  = aux1 * 2;
    cofa  = aux2 * (aux2 + 1) * (aux2 + 2);
    cofb  = (aux2 + 2) * -2. * aux1 * aux1;
    denom = kk1 * 2. * (kk2 + (*iordre << 1) + 1) * aux2;
    denom = 1. / denom;

    valjac(ii) = (cofa * *tparam * valjac(kk1) + cofb * valjac(kk2)) * denom;

    if (*nderiv >= 1)
    {
      valjac(ii + valjac_dim1) = (cofa * *tparam * valjac(kk1 + valjac_dim1) + cofa * valjac(kk1)
                                  + cofb * valjac(kk2 + valjac_dim1))
                                 * denom;

      if (*nderiv >= 2)
      {
        valjac(ii + (valjac_dim1 << 1)) =
          (cofa * *tparam * valjac(kk1 + (valjac_dim1 << 1)) + cofa * 2 * valjac(kk1 + valjac_dim1)
           + cofb * valjac(kk2 + (valjac_dim1 << 1)))
          * denom;
      }

      if (*nderiv >= 3)
      {
        valjac(ii + valjac_dim1 * 3) =
          (cofa * *tparam * valjac(kk1 + valjac_dim1 * 3)
           + cofa * 3 * valjac(kk1 + (valjac_dim1 << 1)) + cofb * valjac(kk2 + valjac_dim1 * 3))
          * denom;
      }
    }
  }

  i__1 = *ncoeff;
  for (ii = 1; ii <= i__1; ++ii)
  {
    i__2 = *nderiv;
    for (jj = 0; jj <= i__2; ++jj)
    {
      valjac(ii + jj * valjac_dim1) = tnorm[ii - 1] * valjac(ii + jj * valjac_dim1);
    }
  }

  goto L9999;

L9101:
  *iercod = 1;
  goto L9999;

L9999:

  if (*iercod > 0)
  {
    AdvApp2Var_SysBase::maermsg_("MMPOJAC", iercod, 7L);
  }
  return 0;
}

int AdvApp2Var_MathBase::mmposui_(integer* dimmat,
                                  integer*,
                                  integer* aposit,
                                  integer* posuiv,
                                  integer* iercod)

{

  integer i__1, i__2;

  logical ldbg;
  integer imin, jmin, i__, j, k;
  logical trouve;

  aposit -= 3;
  --posuiv;

  ldbg = AdvApp2Var_SysBase::mnfndeb_() >= 2;
  if (ldbg)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMPOSUI", 7L);
  }
  *iercod = 0;

  i__1 = *dimmat;
  for (i__ = 1; i__ <= i__1; ++i__)
  {
    jmin = i__ - aposit[(i__ << 1) + 1];
    i__2 = i__;
    for (j = jmin; j <= i__2; ++j)
    {
      imin   = i__ + 1;
      trouve = FALSE_;
      while (!trouve && imin <= *dimmat)
      {
        if (imin - aposit[(imin << 1) + 1] <= j)
        {
          trouve = TRUE_;
        }
        else
        {
          ++imin;
        }
      }
      k = aposit[(i__ << 1) + 2] - i__ + j;
      if (trouve)
      {
        posuiv[k] = imin;
      }
      else
      {
        posuiv[k] = -1;
      }
    }
  }

  goto L9999;

L9999:

  AdvApp2Var_SysBase::maermsg_("MMPOSUI", iercod, 7L);
  if (ldbg)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMPOSUI", 7L);
  }
  return 0;
}

int AdvApp2Var_MathBase::mmresol_(integer*    hdimen,
                                  integer*    gdimen,
                                  integer*    hnstoc,
                                  integer*    gnstoc,
                                  integer*    mnstoc,
                                  doublereal* matsyh,
                                  doublereal* matsyg,
                                  doublereal* vecsyh,
                                  doublereal* vecsyg,
                                  integer*    hposit,
                                  integer*    hposui,
                                  integer*    gposit,
                                  integer*    mmposui,
                                  integer*    mposit,
                                  doublereal* vecsol,
                                  integer*    iercod)

{
  integer c__100 = 100;

  integer i__1, i__2;

  logical     ldbg;
  doublereal* mcho = nullptr;
  integer     jmin, jmax, i__, j, k, l;
  intptr_t    iofv1, iofv2, iofv3, iofv4;
  doublereal *v1 = nullptr, *v2 = nullptr, *v3 = nullptr, *v4 = nullptr;
  integer     deblig, dimhch;
  doublereal* hchole = nullptr;
  intptr_t    iofmch, iofmam, iofhch;
  doublereal* matsym = nullptr;
  integer     ier;
  integer     aux;

  --vecsol;
  hposit -= 3;
  --vecsyh;
  --hposui;
  --matsyh;
  --matsyg;
  --vecsyg;
  gposit -= 4;
  --mmposui;
  mposit -= 3;

  ldbg = AdvApp2Var_SysBase::mnfndeb_() >= 2;
  if (ldbg)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMRESOL", 7L);
  }
  *iercod = 0;
  iofhch  = 0;
  iofv1   = 0;
  iofv2   = 0;
  iofv3   = 0;
  iofv4   = 0;
  iofmam  = 0;
  iofmch  = 0;

  AdvApp2Var_SysBase anAdvApp2Var_SysBase;
  anAdvApp2Var_SysBase.macrar8_(hdimen, &c__100, v1, &iofv1, &ier);
  if (ier > 0)
  {
    goto L9102;
  }
  dimhch = hposit[(*hdimen << 1) + 2];
  anAdvApp2Var_SysBase.macrar8_(&dimhch, &c__100, hchole, &iofhch, &ier);
  if (ier > 0)
  {
    goto L9102;
  }

  mmchole_(hnstoc, hdimen, &matsyh[1], &hposit[3], &hposui[1], &hchole[iofhch], &ier);
  if (ier > 0)
  {
    goto L9101;
  }
  mmrslss_(hnstoc, hdimen, &hchole[iofhch], &hposit[3], &hposui[1], &vecsyh[1], &v1[iofv1], &ier);
  if (ier > 0)
  {
    goto L9102;
  }

  if (*gdimen > 0)
  {

    anAdvApp2Var_SysBase.macrar8_(gdimen, &c__100, v2, &iofv2, &ier);
    if (ier > 0)
    {
      goto L9102;
    }
    anAdvApp2Var_SysBase.macrar8_(hdimen, &c__100, v3, &iofv3, &ier);
    if (ier > 0)
    {
      goto L9102;
    }
    anAdvApp2Var_SysBase.macrar8_(gdimen, &c__100, v4, &iofv4, &ier);
    if (ier > 0)
    {
      goto L9102;
    }
    anAdvApp2Var_SysBase.macrar8_(mnstoc, &c__100, matsym, &iofmam, &ier);
    if (ier > 0)
    {
      goto L9102;
    }

    deblig = 1;
    mmatvec_(gdimen, hdimen, &gposit[4], gnstoc, &matsyg[1], &v1[iofv1], &deblig, &v2[iofv2], &ier);
    if (ier > 0)
    {
      goto L9101;
    }
    i__1 = *gdimen;
    for (i__ = 1; i__ <= i__1; ++i__)
    {
      v2[i__ + iofv2 - 1] -= vecsyg[i__];
    }

    i__1 = *gdimen;
    for (i__ = 1; i__ <= i__1; ++i__)
    {
      AdvApp2Var_SysBase::mvriraz_(hdimen, &v1[iofv1]);
      AdvApp2Var_SysBase::mvriraz_(hdimen, &v3[iofv3]);
      AdvApp2Var_SysBase::mvriraz_(gdimen, &v4[iofv4]);
      jmin = gposit[i__ * 3 + 3];
      jmax = gposit[i__ * 3 + 1] + gposit[i__ * 3 + 3] - 1;
      aux  = gposit[i__ * 3 + 2] - gposit[i__ * 3 + 1] - jmin + 1;
      i__2 = jmax;
      for (j = jmin; j <= i__2; ++j)
      {
        k                 = j + aux;
        v1[j + iofv1 - 1] = matsyg[k];
      }
      mmrslss_(hnstoc,
               hdimen,
               &hchole[iofhch],
               &hposit[3],
               &hposui[1],
               &v1[iofv1],
               &v3[iofv3],
               &ier);
      if (ier > 0)
      {
        goto L9101;
      }

      deblig = i__;
      mmatvec_(gdimen,
               hdimen,
               &gposit[4],
               gnstoc,
               &matsyg[1],
               &v3[iofv3],
               &deblig,
               &v4[iofv4],
               &ier);
      if (ier > 0)
      {
        goto L9101;
      }

      k                      = mposit[(i__ << 1) + 2];
      matsym[k + iofmam - 1] = v4[i__ + iofv4 - 1];
      while (mmposui[k] > 0)
      {
        l                      = mmposui[k];
        k                      = mposit[(l << 1) + 2] - l + i__;
        matsym[k + iofmam - 1] = v4[l + iofv4 - 1];
      }
    }

    AdvApp2Var_SysBase::mvriraz_(gdimen, &v4[iofv4]);
    anAdvApp2Var_SysBase.macrar8_(mnstoc, &c__100, mcho, &iofmch, &ier);
    if (ier > 0)
    {
      goto L9102;
    }
    mmchole_(mnstoc, gdimen, &matsym[iofmam], &mposit[3], &mmposui[1], &mcho[iofmch], &ier);
    if (ier > 0)
    {
      goto L9101;
    }
    mmrslss_(mnstoc, gdimen, &mcho[iofmch], &mposit[3], &mmposui[1], &v2[iofv2], &v4[iofv4], &ier);
    if (ier > 0)
    {
      goto L9102;
    }

    AdvApp2Var_SysBase::mvriraz_(hdimen, &v1[iofv1]);
    mmtmave_(gdimen, hdimen, &gposit[4], gnstoc, &matsyg[1], &v4[iofv4], &v1[iofv1], &ier);
    if (ier > 0)
    {
      goto L9101;
    }
    i__1 = *hdimen;
    for (i__ = 1; i__ <= i__1; ++i__)
    {
      v1[i__ + iofv1 - 1] = vecsyh[i__] - v1[i__ + iofv1 - 1];
    }

    mmrslss_(hnstoc, hdimen, &hchole[iofhch], &hposit[3], &hposui[1], &v1[iofv1], &vecsol[1], &ier);
    if (ier > 0)
    {
      goto L9102;
    }
  }
  else
  {
    i__1 = *hdimen;
    for (i__ = 1; i__ <= i__1; ++i__)
    {
      vecsol[i__] = v1[i__ + iofv1 - 1];
    }
  }

  goto L9999;

L9101:
  *iercod = 1;
  goto L9999;

L9102:
  AdvApp2Var_SysBase::mswrdbg_("MMRESOL : PROBLEM WITH DIMMAT", 30L);
  *iercod = 2;

L9999:

  anAdvApp2Var_SysBase.macrdr8_(hdimen, &c__100, v1, &iofv1, &ier);
  if (*iercod == 0 && ier > 0)
  {
    *iercod = 3;
  }
  anAdvApp2Var_SysBase.macrdr8_(&dimhch, &c__100, hchole, &iofhch, &ier);
  if (*iercod == 0 && ier > 0)
  {
    *iercod = 3;
  }
  anAdvApp2Var_SysBase.macrdr8_(gdimen, &c__100, v2, &iofv2, &ier);
  if (*iercod == 0 && ier > 0)
  {
    *iercod = 3;
  }
  anAdvApp2Var_SysBase.macrdr8_(hdimen, &c__100, v3, &iofv3, &ier);
  if (*iercod == 0 && ier > 0)
  {
    *iercod = 3;
  }
  anAdvApp2Var_SysBase.macrdr8_(gdimen, &c__100, v4, &iofv4, &ier);
  if (*iercod == 0 && ier > 0)
  {
    *iercod = 3;
  }
  anAdvApp2Var_SysBase.macrdr8_(mnstoc, &c__100, matsym, &iofmam, &ier);
  if (*iercod == 0 && ier > 0)
  {
    *iercod = 3;
  }
  anAdvApp2Var_SysBase.macrdr8_(mnstoc, &c__100, mcho, &iofmch, &ier);
  if (*iercod == 0 && ier > 0)
  {
    *iercod = 3;
  }

  AdvApp2Var_SysBase::maermsg_("MMRESOL", iercod, 7L);
  if (ldbg)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMRESOL", 7L);
  }
  return 0;
}

int mmrslss_(integer*,
             integer*    dimens,
             doublereal* smatri,
             integer*    sposit,
             integer*    posuiv,
             doublereal* mscnmbr,
             doublereal* soluti,
             integer*    iercod)
{

  integer i__1, i__2;

  logical    ldbg;
  integer    i__, j;
  doublereal somme;
  integer    pointe, ptcour;

  --posuiv;
  --smatri;
  --soluti;
  --mscnmbr;
  sposit -= 3;

  ldbg = AdvApp2Var_SysBase::mnfndeb_() >= 4;
  if (ldbg)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMRSLSS", 7L);
  }
  *iercod = 0;

  i__1 = *dimens;
  for (i__ = 1; i__ <= i__1; ++i__)
  {

    pointe = sposit[(i__ << 1) + 2];
    somme  = 0.;
    i__2   = i__ - 1;
    for (j = i__ - sposit[(i__ << 1) + 1]; j <= i__2; ++j)
    {
      somme += smatri[pointe - (i__ - j)] * soluti[j];
    }

    soluti[i__] = (mscnmbr[i__] - somme) / smatri[pointe];
  }

  for (i__ = *dimens; i__ >= 1; --i__)
  {

    pointe = sposit[(i__ << 1) + 2];
    j      = posuiv[pointe];
    somme  = 0.;
    while (j > 0)
    {
      ptcour = sposit[(j << 1) + 2] - (j - i__);
      somme += smatri[ptcour] * soluti[j];
      j = posuiv[ptcour];
    }

    soluti[i__] = (soluti[i__] - somme) / smatri[pointe];
  }

  goto L9999;

L9999:

  AdvApp2Var_SysBase::maermsg_("MMRSLSS", iercod, 7L);
  if (ldbg)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMRSLSS", 7L);
  }
  return 0;
}

int mmrslw_(integer*    normax,
            integer*    nordre,
            integer*    ndimen,
            doublereal* epspiv,
            doublereal* abmatr,
            doublereal* xmatri,
            integer*    iercod)
{

  integer    abmatr_dim1, abmatr_offset, xmatri_dim1, xmatri_offset, i__1, i__2, i__3;
  doublereal d__1;

  integer    kpiv;
  doublereal pivot;
  integer    ii, jj, kk;
  doublereal akj;

  xmatri_dim1   = *normax;
  xmatri_offset = xmatri_dim1 + 1;
  xmatri -= xmatri_offset;
  abmatr_dim1   = *nordre + *ndimen;
  abmatr_offset = abmatr_dim1 + 1;
  abmatr -= abmatr_offset;

  *iercod = 0;

  i__1 = *nordre;
  for (kk = 1; kk <= i__1; ++kk)
  {

    pivot = *epspiv;
    kpiv  = 0;
    i__2  = *nordre;
    for (jj = kk; jj <= i__2; ++jj)
    {
      akj = (d__1 = abmatr[kk + jj * abmatr_dim1], advapp_abs(d__1));
      if (akj > pivot)
      {
        pivot = akj;
        kpiv  = jj;
      }
    }
    if (kpiv == 0)
    {
      goto L9900;
    }

    if (kpiv != kk)
    {
      i__2 = *nordre + *ndimen;
      for (jj = kk; jj <= i__2; ++jj)
      {
        akj                             = abmatr[jj + kk * abmatr_dim1];
        abmatr[jj + kk * abmatr_dim1]   = abmatr[jj + kpiv * abmatr_dim1];
        abmatr[jj + kpiv * abmatr_dim1] = akj;
      }
    }

    pivot = -abmatr[kk + kk * abmatr_dim1];
    i__2  = *nordre;
    for (ii = kk + 1; ii <= i__2; ++ii)
    {
      akj  = abmatr[kk + ii * abmatr_dim1] / pivot;
      i__3 = *nordre + *ndimen;
      for (jj = kk + 1; jj <= i__3; ++jj)
      {
        abmatr[jj + ii * abmatr_dim1] += akj * abmatr[jj + kk * abmatr_dim1];
      }
    }
  }

  for (kk = *nordre; kk >= 1; --kk)
  {
    pivot = abmatr[kk + kk * abmatr_dim1];
    i__1  = *ndimen;
    for (ii = 1; ii <= i__1; ++ii)
    {
      akj  = abmatr[ii + *nordre + kk * abmatr_dim1];
      i__2 = *nordre;
      for (jj = kk + 1; jj <= i__2; ++jj)
      {
        akj -= abmatr[jj + kk * abmatr_dim1] * xmatri[jj + ii * xmatri_dim1];
      }
      xmatri[kk + ii * xmatri_dim1] = akj / pivot;
    }
  }
  goto L9999;

L9900:
  *iercod = 1;

L9999:
  if (*iercod > 0)
  {
    AdvApp2Var_SysBase::maermsg_("MMRSLW ", iercod, 7L);
  }

  return 0;
}

int AdvApp2Var_MathBase::mmmrslwd_(integer*    normax,
                                   integer*    nordre,
                                   integer*    ndim,
                                   doublereal* amat,
                                   doublereal* bmat,
                                   doublereal* epspiv,
                                   doublereal* aaux,
                                   doublereal* xmat,
                                   integer*    iercod)

{

  integer amat_dim1, amat_offset, bmat_dim1, bmat_offset, xmat_dim1, xmat_offset, aaux_dim1,
    aaux_offset, i__1, i__2;

  integer i__, j;
  integer ibb;

  amat_dim1   = *normax;
  amat_offset = amat_dim1 + 1;
  amat -= amat_offset;
  xmat_dim1   = *normax;
  xmat_offset = xmat_dim1 + 1;
  xmat -= xmat_offset;
  aaux_dim1   = *nordre + *ndim;
  aaux_offset = aaux_dim1 + 1;
  aaux -= aaux_offset;
  bmat_dim1   = *normax;
  bmat_offset = bmat_dim1 + 1;
  bmat -= bmat_offset;

  ibb = AdvApp2Var_SysBase::mnfndeb_();
  if (ibb >= 3)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMMRSLW", 7L);
  }

  i__1 = *nordre;
  for (i__ = 1; i__ <= i__1; ++i__)
  {
    i__2 = *nordre;
    for (j = 1; j <= i__2; ++j)
    {
      aaux[j + i__ * aaux_dim1] = amat[i__ + j * amat_dim1];
    }
  }

  i__1 = *nordre;
  for (i__ = 1; i__ <= i__1; ++i__)
  {
    i__2 = *ndim;
    for (j = 1; j <= i__2; ++j)
    {
      aaux[j + *nordre + i__ * aaux_dim1] = bmat[i__ + j * bmat_dim1];
    }
  }

  mmrslw_(normax, nordre, ndim, epspiv, &aaux[aaux_offset], &xmat[xmat_offset], iercod);

  if (*iercod != 0)
  {
    AdvApp2Var_SysBase::maermsg_("MMMRSLW", iercod, 7L);
  }
  if (ibb >= 3)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMMRSLW", 7L);
  }
  return 0;
}

int AdvApp2Var_MathBase::mmrtptt_(integer* ndglgd, doublereal* rtlegd)

{
  integer ideb, nmod2, nsur2, ilong, ibb;

  --rtlegd;

  ibb = AdvApp2Var_SysBase::mnfndeb_();
  if (ibb >= 3)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMRTPTT", 7L);
  }
  if (*ndglgd < 2)
  {
    goto L9999;
  }

  nsur2 = *ndglgd / 2;
  nmod2 = *ndglgd % 2;

  ilong = nsur2 << 3;
  ideb  = nsur2 * (nsur2 - 1) / 2 + 1;
  AdvApp2Var_SysBase::mcrfill_(&ilong, &mlgdrtl_.rootab[ideb + nmod2 * 465 - 1], &rtlegd[1]);

L9999:
  if (ibb >= 3)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMRTPTT", 7L);
  }
  return 0;
}

int AdvApp2Var_MathBase::mmsrre2_(doublereal* tparam,
                                  integer*    nbrval,
                                  doublereal* tablev,
                                  doublereal* epsil,
                                  integer*    numint,
                                  integer*    itypen,
                                  integer*    iercod)
{

  doublereal d__1;

  integer ideb, ifin, imil, ibb;

  --tablev;

  ibb = AdvApp2Var_SysBase::mnfndeb_();
  if (ibb >= 6)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMSRRE2", 7L);
  }

  *iercod = 0;
  *numint = 0;
  *itypen = 0;
  ideb    = 1;
  ifin    = *nbrval;

  if (*nbrval < 2)
  {
    *iercod = 1;
    goto L9999;
  }

  if (*tparam < tablev[1] || *tparam > tablev[*nbrval])
  {
    *iercod = 2;
    goto L9999;
  }

L1000:

  if (ideb + 1 == ifin)
  {
    *numint = ideb;
    goto L2000;
  }

  imil = (ideb + ifin) / 2;
  if (*tparam >= tablev[ideb] && *tparam <= tablev[imil])
  {
    ifin = imil;
  }
  else
  {
    ideb = imil;
  }

  goto L1000;

L2000:
  if ((d__1 = *tparam - tablev[ideb], advapp_abs(d__1)) < *epsil)
  {
    *itypen = 1;
    goto L9999;
  }
  if ((d__1 = *tparam - tablev[ifin], advapp_abs(d__1)) < *epsil)
  {
    *itypen = 2;
    goto L9999;
  }

L9999:
  if (*iercod > 0)
  {
    AdvApp2Var_SysBase::maermsg_("MMSRRE2", iercod, 7L);
  }
  if (ibb >= 6)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMSRRE2", 7L);
  }
  return 0;
}

int mmtmave_(integer* nligne,
             integer* ncolon,
             integer* gposit,
             integer*,
             doublereal* gmatri,
             doublereal* vecin,
             doublereal* vecout,
             integer*    iercod)

{

  integer i__1, i__2;

  logical    ldbg;
  integer    imin, imax, i__, j, k;
  doublereal somme;
  integer    aux;

  --vecin;
  gposit -= 4;
  --vecout;
  --gmatri;

  ldbg = AdvApp2Var_SysBase::mnfndeb_() >= 2;
  if (ldbg)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMTMAVE", 7L);
  }
  *iercod = 0;

  i__1 = *ncolon;
  for (i__ = 1; i__ <= i__1; ++i__)
  {
    somme = 0.;
    i__2  = *nligne;
    for (j = 1; j <= i__2; ++j)
    {
      imin = gposit[j * 3 + 3];
      imax = gposit[j * 3 + 1] + gposit[j * 3 + 3] - 1;
      aux  = gposit[j * 3 + 2] - gposit[j * 3 + 1] - imin + 1;
      if (imin <= i__ && i__ <= imax)
      {
        k = i__ + aux;
        somme += gmatri[k] * vecin[j];
      }
    }
    vecout[i__] = somme;
  }

  goto L9999;

L9999:

  AdvApp2Var_SysBase::maermsg_("MMTMAVE", iercod, 7L);
  if (ldbg)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMTMAVE", 7L);
  }
  return 0;
}

int mmtrpj0_(integer*    ncofmx,
             integer*    ndimen,
             integer*    ncoeff,
             doublereal* epsi3d,
             doublereal* crvlgd,
             doublereal* ycvmax,
             doublereal* epstrc,
             integer*    ncfnew)

{

  integer    crvlgd_dim1, crvlgd_offset, i__1, i__2;
  doublereal d__1;

  integer    ncut, i__;
  doublereal bidon, error;
  integer    nd;

  --ycvmax;
  crvlgd_dim1   = *ncofmx;
  crvlgd_offset = crvlgd_dim1 + 1;
  crvlgd -= crvlgd_offset;

  *ncfnew = 1;

  i__1 = *ndimen;
  for (i__ = 1; i__ <= i__1; ++i__)
  {
    ycvmax[i__] = 0.;
  }
  *epstrc = 0.;
  error   = 0.;

  ncut = 2;

  i__1 = ncut;
  for (i__ = *ncoeff; i__ >= i__1; --i__)
  {

    bidon = ((i__ - 1) * 2. + 1.) / 2.;
    bidon = sqrt(bidon);
    i__2  = *ndimen;
    for (nd = 1; nd <= i__2; ++nd)
    {
      ycvmax[nd] += (d__1 = crvlgd[i__ + nd * crvlgd_dim1], advapp_abs(d__1)) * bidon;
    }

    error = AdvApp2Var_MathBase::mzsnorm_(ndimen, &ycvmax[1]);
    if (error > *epsi3d)
    {
      *ncfnew = i__;
      goto L9999;
    }

    *epstrc = error;
  }

L9999:
  return 0;
}

int mmtrpj2_(integer*    ncofmx,
             integer*    ndimen,
             integer*    ncoeff,
             doublereal* epsi3d,
             doublereal* crvlgd,
             doublereal* ycvmax,
             doublereal* epstrc,
             integer*    ncfnew)

{

  static doublereal xmaxj[57] = {
    .9682458365518542212948163499456,   .986013297183269340427888048593603,
    1.07810420343739860362585159028115, 1.17325804490920057010925920756025,
    1.26476561266905634732910520370741, 1.35169950227289626684434056681946,
    1.43424378958284137759129885012494, 1.51281316274895465689402798226634,
    1.5878364329591908800533936587012,  1.65970112228228167018443636171226,
    1.72874345388622461848433443013543, 1.7952515611463877544077632304216,
    1.85947199025328260370244491818047, 1.92161634324190018916351663207101,
    1.98186713586472025397859895825157, 2.04038269834980146276967984252188,
    2.09730119173852573441223706382076, 2.15274387655763462685970799663412,
    2.20681777186342079455059961912859, 2.25961782459354604684402726624239,
    2.31122868752403808176824020121524, 2.36172618435386566570998793688131,
    2.41117852396114589446497298177554, 2.45964731268663657873849811095449,
    2.50718840313973523778244737914028, 2.55385260994795361951813645784034,
    2.59968631659221867834697883938297, 2.64473199258285846332860663371298,
    2.68902863641518586789566216064557, 2.73261215675199397407027673053895,
    2.77551570192374483822124304745691, 2.8177699459714315371037628127545,
    2.85940333797200948896046563785957, 2.90044232019793636101516293333324,
    2.94091151970640874812265419871976, 2.98083391718088702956696303389061,
    3.02023099621926980436221568258656, 3.05912287574998661724731962377847,
    3.09752842783622025614245706196447, 3.13546538278134559341444834866301,
    3.17295042316122606504398054547289, 3.2099992681699613513775259670214,
    3.24662674946606137764916854570219, 3.28284687953866689817670991319787,
    3.31867291347259485044591136879087, 3.35411740487202127264475726990106,
    3.38919225660177218727305224515862, 3.42390876691942143189170489271753,
    3.45827767149820230182596660024454, 3.49230918177808483937957161007792,
    3.5260130200285724149540352829756,  3.55939845146044235497103883695448,
    3.59247431368364585025958062194665, 3.62524904377393592090180712976368,
    3.65773070318071087226169680450936, 3.68992700068237648299565823810245,
    3.72184531357268220291630708234186};

  integer    crvlgd_dim1, crvlgd_offset, i__1, i__2;
  doublereal d__1;

  integer    ncut, i__;
  doublereal bidon, error;
  integer    ia, nd;
  doublereal bid, eps1;

  --ycvmax;
  crvlgd_dim1   = *ncofmx;
  crvlgd_offset = crvlgd_dim1 + 1;
  crvlgd -= crvlgd_offset;

  ia      = 2;
  *ncfnew = ia;

  i__1 = *ndimen;
  for (i__ = 1; i__ <= i__1; ++i__)
  {
    ycvmax[i__] = 0.;
  }
  *epstrc = 0.;
  error   = 0.;

  ncut = ia + 1;

  i__1 = ncut;
  for (i__ = *ncoeff; i__ >= i__1; --i__)
  {

    bidon = xmaxj[i__ - ncut];
    i__2  = *ndimen;
    for (nd = 1; nd <= i__2; ++nd)
    {
      ycvmax[nd] += (d__1 = crvlgd[i__ + nd * crvlgd_dim1], advapp_abs(d__1)) * bidon;
    }

    error = AdvApp2Var_MathBase::mzsnorm_(ndimen, &ycvmax[1]);
    if (error > *epsi3d)
    {
      *ncfnew = i__;
      goto L400;
    }

    *epstrc = error;
  }

L400:
  if (*ncfnew == ia)
  {
    AdvApp2Var_MathBase::mmeps1_(&eps1);
    for (i__ = ia; i__ >= 2; --i__)
    {
      bid  = 0.;
      i__1 = *ndimen;
      for (nd = 1; nd <= i__1; ++nd)
      {
        bid += (d__1 = crvlgd[i__ + nd * crvlgd_dim1], advapp_abs(d__1));
      }
      if (bid > eps1)
      {
        *ncfnew = i__;
        goto L9999;
      }
    }

    *ncfnew = 1;
  }

L9999:
  return 0;
}

int mmtrpj4_(integer*    ncofmx,
             integer*    ndimen,
             integer*    ncoeff,
             doublereal* epsi3d,
             doublereal* crvlgd,
             doublereal* ycvmax,
             doublereal* epstrc,
             integer*    ncfnew)
{

  static doublereal xmaxj[55] = {
    1.1092649593311780079813740546678,  1.05299572648705464724876659688996,
    1.0949715351434178709281698645813,  1.15078388379719068145021100764647,
    1.2094863084718701596278219811869,  1.26806623151369531323304177532868,
    1.32549784426476978866302826176202, 1.38142537365039019558329304432581,
    1.43575531950773585146867625840552, 1.48850442653629641402403231015299,
    1.53973611681876234549146350844736, 1.58953193485272191557448229046492,
    1.63797820416306624705258190017418, 1.68515974143594899185621942934906,
    1.73115699602477936547107755854868, 1.77604489805513552087086912113251,
    1.81989256661534438347398400420601, 1.86276344480103110090865609776681,
    1.90471563564740808542244678597105, 1.94580231994751044968731427898046,
    1.98607219357764450634552790950067, 2.02556989246317857340333585562678,
    2.06433638992049685189059517340452, 2.10240936014742726236706004607473,
    2.13982350649113222745523925190532, 2.17661085564771614285379929798896,
    2.21280102016879766322589373557048, 2.2484214321456956597803794333791,
    2.28349755104077956674135810027654, 2.31805304852593774867640120860446,
    2.35210997297725685169643559615022, 2.38568889602346315560143377261814,
    2.41880904328694215730192284109322, 2.45148841120796359750021227795539,
    2.48374387161372199992570528025315, 2.5155912654873773953959098501893,
    2.54704548720896557684101746505398, 2.57812056037881628390134077704127,
    2.60882970619319538196517982945269, 2.63918540521920497868347679257107,
    2.66919945330942891495458446613851, 2.69888301230439621709803756505788,
    2.72824665609081486737132853370048, 2.75730041251405791603760003778285,
    2.78605380158311346185098508516203, 2.81451587035387403267676338931454,
    2.84269522483114290814009184272637, 2.87060005919012917988363332454033,
    2.89823818258367657739520912946934, 2.92561704377132528239806135133273,
    2.95274375377994262301217318010209, 2.97962510678256471794289060402033,
    3.00626759936182712291041810228171, 3.03267744830655121818899164295959,
    3.05886060707437081434964933864149};

  integer    crvlgd_dim1, crvlgd_offset, i__1, i__2;
  doublereal d__1;

  integer    ncut, i__;
  doublereal bidon, error;
  integer    ia, nd;
  doublereal bid, eps1;

  --ycvmax;
  crvlgd_dim1   = *ncofmx;
  crvlgd_offset = crvlgd_dim1 + 1;
  crvlgd -= crvlgd_offset;

  ia      = 4;
  *ncfnew = ia;

  i__1 = *ndimen;
  for (i__ = 1; i__ <= i__1; ++i__)
  {
    ycvmax[i__] = 0.;
  }
  *epstrc = 0.;
  error   = 0.;

  ncut = ia + 1;

  i__1 = ncut;
  for (i__ = *ncoeff; i__ >= i__1; --i__)
  {

    bidon = xmaxj[i__ - ncut];
    i__2  = *ndimen;
    for (nd = 1; nd <= i__2; ++nd)
    {
      ycvmax[nd] += (d__1 = crvlgd[i__ + nd * crvlgd_dim1], advapp_abs(d__1)) * bidon;
    }

    error = AdvApp2Var_MathBase::mzsnorm_(ndimen, &ycvmax[1]);
    if (error > *epsi3d)
    {
      *ncfnew = i__;
      goto L400;
    }

    *epstrc = error;
  }

L400:
  if (*ncfnew == ia)
  {
    AdvApp2Var_MathBase::mmeps1_(&eps1);
    for (i__ = ia; i__ >= 2; --i__)
    {
      bid  = 0.;
      i__1 = *ndimen;
      for (nd = 1; nd <= i__1; ++nd)
      {
        bid += (d__1 = crvlgd[i__ + nd * crvlgd_dim1], advapp_abs(d__1));
      }
      if (bid > eps1)
      {
        *ncfnew = i__;
        goto L9999;
      }
    }

    *ncfnew = 1;
  }

L9999:
  return 0;
}

int mmtrpj6_(integer*    ncofmx,
             integer*    ndimen,
             integer*    ncoeff,
             doublereal* epsi3d,
             doublereal* crvlgd,
             doublereal* ycvmax,
             doublereal* epstrc,
             integer*    ncfnew)

{

  static doublereal xmaxj[53] = {
    1.21091229812484768570102219548814, 1.11626917091567929907256116528817,
    1.1327140810290884106278510474203,  1.1679452722668028753522098022171,
    1.20910611986279066645602153641334, 1.25228283758701572089625983127043,
    1.29591971597287895911380446311508, 1.3393138157481884258308028584917,
    1.3821288728999671920677617491385,  1.42420414683357356104823573391816,
    1.46546895108549501306970087318319, 1.50590085198398789708599726315869,
    1.54550385142820987194251585145013, 1.58429644271680300005206185490937,
    1.62230484071440103826322971668038, 1.65955905239130512405565733793667,
    1.69609056468292429853775667485212, 1.73193098017228915881592458573809,
    1.7671112206990325429863426635397,  1.80166107681586964987277458875667,
    1.83560897003644959204940535551721, 1.86898184653271388435058371983316,
    1.90180515174518670797686768515502, 1.93410285411785808749237200054739,
    1.96589749778987993293150856865539, 1.99721027139062501070081653790635,
    2.02806108474738744005306947877164, 2.05846864831762572089033752595401,
    2.08845055210580131460156962214748, 2.11802334209486194329576724042253,
    2.14720259305166593214642386780469, 2.17600297710595096918495785742803,
    2.20443832785205516555772788192013, 2.2325216999457379530416998244706,
    2.2602654243075083168599953074345,  2.28768115912702794202525264301585,
    2.3147799369092684021274946755348,  2.34157220782483457076721300512406,
    2.36806787963276257263034969490066, 2.39427635443992520016789041085844,
    2.42020656255081863955040620243062, 2.44586699364757383088888037359254,
    2.47126572552427660024678584642791, 2.49641045058324178349347438430311,
    2.52130850028451113942299097584818, 2.54596686772399937214920135190177,
    2.5703922285006754089328998222275,  2.59459096001908861492582631591134,
    2.61856915936049852435394597597773, 2.64233265984385295286445444361827,
    2.66588704638685848486056711408168, 2.68923766976735295746679957665724,
    2.71238965987606292679677228666411};

  integer    crvlgd_dim1, crvlgd_offset, i__1, i__2;
  doublereal d__1;

  integer    ncut, i__;
  doublereal bidon, error;
  integer    ia, nd;
  doublereal bid, eps1;

  --ycvmax;
  crvlgd_dim1   = *ncofmx;
  crvlgd_offset = crvlgd_dim1 + 1;
  crvlgd -= crvlgd_offset;

  ia      = 6;
  *ncfnew = ia;

  i__1 = *ndimen;
  for (i__ = 1; i__ <= i__1; ++i__)
  {
    ycvmax[i__] = 0.;
  }
  *epstrc = 0.;
  error   = 0.;

  ncut = ia + 1;

  i__1 = ncut;
  for (i__ = *ncoeff; i__ >= i__1; --i__)
  {

    bidon = xmaxj[i__ - ncut];
    i__2  = *ndimen;
    for (nd = 1; nd <= i__2; ++nd)
    {
      ycvmax[nd] += (d__1 = crvlgd[i__ + nd * crvlgd_dim1], advapp_abs(d__1)) * bidon;
    }

    error = AdvApp2Var_MathBase::mzsnorm_(ndimen, &ycvmax[1]);
    if (error > *epsi3d)
    {
      *ncfnew = i__;
      goto L400;
    }

    *epstrc = error;
  }

L400:
  if (*ncfnew == ia)
  {
    AdvApp2Var_MathBase::mmeps1_(&eps1);
    for (i__ = ia; i__ >= 2; --i__)
    {
      bid  = 0.;
      i__1 = *ndimen;
      for (nd = 1; nd <= i__1; ++nd)
      {
        bid += (d__1 = crvlgd[i__ + nd * crvlgd_dim1], advapp_abs(d__1));
      }
      if (bid > eps1)
      {
        *ncfnew = i__;
        goto L9999;
      }
    }

    *ncfnew = 1;
  }

L9999:
  return 0;
}

int AdvApp2Var_MathBase::mmtrpjj_(integer*    ncofmx,
                                  integer*    ndimen,
                                  integer*    ncoeff,
                                  doublereal* epsi3d,
                                  integer*    iordre,
                                  doublereal* crvlgd,
                                  doublereal* ycvmax,
                                  doublereal* errmax,
                                  integer*    ncfnew)
{

  integer crvlgd_dim1, crvlgd_offset;

  integer ia;

  --ycvmax;
  crvlgd_dim1   = *ncofmx;
  crvlgd_offset = crvlgd_dim1 + 1;
  crvlgd -= crvlgd_offset;

  ia = (*iordre + 1) << 1;

  if (ia == 0)
  {
    mmtrpj0_(ncofmx, ndimen, ncoeff, epsi3d, &crvlgd[crvlgd_offset], &ycvmax[1], errmax, ncfnew);
  }
  else if (ia == 2)
  {
    mmtrpj2_(ncofmx, ndimen, ncoeff, epsi3d, &crvlgd[crvlgd_offset], &ycvmax[1], errmax, ncfnew);
  }
  else if (ia == 4)
  {
    mmtrpj4_(ncofmx, ndimen, ncoeff, epsi3d, &crvlgd[crvlgd_offset], &ycvmax[1], errmax, ncfnew);
  }
  else
  {
    mmtrpj6_(ncofmx, ndimen, ncoeff, epsi3d, &crvlgd[crvlgd_offset], &ycvmax[1], errmax, ncfnew);
  }

  return 0;
}

int AdvApp2Var_MathBase::mmunivt_(integer*    ndimen,
                                  doublereal* vector,
                                  doublereal* vecnrm,
                                  doublereal* epsiln,
                                  integer*    iercod)
{

  doublereal c_b2 = 10.;

  integer    i__1;
  doublereal d__1;

  integer    nchif, iunit = 1, izero;
  doublereal vnorm;
  integer    ii;
  doublereal bid;
  doublereal eps0;

  --vecnrm;
  --vector;

  *iercod = 0;

  AdvApp2Var_SysBase::maovsr8_(&nchif);
  if (*epsiln <= 0.)
  {
    i__1 = -nchif;
    eps0 = AdvApp2Var_MathBase::pow__di(&c_b2, &i__1);
  }
  else
  {
    eps0 = *epsiln;
  }

  vnorm = AdvApp2Var_MathBase::mzsnorm_(ndimen, &vector[1]);
  if (vnorm <= eps0)
  {
    AdvApp2Var_SysBase::mvriraz_(ndimen, &vecnrm[1]);
    *iercod = 101;
    goto L9999;
  }

  izero = 0;
  i__1  = (-nchif - 1) / 2;
  eps0  = AdvApp2Var_MathBase::pow__di(&c_b2, &i__1);
  i__1  = *ndimen;
  for (ii = 1; ii <= i__1; ++ii)
  {
    vecnrm[ii] = vector[ii] / vnorm;
    if ((d__1 = vecnrm[ii], advapp_abs(d__1)) <= eps0)
    {
      ++izero;
    }
    else
    {
      iunit = ii;
    }
  }

  if (izero == *ndimen - 1)
  {
    bid  = vecnrm[iunit];
    i__1 = *ndimen;
    for (ii = 1; ii <= i__1; ++ii)
    {
      vecnrm[ii] = 0.;
    }
    if (bid > 0.)
    {
      vecnrm[iunit] = 1.;
    }
    else
    {
      vecnrm[iunit] = -1.;
    }
  }

L9999:
  return 0;
}

int AdvApp2Var_MathBase::mmveps3_(doublereal* eps03)
{

  static char nomprg[8 + 1] = "MMEPS1  ";

  integer ibb;

  ibb = AdvApp2Var_SysBase::mnfndeb_();
  if (ibb >= 5)
  {
    AdvApp2Var_SysBase::mgenmsg_(nomprg, 6L);
  }

  *eps03 = mmprcsn_.eps3;

  return 0;
}

int AdvApp2Var_MathBase::mmvncol_(integer*    ndimen,
                                  doublereal* vecin,
                                  doublereal* vecout,
                                  integer*    iercod)

{

  integer i__1;

  logical    ldbg;
  integer    d__;
  doublereal vaux1[3], vaux2[3];
  logical    colin;
  doublereal valaux;
  integer    aux;

  --vecout;
  --vecin;

  ldbg = AdvApp2Var_SysBase::mnfndeb_() >= 2;
  if (ldbg)
  {
    AdvApp2Var_SysBase::mgenmsg_("MMVNCOL", 7L);
  }
  *iercod = 0;

  if (*ndimen <= 1 || *ndimen > 3)
  {
    goto L9101;
  }
  d__ = 1;
  aux = 0;
  while (d__ <= *ndimen)
  {
    if (vecin[d__] == 0.)
    {
      ++aux;
    }
    ++d__;
  }
  if (aux == *ndimen)
  {
    goto L9101;
  }

  for (d__ = 1; d__ <= 3; ++d__)
  {
    vaux1[d__ - 1] = 0.;
  }
  i__1 = *ndimen;
  for (d__ = 1; d__ <= i__1; ++d__)
  {
    vaux1[d__ - 1] = vecin[d__];
    vaux2[d__ - 1] = vecin[d__];
  }
  colin = TRUE_;
  d__   = 0;
  while (colin)
  {
    ++d__;
    if (d__ > 3)
    {
      goto L9101;
    }
    vaux2[d__ - 1] += 1;
    valaux = vaux1[1] * vaux2[2] - vaux1[2] * vaux2[1];
    if (valaux == 0.)
    {
      valaux = vaux1[2] * vaux2[0] - vaux1[0] * vaux2[2];
      if (valaux == 0.)
      {
        valaux = vaux1[0] * vaux2[1] - vaux1[1] * vaux2[0];
        if (valaux != 0.)
        {
          colin = FALSE_;
        }
      }
      else
      {
        colin = FALSE_;
      }
    }
    else
    {
      colin = FALSE_;
    }
  }
  if (colin)
  {
    goto L9101;
  }
  i__1 = *ndimen;
  for (d__ = 1; d__ <= i__1; ++d__)
  {
    vecout[d__] = vaux2[d__ - 1];
  }

  goto L9999;

L9101:
  *iercod = 1;
  goto L9999;

L9999:

  AdvApp2Var_SysBase::maermsg_("MMVNCOL", iercod, 7L);
  if (ldbg)
  {
    AdvApp2Var_SysBase::mgsomsg_("MMVNCOL", 7L);
  }
  return 0;
}

void AdvApp2Var_MathBase::mmwprcs_(doublereal* epsil1,
                                   doublereal* epsil2,
                                   doublereal* epsil3,
                                   doublereal* epsil4,
                                   integer*    niter1,
                                   integer*    niter2)

{

  mmprcsn_.eps1   = *epsil1;
  mmprcsn_.eps2   = *epsil2;
  mmprcsn_.eps3   = *epsil3;
  mmprcsn_.eps4   = *epsil4;
  mmprcsn_.niterm = *niter1;
  mmprcsn_.niterr = *niter2;
  return;
}

doublereal AdvApp2Var_MathBase::pow__di(doublereal* x, integer* n)
{
  doublereal result;
  integer    absolute;
  result = 1.0e0;
  if (*n > 0)
  {
    absolute = *n;
  }
  else
  {
    absolute = -*n;
  }

  for (integer ii = 0; ii < absolute; ii++)
  {
    result *= *x;
  }
  if (*n < 0)
  {
    result = 1.0e0 / result;
  }
  return result;
}

integer pow__ii(integer* x, integer* n)

{
  integer result;
  integer absolute;
  result = 1;
  if (*n > 0)
  {
    absolute = *n;
  }
  else
  {
    absolute = -*n;
  }

  for (integer ii = 0; ii < absolute; ii++)
  {
    result *= *x;
  }
  if (*n < 0)
  {
    result = 1 / result;
  }
  return result;
}

doublereal AdvApp2Var_MathBase::msc_(integer* ndimen, doublereal* vecte1, doublereal* vecte2)

{

  integer    i__1;
  doublereal ret_val;

  integer    i__;
  doublereal x;

  --vecte2;
  --vecte1;

  x = 0.;

  i__1 = *ndimen;
  for (i__ = 1; i__ <= i__1; ++i__)
  {
    x += vecte1[i__] * vecte2[i__];
  }
  ret_val = x;

  return ret_val;
}

int mvcvin2_(integer* ncoeff, doublereal* crvold, doublereal* crvnew, integer* iercod)

{

  integer i__1, i__2;

  integer    m1jm1, ncfm1, j, k;
  doublereal bid;
  doublereal cij1, cij2;

  crvnew -= 3;
  crvold -= 3;

  if (*ncoeff < 1 || *ncoeff - 1 > 60)
  {
    *iercod = 10;
    goto L9999;
  }
  *iercod = 0;

  cij1 = crvold[3];
  cij2 = crvold[4];
  i__1 = *ncoeff;
  for (k = 2; k <= i__1; ++k)
  {
    cij1 += crvold[(k << 1) + 1];
    cij2 += crvold[(k << 1) + 2];
  }
  crvnew[3] = cij1;
  crvnew[4] = cij2;
  if (*ncoeff == 1)
  {
    goto L9999;
  }

  ncfm1 = *ncoeff - 1;
  m1jm1 = 1;
  i__1  = ncfm1;
  for (j = 2; j <= i__1; ++j)
  {
    m1jm1 = -m1jm1;
    cij1  = crvold[(j << 1) + 1];
    cij2  = crvold[(j << 1) + 2];
    i__2  = *ncoeff;
    for (k = j + 1; k <= i__2; ++k)
    {
      bid = mmcmcnp_.cnp[k - 1 + (j - 1) * 61];
      cij1 += crvold[(k << 1) + 1] * bid;
      cij2 += crvold[(k << 1) + 2] * bid;
    }
    crvnew[(j << 1) + 1] = cij1 * m1jm1;
    crvnew[(j << 1) + 2] = cij2 * m1jm1;
  }

  crvnew[(*ncoeff << 1) + 1] = -crvold[(*ncoeff << 1) + 1] * m1jm1;
  crvnew[(*ncoeff << 1) + 2] = -crvold[(*ncoeff << 1) + 2] * m1jm1;

L9999:
  if (*iercod > 0)
  {
    AdvApp2Var_SysBase::maermsg_("MVCVIN2", iercod, 7L);
  }
  return 0;
}

int mvcvinv_(integer* ncoeff, doublereal* crvold, doublereal* crvnew, integer* iercod)

{

  integer i__1, i__2;

  integer    m1jm1, ncfm1, j, k;
  doublereal bid;

  doublereal cij1, cij2, cij3;

  crvnew -= 4;
  crvold -= 4;

  if (*ncoeff < 1 || *ncoeff - 1 > 60)
  {
    *iercod = 10;
    goto L9999;
  }
  *iercod = 0;

  cij1 = crvold[4];
  cij2 = crvold[5];
  cij3 = crvold[6];
  i__1 = *ncoeff;
  for (k = 2; k <= i__1; ++k)
  {
    cij1 += crvold[k * 3 + 1];
    cij2 += crvold[k * 3 + 2];
    cij3 += crvold[k * 3 + 3];
  }
  crvnew[4] = cij1;
  crvnew[5] = cij2;
  crvnew[6] = cij3;
  if (*ncoeff == 1)
  {
    goto L9999;
  }

  ncfm1 = *ncoeff - 1;
  m1jm1 = 1;
  i__1  = ncfm1;
  for (j = 2; j <= i__1; ++j)
  {
    m1jm1 = -m1jm1;
    cij1  = crvold[j * 3 + 1];
    cij2  = crvold[j * 3 + 2];
    cij3  = crvold[j * 3 + 3];
    i__2  = *ncoeff;
    for (k = j + 1; k <= i__2; ++k)
    {
      bid = mmcmcnp_.cnp[k - 1 + (j - 1) * 61];
      cij1 += crvold[k * 3 + 1] * bid;
      cij2 += crvold[k * 3 + 2] * bid;
      cij3 += crvold[k * 3 + 3] * bid;
    }
    crvnew[j * 3 + 1] = cij1 * m1jm1;
    crvnew[j * 3 + 2] = cij2 * m1jm1;
    crvnew[j * 3 + 3] = cij3 * m1jm1;
  }

  crvnew[*ncoeff * 3 + 1] = -crvold[*ncoeff * 3 + 1] * m1jm1;
  crvnew[*ncoeff * 3 + 2] = -crvold[*ncoeff * 3 + 2] * m1jm1;
  crvnew[*ncoeff * 3 + 3] = -crvold[*ncoeff * 3 + 3] * m1jm1;

L9999:
  AdvApp2Var_SysBase::maermsg_("MVCVINV", iercod, 7L);
  return 0;
}

int mvgaus0_(integer*    kindic,
             doublereal* urootl,
             doublereal* hiltab,
             integer*    nbrval,
             integer*    iercod)

{

  integer i__1 = 0;

  doublereal                     tampc[40] = {};
  NCollection_Array1<doublereal> tamp(tampc[0], 1, 40);
  integer                        ndegl = 0, kg = 0, ii = 0;

  --hiltab;
  --urootl;

  *iercod = 0;
  kg      = *kindic;
  if (kg < 1 || kg > 10)
  {
    kg      = 10;
    *iercod = -1;
  }
  *nbrval = kg << 1;
  ndegl   = *nbrval << 1;

  mmextrl_(&ndegl, tamp);
  i__1 = *nbrval;
  for (ii = 1; ii <= i__1; ++ii)
  {
    urootl[ii] = -tamp(ii);
  }

  mmexthi_(&ndegl, tamp);
  i__1 = *nbrval;
  for (ii = 1; ii <= i__1; ++ii)
  {
    hiltab[ii] = tamp(ii);
  }

  return 0;
}

int mvpscr2_(integer* ncoeff, doublereal* curve2, doublereal* tparam, doublereal* pntcrb)
{

  integer i__1;

  integer    ndeg, kk;
  doublereal xxx, yyy;

  --pntcrb;
  curve2 -= 3;

  if (*ncoeff >= 2)
  {
    goto L1000;
  }

  if (*ncoeff <= 0)
  {
    pntcrb[1] = 0.;
    pntcrb[2] = 0.;
    goto L9999;
  }
  else if (*ncoeff == 1)
  {
    pntcrb[1] = curve2[3];
    pntcrb[2] = curve2[4];
    goto L9999;
  }

L1000:

  if (*tparam == 1.)
  {
    xxx  = 0.;
    yyy  = 0.;
    i__1 = *ncoeff;
    for (kk = 1; kk <= i__1; ++kk)
    {
      xxx += curve2[(kk << 1) + 1];
      yyy += curve2[(kk << 1) + 2];
    }
    goto L5000;
  }
  else if (*tparam == 0.)
  {
    pntcrb[1] = curve2[3];
    pntcrb[2] = curve2[4];
    goto L9999;
  }

  ndeg = *ncoeff - 1;
  xxx  = curve2[(*ncoeff << 1) + 1];
  yyy  = curve2[(*ncoeff << 1) + 2];
  for (kk = ndeg; kk >= 1; --kk)
  {
    xxx = xxx * *tparam + curve2[(kk << 1) + 1];
    yyy = yyy * *tparam + curve2[(kk << 1) + 2];
  }
  goto L5000;

L5000:
  pntcrb[1] = xxx;
  pntcrb[2] = yyy;

L9999:
  return 0;
}

int mvpscr3_(integer* ncoeff, doublereal* curve3, doublereal* tparam, doublereal* pntcrb)

{

  integer i__1;

  integer    ndeg, kk;
  doublereal xxx, yyy, zzz;

  --pntcrb;
  curve3 -= 4;

  if (*ncoeff >= 2)
  {
    goto L1000;
  }

  if (*ncoeff <= 0)
  {
    pntcrb[1] = 0.;
    pntcrb[2] = 0.;
    pntcrb[3] = 0.;
    goto L9999;
  }
  else if (*ncoeff == 1)
  {
    pntcrb[1] = curve3[4];
    pntcrb[2] = curve3[5];
    pntcrb[3] = curve3[6];
    goto L9999;
  }

L1000:

  if (*tparam == 1.)
  {
    xxx  = 0.;
    yyy  = 0.;
    zzz  = 0.;
    i__1 = *ncoeff;
    for (kk = 1; kk <= i__1; ++kk)
    {
      xxx += curve3[kk * 3 + 1];
      yyy += curve3[kk * 3 + 2];
      zzz += curve3[kk * 3 + 3];
    }
    goto L5000;
  }
  else if (*tparam == 0.)
  {
    pntcrb[1] = curve3[4];
    pntcrb[2] = curve3[5];
    pntcrb[3] = curve3[6];
    goto L9999;
  }

  ndeg = *ncoeff - 1;
  xxx  = curve3[*ncoeff * 3 + 1];
  yyy  = curve3[*ncoeff * 3 + 2];
  zzz  = curve3[*ncoeff * 3 + 3];
  for (kk = ndeg; kk >= 1; --kk)
  {
    xxx = xxx * *tparam + curve3[kk * 3 + 1];
    yyy = yyy * *tparam + curve3[kk * 3 + 2];
    zzz = zzz * *tparam + curve3[kk * 3 + 3];
  }
  goto L5000;

L5000:
  pntcrb[1] = xxx;
  pntcrb[2] = yyy;
  pntcrb[3] = zzz;

L9999:
  return 0;
}

int AdvApp2Var_MathBase::mvsheld_(integer* n, integer* is, doublereal* dtab, integer* icle)

{

  integer dtab_dim1, dtab_offset, i__1, i__2;

  integer    incr;
  doublereal dsave;
  integer    i3, i4, i5, incrp1;

  dtab_dim1   = *is;
  dtab_offset = dtab_dim1 + 1;
  dtab -= dtab_offset;

  if (*n <= 1)
  {
    goto L9900;
  }

  incr = 1;
L1001:
  if (incr >= *n / 9)
  {
    goto L1002;
  }

  incr = incr * 3 + 1;
  goto L1001;

L1002:
  incrp1 = incr + 1;

  i__1 = *n;
  for (i3 = incrp1; i3 <= i__1; ++i3)
  {

    i4 = i3 - incr;
  L1004:
    if (i4 < 1)
    {
      goto L1003;
    }

    if (dtab[*icle + i4 * dtab_dim1] <= dtab[*icle + (i4 + incr) * dtab_dim1])
    {
      goto L1003;
    }

    i__2 = *is;
    for (i5 = 1; i5 <= i__2; ++i5)
    {

      dsave                              = dtab[i5 + i4 * dtab_dim1];
      dtab[i5 + i4 * dtab_dim1]          = dtab[i5 + (i4 + incr) * dtab_dim1];
      dtab[i5 + (i4 + incr) * dtab_dim1] = dsave;
    }

    i4 -= incr;
    goto L1004;

  L1003:;
  }

  incr /= 3;
  if (incr >= 1)
  {
    goto L1002;
  }

L9900:
  return 0;
}

doublereal AdvApp2Var_MathBase::mzsnorm_(integer* ndimen, doublereal* vecteu)

{

  integer    i__1;
  doublereal ret_val, d__1, d__2;

  doublereal xsom;
  integer    i__, irmax;

  --vecteu;

  irmax = 1;
  i__1  = *ndimen;
  for (i__ = 2; i__ <= i__1; ++i__)
  {
    if ((d__1 = vecteu[irmax], advapp_abs(d__1)) < (d__2 = vecteu[i__], advapp_abs(d__2)))
    {
      irmax = i__;
    }
  }

  if ((d__1 = vecteu[irmax], advapp_abs(d__1)) < 1.)
  {
    xsom = 0.;
    i__1 = *ndimen;
    for (i__ = 1; i__ <= i__1; ++i__)
    {

      d__1 = vecteu[i__];
      xsom += d__1 * d__1;
    }
    ret_val = sqrt(xsom);
  }
  else
  {
    xsom = 0.;
    i__1 = *ndimen;
    for (i__ = 1; i__ <= i__1; ++i__)
    {
      if (i__ == irmax)
      {
        xsom += 1.;
      }
      else
      {

        d__1 = vecteu[i__] / vecteu[irmax];
        xsom += d__1 * d__1;
      }
    }
    ret_val = (d__1 = vecteu[irmax], advapp_abs(d__1)) * sqrt(xsom);
  }

  return ret_val;
}
