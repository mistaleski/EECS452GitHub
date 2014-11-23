%% Cleanup
% ============
clear;
close all;
clc;

list = ls('data/*.mat');
[xsize ysize] = size(list);

%% Loop
%============

for i = 1:xsize

    % Load Data
    % ============
    fname = sprintf('data/%s', list(i,:));
    load(fname);
    
    disp = sprintf('Press OK to view %s', list(i,:));
    blah = input(disp);

    plot1Name = sprintf('Impulse Response FFT: %s', list(i,:));
    plot2Name = sprintf('Sweep-derived transfer function FFT: %s', list(i,:));
    
    % Make Plots
    % ============
    hFig = figure(i);
    clf;
    set(hFig, 'OuterPosition', [200 200 1000 500]);
    plotFFT( FFTClapresponse, i, 1, 2, 1, plot1Name, FS );
    plotFFT( HSweepResponse, i, 1, 2, 2, plot2Name, FS );

end