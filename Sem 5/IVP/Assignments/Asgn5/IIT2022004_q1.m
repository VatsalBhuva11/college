% Read the facial image
image = imread('VATSALBHUVA.jpeg'); 
image = double(image);           

% Convert the image to grayscale
gray_image = 0.2989 * image(:,:,1) + 0.5870 * image(:,:,2) + 0.1140 * image(:,:,3);

% Define filter function to apply convolution
function output = apply_filter(image, filter)
    [rows, cols] = size(image);
    [frows, fcols] = size(filter);
    pad_size_r = floor(frows / 2);
    pad_size_c = floor(fcols / 2);
    
    % Padding the image with zeros
    padded_image = padarray(image, [pad_size_r, pad_size_c], 0, 'both');
    output = zeros(rows, cols);

    % Applying the filter
    for i = 1:rows
        for j = 1:cols
            region = padded_image(i:i+frows-1, j:j+fcols-1);
            output(i, j) = sum(sum(region .* filter));
        end
    end
end

% 1. Average filter (3x3)
avg_filter = ones(3, 3) / 9;
avg_filtered_image = apply_filter(gray_image, avg_filter);

% 2. Gaussian filter (3x3)
sigma = 0.5;
gaussian_filter = zeros(3, 3);
for x = -1:1
    for y = -1:1
        gaussian_filter(x+2, y+2) = exp(-(x^2 + y^2) / (2 * sigma^2)) / (2 * pi * sigma^2);
    end
end
gaussian_filter = gaussian_filter / sum(gaussian_filter(:)); % Normalize
gaussian_filtered_image = apply_filter(gray_image, gaussian_filter);

% 3. Laplacian filter (3x3)
laplacian_filter = [0 -1 0; -1 4 -1; 0 -1 0]; % Explicitly define the Laplacian filter
laplacian_filtered_image = apply_filter(gray_image, laplacian_filter);

% 4. Sobel filter (3x3)
sobel_x = [-1 0 1; -2 0 2; -1 0 1];
sobel_y = [-1 -2 -1; 0 0 0; 1 2 1];
sobel_x_image = apply_filter(gray_image, sobel_x);
sobel_y_image = apply_filter(gray_image, sobel_y);
sobel_filtered_image = sqrt(sobel_x_image.^2 + sobel_y_image.^2);

% 5. Median filter (3x3)
function output = median_filter(image, filter_size)
    [rows, cols] = size(image);
    pad_size = floor(filter_size / 2);
    padded_image = padarray(image, [pad_size, pad_size], 0, 'both');
    output = zeros(rows, cols);

    for i = 1:rows
        for j = 1:cols
            region = padded_image(i:i+filter_size-1, j:j+filter_size-1);
            output(i, j) = median(region(:));
        end
    end
end

median_filtered_image = median_filter(gray_image, 3);

% Display the results in one page
figure;
subplot(2,3,1), imshow(uint8(gray_image)), title('Original Grayscale Image');
subplot(2,3,2), imshow(uint8(avg_filtered_image)), title('Average Filter');
subplot(2,3,3), imshow(uint8(gaussian_filtered_image)), title('Gaussian Filter');
subplot(2,3,4), imshow(uint8(laplacian_filtered_image)), title('Laplacian Filter');
subplot(2,3,5), imshow(uint8(sobel_filtered_image)), title('Sobel Filter');
subplot(2,3,6), imshow(uint8(median_filtered_image)), title('Median Filter');
