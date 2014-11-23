function [ t, sweep ] = makeSweep( fs, fmin, fmax, isLog, sweepTime )

    fftSize = 2.^(floor(log2(48000*sweepTime)));

    %ramp
    t = 0:(1./fs):(fftSize-1)/fs;
    if isLog == 1
        sweep = chirp(t,fmin,fftSize/fs,fmax,'logarithmic');
    else
        sweep = chirp(t,fmin,fftSize/fs,fmax);
    end

end

