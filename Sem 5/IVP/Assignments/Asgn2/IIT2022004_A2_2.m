M = zeros(180,180);

centerX = 90;
centerY = 90;

for i=1:180
    for j=1:180
        if (j>=(90-45*sqrt(2)) && j<= (90 + 45*sqrt(2)) && i >= (90-45*sqrt(2)) && i <= (90+45*sqrt(2)))
            M(i,j) = 255;
        elseif (sqrt((centerX-i)^2 + (centerY-j)^2) <= 90)
            M(i,j) = 0;
        else
            M(i,j) = 255;
        end
    end
end

image(M);
colormap('gray')
