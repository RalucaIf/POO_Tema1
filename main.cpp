#include<iostream>
#include<string>
#include<vector>
#include<list>
/*Grupa 262, Iftime Raluca-Andreea, Turneu de tenis
La rularea programului, exista o eroare: std::bad_alloc, pe care nu stiu cum sa o repar
De asemenea, programul nu este unul complex si mai pot adauga functionalitati, precum: calculul probabiltatii pentru un jucator
de a castiga turneul, in functie de istoricul meciurilor castigate; adaugare regulament turneu si eliminarea implicita a 
unui jucator odata cu incalcarea regulamentului.*/
class Jucator{
private:
    int id;
    std:: string nume;
     int ranking;
     int punctajActual = 0;
     int meciuriCastigate=0;
public:
    Jucator(int _id=0,  int _ranking=0, std::string _nume=""): id(_id),nume(_nume), ranking(_ranking){}
    //constr de intializare
    Jucator(const Jucator &src){ id=src.id; nume=src.nume; ranking=src.ranking;}
    //constr de copiere
    ~Jucator(){}//destructor
    /*Jucator& operator=(const Jucator& other){
        id=other.id;
        ranking=other.ranking;
        return *this;
    }*/ //supraincarcarea operatorului =
    int getPc(){ return punctajActual;}
    void modifPc(){punctajActual++;}
    int getCastig() const {return this->meciuriCastigate;}
    std::string getNume(){return nume;}
    friend std::ostream&  operator<<(std::ostream& out, const Jucator& ob);
};
std::ostream&  operator<<(std::ostream& out, const Jucator& ob){
    out<<"Nume: "<<ob.nume<<std::endl;
    out<<"Id: "<<ob.id<<std::endl;    
    out<<"Ranking: "<<ob.ranking<<std::endl;
    out<<"Meciuri castigate: "<<ob.meciuriCastigate<<std::endl;
    return out;   
}
class Meci{
private:
    Jucator jucator1; //comp de clase
    Jucator jucator2;
    std::string locatie;
    std::string arbitru;
    int nrRunda;
public:
    Meci(int _nrRunda=0, std::string _locatie="", std::string _arbitru=""):nrRunda(_nrRunda), locatie(_locatie), arbitru(_arbitru){}
    Meci(const Meci &src){ nrRunda=src.nrRunda; locatie=src.locatie; arbitru=src.arbitru;}
    ~Meci(){}
    Meci& operator=(const Meci &other){
        locatie=other.locatie;
        arbitru=other.arbitru;
        nrRunda=other.nrRunda;
        return *this;
    }
    int getNrRunda() const{ return nrRunda;}
    void Puncteaza(Jucator juc) {juc.modifPc();}
    void win();
    void schLoc(std::string locNoua);
    friend std::ostream&  operator<<(std::ostream& out, const Meci& ob);
};
void Meci::win() {
        if(jucator1.getPc()>jucator2.getPc())
            std::cout<<"Meciul a fost castigat de "<<jucator1.getNume();
        else
            if(jucator1.getPc()<jucator2.getPc())
                std::cout<<"Meciul a fost castigat de "<<jucator2.getNume();
    }
void Meci::schLoc(std::string locNoua){
    std::cout<<"Conditiile meteo sunt nefavorabile" << std::endl << "Locatia noua este: " << locNoua << std::endl;
    this->locatie = locNoua;
}
std::ostream&  operator<<(std::ostream& out, const Meci& ob){
    out<<"Meciul se joaca in runda: "<<ob.nrRunda<<std::endl;
    out<<"Locatia initiala a meciului este: "<<ob.locatie<<std::endl;
    out<<"Arbitrul meciului este: "<<ob.arbitru<<std::endl;    
    out<<"Jucatorii meciului sunt: "<<ob.jucator1<<" si "<<ob.jucator2<<std::endl; 
    return out;   
}
class Turneu{
private:
    std::string numeTurneu;
    std::string locatieTurneu;
    std::vector<Jucator>TotiJuc{"1","2"};
    std::list<Meci>Runde;
    const int nrRunde=5;
    Jucator castigator;
    int an;
    int runda=1;  
public:
    Turneu(const int _an=2023, std::string _numeTurneu="", std::string _locatieTurneu=""):an(_an), numeTurneu(_numeTurneu), locatieTurneu(_locatieTurneu){}
    Turneu(const Turneu &src){ an=src.an; locatieTurneu=src.locatieTurneu; numeTurneu=src.numeTurneu;}
    ~Turneu(){}
    Turneu& operator=(const Turneu &other){
        numeTurneu=other.numeTurneu;
        locatieTurneu=other.locatieTurneu;
        return *this;
    }
    void win(Jucator* toti, int nrJuc);
    friend std::ostream&  operator<<(std::ostream& out, Turneu& ob);
    int getRunda(){ return runda;}
    Turneu& operator+=(Jucator juc) {
        this->TotiJuc.push_back(juc);
       // return *this;
    }
    const std::vector<Jucator> TotiJucatorii() const{
        return TotiJuc;
    }
    void MeciAdaugare(const Meci& meci){ Runde.push_back(meci);}
};

/*void Simulare() {
    for (int i = 1; i <= 5; i++) {
        std::cout << "Runda " << r << ":\n";
        for (j = TotiJuc.begin(); j!= TotiJuc.end(); ++j) {
            Jucator& juc11 = *j;
            k = j;
            ++k;
            while (k != TotiJuc.end()) {
                Jucator& juc2 = *k;
                Meci meci(i, "Location" + std::to_string(r), "Arbitru" + std::to_string(r));
                meci.jucator1 = juc1;
                meci.jucator2 = juc2;
                meci.Puncteaza(juc1);
                meci.Puncteaza(juc2);
                 meci.Puncteaza(juc1);
                 meci.Puncteaza(juc2);
                 meci.win();
                 std::cout << std::endl;

                Runde.push_back(meci);
                ++k;
                }
            }
        }
    }*/
void Turneu::win(Jucator* toti, int nrJuc){
    int max = 0;
    std::string numeCastig;
    for(int i = 0; i < nrJuc; i++){
        if(toti[i].getCastig() >= max){
            max = toti[i].getCastig();
            numeCastig = toti[i].getNume();
        }
    }
    std::cout<<"Castigatorul turneului este:" << numeCastig;
}
std::ostream&  operator<<(std::ostream& out, Turneu& ob){

    out<<"Meciurile care se joaca in runda "<<ob.getRunda()<<"sunt: "<<std::endl;
    for(const Meci& meci:ob.Runde) {
        out<<meci<<std::endl;
    }
    return out;   
}

int main(){
    Jucator juc1(1,1500,"jucator1");
    Jucator juc2(2,1600,"jucator2");
    std::vector<Jucator>TotiJuc{"1","2"};

    Turneu turneu(2023,"Wimbledon","Londra");
    turneu+=juc1;
    turneu+=juc2;
    std::cout<<turneu<<std::endl;
    //declarare jucatori intr un vector

    //initiere meci

    //declarare meci

    return 0;
}
