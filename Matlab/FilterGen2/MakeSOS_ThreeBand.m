function [ SOS ] = MakeSOS_ThreeBand( )

%% const
filterNum = 5;
fBands = [20, 80,500,5e3, 10e3, 20e3];


%% Analysis

for i = 1:1:filterNum
    Fc1 = fBands(i);
    Fc2 = fBands(i+1);
    Hd = FilterDesigner(Fc1,Fc2,1);
    coeffsFoo = coeffs(Hd);
    coeffArray(i,:) = coeffsFoo.SOSMatrix;
    clear coeffs
    clear Hd
end

SOS = coeffArray;

end

