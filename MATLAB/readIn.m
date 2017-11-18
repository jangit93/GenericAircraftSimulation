% read in 

function [Data,delimiterOut,headerlinesOut] = readIn(filename,delimiterIn,headerlinesIn)
cd ../
cd Output
% delimiterIn = ' ';
% headerlinesIn = 1;
[Data,delimiterOut,headerlinesOut] = importdata(filename,delimiterIn,headerlinesIn);

cd ../
cd MATLAB
end