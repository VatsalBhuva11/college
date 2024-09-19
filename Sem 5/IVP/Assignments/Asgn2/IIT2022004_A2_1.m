M = zeros(180,180);
for i=1:180
    for j=1:90
        M(i,j) = floor(((j-1)/89)*255);
    end
    for j=91:180
        M(i,j) = floor(((180-j)/89) * 255);
    end
end
    
image(M);
colormap('gray')
