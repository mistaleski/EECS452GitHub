%% Cleanup
% ============
clear;
close all;
clc;

%% Load Data
% ============
% load('452Lab_20140511_2/variables.mat');
%path = input('Enter Filepath','s');
load('data/452lab.mat');

%% Run calculations
% ============
InvH_NoClip = FFTsweep./FFTSweepResponse;

In = real(ifft(FFTsweep));
Out = real(ifft(FFTSweepResponse));

SanityCheck = real(ifft(InvH .* FFTSweepResponse));
SanityCheck_NoClip = real(ifft(InvH_NoClip .* FFTSweepResponse));

SimpleCorrected = real(ifft(InvH .* FFTsweep));

SmoothInvH = smoothFFT(InvH_NoClip);

FilteredSmoothInvH = perfectBandpass( FS, 20, 13000, SmoothInvH );

SmoothNoTrebleCorrected = real(ifft(FilteredSmoothInvH .* FFTsweep));

%% Prepare to skip ahead
% ============
toDisp = ...
[ 'Press enter to begin demo,\n', ...
  'or input one of the following choices to skip ahead\n', ...
  '1 - Input\n', ...
  '2 - Output\n', ...
  '3 - Sanity Check with Clipped Inverse\n', ...
  '4 - Plot Inverse alone\n', ...
  '5 - Sanity Check without Clipped Inverse\n', ...
  '6 - Corrected Signal 1\n', ...
  '7 - Plot Smoothed Inverse\n', ...
  '8 - Play corrected signal iteration 2\n', ...
  '9 - Filter Smoothed Inverse (remove high treble)\n', ...
  '10 - Play Smoothed Inverse\n'];

skip = input(toDisp);
if isempty(skip)
    skip = 0;
end


%% Play Sounds
% ============
% 1 - Input
if skip <= 1
    blah = input('Press Enter to play Input', 's');
    plotFFT(FFTsweep, 1, 1, 1, 1, 'Input Signal FFT', FS);
    playNormalizedRepeat(In, FS);
end

% 2 - Output
if skip <= 2
    blah = input('Press Enter to play Response');
    plotFFT(FFTSweepResponse, 2, 1, 1, 1, 'Room Response FFT', FS);
    playNormalizedRepeat(Out, FS);
end

% 3 - Sanity Check with Clipped Inverse
if skip <= 3
    blah = input('Press Enter to play (R^-1 [with clipping])*Output');
    FFTCompare(InvH .* FFTSweepResponse, FFTsweep, 3, 1, 1, 1, 'Sanity Check: Input*(Room Inverse with Clipping)', ...
        '(R^-^1 Clipped)*Output','Original Signal', FS);
    playNormalizedRepeat(SanityCheck, FS);
end
    
% 4 - Plot Inverse alone
if skip <= 4
    blah = input('Press Enter to plot Inverse Alone');
    plotFFT(InvH_NoClip, 4, 2,1,1, 'Calculated Room Inverse', FS);
    plotFFT(InvH, 4, 2,1,2, 'Calculated Room Inverse with Clipping', FS);
end

% 5 - Sanity Check without Clipped Inverse
if skip <= 5
    blah = input('Press Enter to play (R^-1 [without clipping])*Output');
    FFTCompare(InvH_NoClip .* FFTSweepResponse, FFTsweep, 5, 1,1,1, 'Sanity Check: Input*(Room Inverse without Clipping)', ...
        '(R^-^1 Unclipped)*Output','Original Signal', FS);
    playNormalizedRepeat(SanityCheck_NoClip, FS);
end
    
% 6 - Corrected Signal 1
if skip <= 6
    blah = input('Press Enter to play 1st Iteration Corrected signal (Input * Room Inverse)');
    playNormalizedRepeat(SimpleCorrected, FS);
end

% 7 - Plot Smoothed Inverse
if skip <= 7
    blah = input('Press Enter to plot smoothed inverse');
    FFTCompare(InvH_NoClip, SmoothInvH, 6, 1, 1, 1, 'Smoothed Room Inverse', ...
        'Not Smoothed', 'Smoothed', FS );
end

% 8 - Play corrected signal iteration 2
if skip <= 8
    SmoothCorrected = real(ifft(SmoothInvH .* FFTsweep));
    blah = input('Press Enter to play 2nd Iteration Corrected signal (Input * Smoothed Room Inverse)');
    playNormalizedRepeat(SmoothCorrected, FS);
end

% 9 - Filter Smoothed Inverse (remove high treble)
if skip <= 9
    blah = input('Press Enter to plot smoothed inverse with treble removed');
    FFTCompare(InvH_NoClip, FilteredSmoothInvH, 7, 1, 1, 1, 'Smoothed Room Inverse with High Treble Removed', ...
        'Not Smoothed', 'Smoothed + Treble Removal', FS );
end

% 10 - Play Smoothed Inverse
if skip <= 10
    blah = input('Press OK to play applied smoothed inverse');
    playNormalizedRepeat(SmoothNoTrebleCorrected, FS);
end