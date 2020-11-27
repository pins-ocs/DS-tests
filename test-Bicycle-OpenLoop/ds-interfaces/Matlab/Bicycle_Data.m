%-----------------------------------------------------------------------%
%  file: Bicycle                                                        %
%                                                                       %
%  version: 1.0   date 28/11/2020                                       %
%                                                                       %
%  Copyright (C) 2020                                                   %
%                                                                       %
%      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             %
%      Dipartimento di Ingegneria Industriale                           %
%      Universita` degli Studi di Trento                                %
%      Via Sommarive 9, I-38123, Trento, Italy                          %
%      email: enrico.bertolazzi@unitn.it                                %
%             francesco.biral@unitn.it                                  %
%             paolo.bosetti@unitn.it                                    %
%-----------------------------------------------------------------------%


%===========================================================================%
% CONSTANTS
%===========================================================================%

LU_automatic = int32(0);
LU_amodio    = int32(1);
LU_block     = int32(2);
LU_arceco    = int32(3);
LU_superLU   = int32(4);

SET  = true;
FREE = false;

% Auxiliary values

Bicycle_data.LU_method = LU_automatic;

% Level of message
Bicycle_data.InfoLevel = int32(4);

% spline output (all values as function of "s")
Bicycle_data.OutputSplines = {'s'};

% setup solver
Bicycle_data.Solver.max_iter             = int32(100);
Bicycle_data.Solver.max_step_iter        = int32(20);
Bicycle_data.Solver.max_accumulated_iter = int32(500);
Bicycle_data.Solver.tolerance            = 1.0e-08;

% ode solver parameter
Bicycledata.OdeSolver.integration_step  = 0.05;
Bicycledata.OdeSolver.integration_start = 0;
Bicycledata.OdeSolver.integration_end   = 10;




% Model Parameters
Bicycle_data.Parameters.Cdelta  = 10;
Bicycle_data.Parameters.Cf1     = 11174;
Bicycle_data.Parameters.Cf2     = 938.6;
Bicycle_data.Parameters.Cr1     = 15831;
Bicycle_data.Parameters.Cr2     = 1325.6;
Bicycle_data.Parameters.Cxz     = 0;
Bicycle_data.Parameters.Ifz     = 1.5;
Bicycle_data.Parameters.Ix      = 32;
Bicycle_data.Parameters.Iy      = 40;
Bicycle_data.Parameters.Iz      = 21;
Bicycle_data.Parameters.an      = 0.12;
Bicycle_data.Parameters.b       = 0.5;
Bicycle_data.Parameters.epsilon = 0.45;
Bicycle_data.Parameters.g       = 9.81;
Bicycle_data.Parameters.h       = 0.65;
Bicycle_data.Parameters.iwf     = 1;
Bicycle_data.Parameters.iwr     = 1;
Bicycle_data.Parameters.kD      = 0.2;
Bicycle_data.Parameters.m       = 220;
Bicycle_data.Parameters.rf      = 0.3048;
Bicycle_data.Parameters.rr      = 0.3048;
Bicycle_data.Parameters.sigma   = 0.2438;
Bicycle_data.Parameters.w       = 1.42;

% Initial conditions Parameters
Bicycle_data.Parameters.u0 = 10;

% Steady state parameters
Bicycle_data.Parameters.omega0 = 0;

% Closed-loop  parameters
Bicycle_data.Parameters.Xr0  = 0;
Bicycle_data.Parameters.f0   = 2;
Bicycle_data.Parameters.tau0 = 0.5;

% Post-processing  parameters

% User function parameters

% functions mapped on objects
Bicycle_data.MappedObjects = {};

% User defined classes initialization




% EOF
