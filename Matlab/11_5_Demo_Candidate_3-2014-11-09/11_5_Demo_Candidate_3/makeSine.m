function [ t, x ] = makeSine( fs, f, sweepTime )

fftSize = 2.^(floor(log2(fs*sweepTime)));

% sinusoid
t = 0:(1./fs):(fftSize-1)/fs;
x = sin(t*2*pi*f);

end

