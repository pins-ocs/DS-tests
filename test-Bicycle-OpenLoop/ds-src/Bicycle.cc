/*-----------------------------------------------------------------------*\
 |  file: Bicycle.cc                                                     |
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


#include "Bicycle.hh"
#include "Bicycle_Pars.hh"

namespace BicycleDefine {

  char const *namesXvars[numXvars+1] = {
    "u",
    "v",
    "omega",
    "phi",
    "delta",
    "Yr",
    "Yf",
    "phi_dot",
    "delta_dot",
    nullptr
  };

  char const *namesUvars[numUvars+1] = {
    "tau",
    "Xr",
    "Xf",
    nullptr
  };

  char const *namesPostProcess[numPostProcess+1] = {
    nullptr
  };

  char const *namesModelPars[numModelPars+1] = {
    "Cdelta",
    "Cf1",
    "Cf2",
    "Cr1",
    "Cr2",
    "Cxz",
    "Ifz",
    "Ix",
    "Iy",
    "Iz",
    "Xr0",
    "an",
    "b",
    "epsilon",
    "f0",
    "g",
    "h",
    "iwf",
    "iwr",
    "kD",
    "m",
    "omega0",
    "rf",
    "rr",
    "sigma",
    "tau0",
    "u0",
    "w",
    nullptr
  };

  char const *namesConstraint1D[numConstraint1D+1] = {
    nullptr
  };

  char const *namesConstraint2D[numConstraint2D+1] = {
    nullptr
  };

  // --------------------------------------------------------------------------
  Bicycle::Bicycle( string const & name, Console * console )
  : m_solver( name )
  , m_nlsys( name, this )
  , m_console( console )
  , Mechatronix::ModelDynamicalSystem(
      name,
      numXvars,       namesXvars,
      numUvars,       namesUvars,
      numPostProcess, namesPostProcess
    )
  , m_baseValue( name + "_values_allocator" )
  , m_baseIndex( name + "_indices_allocator" )
  , m_zeta0(0)
  // Controls
  // Constraints 1D
  // Constraints 2D
  // User classes
  {
    // allocate from virtual base class
    Mechatronix::ModelDynamicalSystem::allocate();

    // Initialize to NaN all the ModelPars
    std::fill( ModelPars, ModelPars + numModelPars, Utils::NaN<real_type>() );

    integer NR  = steady_state_DequationsDz_numRows();
    integer NC  = steady_state_DequationsDz_numCols();
    integer NNZ = steady_state_DequationsDz_nnz();

    m_baseIndex.allocate( 2*NNZ + NR );
    m_baseValue.allocate( NNZ + 2 * NR * NC );

    m_DeqDz_sparse.numRows = NR;
    m_DeqDz_sparse.numCols = NC;
    m_DeqDz_sparse.nnz     = NNZ;
    m_DeqDz_sparse.rows    = m_baseIndex( NNZ );
    m_DeqDz_sparse.cols    = m_baseIndex( NNZ );
    m_DeqDz_sparse_vals    = m_baseValue( NNZ );
    steady_state_DequationsDz_pattern( m_DeqDz_sparse.rows, m_DeqDz_sparse.cols );
    m_lu.no_allocate( NR, NC, m_baseValue( NR * NC ), m_baseIndex( NR ) );
    m_A.setup( m_baseValue( NR * NC ), NR, NC, NR );
  }

  Bicycle::~Bicycle() {
  }

  // --------------------------------------------------------------------------
  // Continuation (NOT USED)
  void
  Bicycle::NonlinearSystem::updateContinuation(
    integer phase,
    real_type s
  ) {
    /* NOT USED */
  }

  // --------------------------------------------------------------------------
  // initialize parameters using associative array

  void
  Bicycle::setupParameters( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Parameters"),
      "Bicycle::setupParameters: Missing key `Parameters` in data\n"
    );
    GenericContainer const & gc = gc_data("Parameters");
    bool allfound = true;
    for ( integer i = 0; i < numModelPars; ++i ) {
      char const * namei = namesModelPars[i];
      if ( gc.exists(namei) ) {
        ModelPars[i] = gc(namei).get_number();
      } else {
        m_console->error( fmt::format("Missing parameter: '{}'\n", namei ) );
        allfound = false;
      }
    }
    UTILS_ASSERT0(
      allfound, "in Bicycle::setup not all parameters are set!\n"
    );
  }

  // --------------------------------------------------------------------------
  void
  Bicycle::setupClasses( GenericContainer const & gc_data ) {
    UTILS_ASSERT0(
      gc_data.exists("Constraints"),
      "Bicycle::setupClasses: Missing key `Constraints` in data\n"
    );
    GenericContainer const & gc = gc_data("Constraints");
  }

  // --------------------------------------------------------------------------
  void
  Bicycle::setupUserClasses( GenericContainer const & gc ) {
  }

  // --------------------------------------------------------------------------
  void
  Bicycle::setupUserMappedFunctions( GenericContainer const & gc_data ) {
  }

  // --------------------------------------------------------------------------
  void
  Bicycle::setupPointers( GenericContainer const & gc_data ) {
  }

  // --------------------------------------------------------------------------
  void
  Bicycle::setup( GenericContainer const & gc ) {

    setupParameters( gc );
    setupClasses( gc );
    setupUserMappedFunctions( gc );
    setupUserClasses( gc );
    setupPointers( gc );

    if ( gc.exists("Debug") )
      m_debug = gc("Debug").get_bool("Bicycle::setup, Debug");

    // setup model
    infoClasses();

    // setup solver
    m_solver.setup( &m_nlsys, m_console );
    m_solver.setSolverParameters( gc("Solver") );
  }

  // --------------------------------------------------------------------------
  void
  Bicycle::infoClasses() const {
    int msg_level = 2;
    std::ostringstream mstr;

    m_console->message("\nModel Parameters\n",msg_level);
    for ( integer i = 0; i < numModelPars; ++i ) {
      m_console->message(
        fmt::format("{:.>40} = {}\n",namesModelPars[i], ModelPars[i]),
        msg_level
      );
    }
  }

  //   ___                          _
  //  | _ \___ _ __  __ _ _ __ _ __(_)_ _  __ _
  //  |   / -_) '  \/ _` | '_ \ '_ \ | ' \/ _` |
  //  |_|_\___|_|_|_\__,_| .__/ .__/_|_||_\__, |
  //                     |_|  |_|         |___/
  integer
  Bicycle::NonlinearSystem::numEquations(void) const
  { return pNLSYS->steady_state_equations_numEqns(); }

  void
  Bicycle::NonlinearSystem::initialGuess( real_type x[] )
  { pNLSYS->get_steady_state_default_guess( pNLSYS->m_zeta0, x, x+numXvars ); }

  bool
  Bicycle::NonlinearSystem::checkIfAdmissible( real_type const x[] ) const
  { return true; }

  bool
  Bicycle::NonlinearSystem::evaluateFunction(
    real_type const x[],
    real_type       F[]
  ) {
    return pNLSYS->steady_state_equations( pNLSYS->m_zeta0, x, F );
  }

  integer
  Bicycle::NonlinearSystem::evaluateMeritFunctions(
    real_type const x[],
    real_type       m[]
  ) const {
    return 0;
  }

  bool
  Bicycle::NonlinearSystem::loadJacobian(
    real_type const x[]
  ) {
    pNLSYS->steady_state_DequationsDz_sparse(
      pNLSYS->m_zeta0, x, pNLSYS->m_DeqDz_sparse_vals
    );
    pNLSYS->m_A.zero_fill();
    pNLSYS->m_A.load(
      pNLSYS->m_DeqDz_sparse.rows,
      pNLSYS->m_DeqDz_sparse.cols,
      pNLSYS->m_DeqDz_sparse_vals,
      pNLSYS->m_DeqDz_sparse.nnz
    );
    return true;
  }

  bool
  Bicycle::NonlinearSystem::factorizeJacobian() {
    return pNLSYS->m_lu.factorize( pNLSYS->m_A.data(), pNLSYS->m_A.lDim() );
  }

  bool
  Bicycle::NonlinearSystem::solveJacobianSystem ( real_type inout[] ) {
    return pNLSYS->m_lu.solve( inout );
  }

  /*
  //    ____        _
  //   / ___|  ___ | |_   _____
  //   \___ \ / _ \| \ \ / / _ \
  //    ___) | (_) | |\ V /  __/
  //   |____/ \___/|_| \_/ \___|
  */
  // --------------------------------------------------------------------------
  bool
  Bicycle::solve_steady_state( GenericContainer & gc,
                               GenericContainer & gc_sol ) {
    bool ok = true;
    gc_sol["converged"]  = false;
    gc_sol["iterations"] = 0;

    try {

      // setup model
      this->setup( gc );

      // compute steady state solution
      this->compute_steady_state();

      // get guess and steady state solution
      vec_real_type   & XG      = gc_sol["states_guess"].set_vec_real(9);
      vec_real_type   & X       = gc_sol["states"].set_vec_real(9);
      vec_real_type   & UG      = gc_sol["controls_guess"].set_vec_real(3);
      vec_real_type   & U       = gc_sol["controls"].set_vec_real(3);
      vec_string_type & xnames  = gc_sol["state_names"].set_vec_string(9);
      vec_string_type & unames  = gc_sol["control_names"].set_vec_string(3);

      for ( integer i = 0; i < 9; ++i ) xnames[i] = xLabel(i);
      for ( integer i = 0; i < 3; ++i ) unames[i] = uLabel(i);

      real_type t0=0;
      this->get_steady_state_default_guess( t0, &XG.front(), &UG.front() );
      this->get_steady_state_solution( t0, &X.front(), &U.front() );

      // Compute and get eigen values
      GenericContainer & eigsVec = gc_sol["steady_state_analysis"];
      this->compute_eigensystem( 0.0, &X.front(), &U.front(), eigsVec );

      // add some informations
      ok = m_solver.isConverged();
      gc_sol("converged")  = ok;
      gc_sol("iterations") = m_solver.iterations();
    }
    catch ( std::exception const & exc ) {
      gc_sol["Error"] = exc.what();
      ok = false;
    }
    catch ( char const exc[] ) {
      gc_sol["Error"] = exc;
      ok = false;
    }
    catch (...) {
      gc_sol["Error"] = "Bicycle::solver, fatal: unknown error";
      ok = false;
    }
    return ok;
  }

}
