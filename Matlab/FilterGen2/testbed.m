for i = 1:1:5
    b_0 = round(mySOS(i,1)*32768);
    b_1 = round(mySOS(i,2)*32768);
    b_2 = round(mySOS(i,3)*32768);
    a_0 = round(mySOS(i,4)*32768);
    a_1 = round(mySOS(i,5)*32768);
    a_2 = round(mySOS(i,6)*32768);
    fprintf('%d, //B0 \n %d, //B1 \n %d, //B2 \n %d, //A0 \n %d, //A1 \n  %d, //A2 \n \n', b_0, b_1,b_2, a_0, a_1, a_2);
end

for i = 1:1:5
   a = round(1/maxfoo(i)*32768)
end
% count = 1;
% 
% for i = 1:1:length(mySOS)
%     if count ==3
%         count =1;
%     end
%     b_0 = round(mySOS(i,1)*32768);
%     b_1 = round(mySOS(i,2)*32768);
%     b_2 = round(mySOS(i,3)*32768);
%     a_0 = round(mySOS(i,4)*32768);
%     a_1 = round(mySOS(i,5)*32768);
%     a_2 = round(mySOS(i,6)*32768);
%     fprintf('%d, //B%d0 \n %d, //B%d1 \n %d, //B%d2 \n %d, //A%d0 \n %d, //A%d1 \n  %d, //A%d2 \n \n', b_0,count ,b_1,count, b_2, count, a_0, count, a_1, count, a_2,count);
%     
%     count = count+1;
% end
      
% 
% for i = 1:length(maxfoo)
%     display(round(1/maxfoo(i)*32768))
% end