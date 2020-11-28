/*-----------------------------------------------------------------------*\
 |  file: Bicycle_Main.cc                                                |
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


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wundef"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wswitch-enum"
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wall"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wc99-extensions"
#pragma clang diagnostic ignored "-Wundef"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wswitch-enum"
#endif
#ifdef _MSC_VER
#pragma warning( disable : 4200 )
#endif

#include <MechatronixInterfaceMruby/MechatronixInterfaceMruby.hh>

#include "Bicycle.hh"
#include "Bicycle_Pars.hh"

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic pop
#endif

using namespace std;
using namespace MechatronixLoad;


using namespace BicycleLoad;

using GenericContainerNamespace::GenericContainer;
using GenericContainerNamespace::vec_real_type;
using GenericContainerNamespace::real_type;

#define EXTERN_C extern "C"

class Bicycle_Problem {
  Bicycle model;

  // block copy constructor
  Bicycle_Problem( Bicycle_Problem const & );
  Bicycle_Problem const & operator = ( Bicycle_Problem const & );

  // solutore ODE
  Mechatronix::Radau5ODE ODEsolver;

public:

  Bicycle_Problem( Console * console )
  : model("Bicycle",console)
  , ODEsolver(console)
  {}

  ~Bicycle_Problem() {}

  // ---------------------------------------------------------------------
  bool
  setup( GenericContainer & gc_data ) {
    bool ok = true;
    try {
      GenericContainer & ptrs = gc_data["Pointers"];
      model.setup(gc_data);
    }
    catch ( std::exception const & exc ) {
      ok = false;
      gc_data["Error"] = exc.what();
    }
    catch (...) {
      ok = false;
      gc_data["Error"] = "Bicycle_ds_setup, fatal: unknown error";
    }
    return ok;
  }

  // ---------------------------------------------------------------------
  void
  get_initial_condition( GenericContainer & gc_init ) {
    try {
      vec_real_type & x0 = gc_init["initial_value"].set_vec_real(9);
      real_type     & t0 = gc_init["integration_start"].set_real(0);
      model.get_initial_conditions( t0, &x0.front() ); // read initial condition generated
    }
    catch ( std::exception const & exc ) {
      gc_init["Error"] = exc.what();
    }
    catch (...) {
      gc_init["Error"] = "Bicycle_ds_setup, fatal: unknown error";
    }
  }

  // ---------------------------------------------------------------------
  void
  init_ODE(
    GenericContainer & odeData,
    GenericContainer & odeSol
  ) {
    try {
      // Setup ode integrator with dynamic model parameters
      ODEsolver.setup( &model );
      ODEsolver.gc_init( odeData, odeSol, "t" );
    }
    catch ( std::exception const & exc ) {
      odeSol["Error"] = exc.what();
    }
    catch (...) {
      odeSol["Error"] = "Bicycle_ds_setup, fatal: unknown error";
    }
  }

  // ---------------------------------------------------------------------
  void
  step_ODE( real_type t, GenericContainer & odeSol ) {
    try {
      ODEsolver.gc_evaluate( t, odeSol );
    }
    catch ( std::exception const & exc ) {
      odeSol["Error"] = exc.what();
    }
    catch (...) {
      odeSol["Error"] = "Bicycle_ds_setup, fatal: unknown error";
    }
  }

  // ---------------------------------------------------------------------
  void
  solve_ODE(
    GenericContainer & odeData,
    GenericContainer & odeSol
  ) {
    try {
      GenericContainer & odeSolver_gc = odeData("OdeSolver");
      real_type dt = odeSolver_gc("integration_step").get_number();
      real_type t0 = odeSolver_gc("integration_start").get_number();
      real_type t1 = odeSolver_gc("integration_end").get_number();

      // Setup ode integrator with dynamic model parameters
      ODEsolver.setup( &model );
      ODEsolver.gc_init( odeSolver_gc, odeSol, "t" );
      for ( integer i = 0; t0+i*dt <= t1; ++i )
        ODEsolver.gc_evaluate( t0+i*dt, odeSol );

      model.post_processing( odeSol );

    }
    catch ( std::exception const & exc ) {
      odeSol["Error"] = exc.what();
    }
    catch (...) {
      odeSol["Error"] = "Bicycle_ds_setup, fatal: unknown error";
    }
  }

  // ---------------------------------------------------------------------
  void
  solve_steady_state(
    GenericContainer & gc_data,
    GenericContainer & gc_solution
  ) {
    gc_solution["Error"] = ""; // no error found
    try {

      // alias for user object classes passed as pointers
      GenericContainer & ptrs = gc_data["Pointers"];

      model.solve_steady_state( gc_data, gc_solution );

    }
    catch ( std::exception const & exc ) {
      gc_solution["Error"] = exc.what();
    }
    catch (...) {
      gc_solution["Error"] = "Bicycle_ds_setup, fatal: unknown error";
    }
  }

};

// ---------------------------------------------------------------------

static map< string, Bicycle_Problem * > problems;
static Console console(&std::cout,4);

/*
::  ____        _             _____ _____ ___
:: |  _ \ _   _| |__  _   _  |  ___|  ___|_ _|
:: | |_) | | | | '_ \| | | | | |_  | |_   | |
:: |  _ <| |_| | |_) | |_| | |  _| |  _|  | |
:: |_| \_\\__,_|_.__/ \__, | |_|   |_|   |___|
::                    |___/
::  ___       _             __
:: |_ _|_ __ | |_ ___ _ __ / _| __ _  ___ ___
::  | || '_ \| __/ _ \ '__| |_ / _` |/ __/ _ \
::  | || | | | ||  __/ |  |  _| (_| | (_|  __/
:: |___|_| |_|\__\___|_|  |_|  \__,_|\___\___|
*/

EXTERN_C
BICYCLE_API_DLL
bool
Bicycle_ds_setup( char const id[], GenericContainer & gc_data ) {
  map< string, Bicycle_Problem * >::iterator it = problems.find(id);
  if ( it == problems.end() ) {
    problems[id] = new Bicycle_Problem(&console);
    return problems[id]->setup(gc_data);
  } else {
    return it->second->setup(gc_data);
  }
}

// ---------------------------------------------------------------------

EXTERN_C
BICYCLE_API_DLL
void
Bicycle_ds_solve_steady_state(
  char const         id[],
  GenericContainer & gc_data,
  GenericContainer & gc_solution
) {
  map< string, Bicycle_Problem * >::iterator it = problems.find(id);
  if ( it == problems.end() ) {
    gc_solution["Error"] = "Bicycle_ds_solve_steady_state, missing call to Bicycle_ds_setup!";
  } else {
    it->second->solve_steady_state( gc_data, gc_solution );
  }
}

// ---------------------------------------------------------------------

EXTERN_C
BICYCLE_API_DLL
void
Bicycle_ds_solve_ODE(
  char const         id[],
  GenericContainer & gc_data,
  GenericContainer & gc_solution
) {
  map< string, Bicycle_Problem * >::iterator it = problems.find(id);
  if ( it == problems.end() ) {
    gc_solution["Error"] = "Bicycle_ds_solve_ODE, missing call to Bicycle_ds_setup!";
  } else {
    it->second->solve_ODE(gc_data,gc_solution);
  }
}

// ---------------------------------------------------------------------

EXTERN_C
BICYCLE_API_DLL
void
Bicycle_ds_get_initial_condition(
  char const         id[],
  GenericContainer & gc_init
) {
  map< string, Bicycle_Problem * >::iterator it = problems.find(id);
  if ( it == problems.end() ) {
    gc_init["Error"] = "Bicycle_ds_get_initial_condition, missing call to Bicycle_ds_setup!";
  } else {
    it->second->get_initial_condition(gc_init);
  }
}

// ---------------------------------------------------------------------

EXTERN_C
BICYCLE_API_DLL
void
Bicycle_ds_init_ODE(
  char const         id[],
  GenericContainer & odeData,
  GenericContainer & odeSol
) {
  map< string, Bicycle_Problem * >::iterator it = problems.find(id);
  if ( it == problems.end() ) {
    odeSol["Error"] = "Bicycle_ds_init_ODE, missing call to Bicycle_ds_setup!";
  } else {
    it->second->init_ODE(odeData("OdeSolver"),odeSol);
  }
}

// ---------------------------------------------------------------------

EXTERN_C
BICYCLE_API_DLL
void
Bicycle_ds_step_ODE(
  char const         id[],
  real_type          t,
  GenericContainer & odeSol
) {
  map< string, Bicycle_Problem * >::iterator it = problems.find(id);
  if ( it == problems.end() ) {
    odeSol["Error"] = "Bicycle_ds_step_ODE, missing call to Bicycle_ds_setup!";
  } else {
    it->second->step_ODE(t,odeSol);
  }
}

/*                       _             _       _             __
::  _ __ ___  _ __ _   _| |__  _   _  (_)_ __ | |_ ___ _ __ / _| __ _  ___ ___
:: | '_ ` _ \| '__| | | | '_ \| | | | | | '_ \| __/ _ \ '__| |_ / _` |/ __/ _ \
:: | | | | | | |  | |_| | |_) | |_| | | | | | | ||  __/ |  |  _| (_| | (_|  __/
:: |_| |_| |_|_|   \__,_|_.__/ \__, | |_|_| |_|\__\___|_|  |_|  \__,_|\___\___|
::                             |___/
*/

EXTERN_C
BICYCLE_API_DLL
mrb_value
mrb_Bicycle_ds_solve_steady_state( mrb_state *mrb, mrb_value self ) {

  GenericContainer gc_data, gc_solution;

  // ruby parameters
  mrb_value id_value   = mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@id"   ));
  mrb_value data_value = mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@data" ));

  // to C++ parameters
  string id = mrb_str_to_cstr(mrb, id_value);
  Mechatronix::mrb_to_GC( mrb, data_value, gc_data, "mrb_to_GC:" );

  // call to the solver
  map< string, Bicycle_Problem * >::iterator it = problems.find(id);
  if ( it == problems.end() ) {
    gc_solution["Error"] = "Bicycle_ds_solve_steady_state, missing call to Bicycle_ds_setup!";
  } else {
    it->second->solve_steady_state( gc_data, gc_solution );
  }

  // return values
  mrb_value res = mrb_hash_new(mrb);
  Mechatronix::mrb_from_GC( mrb, gc_solution, res, "mrb_from_GC:" );
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@stationary_solution" ), res);
  return res;
}

// ---------------------------------------------------------------------

EXTERN_C
BICYCLE_API_DLL
mrb_value
mrb_Bicycle_ds_setup( mrb_state *mrb, mrb_value self ) {

  GenericContainer gc_data;

  // ruby parameters
  mrb_value id_value   = mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@id"   ));
  mrb_value data_value = mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@data" ));

  // to C++ parameters
  string id = mrb_str_to_cstr(mrb, id_value);
  Mechatronix::mrb_to_GC( mrb, data_value, gc_data, "mrb_to_GC:" );

  // call to the solver
  bool ok;
  map< string, Bicycle_Problem * >::iterator it = problems.find(id);
  if ( it == problems.end() ) {
    problems[id] = new Bicycle_Problem(&console);
    ok = problems[id]->setup(gc_data);
  } else {
    ok = it->second->setup(gc_data);
  }

  // return values
  if ( ok ) {
    return mrb_true_value();
  } else {
    mrb_raise(mrb, mrb_class_get(mrb, "RuntimeError"), gc_data("Error").get_string().c_str());
    return mrb_false_value();
  }
}

// ---------------------------------------------------------------------

EXTERN_C
BICYCLE_API_DLL
mrb_value
mrb_Bicycle_ds_init_ODE( mrb_state *mrb, mrb_value self ) {

  GenericContainer odeData, odeSol;

  // ruby parameters
  mrb_value id_value   = mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@id"   ));
  mrb_value data_value = mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@data" ));

  // to C++ parameters
  string id = mrb_str_to_cstr(mrb, id_value);
  Mechatronix::mrb_to_GC( mrb, data_value, odeData, "mrb_to_GC:" );

  // call to the solver
  map< string, Bicycle_Problem * >::iterator it = problems.find(id);
  if ( it == problems.end() ) {
    odeSol["Error"] = "Bicycle_ds_init_ODE, missing call to Bicycle_ds_setup!";
  } else {
    it->second->init_ODE(odeData("OdeSolver"),odeSol);
  }

  // return values
  mrb_value res = mrb_hash_new(mrb);
  Mechatronix::mrb_from_GC( mrb, odeSol, res, "mrb_from_GC:" );
  return res;
}

// ---------------------------------------------------------------------

EXTERN_C
BICYCLE_API_DLL
mrb_value
mrb_Bicycle_ds_step_ODE( mrb_state *mrb, mrb_value self ) {

  GenericContainer odeSol;

  // ruby parameters
  mrb_value id_value = mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@id" ));
  mrb_value t_value  = mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@t"  ));

  // to C++ parameters
  string id = mrb_str_to_cstr(mrb, id_value);
  real_type t = mrb_float( t_value );

  // call to the solver
  map< string, Bicycle_Problem * >::iterator it = problems.find(id);
  if ( it == problems.end() ) {
    odeSol["Error"] = "Bicycle_ds_step_ODE, missing call to Bicycle_ds_setup!";
  } else {
    it->second->step_ODE(t,odeSol);
  }

  // return values
  mrb_value res = mrb_hash_new(mrb);
  Mechatronix::mrb_from_GC( mrb, odeSol, res, "mrb_from_GC:" );
  return res;
}

// ---------------------------------------------------------------------

EXTERN_C
BICYCLE_API_DLL
mrb_value
mrb_Bicycle_ds_solve_ODE( mrb_state *mrb, mrb_value self ) {

  GenericContainer gc_data, gc_solution;

  // ruby parameters
  mrb_value id_value   = mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@id"   ));
  mrb_value data_value = mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@data" ));

  // to C++ parameters
  string id = mrb_str_to_cstr(mrb, id_value);
  Mechatronix::mrb_to_GC( mrb, data_value, gc_data, "mrb_to_GC:" );

  // call to the solver
  map< string, Bicycle_Problem * >::iterator it = problems.find(id);
  if ( it == problems.end() ) {
    gc_solution["Error"] = "Bicycle_ds_solve_ODE, missing call to Bicycle_ds_setup!";
  } else {
    it->second->solve_ODE(gc_data,gc_solution);
  }

  // return values
  mrb_value res = mrb_hash_new(mrb);
  Mechatronix::mrb_from_GC( mrb, gc_solution, res, "mrb_from_GC:" );
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@ode_solution" ), res);
  return res;
}

// ---------------------------------------------------------------------

EXTERN_C
BICYCLE_API_DLL
mrb_value
mrb_Bicycle_ds_get_initial_condition( mrb_state *mrb, mrb_value self ) {

  GenericContainer modelData;
  // ruby parameters
  mrb_value id_value = mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@id"   ));
  mrb_value data_value = mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "@data" ));
  Mechatronix::mrb_to_GC( mrb, data_value, modelData, "mrb_to_GC:" );

  // to C++ parameters
  string id = mrb_str_to_cstr(mrb, id_value);

  // call to the solver
  GenericContainer &ODEData = modelData("OdeSolver");
  map< string, Bicycle_Problem * >::iterator it = problems.find(id);
  if ( it == problems.end() ) {
    ODEData["Error"] = "Bicycle_ds_get_initial_condition, missing call to Bicycle_ds_setup!";
  } else {
    it->second->get_initial_condition(ODEData);
  }

  // return values
  mrb_value res = mrb_hash_new(mrb);
  Mechatronix::mrb_from_GC( mrb, modelData, res, "mrb_from_GC:" );
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@data" ), res);
  return res;
}

// ---------------------------------------------------------------------

EXTERN_C
BICYCLE_API_DLL
void
mrb_libBicycle_gem_init(mrb_state* mrb)
{
  struct RClass *ds_class;
  struct RClass *mechatronix;

  mechatronix = mrb_module_get(mrb, "Mechatronix");
  ds_class = mrb_class_get_under(mrb, mechatronix, "DSSolver");

  mrb_define_method(mrb, ds_class, "solve_steady_state",    mrb_Bicycle_ds_solve_steady_state,    MRB_ARGS_NONE());
  mrb_define_method(mrb, ds_class, "setup",                 mrb_Bicycle_ds_setup,                 MRB_ARGS_NONE());
  mrb_define_method(mrb, ds_class, "init_ODE",              mrb_Bicycle_ds_init_ODE,              MRB_ARGS_NONE());
  mrb_define_method(mrb, ds_class, "step_ODE",              mrb_Bicycle_ds_step_ODE,              MRB_ARGS_NONE());
  mrb_define_method(mrb, ds_class, "solve_ODE",             mrb_Bicycle_ds_solve_ODE,             MRB_ARGS_NONE());
  mrb_define_method(mrb, ds_class, "get_initial_condition", mrb_Bicycle_ds_get_initial_condition, MRB_ARGS_NONE());
}

// ---------------------------------------------------------------------

EXTERN_C
BICYCLE_API_DLL
void
mrb_libBicycle_gem_final(mrb_state* mrb)
{
}

// EOF: Bicycle_ruby_dll.cc
