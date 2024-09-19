% import image from files
[file, path] = uigetfile({'*.jpg;*.jpeg;*.png;*.bmp', 'Image Files (*.jpg, *.jpeg, *.png, *.bmp)'}, 'Select an Image');
if isequal(file, 0)
    disp('User selected Cancel');
else
    img = imread(fullfile(path, file));
end

% crop a portion that mostly shows the head (manually adjust as per image)
head_crop = imcrop(img, [100 50 400 400]);  % Example parameters [x, y, width, height]
figure;
subplot(2,3,1);
imshow(head_crop);
title('Head Crop');
fprintf('Head crop parameters: x=100, y=50, width=200, height=200\n');

% crop a portion that mostly shows the eyes
eyes_crop = imcrop(img, [225 210 160 80]);  % Example parameters [x, y, width, height]
subplot(2,3,2);
imshow(eyes_crop);
title('Eyes Crop');
fprintf('Eyes crop parameters: x=120, y=80, width=160, height=80\n');

% compute the square root and negative of the image
sqrt_img = sqrt(double(img)/255);  % square root operation
neg_img = imcomplement(img);  % negative operation

subplot(2,3,3);
imshow(sqrt_img);
title('Square Root of Image');

subplot(2,3,4);
imshow(neg_img);
title('Negative of Image');

% calculate mean, variance, and histogram of the image
mean_val = mean(img(:));
variance_val = var(double(img(:)));
fprintf('Mean: %.2f, Variance: %.2f\n', mean_val, variance_val);

% display histogram next to the image
subplot(2,3,5);
imhist(img);
title('Histogram of Original Image');
xlabel('Intensity');
ylabel('Frequency');

% indicate the size of the image
img_size = size(img);
fprintf('Image size: %dx%dx%d\n', img_size(1), img_size(2), img_size(3));

% convert the image to grayscale and calculate mean, variance, and histogram
gray_img = rgb2gray(img);
mean_gray = mean(gray_img(:));
variance_gray = var(double(gray_img(:)));
fprintf('Grayscale Mean: %.2f, Grayscale Variance: %.2f\n', mean_gray, variance_gray);

% display grayscale image and histogram next to each other
figure;
subplot(1,2,1);
imshow(gray_img);
title('Grayscale Image');

subplot(1,2,2);
imhist(gray_img);
title('Histogram of Grayscale Image');
xlabel('Intensity');
ylabel('Frequency');

% indicate the size of the grayscale image
gray_img_size = size(gray_img);
fprintf('Grayscale image size: %dx%d\n', gray_img_size(1), gray_img_size(2));
