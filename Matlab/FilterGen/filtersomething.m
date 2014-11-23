% clear;
% clc;
[y, fs] = audioread('SuperstitionSnippet.wav');

% Constants
NUMFILTERS = 8;

% mySOS = MakeSOS(NUMFILTERS);
% 
% scale = ones(1,NUMFILTERS);

w(:,1) = ApplySOS(mySOS, y(:,1), ((1./maxfoo)'));
w(:,2) = ApplySOS(mySOS, y(:,2), ((1./maxfoo)'));


% From Wakefield demo 1
aP = audioplayer(y,fs);
playblocking(aP);
disp('Other one');

aP2 = audioplayer(w,fs);
playblocking(aP2);