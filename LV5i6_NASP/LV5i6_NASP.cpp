#include <iostream>
#include <utility>
#include <vector>
#include <sstream>
#include <cmath>


template <typename Tip> class Formula_3_CNF {

  
  int n=0;
  std::vector<std::vector<Tip>> tabelaKomb;
  std::vector<std::vector<Tip>> klauzeIzFormule;
public:
    bool provjeriKlauze(std::vector<int> vrijednostLiterala) {
        
        bool check = true;
        bool control;
        int indexLiterala;
        for (int i = 0; i < klauzeIzFormule.size(); i++) {
            
            control = false;
            for (int j = 0; j < klauzeIzFormule.at(i).size(); j++) {
                indexLiterala = abs(klauzeIzFormule.at(i).at(j)) - 1;
                
                if (klauzeIzFormule.at(i).at(j) > 0 && vrijednostLiterala.at(indexLiterala)==1) //Provjera da li je isti znak u literalu i kombinaciji 
                {
                    control = true;
                    break;
                }
                else if (klauzeIzFormule.at(i).at(j) < 0 && vrijednostLiterala.at(indexLiterala)==0) //Provjera da li je isti znak u literalu i kombinaciji
                {
                    control = true;
                    break;
                }
            }
            if (!control) {
                check = false;
                break;
            }
        }
        return check;
    }
    void generateCombinations() {
        std::vector<std::vector<int>> outer_vec;

        for (unsigned i = 0; i < (1U << n); ++i) {
            std::vector<int> inner_vec(n);  // create an inner vector with n elements
            for (int j = 0; j < n; ++j) {
                inner_vec[j] = (i >> j) & 1;  // set the j-th element to be the j-th bit of i
            }
            outer_vec.push_back(inner_vec);  // add the inner vector to the outer vector
        }
        for (int i = 0; i < outer_vec.size(); i++) {
            std::vector<int> inner_vec = outer_vec.at(i);
            for (int j = 0; j < inner_vec.size(); j++) {
                std::cout << inner_vec.at(j) << " ";
            }
            std::cout << std::endl;
        }

        tabelaKomb = outer_vec;
    }
    
    void Unos_3_CNF() {
        std::vector<std::vector<int>> outer_vec;

        while (true) {
            std::cout << "\nUnesite 3-sat formule, maksimalno 8 ili q za kraj unosa - kada unesete jednu formulu pritisnite ENTER: ";

            std::string input;
            std::getline(std::cin, input);

            if (input == "q") {
                break;  // exit the loop
            }

            std::vector<int> inner_vec(3);  // Unutrasnji vektor sa 3 literala
            std::stringstream ss(input);  // stringstream objekat radi odvajanja zareza
            for (int i = 0; i < 3; ++i) {
                int x;
                char c;
                ss >> x >> c;  // read an integer and a character from the stringstream
                inner_vec[i] = x;
                if (abs(x) > n) n = abs(x);
            }
            outer_vec.push_back(inner_vec);  // add the inner vector to the outer vector
        }
    
        klauzeIzFormule = outer_vec;
        generateCombinations();
  }


    bool Rjesenje_3_CNF() {
       
        std::vector<int> temp;
        bool flag = false;
        std::cout << "\nUnesene su iduce klauze: \n";
        for (int i = 0; i < klauzeIzFormule.size(); i++) {
            std::vector<int> inner_vec = klauzeIzFormule.at(i);
            for (int j = 0; j < inner_vec.size(); j++) {
                std::cout << inner_vec.at(j) << " ";
            }
            std::cout << std::endl;
        }
        for (int x = 0; x < (1 << n); x++) {
            temp.clear();
            for (int y = 0; y < n; y++) temp.push_back(tabelaKomb.at(x).at(y)); //Uzimanje svake kombinacije
            if (provjeriKlauze(temp)) {
                flag = true;
                break;
            }
        }
        if (!flag) std::cout << "Logicka formula nije ispunjiva!\n";
        return flag;
    }

    bool Verifikacija_3_CNF(std::vector<int> argumenti) {
        return provjeriKlauze(std::move(argumenti));
    }
};

int main() {
    int unos;
    std::vector<int> argumenti; 
    argumenti.push_back(1);
    argumenti.push_back(1);
    argumenti.push_back(1);
       
    Formula_3_CNF<int> formula;
    //formula.Verifikacija_3_CNF(argumenti);
    
    do {
        std::cout << "Dobrodosli u program za rad sa 3-SAT problemom i k-indsetom i clique-om.\n"
            "Pritisnite 1 - Za unos logicke formule \n"
            "Pritisnite 2 - Za unos grafa\n"
            "Pritisnite 3 - Za ispitivanje da li je formula ispunjiva\n"
            "Pritisnite 4 - Za ispitivanje postoji li k nezavisnih cvorova u grafu\n"
            "Pritisnite 5 - Za ispitivanje postoji li k-klika\n"
            "Pritisnite 6 - Za verifikaciju formule\n"
            "Pritisnite 7 - Za verifikaciju skupa nezavisnih cvorova\n"
            "Pritisnite 8 - Za verifikaciju k-klike\n"
            "Pritisnite 9 - Za izlaz\n";
        std::cin >> unos;
        switch (unos) {

        case 1:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Odabrali ste unos logicke formule.\n";
            formula.Unos_3_CNF();
            std::cout << "Unos uspjesno zavrsen.\n\n\n";
            break;
        case 3:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nOdabrali ste ispitivanje da li je logicka formula ispunjiva. Ispod ovog teksta su rezultati. \n";
            if (formula.Rjesenje_3_CNF()) std::cout << "Logicka formula je ispunjiva! \n\n\n";
            break;
        case 6: 
            std::vector<int> vec;
            int broj;
            std::cout << "Odabrali ste verifikaciju vektor. Unesite vrijednosti literala, za zavrsetak unijeti -1:  " << std::endl;

            do {
                std::cin >> broj;
                if (broj != -1) vec.push_back(broj);
            } while (broj != -1);

            std::cout << "Verifikacija unesene vrijednosti: " << formula.Verifikacija_3_CNF(vec) << std::endl;
            break;
        }
    } while (unos != 9);
    
  /*Formula_3_CNF<int> proba;
  int dimenzija ;
  std::cout << "Unesite dimenzije matrice(ne vece od 8x3): \n";
  std::cin >> dimenzija;
  proba.Unos_3_CNF(dimenzija);
  if(proba.Rjesenje_3_CNF()) std::cout << "Data formula je ispunjiva! \n";
  std::vector<bool> v; 
  v.push_back(false);
  v.push_back(false);
  v.push_back(false);
  v.push_back(false);
  v.push_back(false);
  v.push_back(false);
  v.push_back(false);
  v.push_back(false);
  v.push_back(false);
  if (!proba.Verifikacija_3_CNF(v)) std::cout << "Vektor koji ste zadali nije rjesiv.\n";
  else std::cout << "Vektor koji ste zadali je rjesiv.\n";*/
  return 0;
}
