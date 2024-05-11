#include <iostream>
#include <string>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;

struct Date
{
    int jour;
    int mois; // Struct qui stocke la date
    int annee;
};
class Paiement;

/// Clas utilisateur
class Utilisateur
{
private:
    int id;
    string email;
    string nom;
    string adresse;
    set<Paiement *> paiements; // Utilisateur – Paiement (1 à *)
public:
    Utilisateur(int _id, string _email, string _nom, string _adresse)
    {
        id = _id;
        email = _email;
        nom = _nom;
        adresse = _adresse;
    }

    int getId() const { return id; }
    string getEmail() const { return email; }
    string getNom() const { return nom; }
    string getAdresse() const { return adresse; }
    void setId(int _id) { id = _id; }
    void setEmail(const string &_email) { email = _email; }
    void setNom(const string &_nom) { nom = _nom; }
    void setAdresse(const string &_adresse) { adresse = _adresse; }
    bool operator<(const Utilisateur &autre) const
    {
        return id < autre.id;
    } // jai ajouter ca car j'ai un probleme sur une fonction il ma demande un surchargej'ai essaye et ca marche
    void ajouterPaiement(Paiement *paiement)
    {
        paiements.insert(paiement);
    }

    int nombrePaiements() const
    {
        return paiements.size();
    }
    void affichernom() { cout << nom; } /// pour afficher sur la facture
    ~Utilisateur(){};
};
class Facture; // forward je veux utilise class facture pour declare la relation sur paiment
// Class Paiement abstraite
class Paiement
{
protected:
    int idPaiement;
    Date date;
    Utilisateur *utilisateur; // Paiement - Utilisateur (* à 1),
    Facture *facture;         // Paiement – Facture (1 à 1)
public:
    Paiement(int _idPaiement = 0, Date _date = Date(), Utilisateur *_utilisateur = nullptr, Facture *_facture = nullptr)
    {
        idPaiement = _idPaiement;
        date = _date;
        this->utilisateur = _utilisateur;
        facture = _facture;
    }

    int getIdPaiement() { return idPaiement; }
    Date getDate() { return date; }
    Utilisateur *getUtilisateur() { return utilisateur; }
    Facture *getFacture() { return facture; }
    virtual string getType() const = 0; // pour return le type de paiment sur la facture+virtual
    ~Paiement() {}
};

// Classe Cheque
class Cheque : public Paiement
{
private:
    string idcheque;
    string proprietaire;
    Date dateEncaissement;

public:
    Cheque(int _idPaiement = 0, Date _date = Date(), Utilisateur *_utilisateur = nullptr, Facture *_facture = nullptr, const string &_idCheque = "", const string &_proprietaire = "", const Date &_dateEncaissement = Date())
        : Paiement(idPaiement, date, utilisateur, facture)
    {
        idcheque = _idCheque;
        proprietaire = _proprietaire;
        date = _dateEncaissement;
    }
    string getIdCheque() const { return idcheque; }
    void setIdCheque(const string &_idCheque) { idcheque = _idCheque; }

    string getProprietaire() const { return proprietaire; }
    void setProprietaire(const string &_proprietaire) { proprietaire = _proprietaire; }

    Date getDateEncaissement() const { return dateEncaissement; }
    void setDateEncaissement(const Date &_dateEncaissement) { dateEncaissement = _dateEncaissement; }
    string getType() const override
    {
        return "Cheque"; // nous avons besoin de cela pour l'affichage de la facture sur paypal et carte aussi
    }
};

// Classe Paypal
class Paypal : public Paiement
{
private:
    string emailCompte;

public:
    Paypal(int _idPaiement = 0, Date _date = Date(), Utilisateur *utilisateur = nullptr, Facture *_facture = nullptr, const string &_emailCompte = "")
        : Paiement(idPaiement, date, utilisateur, facture)
    {
        emailCompte = _emailCompte;
    }
    string getEmailCompte() const { return emailCompte; }
    void setEmailCompte(const string &_emailCompte) { emailCompte = _emailCompte; }
    string getType() const override
    {
        return "paypal";
    }
};

// clads Cartes
class Cartes : public Paiement
{
private:
    string numeroCarte;
    string nomProprietaire;
    int CSV;
    Date dateExpiration;

public:
    Cartes(int _idPaiement, Date _date, Utilisateur *_utilisateur, Facture *_facture, string &_numeroCarte, string &_nomProprietaire, int _CSV, const Date &_dateExpiration)
        : Paiement(idPaiement, date, utilisateur, facture)
    {
        numeroCarte = _numeroCarte;
        nomProprietaire = _nomProprietaire;
        CSV = _CSV;
        dateExpiration = _dateExpiration;
    }
    string getNumeroCarte() const { return numeroCarte; }
    void setNumeroCarte(const string &_numeroCarte) { numeroCarte = _numeroCarte; }

    string getNomProprietaire() const { return nomProprietaire; }
    void setNomProprietaire(const string &_nomProprietaire) { nomProprietaire = _nomProprietaire; }

    int getCSV() const { return CSV; }
    void setCSV(int _CSV) { CSV = _CSV; }

    Date getDateExpiration() const { return dateExpiration; }
    void setDateExpiration(const Date &_dateExpiration) { dateExpiration = _dateExpiration; }
    string getType() const override
    {
        return "cartes";
    }

    ~Cartes(){};
};
// Classe Service
class Service
{
private:
    string referenceService;
    Date date;
    double prixHT;
    string typeService;
    Facture *factureAssociee;

public:
    Service(string &_referenceService, Date &_date, double _prixHT, string &_typeService, Facture *_FactureAssociee)
    {
        referenceService = _referenceService;
        date = _date;
        prixHT = _prixHT;
        typeService = _typeService;
        factureAssociee = _FactureAssociee;
    }

    double getPrixHT() const { return prixHT; }
    Date getDate() const { return date; }
    string getReferenceService() const { return referenceService; }
    string getTypeService() const { return typeService; }
    void setReferenceService(const string &newReferenceService)
    {
        referenceService = newReferenceService;
    }

    void setDate(const Date &newDate)
    {
        date = newDate;
    }

    void setPrixHT(double newPrixHT)
    {
        prixHT = newPrixHT;
    }

    void setTypeService(const string &newTypeService)
    {
        typeService = newTypeService;
    }
};

// Classe Facture
class Facture
{
private:
    int numeroFacture;
    Date date;
    double total;
    map<int, Paiement *> paiements; // Utilisation d'un map pour associer les paiements à leurs IDs
    vector<Service *> services;

public:
    Facture(int _numeroFacture, Date &_date, double _total)
    {
        numeroFacture = _numeroFacture;
        date = _date;
        total = _total;
    }
    void ajouterService(Service *service)
    {
        services.push_back(service);
    }
    int getNumeroFacture() const
    {
        return numeroFacture;
    }
    vector<Service *> &getServices()
    {
        return services;
    }

    Date getDate() const
    {
        return date;
    }

    double getTotal() const
    {
        return total;
    }
    void setTotal(double value)
    {
        total = value;
    }
    void imprimerFacture()
    {
        cout << "Numéro facture: " << numeroFacture << " - Date facture: " << date.jour << "/" << date.mois << "/" << date.annee << endl;
        cout << "- Identifiant fournisseur: " << endl;
        cout << "- Nom utilisateur: " << Utilisateur::affichernom << endl;
        cout << "- Type de paiement: " << Paiement::getType << endl;
        cout << "Liste des services :" << endl;
        cout << "Référence service\tDate\tType\tPrix" << endl;
        for (const auto &service : services)
        {
            cout << service->getReferenceService() << " \t " << service->getDate().jour << "/" << service->getDate().mois << "/" << service->getDate().annee << " \t " << service->getTypeService() << " \t " << service->getPrixHT() << endl;
        }
        cout << "- Total à payer: " << total << endl;
    }

    ~Facture(){};
};

void remplirUtilisateurs(set<Utilisateur> &utilisateurs)
{
    cout << "choisir le 3eme choix ";
}

void afficherNombrePaiements(const set<Utilisateur> &utilisateurs)
{
    for (const auto &utilisateur : utilisateurs)
    {
        cout << utilisateur.nombrePaiements() << endl;
    }
}

void ajouterUtilisateur(set<Utilisateur> &utilisateurs)
{
    int id;
    string email, nom, adresse;

    cout << "Saisir les détails :" << endl;
    cout << "ID ";
    cin >> id;
    cin.ignore(); // dans le test de systeme J'avais une boucle infinie
    cout << "Email : ";
    cin >> email;
    cout << "Nom : ";
    cin >> nom;
    cout << "Adresse : ";
    cin >> adresse;

    Utilisateur nouvelUtilisateur(id, email, nom, adresse);
    utilisateurs.insert(nouvelUtilisateur);
}

void supprimerUtilisateur(set<Utilisateur> &utilisateurs)
{
    int id;
    cout << "Saisir l'ID  : ";
    cin >> id;

    // recherche de lutilisateur
    auto it = utilisateurs.begin();
    while (it != utilisateurs.end())
    {
        if (it->getId() == id)
        {
            utilisateurs.erase(it); // supprimer lutilisateur
            cout << "succès." << endl;
            return;
        }
        ++it; // incrementation
    }
}

void remplirPaiements(list<Paiement *> &paiements)
{
    cout << "choix 2";
}

void ajouterPaiement(list<Paiement *> &paiements)
{
    int choixTypePaiement;
    do
    {
        cout << "Menu ajouter paiement :" << endl;
        cout << "1.Ajouter un paiement par chèque" << endl;
        cout << "2. Ajouter un paiement par Paypal" << endl;
        cout << "3.Ajouter un paiement par carte" << endl;
        cout << "4.Retour au menu principal" << endl;
        cout << "Entrez votre choix ";
        cin >> choixTypePaiement;

        switch (choixTypePaiement)
        {
        case 1:
        {
            // Ajouter un paiement par chèque
            int idPaiement;
            Date date;
            string idCheque, proprietaire;
            Date dateEncaissement;

            cout << "ID  : ";
            cin >> idPaiement;
            cin.ignore();
            cout << "Date  (jour mois annee) : ";
            cin >> date.jour >> date.mois >> date.annee;
            cout << "ID : ";
            cin >> idCheque;
            cout << "Propriétaire : ";
            cin >> proprietaire;
            cout << "Date (jour mois annee) : ";
            cin >> dateEncaissement.jour >> dateEncaissement.mois >> dateEncaissement.annee;

            Paiement *nouveauPaiement = new Cheque(idPaiement, date, nullptr, nullptr, idCheque, proprietaire, dateEncaissement);
            paiements.push_back(nouveauPaiement);
            break;
        }
        case 2:
        {
            // Ajouter un paiement par Paypal
            int idPaiement;
            Date date;
            string emailCompte;

            cout << "ID  : ";
            cin >> idPaiement;
            cin.ignore();
            cout << "Date  (jour mois annee) : ";
            cin >> date.jour >> date.mois >> date.annee;
            cout << "Email  ";
            cin >> emailCompte;

            Paiement *nouveauPaiement = new Paypal(idPaiement, date, nullptr, nullptr, emailCompte);
            paiements.push_back(nouveauPaiement);
            break;
        }
        case 3:
        {
            // Ajouter un paiement par carte
            int idPaiement;
            Date date;
            string numeroCarte, nomProprietaire;
            int CSV;
            Date dateExpiration;

            cout << "ID : ";
            cin >> idPaiement;
            cin.ignore();
            cout << "Date$ (jour mois annee) : ";
            cin >> date.jour >> date.mois >> date.annee;
            cout << "Numéro  : ";
            cin >> numeroCarte;
            cout << "Nom de propriétaire  ";
            cin >> nomProprietaire;
            cout << "CSV : ";
            cin >> CSV;
            cout << "Date d'expiration (mois annee) : ";
            cin >> dateExpiration.mois >> dateExpiration.annee;

            Paiement *nouveauPaiement = new Cartes(idPaiement, date, nullptr, nullptr, numeroCarte, nomProprietaire, CSV, dateExpiration);
            paiements.push_back(nouveauPaiement);
            break;
        }
        case 4:
            cout << "Retour au menu" << endl;
            break;
        default:
            cout << "error" << endl;
        }
    } while (choixTypePaiement != 4);
}

void modifierPaiement(list<Paiement *> &paiements)
{
    int idPaiement;
    cout << "Entrez l'ID ";
    cin >> idPaiement;

    // Recherche du paiement dans la liste
    auto it = paiements.begin();
    while (it != paiements.end())
    {
        if ((*it)->getIdPaiement() == idPaiement)
        {
            // Afficher les détails du paiement
            cout << "ID  : " << (*it)->getIdPaiement() << endl;
            cout << "Date  : " << (*it)->getDate().jour << "/" << (*it)->getDate().mois << "/" << (*it)->getDate().annee << endl;
            cout << "Utilisateur: " << (*it)->getUtilisateur()->getNom() << endl;
            cout << "Type de paiement : " << (*it)->getType() << endl;

            // Afficher d'autres détails spécifiques au type de paiement (chèque, Paypal, carte)
            string typePaiement = (*it)->getType();
            if (typePaiement == "Cheque")
            {
                Cheque *cheque = dynamic_cast<Cheque *>(*it);
                cout << "ID Chèque : " << cheque->getIdCheque() << endl;
                cout << "Propriétaire : " << cheque->getProprietaire() << endl;
                cout << "Date : " << cheque->getDateEncaissement().jour << "/" << cheque->getDateEncaissement().mois << "/" << cheque->getDateEncaissement().annee << endl;
            }
            else if (typePaiement == "paypal")
            {
                Paypal *paypal = dynamic_cast<Paypal *>(*it);
                cout << "Email : " << paypal->getEmailCompte() << endl;
            }
            else if (typePaiement == "cartes")
            {
                Cartes *cartes = dynamic_cast<Cartes *>(*it);
                cout << "Numéro : " << cartes->getNumeroCarte() << endl;
                cout << "Nom de propriétaire  : " << cartes->getNomProprietaire() << endl;
                cout << "Date d'expiration  : " << cartes->getDateExpiration().mois << "/" << cartes->getDateExpiration().annee << endl;
                cout << "CSV : " << cartes->getCSV() << endl;
            }
            cout << "succès." << endl;
            return;
        }
        ++it;
    }
}

void supprimerPaiement(list<Paiement *> &paiements)
{
    int idPaiement;
    cout << "Entrez l'ID  : ";
    cin >> idPaiement;

    // Recherche du paiement sur list
    auto it = paiements.begin();
    while (it != paiements.end())
    {
        if ((*it)->getIdPaiement() == idPaiement)
        {
            delete *it;          // libere la memoire
            paiements.erase(it); // Supprime le pointeur de paiment
            cout << "succès." << endl;
            return;
        }
        ++it;
    }
}
void remplirServices(vector<Service *> &services)
{
    string referenceService, typeService;
    double prixHT;
    int jour, mois, annee;

    cout << "Entrez referenceservice : ";
    cin >> referenceService;
    cin.ignore();
    cout << "Entrez typeservice : ";
    cin >> typeService;
    cout << "Entrez la date service (jour mois annee) : ";
    cin >> jour >> mois >> annee;
    Date date = {jour, mois, annee};
    cout << "Entrez le prixHT : ";
    cin >> prixHT;

    Service *nouveauService = new Service(referenceService, date, prixHT, typeService, nullptr);
    services.push_back(nouveauService);
}
void ajouterService(vector<Service *> &services)
{
    string referenceService, typeService;
    double prixHT;
    Date date;

    cout << "Entre la referenceservice : ";
    cin >> referenceService;
    cin.ignore(); // pour la boucle
    cout << "Entre typeservice : ";
    cin >> typeService;
    cout << "Entrr la date service (jour mois annee) : ";
    cin >> date.jour >> date.mois >> date.annee;
    cout << "Entre le prixHT : ";
    cin >> prixHT;

    Service *nouveauService = new Service(referenceService, date, prixHT, typeService, nullptr);
    services.push_back(nouveauService);
}

void modifierService(vector<Service *> &services)
{
    string referenceService;
    cout << "Entre la referenceservice à modifier : ";
    cin >> referenceService;

    // Recherche du service dans la liste
    for (auto service : services)
    {
        if (service->getReferenceService() == referenceService)
        {
            // Affichage des détails actuels du service
            cout << "Détails actuels du service :" << endl;
            cout << "Référence : " << service->getReferenceService() << endl;
            cout << "Type : " << service->getTypeService() << endl;
            cout << "Date : " << service->getDate().jour << "/" << service->getDate().mois << "/" << service->getDate().annee << endl;
            cout << "Prix HT : " << service->getPrixHT() << endl;

            // Saisie des nouveaux détails
            double newPrixHT;
            string newTypeService;
            string newReference;
            Date newDate;
            cout << "Entre new prixHT service : ";
            cin >> newPrixHT;
            cin.ignore();
            cout << "Entre new referenceservice : ";
            cin >> newReference;
            service->setReferenceService(newReference);
            cout << "Entre new date du service (jour mois annee) : ";
            cin >> newDate.jour >> newDate.mois >> newDate.annee;
            service->setDate(newDate);
            service->setPrixHT(newPrixHT);
            cout << "Entre new type de service : ";
            cin >> newTypeService;
            service->setTypeService(newTypeService);
            cout << "succès" << endl;
            return;
        }
    }
}

void supprimerService(vector<Service *> &services)
{
    string referenceService;
    cout << "Entre referenceservice a supprimer ";
    cin >> referenceService;

    // recherche du service sur la list
    for (auto it = services.begin(); it != services.end(); ++it)
    {
        if ((*it)->getReferenceService() == referenceService)
        {
            delete *it;         // librer la memoire
            services.erase(it); // supprime service dans la list
            cout << "succès." << endl;
            return;
        }
    }
}
void afficherServicesPrixSup1000(const vector<Service *> &services)
{
    cout << "Services>1000 dh :" << endl;
    cout << "Reference\tDate\t\tType\tPrixHT" << endl;

    for (const auto &service : services)
    {
        if (service->getPrixHT() > 1000)
        {
            cout << service->getReferenceService() << "\t\t"
                 << service->getDate().jour << "/" << service->getDate().mois << "/" << service->getDate().annee << "\t"
                 << service->getTypeService() << "\t"
                 << service->getPrixHT() << endl;
        }
    }
}

void afficherServicesMoins12Mois(const vector<Service *> &services)
{
    cout << "le service va etre apres le mise a jour(jsp comment faire :( )";
}

void remplirFactures(map<int, Facture *> &factures)
{
    int numFacture;
    cout << "Combien de factures tu veux ajouter ? ";
    int nombreFactures;
    cin >> nombreFactures;

    for (int i = 0; i < nombreFactures; ++i)
    {
        cout << "Facture " << i + 1 << ":" << endl;
        cout << "Numéro de facture:";
        cin >> numFacture;

        // verification d'existance
        if (factures.find(numFacture) != factures.end())
        {
            cout << "existe deja ,une autre?" << endl;
            --i;
            continue;
        }

        Date dateFacture;
        double totalFacture;

        // Create new facture
        Facture *nouvelleFacture = new Facture(numFacture, dateFacture, totalFacture);
        factures[numFacture] = nouvelleFacture; // ajouter la facture a la map
    }
}

void ajouterServiceFacture(map<int, Facture *> &factures)
{
    int numFacture;
    cout << "Numero de facture pour ajouter un service : ";
    cin >> numFacture;

    // verifier si la facture exist
    auto it = factures.find(numFacture);
    if (it == factures.end())
    {
        cout << "La facture avec le numero " << numFacture << " n existe pas" << endl;
        return;
    }

    // Demander les détails du service à ajouter
    string refService;
    Date dateService;
    double prixHT;
    string typeService;

    cout << "referenceservice: ";
    cin >> refService;
    cin.ignore();
    cout << "Date du service (jour mois année) : ";
    cin >> dateService.jour >> dateService.mois >> dateService.annee;
    cout << "TypeService : ";
    cin >> typeService;
    cout << "prixHT du service  ";
    cin >> prixHT;

    // Créer new Service
    Service *nouveauService = new Service(refService, dateService, prixHT, typeService, nullptr);

    // Ajouter le service à la facture
    it->second->ajouterService(nouveauService);
    cout << "Service ajouté à la facture numéro " << numFacture << "." << endl;
}

void appliquerTVA(map<int, Facture *> &factures)
{
    const double tauxTVA = 0.1; // 10%=0.1

    for (auto &facture : factures)
    {
        for (auto &service : facture.second->getServices())
        {
            double montantTVA = service->getPrixHT() * tauxTVA;
            service->setPrixHT(service->getPrixHT() + montantTVA);
        }
    }

    cout << "succes." << endl;
}

void appliquerReduction(map<int, Facture *> &factures)
{
    const double tauxReduction = 0.10; // Taux de rduction de 10%
    const double seuilmin = 15500.0;   // Seuil minimal

    for (auto &facture : factures)
    {
        if (facture.second->getTotal() > seuilmin)
        {
            double montantReduction = facture.second->getTotal() * tauxReduction;
            facture.second->setTotal(facture.second->getTotal() - montantReduction); // modifier le prix par le setter
        }
    }

    cout << "reduction bien applique" << endl;
}

void afficherFactures(map<int, Facture *> &factures)
{
    for (auto const &facture : factures)
    {
        facture.second->imprimerFacture();
    }
}

int main()
{
    set<Utilisateur> utilisateurs;
    list<Paiement *> paiements;
    vector<Service *> services;
    map<int, Facture *> factures;

    int choix;
    do
    {
        cout << "Menu :" << endl;
        cout << "1.Gestion Utilisateur" << endl;
        cout << "2. Gestion Paiement" << endl;
        cout << "3.Gestion Service" << endl;
        cout << "4.Gestion Factures" << endl;
        cout << "5. Quitter" << endl;
        cout << "Entrez votre choix ";
        cin >> choix;

        switch (choix)
        {
        case 1:
        {
            //  **Fonctionnalité 1 : gestion Utilisateur **
            int choixUtilisateur;
            do
            {
                cout << "Menu Gestion Utilisateur :" << endl;
                cout << "1. Remplir la liste des utilisateurs" << endl;
                cout << "2. Afficher le nombre de paiements de chaque utilisateur" << endl;
                cout << "3. Ajouter un utilisateur" << endl;
                cout << "4. Supprimer un utilisateur" << endl;
                cout << "5. Retour au menu principal" << endl;
                cout << "Entrez votre choix : ";
                cin >> choixUtilisateur;

                switch (choixUtilisateur)
                {
                case 1:
                    remplirUtilisateurs(utilisateurs);
                    break;
                case 2:
                    afficherNombrePaiements(utilisateurs);
                    break;
                case 3:
                    ajouterUtilisateur(utilisateurs);
                    break;
                case 4:
                    supprimerUtilisateur(utilisateurs);
                    break;
                case 5:
                    cout << "Retour au menu principal." << endl;
                    break;
                default:
                    cout << "entre 1 et 5." << endl;
                }
            } while (choixUtilisateur != 5);
        }
        break;
        case 2:
        {
            // *Fonctionnalité 2 : gestion Paiement **
            int choixPaiement;
            do
            {
                cout << "Menu Gestion Paiement :" << endl;
                cout << "1. Remplir la liste des paiements" << endl;
                cout << "2. Ajouter un paiement" << endl;
                cout << "3. Modifier un paiement" << endl;
                cout << "4. Supprimer un paiement" << endl;
                cout << "5. Retour au menu principal" << endl;
                cout << "Entrez votre choix : ";
                cin >> choixPaiement;

                switch (choixPaiement)
                {
                case 1:
                    remplirPaiements(paiements);
                    break;
                case 2:
                    ajouterPaiement(paiements);
                    break;
                case 3:
                    modifierPaiement(paiements);
                    break;
                case 4:
                    supprimerPaiement(paiements);
                    break;
                case 5:
                    cout << "Retour au menu principal." << endl;
                    break;
                default:
                    cout << "entre 1 et 5." << endl;
                }
            } while (choixPaiement != 5);
        }
        break;
        case 3:
        {
            // **Fonctionnalité 3 : gestion Service **
            int choixService;
            do
            {
                cout << "Menu Gestion Service :" << endl;
                cout << "1. Remplir la liste des services" << endl;
                cout << "2. Ajouter un service" << endl;
                cout << "3. Modifier un service" << endl;
                cout << "4. Supprimer un service" << endl;
                cout << "5. Afficher les services dont le prix depasse 1000dh" << endl;
                cout << "6. Afficher les services effectués dans les 12 derniers mois"
                     << "(service unavailable)" << endl;
                cout << "7. Retour au menu principal" << endl;
                cout << "Entrez votre choix : ";
                cin >> choixService;

                switch (choixService)
                {
                case 1:
                    remplirServices(services);
                    break;
                case 2:
                    ajouterService(services);
                    break;
                case 3:
                    modifierService(services);
                    break;
                case 4:
                    supprimerService(services);
                    break;
                case 5:
                    afficherServicesPrixSup1000(services);
                    break;
                case 6:
                    afficherServicesMoins12Mois(services);
                    break;
                case 7:
                    cout << "Retour au menu principal." << endl;
                    break;
                default:
                    cout << "entre 1 et 7." << endl;
                }
            } while (choixService != 7);
        }
        break;
        case 4:
        {
            // Fonctionnalité 4 : Gestion Factures
            int choixFacture;
            do
            {
                cout << "Menu Gestion Factures :" << endl;
                cout << "1. Remplir la liste des factures" << endl;
                cout << "2. Ajouter/modifier/supprimer un service pour une facture donnée" << endl;
                cout << "3. Appliquer la TVA sur les prix des services" << endl;
                cout << "4. Appliquer une réduction sur les factures dont le total est supérieur à 15500dh" << endl;
                cout << "5. Afficher les factures" << endl;
                cout << "6. Retour au menu principal" << endl;
                cout << "Entrez votre choix : ";
                cin >> choixFacture;

                switch (choixFacture)
                {
                case 1:
                    remplirFactures(factures);
                    break;
                case 2:
                    ajouterServiceFacture(factures);
                    break;
                case 3:
                    appliquerTVA(factures);
                    break;
                case 4:
                    appliquerReduction(factures);
                    break;
                case 5:
                    afficherFactures(factures);
                    break;
                case 6:
                    cout << "Retour au menu " << endl;
                    break;
                default:
                    cout << "invalide" << endl;
                }
            } while (choixFacture != 6);
        }
        break;
        case 5:
            cout << "bye byye " << endl;
            break;
        default:
            cout << "invalide" << endl;
        }
    } while (choix != 5);

    return 0;
}