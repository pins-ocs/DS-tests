#ifndef VEHICLE_COMPONENTS_TIRE_HH
#define VEHICLE_COMPONENTS_TIRE_HH

#include <MechatronixCore/MechatronixCore.hh>

namespace VehicleComponents {

	//using namespace Common;
	//using namespace Regularized;
	using namespace MechatronixCore ;
    using namespace GC ;
    

  /*
  //  _____ _          _     _
  // |_   _(_)_ __ ___| |   (_)_ __   ___  __ _ _ __
  //   | | | | '__/ _ \ |   | | '_ \ / _ \/ _` | '__|
  //   | | | | | |  __/ |___| | | | |  __/ (_| | |
  //   |_| |_|_|  \___|_____|_|_| |_|\___|\__,_|_|
  */

	extern "C" DLL_PUBLIC class TireLinear  {

  private:
    string	  name;
    valueType KLat;   /**< \brief  \f$ K_{ \lambda } \f$ */
    valueType KLong;  /**< \brief \f$ K_{ \kappa }   \f$ */
	valueType Kphi;
    
  public:

	// constructor & destructor
	 TireLinear (string const & _name) : KLat(20.0), KLong(20.0), Kphi(1.0) { name = _name;}
	~TireLinear ()  {}

	  //! Method that make the setup of the tire, reading all the parameters
    void setup( GenericContainer const & gc ) ;
    
	void info( ostream & stream );

 	// LATERAL FORCE

    //! Method that contains the lateral tire force formula
    valueType tireFLat(valueType,valueType,valueType,valueType) const ;

    //! Method that contains the simple derivate of the lateral tire force formula
    valueType tireFLat_D_1(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the simple derivate of the lateral tire force formula
    valueType tireFLat_D_2(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the simple derivate of the lateral tire force formula
    valueType tireFLat_D_3(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the simple derivate of the lateral tire force formula
    valueType tireFLat_D_4(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the lateral tire force formula
    valueType tireFLat_D_1_1(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the lateral tire force formula
    valueType tireFLat_D_1_2(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the lateral tire force formula
    valueType tireFLat_D_1_3(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the lateral tire force formula
    valueType tireFLat_D_1_4(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the lateral tire force formula
    valueType tireFLat_D_2_2(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the lateral tire force formula
    valueType tireFLat_D_2_3(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the lateral tire force formula
    valueType tireFLat_D_2_4(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the lateral tire force formula
    valueType tireFLat_D_3_3(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the lateral tire force formula
    valueType tireFLat_D_3_4(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the lateral tire force formula
    valueType tireFLat_D_4_4(valueType,valueType,valueType,valueType) const ;

	// LONGITUDINAL FORCE
	/*
    
    //! Method that contains the longitudinal tire force formula
    valueType tireFLong(valueType,valueType,valueType,valueType) const ;

    //! Method that contains the simple derivate of the longitudinal tire force formula
    valueType tireFLong_1(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the simple derivate of the longitudinal tire force formula
    valueType tireFLong_2(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the simple derivate of the longitudinal tire force formula
    valueType tireFLong_3(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the simple derivate of the longitudinal tire force formula
    valueType tireFLong_4(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the longitudinal tire force formula
    valueType tireFLong_1_1(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the longitudinal tire force formula
    valueType tireFLong_1_2(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the longitudinal tire force formula
    valueType tireFLong_1_3(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the longitudinal tire force formula
    valueType tireFLong_1_4(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the longitudinal tire force formula
    valueType tireFLong_2_2(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the longitudinal tire force formula
    valueType tireFLong_2_3(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the longitudinal tire force formula
    valueType tireFLong_2_4(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the longitudinal tire force formula
    valueType tireFLong_3_3(valueType,valueType,valueType,valueType) const ;
    
    //! Method that contains the mixed derivate of the longitudinal tire force formula
    valueType tireFLong_3_4(valueType,valueType,valueType,valueType) const ;

    //! Method that contains the mixed derivate of the longitudinal tire force formula
    valueType tireFLong_4_4(valueType,valueType,valueType,valueType) const ; 
	};

	*/


};

}
#endif
