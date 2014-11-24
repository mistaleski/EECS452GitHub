% clear;
% clc;
[y, fs] = audioread('SuperstitionSnippet.wav');

% Constants
NUMFILTERS = 7;

 mySOS = MakeSOS();
% 
% scale = ones(1,NUMFILTERS);

wtemp(1,:) = ApplySOS(mySOS, y(:,1)', maxfoo);
wtemp(2,:) = ApplySOS(mySOS, y(:,2)', maxfoo);

w = wtemp';

% From Wakefield demo 1
aP = audioplayer(y,fs);
playblocking(aP);
disp('Other one');

aP2 = audioplayer(w,fs);
playblocking(aP2);