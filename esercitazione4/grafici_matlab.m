%% Grafici di rappresentazione dei tempi di esecuzione di algoritmi di sorting al crescere della dimensione del vettore a cui sono applicati
% Considero algoritmi di bubble-sort, selection-sort, insertion-sort e standard sort fornito dalla libreria standard di c++ 
dim = [4; 8; 16; 32; 64; 128; 256; 512; 1024];
y_bubble = [2.5e-07; 6.67e-07; 1.959e-06; 8.625e-06; 2.3334e-05; 0.000115417; 0.000390542; 0.00123283; 0.00481067];
y_select = [2.92e-07; 5.84e-07; 1.791e-06; 5.084e-06; 1.7e-05; 6.3125e-05; 0.000201667; 0.000733042; 0.00246671];
y_insert = [2.08e-07; 4.17e-07; 8.33e-07; 2.125e-06; 7.167e-06; 6.2709e-05; 8.3416e-05; 0.00034875; 0.00131212];
y_std = [9.17e-07; 6.67e-07; 1.167e-06; 4.083e-06; 7.667e-06; 1.7833e-05; 3.3375e-05; 7.4458e-05; 0.000143583];

figure;
loglog(dim, y_bubble, '-o', dim, y_select, '-s', dim, y_insert, '-d', dim, y_std, '-x');
xlabel('Dimensione del Vettore');
ylabel('Tempo di Esecuzione (secondi)');
title('Confronto tempi di esecuzione di algoritmi di ordinamento');
legend('Bubble Sort', 'Selection Sort', 'Insertion Sort', 'Standard Sort');
grid on;