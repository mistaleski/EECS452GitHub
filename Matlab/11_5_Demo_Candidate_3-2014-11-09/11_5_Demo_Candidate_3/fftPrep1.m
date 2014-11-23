function [ sig1Cor ] = fftPrep( sig1  )

L1 = length(sig1);

newLen = nearestPow2(L1);

sig1Cor = zeros(1, newLen);

sig1Cor(1:L1) = sig1;

end

