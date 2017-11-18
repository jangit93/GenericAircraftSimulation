% read in 

function [Data] = readIn(filename,delimiterIn,headerlinesIn)
cd ../
cd Output
% delimiterIn = ' ';
% headerlinesIn = 1;
[Data] = importdata(filename,delimiterIn,headerlinesIn);

cd ../
cd MATLAB
end