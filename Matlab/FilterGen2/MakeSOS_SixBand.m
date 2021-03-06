function [ SOS ] = MakeSOS_SixBand( numBQ )

%% const
filterNum = 6;
fBands = [20, 252.9822, 632.4555, 1.581138830084190e3, 3.968626966596887e3,9.721111047611796e3, 20e3];
Fs = 48000;

%% Analysis

for i = 1:1:filterNum
    if i == 2
        Fc1 = fBands(i)*1.1;
    elseif i == 3
        Fc1 = fBands(i)*0.8;
    elseif i == 6
        Fc1 = fBands(i).*0.7;
    else
        Fc1 = fBands(i).*0.7;
    end
    if i == 1 
        Fc2 = fBands(i+1).*0.7;
    elseif i == 6
        Fc2 = fBands(i+1);
    else
        Fc2 = fBands(i+1).*1.3;
    end
    
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

