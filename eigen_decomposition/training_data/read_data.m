% 
% read_data.m
%
% ECE637
% Prof. Charles A. Bouman
% Image Processing Laboratory: Eigenimages and Principal Component Analysis
%
% Description:
%
% This is a Matlab script that reads in a set of training images into
% the Matlab workspace.  The images are sets of English letters written
% in various fonts.  Each image is reshaped and placed into a column
% of a data matrix, "X".
% 

% The following are strings used to assemble the data file names
datadir='.';    % directory where the data files reside
dataset={'arial','bookman_old_style','century','comic_sans_ms','courier_new',...
  'fixed_sys','georgia','microsoft_sans_serif','palatino_linotype',...
  'shruti','tahoma','times_new_roman'};
datachar='abcdefghijklmnopqrstuvwxyz';

Rows=64;    % all images are 64x64
Cols=64;
n=length(dataset)*length(datachar);  % total number of images
p=Rows*Cols;   % number of pixels

X=zeros(p,n);  % images arranged in columns of X
k=1;
for dset=dataset
for ch=datachar
  fname=sprintf('%s/%s/%s.tif',datadir,char(dset),ch);
  img=imread(fname);
  X(:,k)=reshape(img,1,Rows*Cols);
  k=k+1;
end
end

return

% display samples of the training data
for k=1:length(dataset)
  img=reshape(X(:,26*(k-1)+1),64,64);
  figure(20); subplot(3,4,k); image(img); 
  axis('image'); colormap(gray(256)); 
  title(dataset{k},'Interpreter','none');
end


