/*-----------------------------------------------------------------------*\
 |  file: Bicycle_Pars.hh                                                |
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


#ifndef BICYCLEPARS_DOT_HH
#define BICYCLEPARS_DOT_HH

#define numModelPars             28
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 9
#define numUvars                 3
#define numPostProcess           0

// Xvars
#define iX_u         0
#define iX_v         1
#define iX_omega     2
#define iX_phi       3
#define iX_delta     4
#define iX_Yr        5
#define iX_Yf        6
#define iX_phi_dot   7
#define iX_delta_dot 8

// Uvars
#define iU_tau       0
#define iU_Xr        1
#define iU_Xf        2

// ModelPars Maps
#define iM_Cdelta    0
#define iM_Cf1       1
#define iM_Cf2       2
#define iM_Cr1       3
#define iM_Cr2       4
#define iM_Cxz       5
#define iM_Ifz       6
#define iM_Ix        7
#define iM_Iy        8
#define iM_Iz        9
#define iM_Xr0       10
#define iM_an        11
#define iM_b         12
#define iM_epsilon   13
#define iM_f0        14
#define iM_g         15
#define iM_h         16
#define iM_iwf       17
#define iM_iwr       18
#define iM_kD        19
#define iM_m         20
#define iM_omega0    21
#define iM_rf        22
#define iM_rr        23
#define iM_sigma     24
#define iM_tau0      25
#define iM_u0        26
#define iM_w         27

#endif
