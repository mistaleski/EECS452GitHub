function [ HInv ] = getInvMPS( XFFT, YFFT)

addpath('CCRMA_Source');

HInv = XFFT./YFFT;

temp = mps(HInv);
HInv = temp;

% %% Clipping
% % =============
% rangeMag = (10^(dynamicRange/10));
% 
% for i = 1:length(HInv)
%     if abs(HInv(i)) > (rangeMag/2)*Normalize_Factor
%         % HInv(i) = HInv(i) * 0.0000001;
%         HInv(i) = (HInv(i) / abs(HInv(i))) * (rangeMag/2)*Normalize_Factor;
%     elseif abs(HInv(i)) < (2/rangeMag)*Normalize_Factor
%         % HInv(i) = HInv(i) * 0.0000001;
%         HInv(i) = (HInv(i) / abs(HInv(i))) * (2/rangeMag)*Normalize_Factor;
% end

end

