%% Grafici di rappresentazione dei tempi di esecuzione di algoritmi di sorting al crescere della dimensione del vettore a cui sono applicati
% Considero algoritmi di bubble-sort, selection-sort, insertion-sort, merge-sort, quick-sort e standard sort fornito dalla libreria standard di c++ 
% HO 50 dimensioni, partendo da 2 e arrivando a 100 con passo 2 
% Compilazione in modalità debug

dim = [2; 4; 6; 8; 10; 12; 14; 16; 18; 20; 22; 24; 26; 28; 30; 32; 34; 36; 38; 40; 42; 44; 46; 48; 50; 52; 54; ...
    56; 58; 60; 62; 64; 66; 68; 70; 72; 74; 76; 78; 80; 82; 84; 86; 88; 90; 92; 94; 96; 98; 100];

y_bubble = [4.334e-08; 1.7125e-07; 2.7833e-07; 6.2792e-07; 8.6375e-07; 1.41583e-06; 1.67875e-06; 1.81375e-06; ...
    2.2e-06; 2.6e-06; 3.1675e-06; 3.62125e-06; 3.6875e-06; 7.22875e-06; 8.27375e-06; 7.13125e-06; 7.7475e-06; ...
    7.77166e-06; 8.30333e-06; 8.16917e-06; 8.74084e-06; 8.4425e-06; 9.76208e-06; 9.475e-06; 9.64375e-06; 9.86166e-06; ...
    9.63125e-06; 1.07858e-05; 1.03875e-05; 1.12171e-05; 1.18438e-05; 1.18529e-05; 1.25458e-05; 1.35117e-05; 1.29829e-05; ...
    1.32242e-05; 1.40692e-05; 1.47142e-05; 1.48992e-05; 1.58158e-05; 1.76467e-05; 1.68854e-05; 1.78888e-05; 1.89446e-05; ...
    1.93692e-05; 1.99704e-05; 2.08125e-05; 2.15692e-05; 2.25992e-05; 2.35e-05];

y_select = [4e-08; 7.775e-07; 4.275e-07; 4.8916e-07; 9.9708e-07; 8.9125e-07; 1.01291e-06; 1.27375e-06; 1.57708e-06; ...
    1.89208e-06; 2.17041e-06; 2.57333e-06; 2.61292e-06; 4.28791e-06; 3.88542e-06; 4.34709e-06; 4.91334e-06; 4.59792e-06; ...
    5.12959e-06; 4.94208e-06; 5.375e-06; 5.11e-06; 5.58583e-06; 5.49291e-06; 5.36667e-06; 5.74625e-06; 5.84083e-06; 6.26584e-06; ...
    6.28417e-06; 6.42667e-06; 6.81e-06; 6.97375e-06; 7.20584e-06; 7.62292e-06; 7.55541e-06; 7.60792e-06; 8.08583e-06; 8.52042e-06; ...
    8.49625e-06; 8.98791e-06; 9.71666e-06; 9.68917e-06; 1.03013e-05; 1.05779e-05; 1.11467e-05; 1.14367e-05; 1.19579e-05; 1.3925e-05; ...
    1.29462e-05; 1.33758e-05];

y_insert = [3.416e-08; 9.125e-08; 1.7625e-07; 4.4833e-07; 3.5875e-07; 4.5375e-07; 5.1416e-07; 6.1875e-07; 7.5875e-07; 8.6709e-07; ...
    1.02375e-06; 1.19541e-06; 1.21167e-06; 2.03709e-06; 1.92208e-06; 2.07041e-06; 2.48375e-06; 2.2575e-06; 2.39625e-06; 2.42583e-06; ...
    2.57125e-06; 2.49875e-06; 2.63e-06; 2.64583e-06; 2.68792e-06; 2.82375e-06; 2.82542e-06; 3.08833e-06; 3.11e-06; 3.16875e-06; ...
    3.40125e-06; 4.08333e-06; 3.71834e-06; 3.89917e-06; 3.76e-06; 3.90416e-06; 4.18292e-06; 4.34833e-06; 4.375e-06; 4.62208e-06; ...
    4.74667e-06; 4.95584e-06; 5.60542e-06; 5.47791e-06; 5.895e-06; 6.13416e-06; 6.29708e-06; 6.51291e-06; 6.66125e-06; 6.98041e-06];

y_merge = [2.8042e-07; 9.9333e-07; 1.63958e-06; 1.73791e-06; 2.30375e-06; 2.9675e-06; 3.09583e-06; 3.57708e-06; 4.165e-06; 4.51083e-06; ...
    5.265e-06; 5.64458e-06; 5.53709e-06; 8.94959e-06; 7.84083e-06; 8.36209e-06; 9.13e-06; 8.53084e-06; 9.03666e-06; 8.49125e-06; ...
    8.55917e-06; 8.38417e-06; 8.25333e-06; 8.38541e-06; 8.28791e-06; 9.09667e-06; 8.54625e-06; 8.70542e-06; 8.65875e-06; 8.73792e-06; ... 
    8.96959e-06; 9.15959e-06; 9.35042e-06; 9.42e-06; 9.0925e-06; 9.2475e-06; 9.65833e-06; 1.00963e-05; 9.85708e-06; 1.00121e-05; 1.04604e-05; ...
    1.05879e-05; 1.12821e-05; 1.12017e-05; 1.17525e-05; 1.18246e-05; 1.20496e-05; 1.30329e-05; 1.28233e-05; 1.31896e-05];

y_quick = [5.667e-08; 3.6584e-07; 2.5584e-07; 3.8916e-07; 5.4041e-07; 6.775e-07; 7.1125e-07; 8.8416e-07; 9.4833e-07; 1.10833e-06; 1.26084e-06; ...
    1.40834e-06; 1.4925e-06; 2.55875e-06; 2.28292e-06; 2.33666e-06; 2.65083e-06; 2.335e-06; 2.28416e-06; 2.36791e-06; 2.24167e-06; 2.37292e-06; ...
    2.36916e-06; 2.45416e-06; 2.38875e-06; 2.4825e-06; 2.465e-06; 2.43667e-06; 2.68083e-06; 2.55125e-06; 3.0875e-06; 2.71959e-06; 2.85667e-06; ...
    2.7325e-06; 2.79709e-06; 2.79791e-06; 2.89583e-06; 3.03334e-06; 2.99083e-06; 3.08916e-06; 3.15833e-06; 3.34833e-06; 3.56709e-06; 3.71375e-06; ...
    3.80833e-06; 3.78584e-06; 3.80291e-06; 3.86e-06; 4.11292e-06; 4.09375e-06];

y_std = [1.2583e-07; 2.0542e-07; 3.3083e-07; 4.225e-07; 5.625e-07; 7.0416e-07; 7.8e-07; 9.1209e-07; 1.27625e-06; 1.52e-06; 1.63458e-06; ...
    1.84667e-06; 1.81042e-06; 3.02208e-06; 2.64167e-06; 2.95292e-06; 2.82292e-06; 3.00875e-06; 2.70958e-06; 2.90958e-06; 2.8275e-06; ...
    3.00042e-06; 3.38583e-06; 3.03708e-06; 2.94416e-06; 3.055e-06; 3.0275e-06; 2.97292e-06; 3.09334e-06; 3.22125e-06; 3.37375e-06; 3.30584e-06; ...
    3.42833e-06; 3.20958e-06; 3.35375e-06; 3.39583e-06; 3.56792e-06; 3.46e-06; 3.6275e-06; 3.72542e-06; 3.89875e-06; 3.97959e-06; 4.16792e-06; ...
    4.14917e-06; 4.39958e-06; 4.51e-06; 4.49791e-06; 4.78917e-06; 4.875e-06; 4.81666e-06];

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
xticks([2 4 8 16 30 32 36 40 42 64 100])
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