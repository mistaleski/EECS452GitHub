function [ sig1Cor sig2Cor ] = fftPrep( sig1, sig2 )

L1 = length(sig1);
L2 = length(sig2);

newLen = max(nearestPow2(L1), nearestPow2(L2));

sig1Cor = zeros(1, newLen);
sig2Cor = zeros(1, newLen);

sig1Cor(1:L1) = sig1;
sig2Cor(1:L2) = sig2;

end

