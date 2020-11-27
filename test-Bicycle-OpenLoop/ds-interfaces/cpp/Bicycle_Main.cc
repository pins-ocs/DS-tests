/*-----------------------------------------------------------------------*\
 |  file: Bicycle_SteadyState_Main.cc                                    |
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


#define MECHATRONIX_USE_RUBY
//#define MECHATRONIX_USE_LUA

#include "Bicycle.hh"
#include "Bicycle_Pars.hh"

using namespace std;
using namespace MechatronixLoad;


using namespace BicycleLoad;

using GenericContainerNamespace::writeTable;

int
main() {

  Mechatronix::Console console(&std::cout,4);
  GenericContainer     gc_data, gc_sol;
  Mechatronix::Radau5ODE ODEsolver(&console);
  Bicycle              model("Bicycle",&console);

  try {

    #ifdef MECHATRONIX_USE_RUBY
    string fname = "./data/Bicycle_Data.rb";
    #endif
    #ifdef MECHATRONIX_USE_LUA
    string fname = "./data/Bicycle_Data.lua";
    #endif

    // read Ruby/Lua script
    Mechatronix::load_script( fname, gc_data );

    // alias for user object classes passed as pointers
    GenericContainer & ptrs = gc_data["Pointers"];

    model.setup( gc_data );

    #define NO_STATIONARY_SOLUTION
    #ifndef NO_STATIONARY_SOLUTION

    bool ok = model.solve_steady_state( gc_data, gc_sol );
    UTILS_ASSERT0( ok, "Failed to solve stationary problem\n" );

    // get guess and steady state solution
    vec_real_type const & XG = gc_sol["states_guess"].get_vec_real();
    vec_real_type const & X  = gc_sol["states"].get_vec_real();
    vec_real_type const & UG = gc_sol["controls_guess"].get_vec_real();
    vec_real_type const & U  = gc_sol["controls"].get_vec_real();

    integer nx = 9, nu = 3;

    // Print on screen steady state solution
    cout << "\n\nVariable                     | Guess      | Solution\n";
    cout << "________________________________________________________\n";
    for ( integer i = 0; i < nx; ++i )
      fmt::print(
        "{:<20} X[{:3}] = {12.6} | {}", model.xLabel(i), i, XG[i], X[i]
      );
    cout << "________________________________________________________\n";
    for ( integer i = 0; i < nu; ++i )
      fmt::print(
        "{:<20} X[{:3}] = {12.6} | {}", model.uLabel(i), i, UG[i], U[i]
      );
    cout << "________________________________________________________\n";

    GenericContainer const & eigs = gc_sol("steady_state_analysis");

    cout << "\n\nEigenvalues\n";
    writeTableFormatted( eigs("headers_eival").get_vec_string(),
                         eigs("eigenvalues").get_vector(),
                         cout );

    // cout << "\n\nEigen values and eigen vectors\n";
    ofstream file_eigensystem("data/Bicycle_eigensystem_results.txt");
    writeTable( eigs("headers_eivec").get_vec_string(),
                eigs("eigenvectors").get_vector(),
                file_eigensystem );
    file_eigensystem.close();

    #endif

    // ODE integration

    GenericContainer & odeData = gc_data("OdeSolver"); // copy container
    GenericContainer & odeSol  = gc_data["OdeSolution"]; // copy container
    vec_real_type    & x0      = odeData["initial_value"].set_vec_real(9);

    real_type dt = odeData("integration_step").get_number();
    real_type t0 = odeData("integration_start").get_number();
    real_type t1 = odeData("integration_end").get_number();

    // re-initialize model reading parameters from generic container ``gc_data''
    model.setup(gc_data);
    model.get_initial_conditions( t0, &x0.front() ); // read initial condition

    // Setup ode integrator with dynamic model parameters
    ODEsolver.setup( &model );
    ODEsolver.gc_init( odeData, odeSol, "t" );
    for ( integer i = 0; t0+i*dt <= t1; ++i )
      ODEsolver.gc_evaluate( t0+i*dt, odeSol );

    model.post_processing( odeSol );

    cout << "\nWriting result file\n";
    ofstream file( "data/Bicycle_ode_results.txt" );
    writeTable( odeSol("headers").get_vec_string(),
                odeSol("data").get_vector(),
                file );
    file.close();

  }
  catch ( std::exception const & exc ) {
    console.error(exc.what());
    ALL_DONE_FOLKS;
    exit(0);
  }
  catch ( char const exc[] ) {
    console.error(exc);
    ALL_DONE_FOLKS;
    exit(0);
  }
  catch (...) {
    console.error("ERRORE SCONOSCIUTO\n");
    ALL_DONE_FOLKS;
    exit(0);
  }

  ALL_DONE_FOLKS;
}
