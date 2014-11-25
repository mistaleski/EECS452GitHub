% clear;
% clc;
[y, fs] = audioread('SuperstitionSnippet.wav');

% Constants
NUMFILTERS = 7;

numBQ = 3;


 mySOS = MakeSOS(numBQ);
% 
% scale = ones(1,NUMFILTERS);
intValues = ones(1,length(y(:,1)'));
total(1,:) = zeros(1,length(y(:,1)'));
total(2,:) = zeros(1,length(y(:,1)'));

for i = 1:1:NUMFILTERS
    wtemp(1,:) = ApplySOS(mySOS((i-1)*numBQ+1,:), y(:,1)', intValues);
    wtemp(2,:) = ApplySOS(mySOS((i-1)*numBQ+1,:), y(:,2)', intValues);
        for j = 1:1:numBQ-1
            wtemp(1,:) = ApplySOS(mySOS((i-1)*(numBQ)+1+j,:), wtemp(1,:), intValues);
            wtemp(2,:) = ApplySOS(mySOS((i-1)*(numBQ)+1+j,:), wtemp(2,:), intValues);
        end
    wtemp(1,:) = wtemp(1,:)./maxfoo(i);
    wtemp(2,:) = wtemp(2,:)./maxfoo(i);
        
    total(1,:) = wtemp(1,:) + total(1,:);
    total(2,:) = wtemp(2,:) + total(2,:);
end
w = total';

% From Wakefield demo 1
aP = audioplayer(y,fs);
playblocking(aP);
disp('Other one');

aP2 = audioplayer(w,fs);
playblocking(aP2);