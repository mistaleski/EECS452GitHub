function [ ] = FFTCompare3( FFT1, FFT2, FFT3, figNum, m, n, p, figName,sig1Name,sig2Name, sig2Name3, fs )

FMIN = 20; % Hz
FMAX = 20e3; % Hz

figure(figNum);
indices1 = 1:(length(FFT1)/2);
indices2 = 1:(length(FFT2)/2);
indices3 = 1:(length(FFT2)/2);
loglog( ((indices1-1)/length(FFT1))*fs , abs(FFT1(indices1)), 'k--');
hold on;
loglog( ((indices2-1)/length(FFT2))*fs , abs(FFT2(indices2)), 'r:');
loglog( ((indices3-1)/length(FFT2))*fs , abs(FFT3(indices3)), 'g');
title(figName, 'FontSize', 14);
xlabel('f (Hz)');
ylabel('Magitude');
xlim([FMIN FMAX]);
legend(sig1Name,sig2Name, sig2Name3);

end

