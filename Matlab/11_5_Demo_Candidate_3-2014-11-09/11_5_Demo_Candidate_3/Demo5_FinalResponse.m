% Precondition: you have just run InversionDemo.m

% Original response reprise
[originalResponse, timestamp] = RecordReponse(FS, sweep * .8);

[dummy originalResponsePad] = fftPrep(sweep, originalResponse);
FFTOriginalResponse = fft(originalResponsePad);

% Get final response
BestNoisesNormalized = (BestNoises./(max(BestNoises))) * .8;
[finalReponse, timestamp] = RecordReponse(FS, BestNoisesNormalized);

[dummy finalReponsePad] = fftPrep(sweep, finalReponse);
FFTFinalResponse = fft(finalReponsePad);

%% Plotting
% Compare 3 signals
FFTCompare3( FFTsweep, FFTOriginalResponse, FFTFinalResponse, 8, 1, 1, 1, ...
    'Final Comparison','Ideal Response', 'Original Response', 'Final Response', FS )

%% Plotting
% Compare 3 signals
FFTCompare3( smoothFFT(FFTsweep), smoothFFT(FFTOriginalResponse), smoothFFT(FFTFinalResponse(1:2:length(FFTFinalResponse))), 9, 1, 1, 1, ...
    'Final Comparison - smoothed responses','Ideal Response', 'Original Response', 'Final Response', FS );