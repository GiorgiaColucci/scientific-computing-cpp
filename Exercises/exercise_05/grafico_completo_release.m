%% Grafici di rappresentazione dei tempi di esecuzione di algoritmi di sorting al crescere della dimensione del vettore a cui sono applicati
% Considero algoritmi di bubble-sort, selection-sort, insertion-sort, merge-sort, quick-sort e standard sort fornito dalla libreria standard di c++ 
% Ho 50 dimensioni, partendo da 2 e arrivando a 100 con passo 2 
% Compilazione in modalità release

dim = [2; 4; 6; 8; 10; 12; 14; 16; 18; 20; 22; 24; 26; 28; 30; 32; 34; 36; 38; 40; 42; 44; 46; 48; 50; 52; 54; ...
    56; 58; 60; 62; 64; 66; 68; 70; 72; 74; 76; 78; 80; 82; 84; 86; 88; 90; 92; 94; 96; 98; 100];

y_bubble = [3.459e-08; 1.25e-07; 2.6e-07; 4.7708e-07; 8.2459e-07; 1.15167e-06; 1.61625e-06; 2.03208e-06; 2.2075e-06; ...
    2.55292e-06; 3.26458e-06; 3.51042e-06; 3.7375e-06; 4.50041e-06; 4.94584e-06; 4.85125e-06; 5.31541e-06; 6.075e-06; ...
    6.06042e-06; 6.66416e-06; 6.53209e-06; 7.29917e-06; 7.86875e-06; 7.73334e-06; 8.50333e-06; 8.7775e-06; 9.23875e-06; ...
    1.01621e-05; 9.91375e-06; 1.01721e-05; 1.11383e-05; 1.14304e-05; 1.12804e-05; 1.19042e-05; 1.27242e-05; 1.37046e-05; ...
    1.39154e-05; 1.39988e-05; 1.53512e-05; 1.56325e-05; 1.62117e-05; 1.69392e-05; 1.84212e-05; 1.84171e-05; 1.88337e-05; ...
    2.00913e-05; 2.07471e-05; 2.17546e-05; 2.24404e-05; 2.35758e-05];

y_select = [3.459e-08; 1.225e-07; 2.6792e-07; 5.0209e-07; 8.175e-07; 1.07208e-06; 1.125e-06; 1.39375e-06; 1.46667e-06; ...
    1.74417e-06; 2.0375e-06; 2.35209e-06; 2.37417e-06; 2.86792e-06; 2.99458e-06; 2.99375e-06; 3.27375e-06; 3.595e-06; ...
    3.66417e-06; 3.94083e-06; 4.10042e-06; 4.3275e-06; 4.41875e-06; 4.75709e-06; 4.91041e-06; 5.14792e-06; 5.54709e-06; ...
    6.05083e-06; 5.9825e-06; 6.08542e-06; 6.5175e-06; 6.81542e-06; 6.6875e-06; 6.93958e-06; 7.44833e-06; 7.72542e-06; ...
    7.78208e-06; 8.135e-06; 8.65375e-06; 8.9675e-06; 9.27583e-06; 9.90667e-06; 1.01808e-05; 1.07625e-05; 1.09221e-05; 1.15017e-05; ...
    1.22517e-05; 1.30258e-05; 1.28329e-05; 1.36808e-05];

y_insert = [2.917e-08; 9.458e-08; 1.7625e-07; 4.2833e-07; 3.6e-07; 4.525e-07; 5.5292e-07; 6.6709e-07; 7.1167e-07; 8.1791e-07; ...
    9.6083e-07; 1.19e-06; 1.10834e-06; 1.29375e-06; 1.41625e-06; 1.44958e-06; 1.57208e-06; 1.82875e-06; 1.74833e-06; 1.95792e-06; ...
    1.93875e-06; 2.18833e-06; 2.16584e-06; 2.37167e-06; 2.45416e-06; 2.49625e-06; 2.715e-06; 2.94125e-06; 2.9625e-06; 3.03666e-06; ...
    3.26541e-06; 3.33042e-06; 3.26291e-06; 3.50041e-06; 3.8975e-06; 3.98084e-06; 4.06708e-06; 4.20084e-06; 4.37875e-06; 4.55459e-06; ...
    4.95875e-06; 4.97584e-06; 5.32667e-06; 5.49125e-06; 5.67375e-06; 6.03208e-06; 6.42958e-06; 6.44834e-06; 6.73584e-06; 7.14875e-06];

y_merge = [1.9709e-07; 1.12042e-06; 1.43791e-06; 1.86542e-06; 2.27959e-06; 2.63875e-06; 3.22334e-06; 3.1975e-06; 3.97208e-06; ...
    4.39167e-06; 4.75125e-06; 5.10625e-06; 5.14042e-06; 5.70791e-06; 6.18459e-06; 5.72417e-06; 6.365e-06; 6.32167e-06; 6.42e-06; ...
    6.81958e-06; 6.82083e-06; 7.16084e-06; 7.12166e-06; 7.40958e-06; 7.44625e-06; 7.69791e-06; 8.06041e-06; 8.17208e-06; 8.20709e-06; ...
    8.36292e-06; 8.56042e-06; 8.75e-06; 8.41167e-06; 8.62792e-06; 1.00442e-05; 9.5475e-06; 9.29875e-06; 9.62334e-06; 9.79166e-06; 1.00058e-05; ...
    1.03858e-05; 1.11812e-05; 1.08738e-05; 1.12262e-05; 1.17629e-05; 1.19092e-05; 1.23196e-05; 1.25542e-05; 1.36608e-05; 1.32608e-05];

y_quick = [4.542e-08; 1.3166e-07; 2.525e-07; 3.9625e-07; 5.225e-07; 6.6709e-07; 8.0541e-07; 8.2334e-07; 9.6667e-07; 1.10667e-06; 1.25959e-06; ...
    1.23916e-06; 1.42667e-06; 1.65125e-06; 1.75166e-06; 1.60209e-06; 1.70166e-06; 1.68875e-06; 1.89167e-06; 1.99875e-06; 1.91042e-06; ...
    2.09917e-06; 2.0025e-06; 2.21791e-06; 2.12667e-06; 2.21125e-06; 2.4075e-06; 2.39333e-06; 2.34834e-06; 2.58958e-06; 2.76875e-06; 2.43875e-06; ...
    2.48667e-06; 2.63125e-06; 3.09875e-06; 2.92583e-06; 2.8025e-06; 2.9075e-06; 3.00583e-06; 3.08e-06; 3.18417e-06; 3.89583e-06; 3.36792e-06; ...
    3.5925e-06; 3.75541e-06; 3.65958e-06; 3.79791e-06; 4.00833e-06; 4.47e-06; 4.34542e-06];

y_std = [1.0917e-07; 2.2e-07; 3.2375e-07; 4.5166e-07; 5.6458e-07; 7.8666e-07; 8.5875e-07; 1.02792e-06; 1.2225e-06; 1.39375e-06; 1.74125e-06; ...
    1.53833e-06; 1.73e-06; 1.88125e-06; 1.87916e-06; 1.97333e-06; 2.09417e-06; 2.14625e-06; 2.2125e-06; 2.38209e-06; 2.34875e-06; 2.54167e-06; ...
    2.465e-06; 2.61416e-06; 2.54834e-06; 2.72667e-06; 2.84333e-06; 2.87125e-06; 2.84792e-06; 2.9625e-06; 3.25667e-06; 2.91917e-06; 3.0875e-06; ...
    3.13333e-06; 3.2825e-06; 3.3575e-06; 3.38542e-06; 3.45416e-06; 3.54875e-06; 3.72958e-06; 3.83458e-06; 4.59666e-06; 4.03333e-06; 4.11917e-06; ...
    4.24458e-06; 4.45292e-06; 4.58292e-06; 4.7825e-06; 4.84e-06; 4.77875e-06];

%Stampo i risultati
figure('Name', 'Confronto Algoritmi di Ordinamento', 'Color', 'w');
colororder(lines(6));   % Imposto la palette predefinita per 6 colori ben distinti

% Disegno i vettori con marcatori ('MarkerSize') abbastanza piccoli per non 
% creare un confusione visivamente.

%{
% Quadratici
loglog(dim, y_bubble, '--o', 'LineWidth', 1.2); hold on;
loglog(dim, y_select, '--s', 'LineWidth', 1.2);
loglog(dim, y_insert, '--d', 'LineWidth', 1.2);

% n log n
loglog(dim, y_merge,  '-^', 'LineWidth', 1.2);
loglog(dim, y_quick,  '-v', 'LineWidth', 1.2);
loglog(dim, y_std,    '-x', 'LineWidth', 1.2);
%}

% Quadratici
loglog(dim, y_bubble, '--', 'LineWidth', 1.2); hold on;
loglog(dim, y_select, '--', 'LineWidth', 1.2);
loglog(dim, y_insert, '--', 'LineWidth', 1.2);

% n log n
loglog(dim, y_merge, 'LineWidth', 1.2);
loglog(dim, y_quick, 'LineWidth', 1.2);
loglog(dim, y_std, 'LineWidth', 1.2);
%}

% Forzo i tick sull'asse x, così da vedere la soglia
xticks([2 4 8 16 32 36 40 42 44 56 64 100])
xtickangle(45); % Ruoto per leggibilità

% Formattazione etichette e titolo
xlabel('Dimensione del Vettore', 'FontSize', 11, 'FontWeight', 'bold');
ylabel('Tempo di Esecuzione (secondi)', 'FontSize', 11, 'FontWeight', 'bold');
title('Confronto tempi di esecuzione di algoritmi di ordinamento', 'FontSize', 13);

% Metto la box della legenda in alto a sinistra
legend('Bubble Sort', 'Selection Sort', 'Insertion Sort', 'Merge Sort', ...
    'Quick Sort', 'Standard Sort', 'Location', 'northwest', 'FontSize', 10);

% Griglia ottimizzata per scale logaritmiche
grid on;
%grid minor; % Fondamentale per leggere bene i grafici loglog
%box on;

hold off;