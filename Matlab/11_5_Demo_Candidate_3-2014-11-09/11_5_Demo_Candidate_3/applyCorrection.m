% clear;
% clc;

% load('data/452lab.mat');
[y, fs] = audioread('SuperstitionSnippet.wav');


blahFFT = mps(FilteredSmoothInvH);
blah = real(ifft(blahFFT));

w(:,1) = conv(blah, y(:,1));
w(:,2) = conv(blah, y(:,2));


% From Wakefield demo 1
aP = audioplayer(y,fs);
playblocking(aP);
disp('Other one');
playNormalized(w, fs);
%aP2 = audioplayer(w,fs);
%playblocking(aP2);