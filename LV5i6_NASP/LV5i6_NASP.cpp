#include <iostream>
#include <vector>


template <typename Tip> class Formula_3_CNF {

  Tip **ptr;
  int dim;
    
public:
void Unos_3_CNF(int dimenzija) {
      dim = dimenzija;
      ptr = (Tip**)malloc(sizeof(Tip*) * dimenzija);
      for (int i = 0; i < dimenzija; i++) {
          ptr[i] = (Tip*)malloc(sizeof(Tip) * 3);
      }

      std::cout << "Unesite elemente matrice: ";
      for (int i = 0; i < dimenzija; i++) {
          for (int j = 0; j < 3; j++) {
              std::cin >> ptr[i][j];
          }
          std::cout << std::endl;
      }
  }

  bool Rjesenje_3_CNF() {
      std::vector<int> v; 
      std::cout << "Unesena matrica glasi: \n";
      for (int i = 0; i < dim; i++) {
          for (int j = 0; j < 3; j++) {
              std::cout << ptr[i][j] << " ";
          }
          std::cout << std::endl;
      }

      for (int i = 0; i < dim; i++) {
          for (int j = 0; j < 3; j++) {
              if (ptr[i][j] > 0) {
                  v.push_back(1);
                  break;
              }
              if (j == 2) std::cout << "Data formula nije ispunjiva! ";
          }

      }

      if(v.size() == dim) return true;
      return false;
  }


  bool imaJedinicu(std::vector<bool>& vec, int pocetniIndex) {
      if (vec.at(pocetniIndex) == 1 || vec.at(pocetniIndex + 1) == 1 || vec.at(pocetniIndex + 2) == 1) return true;
      return false;

  }
  bool Verifikacija_3_CNF(std::vector<bool> argumenti) {
      int pronalazak = 0;
      std::vector<bool> pom; 
      for (int i = 0; i < dim; i++) {
          for (int j = 0; j < 3; j++) {
              if (ptr[i][j] < 0) pom.push_back(false);
              else pom.push_back(true);
          }
      }
      std::cout << "Ovako izgleda vektor argumenata nakon primjenjene formule: ";
      for (int i = 0; i < pom.size(); i++) {
          if (!pom.at(i)) {
              if (argumenti.at(i)) argumenti.at(i) = false;
              else argumenti.at(i) = true;
          }
          std::cout << argumenti.at(i) << " ";
      }
      
      for (int i = 0; i < argumenti.size() - 2; i += 3) {
          if (!imaJedinicu(argumenti, i)) return false;
      }
      return true;
  }
};

int main() {
   Formula_3_CNF<int> proba;
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
  else std::cout << "Vektor koji ste zadali je rjesiv.\n";
  return 0;
}
