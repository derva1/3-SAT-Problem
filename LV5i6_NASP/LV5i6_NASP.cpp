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
        return provjeriKlauze(argumenti);
    }
};


class KlikaINDSETGraf {
    std::vector<std::vector<int>> graf, matrica_susjedstva, obrnutoGraf, matrica_susjedstva_obrnuto;




public:

    void unosGrafa() {
        
        
        int dimenzija;
        std::cout << "Unesite dimenzije matrice(jedan broj) \n";
        std::cin >> dimenzija;
        graf.resize(dimenzija, std::vector<int>(dimenzija));
        obrnutoGraf.resize(dimenzija,std::vector<int>(dimenzija));

        std::cout << "Unesite elemente matrice: \n";
        for (int i = 0; i < dimenzija; i++) {
            for (int j = 0; j < dimenzija; j++) {
                int unos;
                std::cin >> unos;
                graf.at(i).at(j) = unos;
                if (unos) obrnutoGraf.at(i).at(j) = 0;
                else obrnutoGraf.at(i).at(j) = 1;
            }
        }

        // Spasavanje indexa susjeda u matrici za oba problema
        for (int i = 0; i < graf.size(); i++) {
            std::vector<int> susjed;
            for (int j = 0; j < graf.at(i).size(); j++) if (graf.at(i).at(j) == 1) susjed.push_back(j);
            matrica_susjedstva.push_back(susjed);
        }

        for (int i = 0; i < graf.size(); i++) {
            std::vector<int> susjed;
            for (int j = 0; j < obrnutoGraf.at(i).size(); j++) if (obrnutoGraf.at(i).at(j) == 1) susjed.push_back(j);
            matrica_susjedstva_obrnuto.push_back(susjed);
        }
    }

};

int main() {
    
    int unos;  
    Formula_3_CNF<int> formula;
    KlikaINDSETGraf graf;
    //int K;
    std::vector<int> vec;
    //std::vector<int> verifikacioniVektor;
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

        case 2:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Odabrali ste unos grafa.\n";
            graf.unosGrafa();
            std::cout << "Unos uspjesno zavrsen.\n\n\n";
            break;
        case 3:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nOdabrali ste ispitivanje da li je logicka formula ispunjiva. Ispod ovog teksta su rezultati. \n";
            if (formula.Rjesenje_3_CNF()) std::cout << "Logicka formula je ispunjiva! \n\n\n";
            break;

        /*case 4:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Odabrali ste ispitivanje da li u grafu ima K nezavisnih cvorova. Unesite broj K: \n";
            
            std::cin >> K;
            std::cout << "Za " << K << "cvorova funkcija daje izlaz: " << graf.Rjesenje_K_INDSET(K) << std::endl;
            break;*/
        /*case 5:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Odabrali ste ispitivanje da li u grafu ima K klika. Unesite broj K: \n";
            
            std::cin >> K;
            std::cout << "Za " << K << "cvorova funkcija daje izlaz: " << graf.Rjesenje_K_Clique(K) << std::endl;
            break;*/
        case 6: 
            
            int broj;
            std::cout << "Odabrali ste verifikaciju vektor. Unesite vrijednosti literala, za zavrsetak unijeti -1:  " << std::endl;

            do {
                std::cin >> broj;
                if (broj != -1) vec.push_back(broj);
            } while (broj != -1);

            std::cout << "Verifikacija unesene vrijednosti: " << formula.Verifikacija_3_CNF(vec) << std::endl << std::endl;
            break;
        /*case 7:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Odabrali ste verifikaciju nezavisnih cvorova.";
            std::cout << "Unesite nezavisne cvorove numerisano od 0, za zavrsetak unijeti -1:  " << std::endl;
            
            do {
                std::cin >> broj;
                if (broj != -1) verifikacioniVektor.push_back(broj);
            } while (broj != -1);

            std::cout << "Verifikacija skupa nezavisnih cvorova: " << graf.Verifikacija_K_INDSET(verifikacioniVektor) << std::endl;
            break;*/
        /*case 8:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Odabrali ste verifikaciju K-Klike";
            std::cout << "Unesite nezavisne cvorove numerisano od 0, za zavrsetak unijeti -1:  " << std::endl;
            
            do {
                std::cin >> broj;
                if (broj != -1) verifikacioniVektor.push_back(broj);
            } while (broj != -1);

            std::cout << "Verifikacija skupa nezavisnih cvorova: " << graf.verifikacijaKKlike(verifikacioniVektor) << std::endl;
            break;*/
        }
    } while (unos != 9);
    
  return 0;
}
