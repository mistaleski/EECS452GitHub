clear
%% const
filterNum = 7;
fStandards = [63,160, 400,1e3,2.5e3, 6.3e3,15e3];
fMin = 20; %Hz;
fMax = 20*10^3; %Hz

%% Analysis
fStart = fMin;

for i = 1:1:filterNum
    if i ~=filterNum
        fMiddleDB = (log10(fStandards(i+1)) +log10(fStandards(i)))/2;
        fMiddle = 10^(fMiddleDB);
        Fc1 = fStart;
        Fc2 = fMiddle;
    else
        Fc1 = fStart;
        Fc2 = fMax;
    end
    Hd = FilterDesigner(Fc1,Fc2);
    coeffs = coeffs(Hd);
    coeffArray(i,:) = coeffs.SOSMatrix;
    fStart = fMiddle;
    clear coeffs
    clear Hd
end

