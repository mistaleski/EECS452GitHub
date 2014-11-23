clear
fMin = 20; %Hz;
fMinLog = log10(fMin);
fMax = 20*10^3; %Hz
fMaxLog = log10(fMax);

fSpan = fMaxLog-fMinLog;
numFilters = 8;
fIncrement = fSpan/(numFilters);

for i = 1:1:8
    f(i) = (10^(fIncrement*i))*fMin;
    if (i == 1)
        Fc1 = 20;
    else
        Fc1 = f(i-1);
    end
    Fc2 = f(i);        
    
    Hd = FilterDesigner(Fc1,Fc2);
    coeffs = coeffs(Hd);
    coeffArray(i,:) = coeffs.SOSMatrix; 
    %figure(i);
    %freqz(Hd);
    clear coeffs
    clear Hd
end

