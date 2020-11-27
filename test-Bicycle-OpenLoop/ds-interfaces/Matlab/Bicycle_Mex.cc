/*-----------------------------------------------------------------------*\
 |  file: Bicycle_Mex.cc                                                 |
 |                                                                       |
 |  version: 1.0   date 28/11/2020                                       |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#define BUILDING_DLL

#include "Bicycle.hh"
#include "Bicycle_Pars.hh"

#include "GenericContainerMatlabInterface.hh"

using namespace std;
using namespace MechatronixLoad;


using namespace BicycleLoad;
using namespace std;

namespace GenericContainerNamespace {

  static char const msg[] =
    "%===========================================================================%\n"
    "\n"
    "Mex command has the following possible calls:\n"
    "\n"
    "  - Bicycle_Mex('setup', mstruct):\n"
    "    initialise the problem with a matlab structure 'mstruct'"
    "\n"
    "  - Bicycle_Mex('steady_state', int32(wl)):\n"
    "    wl must be a number between 0 to 4 and set the warning level\n"
    "    solve the steady state problem computing the steady state condition and the eigen values analysis\n"
    "    Solution is return as a matlab structure.\n"
    "\n"
    "  - sol = Bicycle_Mex('do_integration_step',ics,controls,t_sample):\n"
    "    return the full solution as a matlab structure after integrating the equations of motion\n"
    "    between t_sample(1) and t_sample(end) using the given `controls` values and initial conditions `ics`\n"
    "    Solution is sampled on the points of vector `t_sample`.\n"
    "\n"
    "%===========================================================================%\n";

  /*\
   *                      _____                 _   _
   *  _ __ ___   _____  _|  ___|   _ _ __   ___| |_(_) ___  _ __
   * | '_ ` _ \ / _ \ \/ / |_ | | | | '_ \ / __| __| |/ _ \| '_ \
   * | | | | | |  __/>  <|  _|| |_| | | | | (__| |_| | (_) | | | |
   * |_| |_| |_|\___/_/\_\_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|
   *
  \*/

  extern "C"
  void
  mexFunction(
    int             nargout,
    mxArray       * plhs[],
    int             nargin,
    mxArray const * prhs[]
  ) {

    static Mechatronix::Console console(&std::cout,4);

    static GenericContainer     gc_data;
    static GenericContainer     gc_solution;
    static ODE::Radau5ODE       ODEsolver(&cout,1);
    static Splines::SplineSet   spline_set;
    static Bicycle              model("Bicycle",&console);
    static 
    // Read first argument: must be a string
    if ( nargin == 0 || !mxIsChar(prhs[0]) )
      mexErrMsgTxt( "First argument should be a string." );

    try {

      string what = mxArrayToString(prhs[0]);

      for ( string::iterator i = what.begin(); i != what.end(); ++i)
        *i = tolower(*i);

      if ( what == "help" ) { // -----------------------------------------------------

        mexPrintf("%s",msg);

      } else if ( what == "setup" ) { // ---------------------------------------------

        if ( nargin != 2 ) mexErrMsgTxt( msg );

        mxArray_to_GenericContainer( prhs[1], gc_data );
        gc_data["Constraints"]; // work around if no contraints
        gc_data["Parameters"]; // work around if no parameters
        model.setup( gc_data );

      } else if ( what == "steady_state" ) { // ---------------------------------------

        if ( nargin != 2 ) mexErrMsgTxt( "SingleTrackOL_Mex('steady_state',InfoLevel) expected 2 arguments " );

        //change warning level
        mxArray_to_GenericContainer( prhs[1], gc_data["InfoLevel"] );

        model.setup( gc_data );

        bool ok = model.solve_steady_state( gc_data, gc_solution );
        UTILS_ASSERT0( ok, "Failed to solve stationary problem\n" );

        /*build and return matlab structure with solution*/
        GenericContainer_to_mxArray( gc_solution, plhs[0] );

      } else if ( what == "do_integration_step" ) { // --------------------------------

        if ( nargin == 4 ) { /* do integration using the following arguments: x0,u0,t_vec */

          GenericContainer gc_in, gc_out, gc_post_proc;
          mxArray_to_GenericContainer( prhs[1], gc_in["zeta_values"] );
          mxArray_to_GenericContainer( prhs[2], gc_in["initial_value"] );
          mxArray_to_GenericContainer( prhs[3], gc_data );

          gc_in["headers"] =  gc_data[""];
          // re-initialize model reading parameters from generic container ``gc''
          model.setup(gc_data);
          // Setup ode integrator with dynamic model parameters
          ODEsolver.setup( &model );
          ODEsolver.computeSolution( gc_in, gc_out );
          model.post_processing( gc_out, gc_post_proc );
          gc_out["post_process_data"]    = gc_post_proc["data"];
          gc_out["post_process_headers"] = gc_post_proc["headers"];

          GenericContainer_to_mxArray( gc_out, plhs[0] );

      } else { // ------------------------------------------------------------

       UTILS_ERROR(
          "Bicycle_Mex('do_integration_step',...) expected 4 arguments\n"
          "found: {}\n", nargin
        );
      }
      } else {
        mexErrMsgTxt("Bicycle: bad call.");
      }
    } catch ( std::exception const & exc ) {
      mexErrMsgTxt(exc.what());
    } catch ( ... ) {
      mexErrMsgTxt("Bicycle: unknown error");
    }
    cout.flush(); // non dimenticare di fare il flush!
  }
}
