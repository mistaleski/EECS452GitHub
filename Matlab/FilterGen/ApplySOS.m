function [ filtered ] = ApplySOS( SOS, in, scale )

scale = scale./sum(scale);

[ numFilters dummy ] = size(SOS);

intValues = zeros(length(in),1);

for i = 1:numFilters
    intValues = intValues +  sosfilt(SOS(i,:), in).*scale(i);
end

intValues = intValues./numFilters;

filtered = intValues;

end

