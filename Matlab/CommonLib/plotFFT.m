function [ ] = plotFFT( FFT, figNum, m, n, p, figName, fs )

    FMIN = 20; % Hz
    FMAX = 20e3; % Hz

    figure(figNum);
    subplot(m,n,p);
    indices = 1:(length(FFT)/2);
    loglog( ((indices-1)/length(FFT))*fs , abs(FFT(indices)));
    title(figName);
    xlabel('f (Hz)');
    ylabel('Magitude');
    xlim([FMIN FMAX]);

end

