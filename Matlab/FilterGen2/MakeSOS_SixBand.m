function [ SOS ] = MakeSOS_SixBand( numBQ )

%% const
filterNum = 6;
fBands = [20, 252.9822, 632.4555, 1.581138830084190e3, 3.968626966596887e3,9.721111047611796e3, 20e3];
Fs = 48000;

%% Analysis

for i = 1:1:filterNum
    Fc1 = fBands(i);
    Fc2 = fBands(i+1);
    if i == 1
        N = 4;
        h  = fdesign.lowpass('N,F3dB', N, Fc2, Fs);
        Hd = design(h, 'butter');
    else
        Hd = FilterDesigner(Fc1,Fc2,2);
    end
    coeffsFoo = coeffs(Hd);
    coeffArray(2*i-1:i*2,:) = coeffsFoo.SOSMatrix;
    clear coeffs
    clear Hd
end

SOS = coeffArray;

end

