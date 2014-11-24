function [ filtered ] = ApplySOS( SOS, in, scale )

%scale = scale./sum(scale);

%[ numFilters dummy ] = size(SOS);
numFilters = 7;
intValues = zeros(1,length(in));

for i = 1:numFilters
    intValues = intValues +  sosfilt(SOS(i,:), in);%.*scale(i);
end

intValues = intValues./numFilters;

filtered = intValues;

end

