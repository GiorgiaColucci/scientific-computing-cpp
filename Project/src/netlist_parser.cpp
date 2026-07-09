#include "netlist_struct.hpp"

#include <cctype>   //per std::isspace
#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <typeinfo> //per i tipi

// solo_spazivuoti --> restituisce true se la stringa s contiene solo spazi/tab/\n
static bool solo_spazivuoti(const std::string& s) 
{
    for (char c : s) {
        if (!std::isspace(static_cast<unsigned char>(c))) {    
            return false;
        }
    }
    return true;
}

// normalizza_csv - restituisce una copia della riga in cui le virgole sono
// sostituite da spazi, così operator>> puo' leggere correttamente anche netlist 
// in formato CSV (es. "R1,20,1,2").
static std::string normalizza_csv(const std::string& s)
{
    std::string norm = s;
    std::replace(norm.begin(), norm.end(), ',', ' ');
    return norm;
}
 

// ho creato questa funzione in quanto spesso si richiede di stampare un errore 
static void stampa_errore (const int n_riga, const std::string& riga, const std::string& messaggio) 
{
    std::cerr << "Errore nella riga " << n_riga << ": " << messaggio << "\n"
              << "Riga: " << riga << "\n";
}

static void stampa_warning (const int n_riga, const std::string& riga, const std::string& messaggio) 
{
    std::cerr << "Avviso alla riga " << n_riga << ": " << messaggio << "\n"
                  << "Riga: " << riga << "\n";
}



// FUNZIONE PRINCIPALE //
Output parse_netlist (const std::string& filename) {  
    Output out;
    out.ok=true;    // diventa false al primo errore

    // Apertura file 
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "ERRORE: impossibile aprire il file " << filename << "\n";
        out.ok=false;
        return out;
    }

    std::string riga;
    int n_riga=0;

    while (std::getline(in,riga))    // while(!in.eof) processa una riga di troppo (stesso errore in prima esercitazione)
    {
        ++n_riga;   //metto cosi e non alla fine n_riga++ perche quando faccio continue poi non incremento 

        const std::string riga_norm = normalizza_csv(riga);
        
        // Salto righe vuote o solo spazi vuoti 
        if (solo_spazivuoti(riga_norm)) {
            continue;
        }

        // Estraggo i campi NOME VALORE NODO1 NODO2
        std::istringstream iss(riga_norm); // invece di scorrere ogni riga a mano questo lo fa in automatico
        std::string nome;
        double valore;
        double n1_letto;
        double n2_letto;
		
		// meno campi di quelli attesi
        if (!(iss >> nome >> valore >> n1_letto >> n2_letto)) {
            stampa_errore (n_riga, riga, std::string("ERRORE: attesi 4 campi (NOME VALORE NODO1 NODO2)"));
            out.ok = false;
            return out;
        }

        // campi in eccesso: prendo solo i primi 4 
        std::string extra;
        if (iss >> extra) {
            stampa_warning (n_riga, riga, std::string("WARNING: trovati campi in eccesso dopo i 4 attesi: verranno considerati solo i primi 4"));
        }

		int n1 = 0;
		int n2 = 0;

		// Controllo decimali
		int n1_arrotondato = static_cast<int>(std::round(n1_letto));
		if (std::abs(n1_letto - n1_arrotondato) < 1e-12) {
			if (n1_letto != n1_arrotondato) {
				stampa_warning(n_riga, riga, std::string("WARNING: nodo n1 inserito come decimale, arrotondato ad intero"));
			}
			n1 = n1_arrotondato;
		}
		else {
			stampa_errore(n_riga, riga, std::string("ERRORE: il nodo n1 inserito come decimale non è riconducibile a un intero"));
			out.ok = false;
			return out;
		}
		
		int n2_arrotondato = static_cast<int>(std::round(n2_letto));
		if (std::abs(n2_letto - n2_arrotondato) < 1e-12) {
			if (n2_letto != n2_arrotondato) {
				stampa_warning(n_riga, riga, std::string("WARNING: nodo n2 inserito come decimale, arrotondato ad intero"));
			}
			n2 = n2_arrotondato;
		}
		else {
			stampa_errore(n_riga, riga, std::string("ERRORE: il nodo n2 inserito come decimale non è riconducibile a un intero"));
			out.ok = false;
			return out;
		}
		

        // Valutazione prefisso 
        TipoComponente tipo;
        const char prefisso = static_cast<char>(std::toupper(static_cast<unsigned char>(nome[0]))); // preso da https://cppreference.com/cpp/string/byte/toupper

        if (prefisso=='R') {
            tipo = TipoComponente::Resistore;
        } else if (prefisso=='V') {
            tipo = TipoComponente::Generatore;
        } else {
            stampa_errore (n_riga, riga, std::string("ERRORE: tipo componente sconosciuto: prefisso atteso 'R' o 'V', trovato") + prefisso);
            out.ok=false;
            return out;
        }

        // nodi coincidenti 
        if (n1 == n2) {
            stampa_errore (n_riga, riga, std::string("ERRORE: i due nodi del componente coincidono"));
            out.ok=false;
            return out;
        }

		//nodi negativi o uguali a zero
        if (n1<=0 || n2<=0) {
            stampa_errore(n_riga, riga, std::string("ERRORE: nodo non valido, sono ammessi solo valori positivi"));
            out.ok=false;
            return out;
        }

        // Validazione del valore del resitore
        // Nel caso generatore seV<0 dovrebbe significare che la polarità è rovesciata, se V=0 spento
        if (tipo == TipoComponente::Resistore) {
            const double tol = 1e-15;
            if (std::abs(valore) < tol ) {   
                stampa_errore(n_riga, riga, std::string("ERRORE: resistenza pari a zero non ammessa"));
                out.ok=false;
                return out;
            }
            if (valore<-(tol)) {   
                stampa_warning(n_riga, riga, std::string("WARNING: resistenza negativa, scelto il valore assoluto"));
                valore=-valore;
            }
        }

        // Nome duplicato
        bool duplicato = false;
        for (const Componente& c : out.componenti) {
            if (c.nome == nome) {
                duplicato = true;
                break;  // appena trovato esco dal for 
            }
        }

        if (duplicato) {
            stampa_warning(n_riga, riga, std::string("WARNING: nome componente già presente, questa riga viene ignorata e si mantiene la prima occorrenza"));
            continue;   // non inserita nel vettore
        }

        // CONTROLLO PARALLELI: due componenti sullo stesso arco non sono ammessi.
        // Normalizziamo la coppia di nodi a (min, max) per gestire anche il caso
        // "V1 30 2 1" che e' lo stesso arco di "R1 20 1 2".

        int n_min=std::min(n1,n2);
        int n_max=std::max(n1,n2);

        bool parallelo=false;
        for (const Componente& c : out.componenti) {
            int c_min = std::min(c.n1,c.n2);
            int c_max = std::max(c.n1, c.n2);
            if (c_min == n_min && c_max == n_max) {
                parallelo=true;
                break;
            }
        }

        if (parallelo) {
            stampa_warning(n_riga, riga, std::string("WARNING: è già presente un componente sullo stesso arco. NON sono ammessi componenti in parallelo. La riga viene ignorata"));
            continue;
        }

        // Se è tutto ok
        Componente c;
        c.tipo = tipo;
        c.nome = nome;
        c.valore = valore;
        c.n1 = n1;
        c.n2 = n2;

        out.componenti.push_back(c);
    }
    return out;
}