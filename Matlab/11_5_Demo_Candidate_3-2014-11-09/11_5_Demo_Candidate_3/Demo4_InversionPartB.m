% Make filter minimum phase
addpath('CCRMA_Source');
FFTBest = mps(FilteredSmoothInvH) .* FFTsweep;
BestNoises = real(ifft(FFTBest));
blah = input('Press Enter to play applied smoothed MPS inverse');
FFTCompare(FFTsweep, FFTBest, 8, 1, 1, 1, 'Final Sweep', ...
    'Before Correction', 'After Correction', FS );
playNormalizedRepeat(BestNoises, FS);