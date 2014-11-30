Fc = 200;
Hd = LowPassCoeffGen(Fc);
values = coeffs(Hd);
coeffValues = values.SOSMatrix;
for i = 1:1:length(coeffValues)
    fprintf('%d', coeffValues(i));
    if i ~= length(coeffValues)
        fprintf(',\n');
    else
        fprintf(';\n');
    end
end