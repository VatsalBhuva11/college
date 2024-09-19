img = imread('VATSALBHUVA.jpeg');


if size(img, 3) == 3
    gray_img = rgb2gray(img);
else
    
    gray_img = img;
end


image_matrix = double(gray_img); 


figure;
subplot(2,2,1);
image(image_matrix);
colormap(gray(256));
colorbar;
title('Original Grayscale Image');


transposed_img = image_matrix';


subplot(2,2,2);
image(transposed_img);
colormap(gray(256));
colorbar;
title('Transposed Image');

% Flip the image vertically
flipped_vertical_img = flipud(image_matrix);

% Display the flipped vertically image
subplot(2,2,3);
image(flipped_vertical_img);
colormap(gray(256));
colorbar;
title('Flipped Vertically');

% Flip the image horizontally
flipped_horizontal_img = fliplr(image_matrix);

% Display the flipped horizontally image
subplot(2,2,4);
image(flipped_horizontal_img);
colormap(gray(256));
colorbar;
title('Flipped Horizontally');

% Flip diagonally (transpose + flip horizontally)
flipped_diagonal_img = fliplr(transposed_img);

