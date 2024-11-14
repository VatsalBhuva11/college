% Read the images and resize to 180x180 (grayscale images assumed)
img1 = imread('img1.jpeg');  % Replace with your actual first name image file
img2 = imread('img2.jpeg');   % Replace with your actual last name image file

% Resize images to 180x180 if they are not already
img1 = imresize(img1, [180 180]);
img2 = imresize(img2, [180 180]);

% Convert images to binary manually
threshold1 = 128; % Assuming 8-bit grayscale image, threshold to binary
threshold2 = 128;
binary_img1 = img1 > threshold1;
binary_img2 = img2 > threshold2;

% 1. Complement of Img1 (invert pixel values: 0 -> 1, 1 -> 0)
comp_img1 = zeros(size(binary_img1));
for i = 1:size(binary_img1, 1)
    for j = 1:size(binary_img1, 2)
        comp_img1(i,j) = 1 - binary_img1(i,j);
    end
end

% 2. Complement of Img2 (invert pixel values: 0 -> 1, 1 -> 0)
comp_img2 = zeros(size(binary_img2));
for i = 1:size(binary_img2, 1)
    for j = 1:size(binary_img2, 2)
        comp_img2(i,j) = 1 - binary_img2(i,j);
    end
end

% 3. Union of Img1 and Img2 (logical OR: 1 if either pixel is 1)
union_img = zeros(size(binary_img1));
for i = 1:size(binary_img1, 1)
    for j = 1:size(binary_img1, 2)
        union_img(i,j) = binary_img1(i,j) || binary_img2(i,j);
    end
end

% 4. Intersection of Img1 and Img2 (logical AND: 1 if both pixels are 1)
intersect_img = zeros(size(binary_img1));
for i = 1:size(binary_img1, 1)
    for j = 1:size(binary_img1, 2)
        intersect_img(i,j) = binary_img1(i,j) && binary_img2(i,j);
    end
end

% Display results
figure;
subplot(2,3,1), imshow(binary_img1), title('Img1 (First Name)');
subplot(2,3,2), imshow(binary_img2), title('Img2 (Last Name)');
subplot(2,3,3), imshow(comp_img1), title('Complement of Img1');
subplot(2,3,4), imshow(comp_img2), title('Complement of Img2');
subplot(2,3,5), imshow(union_img), title('Union of Img1 and Img2');
subplot(2,3,6), imshow(intersect_img), title('Intersection of Img1 and Img2');

