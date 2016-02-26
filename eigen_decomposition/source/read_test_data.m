datadir='../test_data';    % directory where the data files reside
dataset={'veranda'};
datachar='abcdefghijklmnopqrstuvwxyz';

Rows=64;    % all images are 64x64
Cols=64;
n=length(dataset)*length(datachar);  % total number of images
p=Rows*Cols;   % number of pixels

TX=zeros(p,n);  % images arranged in columns of X
k=1;
for dset=dataset
	for ch=datachar
	  fname=sprintf('%s/%s/%s.tif',datadir,char(dset),ch);
	  img=imread(fname);
	  TX(:,k)=reshape(img,1,Rows*Cols);
	  k=k+1;
	end
end

return
