function [ filtered ] = ApplySOS( SOS, in, scale )

[ numFilters dummy ] = size(SOS);

intValues = zeros(1,length(in));
for i = 1:numFilters
    intValues = intValues +  (sosfilt(SOS(i,:), in))./scale(i);
end

filtered = intValues;

end

