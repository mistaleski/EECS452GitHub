function [ ] = FFTCompare( FFT1, FFT2, figNum, m, n, p, figName,sig1Name,sig2Name, fs )

    FMIN = 20; % Hz
    FMAX = 20e3; % Hz

    figure(figNum);
    subplot(m,n,p);
    indices1 = 1:(length(FFT1)/2);
    indices2 = 1:(length(FFT2)/2);
    loglog( ((indices1-1)/length(FFT1))*fs , abs(FFT1(indices1)));
    hold on;
    loglog( ((indices2-1)/length(FFT2))*fs , abs(FFT2(indices2)), 'r');
    title(figName, 'FontSize', 14);
    xlabel('f (Hz)');
    ylabel('Magitude');
    xlim([FMIN FMAX]);
    legend(sig1Name, sig2Name);

end

