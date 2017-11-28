function f = matrixmul(r, d)
dim = str2num(d);
display(strcat('matrix_multiplication_', r));
m1 = rand(dim,dim);
m2 = rand(dim,dim);
f = m1 * m2;

end
