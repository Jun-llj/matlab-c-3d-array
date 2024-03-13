
for i=1:3
    for j=1:4
        for k=1:2
            d(i,j,k)= (k-1) * 3 * 4 + (i-1) * 4 + (j-1);
        end
    end
end

disp('d在matlab中的输出为:');
disp(d);



output_dd = matrix_3d_demo(d);



disp('output_dd在matlab中的输出为(正确的形式):');
disp(output_dd);

clearvars
