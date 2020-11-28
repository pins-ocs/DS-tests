/*-----------------------------------------------------------------------*\
 |  file: Bicycle.hh                                                     |
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


#ifndef BICYCLE_DOT_HH
#define BICYCLE_DOT_HH

#include <MechatronixCore/MechatronixCore.hh>
#include <MechatronixODE/MechatronixODE.hh>
#include <MechatronixRoad/MechatronixRoad.hh>
#include <MechatronixManufacturing/MechatronixManufacturing.hh>
#include <MechatronixInterfaceMruby/MechatronixInterfaceMruby.hh>


#ifdef MECHATRONIX_OS_WINDOWS
  #ifndef BICYCLE_API_DLL
    #ifdef BICYCLE_EXPORT
      #define BICYCLE_API_DLL __declspec(dllexport)
    #elif defined(BICYCLE_IMPORT)
      #define BICYCLE_API_DLL __declspec(dllimport)
    #else
      #define BICYCLE_API_DLL
    #endif
  #endif
  #ifndef _SCL_SECURE_NO_WARNINGS
    #define _SCL_SECURE_NO_WARNINGS 1
  #endif
#else
  #define BICYCLE_API_DLL
#endif

// Macro definition to use Mechatronix Classes:
// - MechatronixRoad namespace
// - MechatronixVehicle namespace: it includes Tyre Class and Engine Class
// User has to uncomment each macro definition to use appropriate class

namespace BicycleDefine {

  using namespace MechatronixLoad;

  using namespace std;
  using namespace MechatronixLoad;



  class Bicycle : public Mechatronix::ModelDynamicalSystem {

    //   __|_ _  _. _|    __|_ _._|_ _
    //  _> |_(/_(_|(_|\/ _> |_(_| |_(/_
    //                /
    class NonlinearSystem : public Mechatronix::NonlinearSystemBase {
      Bicycle * m_NLSYS;
    public:
      BICYCLE_API_DLL
      explicit
      NonlinearSystem( string const & name, Bicycle * NLSYS )
      : Mechatronix::NonlinearSystemBase(name)
      , m_NLSYS(NLSYS) {}

      BICYCLE_API_DLL
      virtual ~NonlinearSystem() {}

      BICYCLE_API_DLL virtual integer numEquations           ( void ) const MECHATRONIX_OVERRIDE;
      BICYCLE_API_DLL virtual void    initialGuess           ( real_type x[] ) MECHATRONIX_OVERRIDE;
      BICYCLE_API_DLL virtual void    updateContinuation     ( integer phase, real_type s ) MECHATRONIX_OVERRIDE;
      BICYCLE_API_DLL virtual bool    checkIfAdmissible      ( real_type const x[] ) const MECHATRONIX_OVERRIDE;
      BICYCLE_API_DLL virtual integer evaluateMeritFunctions ( real_type const x[], real_type res[] ) const MECHATRONIX_OVERRIDE;
      BICYCLE_API_DLL virtual bool    evaluateFunction       ( real_type const x[], real_type F[] ) MECHATRONIX_OVERRIDE;
      BICYCLE_API_DLL virtual bool    loadJacobian           ( real_type const x[] ) MECHATRONIX_OVERRIDE;
      BICYCLE_API_DLL virtual bool    factorizeJacobian      ( void ) MECHATRONIX_OVERRIDE;
      BICYCLE_API_DLL virtual bool    solveJacobianSystem    ( real_type in_out[] ) MECHATRONIX_OVERRIDE;
    };

    // dynamic allocation
    Malloc<real_type> m_baseValue;
    Malloc<integer>   m_baseIndex;

    NonlinearSystem           m_nlsys;
    Mechatronix::NewtonDumped m_solver;

    bool      m_debug;
    Console * m_console;

    // Model Paramaters
    real_type ModelPars[28];

    // Constraints 1D

    // Constraints 2D

    // User mapped functions

    // User classes (internal)

    // User classes (external)

    // block copy constructor
    Bicycle( Bicycle const & );
    Bicycle const & operator = ( Bicycle const & );

    // Sparse matrix
    mutable SparseCCOOR_struct m_DeqDz_sparse;
    mutable real_type *        m_DeqDz_sparse_vals;
    real_type                  m_zeta0;

    mutable alglin::LU_no_alloc<real_type>   m_lu;
    mutable alglin::MatrixWrapper<real_type> m_A;

  public:

    BICYCLE_API_DLL
    explicit
    Bicycle( string const & name, Console * console );

    BICYCLE_API_DLL virtual ~Bicycle();

    NonlinearSystem       & nlsys()       { return m_nlsys; }
    NonlinearSystem const & nlsys() const { return m_nlsys; }

    BICYCLE_API_DLL void infoClasses() const;

    // C++ initializer (all in one)
    BICYCLE_API_DLL void setup( GenericContainer const & gc );

    // C++ initializer (raccolti in setup( gc ))
    BICYCLE_API_DLL void setupParameters( GenericContainer const & gc );
    BICYCLE_API_DLL void setupParameters( real_type const Pars[] );
    BICYCLE_API_DLL void updateParameter( real_type val, integer idx ) { ModelPars[idx] = val; }
    BICYCLE_API_DLL void setupClasses( GenericContainer const & gc );
    BICYCLE_API_DLL void setupUserClasses( GenericContainer const & gc );
    BICYCLE_API_DLL void setupUserMappedFunctions( GenericContainer const & gc );
    BICYCLE_API_DLL void setupPointers( GenericContainer const & gc );

    // user functions prototype (with derivative)

    //  ___   _   ___
    // |   \ /_\ | __|
    // | |) / _ \| _|
    // |___/_/ \_\___|
    //

    // non virtual!
    BICYCLE_API_DLL
    void
    get_initial_conditions( real_type zeta, real_type X[] ) const;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    BICYCLE_API_DLL
    void
    rhs_eval(
      real_type       zeta,
      real_type const X[],
      real_type const U[],
      real_type       result[]
    ) const;
    integer rhs_numEqns() const
    { return 9; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    BICYCLE_API_DLL
    void
    closed_loop_eval(
      real_type       zeta,
      real_type const X[],
      real_type       result[]
    ) const;
    integer closed_loop_numEqns() const
    { return 3; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    BICYCLE_API_DLL
    void
    DrhsDx_eval(
      real_type       zeta,
      real_type const X[],
      real_type const U[],
      real_type       result[]
    ) const;
    void    DrhsDx_pattern( integer iIndex[], integer jIndex[] ) const;
    integer DrhsDx_numRows() const { return 9; }
    integer DrhsDx_numCols() const { return 9; }
    integer DrhsDx_nnz()     const { return 48; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    BICYCLE_API_DLL
    void
    DrhsDu_eval(
      real_type       zeta,
      real_type const X[],
      real_type const U[],
      real_type       result[]
    ) const;
    BICYCLE_API_DLL void    DrhsDu_pattern( integer iIndex[], integer jIndex[] ) const;
    BICYCLE_API_DLL integer DrhsDu_numRows() const { return 9; }
    BICYCLE_API_DLL integer DrhsDu_numCols() const { return 3; }
    BICYCLE_API_DLL integer DrhsDu_nnz()     const { return 10; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    BICYCLE_API_DLL
    void
    A_eval(
      real_type       zeta,
      real_type const X[],
      real_type       result[]
    ) const;
    BICYCLE_API_DLL void    A_pattern( integer iIndex[], integer jIndex[] ) const;
    BICYCLE_API_DLL integer A_numRows() const { return 9; }
    BICYCLE_API_DLL integer A_numCols() const { return 9; }
    BICYCLE_API_DLL integer A_nnz()     const { return 20; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    BICYCLE_API_DLL
    void
    DetaDx_eval(
      real_type       zeta,
      real_type const X[],
      real_type const L[],
      real_type       result[]
    ) const;
    BICYCLE_API_DLL void    DetaDx_pattern( integer iIndex[], integer jIndex[] ) const;
    BICYCLE_API_DLL integer DetaDx_numRows() const { return 9; }
    BICYCLE_API_DLL integer DetaDx_numCols() const { return 9; }
    BICYCLE_API_DLL integer DetaDx_nnz()     const { return 13; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    BICYCLE_API_DLL
    void
    Dclosed_loopDx_eval(
      real_type       zeta,
      real_type const X[],
      real_type       result[]
    ) const;
    BICYCLE_API_DLL void    Dclosed_loopDx_pattern( integer iIndex[], integer jIndex[] ) const;
    BICYCLE_API_DLL integer Dclosed_loopDx_numRows() const { return 3; }
    BICYCLE_API_DLL integer Dclosed_loopDx_numCols() const { return 9; }
    BICYCLE_API_DLL integer Dclosed_loopDx_nnz()     const { return 0; }

    //   ___ _               _        ___ _        _
    //  / __| |_ ___ __ _ __| |_  _  / __| |_ __ _| |_ ___
    //  \__ \  _/ -_) _` / _` | || | \__ \  _/ _` |  _/ -_)
    //  |___/\__\___\__,_\__,_|\_, | |___/\__\__,_|\__\___|
    //                         |__/
    BICYCLE_API_DLL
    void
    get_steady_state_default_guess(
      real_type & zeta,
      real_type   X[],
      real_type   U[]
    ) const;

    BICYCLE_API_DLL
    integer
    steady_state_equations_numEqns() const { return 12; }

    BICYCLE_API_DLL
    bool
    steady_state_equations(
      real_type       zeta,
      real_type const Z[],
      real_type       result[]
    ) const;

    BICYCLE_API_DLL
    void
    steady_state_DequationsDz_sparse(
      real_type       zeta,
      real_type const Z[],
      real_type       result[]
    ) const;

    BICYCLE_API_DLL void    steady_state_DequationsDz_pattern( integer iIndex[], integer jIndex[] ) const;
    BICYCLE_API_DLL integer steady_state_DequationsDz_numRows() const { return 12; }
    BICYCLE_API_DLL integer steady_state_DequationsDz_numCols() const { return 12; }
    BICYCLE_API_DLL integer steady_state_DequationsDz_nnz()     const { return 61; }

    BICYCLE_API_DLL
    void
    compute_steady_state() {
      m_solver.reset();
      m_solver.allocate();
      m_solver.zeroGuess(); // ricordarsi di azzerare
      m_solver.setGuess(); // da cambiare
      m_solver.resetStatistic(); // da cambiare
      m_solver.solve(m_solver.getMaxIter());
      m_solver.accumulateIter();
      m_solver.statistic();
    }

    //   ___        _     ___                       _
    //  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
    //  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
    //  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
    //                                                    |___/
    BICYCLE_API_DLL virtual
    integer
    postProcessing_numEqns() const;

    BICYCLE_API_DLL virtual
    void
    postProcessing(
      real_type       zeta,
      real_type const X[],
      real_type const U[],
      real_type       result[]
    ) const;

    //   ___ _               _      ___ _        _
    //  / __| |_ ___ __ _ __| |_  _/ __| |_ __ _| |_ ___
    //  \__ \  _/ -_) _` / _` | || \__ \  _/ _` |  _/ -_)
    //  |___/\__\___\__,_\__,_|\_, |___/\__\__,_|\__\___|
    //                         |__/
    //
    BICYCLE_API_DLL
    void
    get_steady_state_solution(
      real_type & zeta,
      real_type   X[],
      real_type   U[]
    ) const {
      real_type const * Z  = m_solver.solution();
      real_type const * Zu = Z+9;
      zeta = m_zeta0;
      std::copy_n( Z, 9, X );
      std::copy_n( Zu, 3, U );
    }

    //
    //    ___      _
    //   / __| ___| |_ _____
    //   \__ \/ _ \ \ V / -_)
    //   |___/\___/_|\_/\___|
    //
    BICYCLE_API_DLL
    bool
    solve_steady_state( GenericContainer & gc_data, GenericContainer & gc_sol );
  };
}

namespace BicycleLoad {
  using BicycleDefine::Bicycle;

}

#endif
