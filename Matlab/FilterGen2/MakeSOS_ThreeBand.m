function [ SOS ] = MakeSOS_ThreeBand( )

%% const
filterNum = 5;
fBands = [20, 300,700,2e3, 4e3, 20e3];
Fs = 48000;

%% Analysis

for i = 1:1:filterNum
    Fc1 = fBands(i);
    Fc2 = fBands(i+1);
    if i == 1
        N = 2;
        h  = fdesign.lowpass('N,F3dB', N, Fc2, Fs);
        Hd = design(h, 'butter');
    else
        Hd = FilterDesigner(Fc1,Fc2,1);
    end
    coeffsFoo = coeffs(Hd);
    coeffArray(i,:) = coeffsFoo.SOSMatrix;
    clear coeffs
    clear Hd
end

SOS = coeffArray;

end

