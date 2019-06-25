function new_inverse_cal(pos, matR)
l = zeros(3,6);
Lp = 24.752; %centimet, length of platform's edge
Lb = 24.752*2; %length of base's edge
L = 20;
%pi = [xpi, ypi, zpi];
%corresponding to each point of platform
p = [0 Lp*sqrt(3)/3 0;
    -Lp/2 -Lp*sqrt(3)/6 0;
    Lp/2 -Lp*sqrt(3)/6 0]';
%bi = [xb1, ybi, zbi];
b = [-Lb/2 Lb*sqrt(3)/6 0;
     0 -Lb*sqrt(3)/3 0;
    Lb/2 Lb*sqrt(3)/6 0]';


    l(:,1) = pos + matR*p(:,1) - b(:,3);
    l(:,2) = pos + matR*p(:,1) - b(:,1);
    
    l(:,3) = pos + matR*p(:,2) - b(:,1);
    l(:,4) = pos + matR*p(:,2) - b(:,2);
    
    l(:,5) = pos + matR*p(:,3) - b(:,2);
    l(:,6) = pos + matR*p(:,3) - b(:,3);
    
    for (i=1:6)
        l_lenght(i) = norm(l(:,i));
    end
    
   
    h(1) = height_calculate(l_lenght(1), l_lenght(2), Lb);
    h(2) = h(1);
    h(3) = height_calculate(l_lenght(3), l_lenght(4), Lb);
    h(4) = h(3);
    h(5) = height_calculate(l_lenght(5), l_lenght(6), Lb);
    h(6) = h(5);
    
    for (i=1:6)
    q(i) = Lb/2 - (sqrt(l_lenght(i)^2 - h(i)^2) - sqrt(L^2 - h(i)^2));
    end
    
    q
end

function height = height_calculate(a,b,c)
p = (a + b + c)/2;
height = 2 * (sqrt(p*(p-a)*(p-b)*(p-c))/c);
end

    
