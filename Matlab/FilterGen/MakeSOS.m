function [ SOS ] = MakeSOS( numFilters )

% Range
fMin = 20; %Hz;
fMinLog = log10(fMin);
fMax = 20*10^3; %Hz
fMaxLog = log10(fMax);

% Get Increment
fSpan = fMaxLog-fMinLog;
fIncrement = fSpan/(numFilters);

% Loop through, make "numFilters" filters
for i = 1:1:numFilters
    f(i) = (10^(fIncrement*i))*fMin;
    if (i == 1)
        Fc1 = 20;
    else
        Fc1 = f(i-1);
    end
    Fc2 = f(i);        
    
    Hd = FilterDesigner(Fc1,Fc2);
    mycoeffs = coeffs(Hd);
    coeffArray(i,:) = mycoeffs.SOSMatrix; 
    clear mycoeffs
    clear Hd
end

SOS = coeffArray;

end

