% Following script sets up 2 local variables.
% Quant[8][8] = typical luminance quant matrix for JPEG
% Zig[64]  = zigzag scan index for 8x8 block for JPEG

Quant = [ 16, 11, 10, 16, 24, 40, 51, 61;
          12, 12, 14, 19, 26, 58, 60, 55;
          14, 13, 16, 24, 40, 57, 69, 56;
          14, 17, 22, 29, 51, 87, 80, 62;
          18, 22, 37, 56, 68,109,103, 77; 
          24, 35, 55, 64, 81,104,113, 92;
          49, 64, 78, 87,103,121,120,101;
          72, 92, 95, 98,112,100,103, 99;] ;

% Zig array shows indices required for zigzag indexing
% of an [8,8] Matlab matrix. So it starts with number 1 
% rather then the number 0 as in the JPEG specification

% order =    [ 1, 2, 6, 7,15,16,28,29;
%              3, 5, 8,14,17,27,30,43;
%              4, 9,13,18,26,31,42,44;
%             10,12,19,25,32,41,45,54;
%             11,20,24,33,40,46,53,55;
%             21,23,34,39,47,52,56,61;
%             22,35,38,48,51,57,60,62;
%             36,37,49,50,58,59,63,64;];
% To read an [8,8] matrix as above order considering
% Matlab's column first indexing property, 
% above order is permuted as follows.
% For example, let x be [8,8] matrix.
% x(Zig) will return a 1x64 row vector
%
Zig = [ 1  9  2  3 10 17 25 18 ...
       11  4  5 12 19 26 33 41 ...
       34 27 20 13  6  7 14 21 ...
       28 35 42 49 57 50 43 36 ...   
       29 22 15  8 16 23 30 37 ...
       44 51 58 59 52 45 38 31 ...
       24 32 39 46 53 60 61 54 ...
       47 40 48 55 62 63 56 64] ;
