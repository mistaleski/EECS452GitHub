%% Cleanup
% ============
% clear;
% close all;
clc;

%% Load Data
% ============
%load('data/452Lab.mat');

%% Minphase Inverses
% ============

InvH_NoClip = FFTsweep./FFTSweepResponse;
InvH_MPS = getInvMPS(FFTsweep,FFTSweepResponse );

% plotFFT(InvH_NoClip, 1, 2,1,1, 'Unclipped Inverse', FS);
% plotFFT(InvH_MPS, 1, 2,1,2, 'Min Phase', FS);

hFig = figure(2);
clf;
set(hFig, 'OuterPosition', [200 200 1500 500]);

%% Play Minphase Inverse
% ============
impulseResponseOrig = real(ifft(InvH_NoClip));
impulseResponseMPS = real(ifft(InvH_MPS));

scaleTop = max(impulseResponseMPS) * 1.1;
scaleBot = min(impulseResponseMPS) * 1.1;

subplot(1,3,1);
plot(impulseResponseOrig)
title('Original Impulse Response', 'FontSize', 14);
xlabel('time (sec)');
ylabel('Audio output');
axis([-1e4 14e4 scaleBot scaleTop ]);

subplot(1,3,2);
plot(impulseResponseMPS)
title('MPS Impulse Response', 'FontSize', 14);
axis([-1e4 14e4 scaleBot scaleTop ]);
xlabel('time (sec)');
ylabel('Audio output');

subplot(1,3,3);
semilogx(phase(InvH_NoClip));
hold on;
semilogx(phase(InvH_MPS), 'r');
title('Room Inverse Phase: Original vs. Min Phase', 'FontSize', 14);
legend('Original', 'Min Phase', 'Location', 'NorthWest', 'FontSize', 14);
xlabel('FFT Index');
ylabel('Phase');
