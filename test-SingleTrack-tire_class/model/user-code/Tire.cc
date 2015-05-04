#include <Tire.hh>
#include <string>
#include <sstream>

namespace VehicleComponents {

  using namespace std;
  

  /*
  //  _____ _          _     _
  // |_   _(_)_ __ ___| |   (_)_ __   ___  __ _ _ __
  //   | | | | '__/ _ \ |   | | '_ \ / _ \/ _` | '__|
  //   | | | | | |  __/ |___| | | | |  __/ (_| | |
  //   |_| |_|_|  \___|_____|_|_| |_|\___|\__,_|_|
  */
  void TireLinear::setup(GenericContainer const & gc) {
    // Records KL, KLong in specified variables
	KLat  = gc( "KLat"  ).get_number();  //gives error if not defined
    //KLat  = gc[ "KLat"  ];  //if not defined, creates it and sets to zero
	Kphi  = gc( "Kphi"  ).get_number();
    KLong = gc( "KLong" ).get_number();

	gc.info(cout);
  }
  

  	void TireLinear::info( ostream & stream ) {
	stream << "KLat" << KLat << "\n";
	};




  #include "linear_tire_formulas_lib.cc"

  

}
