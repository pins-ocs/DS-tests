#include "SingleTrackOL.hh"
#include "SingleTrackOL_Pars.hh"

namespace SingleTrackOLDefine {

  valueType
  SingleTrackOL::kappa( valueType _s ) const {

    //valueType t3   = cos(0.3141592654e1 * _s / 20);
    //return 0.1e-1 * t3;

	  valueType kappa = 0;
	       if (_s <20) kappa = 0;
	  else if (_s <40) kappa = 0.002*(40 - _s);
	  else if (_s <80) kappa = 0.040;
	  else             kappa = 0;

	  return kappa;

  }


  valueType
  SingleTrackOL::kappa_D( valueType _s ) const {

    //valueType t3   = sin(0.3141592654e1 * _s / 20);
    //return -0.5000000000e-3 * t3 * 0.3141592654e1;
	return 0;

  }


  valueType
  SingleTrackOL::kappa_DD( valueType _s ) const {

    //valueType t3   = cos(0.3141592654e1 * _s / 20);
    //valueType t4   = 0.3141592654e1 * 0.3141592654e1;
    //return -0.2500000000e-4 * t3 * t4;
	return 0;

  }
  
}