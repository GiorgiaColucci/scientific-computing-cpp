#pragma once

#include <string>
#include <vector>


/* COMPONENTE
   Rappresenta un elemento del circuito (resistore o generatore).
*/

enum class TipoComponente {
    Resistore,
    Generatore
};

struct Componente {
    TipoComponente  tipo;
    std::string     nome;
    double          valore;
    double             n1;
    double             n2;
};


/* OUTPUT
 * Risultato della lettura della netlist.
 *   - ok          : true se il parsing e' andato bene, false se c'e' stato un errore
 *   - componenti  : lista dei componenti letti (in caso di errore puo' essere parziale)
 */

struct Output {
    bool ok;
    std::vector<Componente> componenti;
};


/* parse_netlist
    Legge una netlist dal file 'filename' e restituisce un Output

    Formato atteso: NOME VALORE NODO1 NODO2
    es:              R1    20     1     2

    dove: - NOME inizia con 'R' o 'V'
          - VALORE è maggiore di 0
          - NODO1 e NODO2 double positivi

    Si prosegue se:
        - sono presenti righe vuote o di soli spazi bianchi
        - spazi e tab multipli tra le colonne 
        - nome inizia con 'r' o 'v' (diventano 'R' e 'V')
        - file vuoto (restituisce vettore vuoto)
        - nodo decimale approssimabile a intero

    Warning (prosegue con scelte di default)
        - presenza di campi in eccesso dopo i primi 4 attesi -> si tengono solo i primi 4
        - resistenza negativa -> uso valore assoluto
        - componente già presente in una riga precedente --> salto la riga mantenendo la prima occorrenza

    Errori
        - file non apribile
        - riga con campi mancanti o errori di battitura
        - tipo componente sconosciuto (prefisso del nome diverso da 'R' o 'V')
        - nodi coincidenti sullp stesso componente
        - indice nodo non positivo 
        - VALORE resistenza = 0
*/


Output parse_netlist(const std::string& filename);