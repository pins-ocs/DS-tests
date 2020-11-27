clc;

MROOT = matlabroot;

SRCS = '-I../../ds-cpp/src -I/usr/local/include -I/usr/local/include/superlu GenericContainerMatlabInterface.cc ';

fdir = dir('../../ds-cpp/src/*.cc');
for n=1:length(fdir)
  if strfind(fdir(n).name, '_dll.cc') > 0
  else
    SRCS = [SRCS,'../../ds-cpp/src/',fdir(n).name,' '];
  end
end

LIBS_MAC = [ '-framework Accelerate ', ...
             '-framework MechatronixCore ', ...
             '-framework MechatronixSolver ', ...
             '-framework MechatronixManufacturing ', ...
             '-framework MechatronixRoad ', ...
             '-framework MechatronixODE ', ...
             '-framework MechatronixVehicle ', ...
             '-framework MechatronixAstro ', ...
             '-lsuperlu ' ];

disp('---------------------------------------------------------');
disp('Compiling: Bicycle');

CMD = ['mex -output Bicycle_Mex -largeArrayDims Bicycle_Mex.cc ', SRCS];
if ismac
  CMD = [CMD, ' CXXFLAGS="$CXXFLAGS -std=c++11 -stdlib=libc++ -static-libgcc -static-libstdc++ -Wall -O2 -g -F/Library/Frameworks" LDFLAGS="$LDFLAGS ',LIBS_MAC,' "' ];
elseif isunix
  CMD = [CMD, ' CXXFLAGS="$CXXFLAGS -static-libgcc -static-libstdc++ -Wall -O2 -g"'];
elseif ispc
end
disp(CMD);
eval(CMD);
disp('----------------------- DONE ----------------------------');
