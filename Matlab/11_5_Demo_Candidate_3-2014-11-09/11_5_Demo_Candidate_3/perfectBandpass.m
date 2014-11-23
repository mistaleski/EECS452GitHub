function [ FFTout ] = perfectBandpass( fs, fstart, fstop, FFTin )

FFTout = FFTin;

N = length(FFTin);

lowIndex = getFFTIndex(N, fs, fstart);
highIndex = getFFTIndex(N, fs, fstop);

FFTout(1:lowIndex+1) = 0;
FFTout((N-lowIndex)+1:N) = 0;
FFTout(highIndex+1:(N-highIndex)+1) = 0;

end

