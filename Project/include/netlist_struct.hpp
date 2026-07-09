#pragma once

#include <string>
#include <vector>


/* COMPONENT
   Represents a circuit element (resistor or voltage source).
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
 * Result of reading the netlist.
 *   - ok          : true if parsing succeeded, false if there was an error
 *   - componenti  : list of parsed components (may be partial in case of error)
 */

struct Output {
    bool ok;
    std::vector<Componente> componenti;
};


/* parse_netlist
    Reads a netlist from file 'filename' and returns an Output

    Expected format: NAME VALUE NODE1 NODE2
    e.g.:            R1    20    1     2

    where: - NAME starts with 'R' or 'V'
           - VALUE is greater than 0
           - NODE1 and NODE2 are positive doubles

    Continues when:
        - there are empty or whitespace-only lines
        - multiple spaces and tabs between columns
        - the name starts with 'r' or 'v' (normalized to 'R' and 'V')
        - the file is empty (returns an empty vector)
        - a decimal node index that rounds to an integer

    Warnings (continues with default choices)
        - extra fields beyond the first 4 expected -> only the first 4 are kept
        - negative resistance -> absolute value is used
        - component already present in an earlier line -> the line is skipped, keeping the first occurrence

    Errors
        - file cannot be opened
        - line with missing fields or typos
        - unknown component type (name prefix other than 'R' or 'V')
        - coincident nodes on the same component
        - non-positive node index
        - resistance VALUE = 0
*/


Output parse_netlist(const std::string& filename);