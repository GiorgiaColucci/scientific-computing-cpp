#include "netlist_struct.hpp"

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>

static const double tol = 1e-12;

static const std::string filename="test_file.txt";

static std::string scrivi_file(const std::string& contenuto) 
{
    std::ofstream f(filename);
    f << contenuto;
    return filename;
}

// 1. Reference netlist 
static int test_parse_traccia()
{
    auto path = scrivi_file(
                "R1 10 1 2\n"
                "R2 20 2 3\n"
                "R3 30 2 4\n"
                "V1 10 1 3\n"
                "V2 20 4 3\n");
    Output risultato = parse_netlist(path);

    if (!risultato.ok || risultato.componenti.size() != 5) {
        std::cerr << "ERROR: test_parse_traccia: \n" 
                  << "ok= " << risultato.ok << "\n"
                  << "size= " << risultato.componenti.size() << "\n";
        return EXIT_FAILURE;
    }

    const Componente& c0 = risultato.componenti[0];
    if (c0.nome != "R1" ||
        c0.tipo != TipoComponente::Resistore ||
        abs(c0.valore-10.0) > tol ||
        c0.n1 != 1 || c0.n2 != 2) {
        std::cerr << "ERROR: test_parse_traccia: R1 doesn't match\n";
        return EXIT_FAILURE;
    }

    const Componente& c3 = risultato.componenti[3];
     if (c3.nome != "V1" ||
        c3.tipo != TipoComponente::Generatore ||
        abs(c3.valore-10.0) > tol ||
        c3.n1 != 1 || c3.n2 != 3) {
        std::cerr << "ERROR: test_parse_traccia: V1 doesn't match\n";
        return EXIT_FAILURE;
        }

    std::cout << "[OK]: test_parse_traccia\n" << "\n";
    return EXIT_SUCCESS;
}


// 2. Empty lines
static int test_parse_righe_vuote() 
{
    auto path= scrivi_file(
                "\n"
                "R1 10 1 2\n"
                "\n"
                "   \n"
                "V1 20 3 4\n");
    Output risultato = parse_netlist(path);

    if (!risultato.ok || risultato.componenti.size() != 2) {
        std::cerr << "ERROR: test_parse_righe_vuote\n\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK]: test_parse_righe_vuote\n"
              << "\n";
    return EXIT_SUCCESS;
}


// 3. Multiple spaces and tabs
static int test_parse_spazi_multipli() 
{
    auto path = scrivi_file(
                "R1    10       1    2\n"
                "  V1   5.5   3   4   \n");

    Output risultato = parse_netlist(path);
        
    if (!risultato.ok || risultato.componenti.size() != 2) {
    std::cerr << "ERROR: test_parse_spazi_multipli: \n\n" 
              << "ok= " << risultato.ok << "\n"
              << "size= " << risultato.componenti.size() << "\n";
    return EXIT_FAILURE;
    }

    const Componente& v1=risultato.componenti[1];

    if (v1.nome != "V1" ||
        v1.tipo != TipoComponente::Generatore ||
        abs(v1.valore-5.5) > tol ||
        v1.n1 != 3 || v1.n2 != 4) {
        std::cerr << "ERROR: test_parse_spazi_multipli: V1 doesn't matche\n";
        return EXIT_FAILURE;
    }

    std::cout << "[OK]: test_parse_spazi_multipli\n\n";
    return EXIT_SUCCESS;       
}


// 4. Lowercase prefix
static int test_parse_minuscolo() 
{
    auto path = scrivi_file (
                "r1 10 1 2\n"
                "v1 5 3 4\n");

    Output risultato = parse_netlist(path);

    if (!risultato.ok || risultato.componenti.size() != 2
        || risultato.componenti[0].tipo != TipoComponente::Resistore
        || risultato.componenti[1].tipo != TipoComponente::Generatore) {
        std::cerr << "ERROR: test_parse_minuscolo\n\n";
        return EXIT_FAILURE;
    }

    std::cout << "[OK]: test_parse_minuscolo\n\n";
    return EXIT_SUCCESS;
}


// 5. Empty file
static int test_parse_file_vuoto() 
{
    auto path = scrivi_file("");

    Output risultato = parse_netlist(path);

    if (!risultato.ok || !risultato.componenti.empty()) {
        std::cerr << "ERROR: test_parse_file_vuoto\n\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_parse_file_vuoto\n\n";
    return EXIT_SUCCESS;
}


// 6. File with only whitespace: same result as the previous one
static int test_parse_file_solo_whitespace()
{
    auto path = scrivi_file(
        "   \n"
        "\t\n"
        "\n");

    Output res = parse_netlist(path);

    if (!res.ok || !res.componenti.empty()) {
        std::cerr << "ERROR: test_parse_file_solo_whitespace\n\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_parse_file_solo_whitespace\n\n";
    return EXIT_SUCCESS;
}


// 7. Double node
static int test_parse_nodo_decimale_esatto()
{
    auto path = scrivi_file("R1 10 1.0 2.0\n");
    Output risultato = parse_netlist(path);

    if (!risultato.ok || risultato.componenti.size() != 1
        || risultato.componenti[0].n1 != 1 || risultato.componenti[0].n2 != 2) {
        std::cerr << "ERROR: test_parse_nodo_decimale_esatto\n\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_parse_nodo_decimale_esatto\n\n";
    return EXIT_SUCCESS;
}


// WARNING TESTS

// 8. Extra fields: only the first 4 are kept
static int test_warning_extra()
{
    auto path = scrivi_file("R1 10 1 2 EXTRA1 EXTRA2\n");
    Output res = parse_netlist(path);

    if (!res.ok || res.componenti.size() != 1
        || res.componenti[0].nome != "R1"
        || std::abs(res.componenti[0].valore - 10.0) > tol) {
        std::cerr << "ERROR: test_warning_token_in_eccesso\n\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_warning_token_in_eccesso\n\n";
    return EXIT_SUCCESS;
}

// 9. Negative resistance: the absolute value is used
static int test_warning_resistenza_negativa()
{
    auto path = scrivi_file("R1 -15.5 1 2\n");
    Output res = parse_netlist(path);

    if (!res.ok || res.componenti.size() != 1
        || std::abs(res.componenti[0].valore - 15.5) > tol) {
        std::cerr << "ERROR: test_warning_resistenza_negativa: value ="
                  << (res.componenti.empty() ? -1.0 : res.componenti[0].valore) << "\n\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_warning_resistenza_negativa\n\n";
    return EXIT_SUCCESS;
}

// 10. Duplicate name: warning + keep the first occurrence
static int test_warning_nome_duplicato()
{
    auto path = scrivi_file(
                "R1 10 1 2\n"
                "R1 20 3 4\n"     // duplicate → warning + skip
                "R2 30 2 3\n");
    Output res = parse_netlist(path);

    if (!res.ok || res.componenti.size() != 2) {
        std::cerr << "ERROR: test_warning_nome_duplicato: size ="
                  << res.componenti.size() << "\n\n";
        return EXIT_FAILURE;
    }
    if (res.componenti[0].nome != "R1"
        || std::abs(res.componenti[0].valore - 10.0) > tol) {
        std::cerr << "ERROR: test_warning_nome_duplicato: altered first occurrence\n\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_warning_nome_duplicato\n\n";
    return EXIT_SUCCESS;
}

// 11. Components in parallel: warning + skip the second
static int test_warning_componenti_paralleli()
{
    auto path = scrivi_file(
                "R1 10 1 2\n"
                "V1 30 1 2\n"     // same edge as R1 → skip
                "R3 5 2 3\n");
    Output res = parse_netlist(path);

    if (!res.ok || res.componenti.size() != 2) {
        std::cerr << "ERROR: test_warning_componenti_paralleli: size ="
                  << res.componenti.size() << "\n\n";
        return EXIT_FAILURE;
    }
    if (res.componenti[0].nome != "R1" || res.componenti[1].nome != "R3") {
        std::cerr << "ERROR: test_warning_componenti_paralleli: expected names R1,R3\\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_warning_componenti_paralleli\n\n";
    return EXIT_SUCCESS;
}

// 12. Components in parallel with swapped nodes
static int test_warning_paralleli_nodi_invertiti()
{
    auto path = scrivi_file(
                "R1 10 1 2\n"
                "V1 30 2 1\n");    // same nodes but swapped → same edge
    Output res = parse_netlist(path);

    if (!res.ok || res.componenti.size() != 1
        || res.componenti[0].nome != "R1") {
        std::cerr << "ERROR: test_warning_paralleli_nodi_invertiti\n\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_warning_paralleli_nodi_invertiti\n\n";
    return EXIT_SUCCESS;
}


// Tests: ERRORS (ok = false)

// 13. Malformed line: missing fields
static int test_error_riga_malformata()
{
    auto path = scrivi_file("R1 10 1\n");
    Output res = parse_netlist(path);

    if (res.ok) {
        std::cerr << "ERROR: test_error_riga_malformata: had to fail\n\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_error_riga_malformata\n\n";
    return EXIT_SUCCESS;
}

// 14. Typo in the numbers (e.g. '20a')
static int test_error_battitura_numero()
{
    auto path = scrivi_file("R1 20a 1 2\n");
    Output res = parse_netlist(path);

    if (res.ok) {
        std::cerr << "ERROR: test_error_battitura_numero: had to fail\n\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_error_battitura_numero\n\n";
    return EXIT_SUCCESS;
}

// 15. Unknown component type (neither R nor V)
static int test_error_tipo_sconosciuto()
{
    auto path = scrivi_file("X1 10 1 2\n");
    Output res = parse_netlist(path);

    if (res.ok) {
        std::cerr << "ERROR: test_error_tipo_sconosciuto: had to fail\n\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_error_tipo_sconosciuto\n\n";
    return EXIT_SUCCESS;
}

// 16. Coincident nodes on the same component
static int test_error_nodi_uguali()
{
    auto path = scrivi_file("R1 10 2 2\n");
    Output res = parse_netlist(path);

    if (res.ok) {
        std::cerr << "ERROR: test_error_nodi_uguali: had to fail\n\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_error_nodi_uguali\n\n";
    return EXIT_SUCCESS;
}

// 17. Non-positive node index: 0 or negative
static int test_error_nodo_non_positivo()
{
    auto path = scrivi_file("R1 10 0 2\n");
    Output res = parse_netlist(path);

    if (res.ok) {
        std::cerr << "ERROR: test_error_nodo_non_positivo (node 0)\n\n";
        return EXIT_FAILURE;
    }

    auto path2 = scrivi_file("R1 10 1 -3\n");
    Output res2 = parse_netlist(path2);

    if (res2.ok) {
        std::cerr << "ERROR: test_error_nodo_non_positivo (node -3)\n\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_error_nodo_non_positivo\n\n";
    return EXIT_SUCCESS;
}

// 18. Zero resistance
static int test_error_resistenza_zero()
{
    auto path = scrivi_file("R1 0 1 2\n");
    Output res = parse_netlist(path);

    if (res.ok) {
        std::cerr << "ERROE: test_error_resistenza_zero: had to fail\n\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_error_resistenza_zero\n\n";
    return EXIT_SUCCESS;
}

// 19. File that cannot be opened (nonexistent)
static int test_error_file_inesistente()
{
    Output res = parse_netlist("__file_che_non_esiste_12345__.txt");

    if (res.ok) {
        std::cerr << "ERROR: test_error_file_inesistente: had to fail\n\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_error_file_inesistente\n\n";
    return EXIT_SUCCESS;
}

// 20. Decimal node indices that are NOT integers (e.g. 1.5)
static int test_error_nodo_decimale()
{
    auto path = scrivi_file("R1 10 1.5 2\n");
    Output res = parse_netlist(path);

    if (res.ok) {
        std::cerr << "ERROR: test_error_nodo_decimale: had to fail\n\n";
        return EXIT_FAILURE;
    }
    std::cout << "[OK] test_error_nodo_decimale\n\n";
    return EXIT_SUCCESS;
}

/* MAIN */


int main()
{
    int falliti = 0;

    // Clean parsing
    falliti += test_parse_traccia()                  == EXIT_SUCCESS ? 0 : 1;
    falliti += test_parse_righe_vuote()              == EXIT_SUCCESS ? 0 : 1;
    falliti += test_parse_spazi_multipli()           == EXIT_SUCCESS ? 0 : 1;
    falliti += test_parse_minuscolo()                == EXIT_SUCCESS ? 0 : 1;
    falliti += test_parse_file_vuoto()               == EXIT_SUCCESS ? 0 : 1;
    falliti += test_parse_file_solo_whitespace()     == EXIT_SUCCESS ? 0 : 1;
    falliti += test_parse_nodo_decimale_esatto()     == EXIT_SUCCESS ? 0 : 1;

    // Warning
    falliti += test_warning_extra()       == EXIT_SUCCESS ? 0 : 1;
    falliti += test_warning_resistenza_negativa()    == EXIT_SUCCESS ? 0 : 1;
    falliti += test_warning_nome_duplicato()         == EXIT_SUCCESS ? 0 : 1;
    falliti += test_warning_componenti_paralleli()   == EXIT_SUCCESS ? 0 : 1;
    falliti += test_warning_paralleli_nodi_invertiti() == EXIT_SUCCESS ? 0 : 1;

    // Errors
    falliti += test_error_riga_malformata()          == EXIT_SUCCESS ? 0 : 1;
    falliti += test_error_battitura_numero()         == EXIT_SUCCESS ? 0 : 1;
    falliti += test_error_tipo_sconosciuto()         == EXIT_SUCCESS ? 0 : 1;
    falliti += test_error_nodi_uguali()              == EXIT_SUCCESS ? 0 : 1;
    falliti += test_error_nodo_non_positivo()        == EXIT_SUCCESS ? 0 : 1;
    falliti += test_error_resistenza_zero()          == EXIT_SUCCESS ? 0 : 1;
    falliti += test_error_file_inesistente()         == EXIT_SUCCESS ? 0 : 1;
    falliti += test_error_nodo_decimale()            == EXIT_SUCCESS ? 0 : 1;


    if (falliti == 0) {
        std::cout << "\nAll the parser tests have passed.\n";
        return EXIT_SUCCESS;
    } else {
        std::cerr << "\n" << falliti << " failed tests.\n";
        return EXIT_FAILURE;
    }
}
