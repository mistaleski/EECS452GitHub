% clear;
% clc;
[y, fs] = audioread('SuperstitionSnippet.wav');

% Constants
NUMFILTERS = 5;

 mySOS = MakeSOS_ThreeBand();
% 
% scale = ones(1,NUMFILTERS);
Plus20dBlin = 10^(8/20);
Minus20dBlin = 10^(-8/20);

maxfooBar =maxfoo(:);
maxfooBar(1) = maxfooBar(1);
% for(i = 2:1:5)
%    maxfooBar(i) = 1000; 
% end
%maxfooBar(2) = maxfooBar(2)/15;
%maxfooBar(4) = maxfooBar(4)*20;
%maxfooBar(5) = maxfooBar(5)/20;


wtemp(1,:) = ApplySOS(mySOS, y(:,1)', maxfooBar);
wtemp(2,:) = ApplySOS(mySOS, y(:,2)', maxfooBar);

w = wtemp';

%From Wakefield demo 1
%aP = audioplayer(y,fs);
%playblocking(aP);
disp('Other one');

aP2 = audioplayer(w,fs);
playblocking(aP2);