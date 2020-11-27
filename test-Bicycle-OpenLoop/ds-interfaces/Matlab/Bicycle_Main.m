% -------------------------------------------------------------------------
% INITIALIZATION
% -------------------------------------------------------------------------
clc;
clear all;
close all
figsize=[0,0,400,800];

Bicycle_Data;

% =============================================================================%
%                           _         ____  ____
%           _ __ ___   __ _(_)_ __   |  _ \/ ___|
%          | '_ ` _ \ / _` | | '_ \  | | | \___ \
%          | | | | | | (_| | | | | | | |_| |___) |
%          |_| |_| |_|\__,_|_|_| |_| |____/|____/
%
% =============================================================================%

%Bicycle_Mex('help'); % usage

% -----------------------------------------------------------------------------
% SET UP OF DS  PROBLEM
% -----------------------------------------------------------------------------
% List of DS problem's variables

xvars = { 'u','v','omega','phi','delta','Yr','Yf','phi_dot','delta_dot' };

% List of DS problem's controls

uvars = { 'tau','Xr','Xf' };

% List of DS problem's post process variables

postvars = {  };


% READ PROBLEM DATA-------------------------------------------------------------
% model data from 'model' structure defined in the following m.file

fprintf(1,'\n> Initializing problem with data\n');
Bicycle_Mex('setup', Bicycle_data);

% -------------------------------------------------------------------------
% COMPUTE STEADY STATE SOLUTION
% -------------------------------------------------------------------------
fprintf(1,'\n> Computing steady state solution and eigen value analysis\n');

warning_level = int32(1);
steady_state = Bicycle_Mex('steady_state', warning_level);

% -------------------------------------------------------------------------
% INTEGRATE EQUATIONS
% -------------------------------------------------------------------------
fprintf(1,'\n> Integrating equations of motion\n');

% Overriding default integration setting
ics      = steady_state.states; % initialise ode with just computed steady state
tsample  = 0:0.01:1.0;          % define integration range

% Closed-loop  parameters to be used in case they need to be updated

Bicycle_data.Parameters.Xr0  = 0;

Bicycle_data.Parameters.f0   = 2;

Bicycle_data.Parameters.tau0 = 0.5;


solution = Bicycle_Mex('do_integration_step',tsample, ics, Bicycle_data);

fprintf(1,'\n> End\n');
%%clear mex
