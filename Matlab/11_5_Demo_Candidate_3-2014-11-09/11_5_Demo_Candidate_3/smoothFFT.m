function [ SmoothedFFT ] = smoothFFT( FFT )

clf

% Apply smoothing in 3 different sections
a1 = sgolayfilt(20*log10(abs(real(FFT))), 1, 11);
a2 = sgolayfilt(20*log10(abs(real(FFT))), 1, 111);
a3 = sgolayfilt(20*log10(abs(real(FFT))), 1, 511);

% Concatenate
xover1 = 600;
xover2 = 3500;
k1(1:xover1) = a1(1:xover1);
k1((xover1+1):xover2) = a2((xover1+1):xover2);
k1((xover2+1):131072) = a3((xover2+1):131072);

SmoothedFFT = (FFT./abs(FFT)) .* (10.^(k1/20));

% plotFFT( FFTsweep, 1, 2, 1, 1, 'sine', FS);
% hold all
% plotFFT( FFTsweep, 1, 2, 1, 2, 'sine', FS);
% hold all
% 
% plotFFT( FFT, 1, 2,1,1, 'measured', FS );
% hold all
% 
% plotFFT( k1, 1, 2,1,1, 'measured', FS );
% hold all
% plotFFT( k1, 1, 2,1,2, 'measured', FS );
% hold all


end

