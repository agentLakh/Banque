#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Fonction pour vérifier si un utilisateur existe dans le fichier et récupérer le solde
bool verifierUtilisateur(const string& fichier, const string& nom, const string& prenom, const string& motDePasse, string& solde) {
    ifstream file(fichier);
    if (!file.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier." << endl;
        return false;
    }

    string ligne;
    string combinaison = nom + "," + prenom + "," + motDePasse;

    while (getline(file, ligne)) {
        stringstream ss(ligne);
        string tempNom, tempPrenom, tempMotDePasse, tempSolde;
        getline(ss, tempNom, ',');
        getline(ss, tempPrenom, ',');
        getline(ss, tempMotDePasse, ',');
        getline(ss, tempSolde, ',');

        if (tempNom == nom && tempPrenom == prenom && tempMotDePasse == motDePasse) {
            solde = tempSolde;  // Récupère le solde
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Fonction pour ajouter un utilisateur dans le fichier avec un solde initial
void ajouterUtilisateur(const string& fichier, const string& nom, const string& prenom, const string& motDePasse) {
    ofstream file(fichier, ios::app);
    if (!file.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier." << endl;
        return;
    }

    file << nom << "," << prenom << "," << motDePasse << ",10000\n";  // Solde de base 10,000 FCFA
    file.close();
}

// Fonction pour gérer le sous-menu après connexion
void afficherSousMenu(const string& solde) {
    int choix;

    while (true) {
        cout << "\n--- MENU APRÈS CONNEXION ---" << endl;
        cout << "1. Voir solde" << endl;
        cout << "2. Faire un depot" << endl;
        cout << "3. Faire un retrait" << endl;
        cout << "4. Retour au menu principal" << endl;
        cout << "Votre choix : ";
        cin >> choix;

        if (choix == 1) {
            cout << "Votre solde actuel est de : " << solde << " FCFA" << endl;
        } else if (choix == 2) {
            cout << "Vous avez choisi de Faire un depot !" << endl;
        } else if (choix == 3) {
            cout << "Vous avez choisi de Faire un retrait !" << endl;
        } else if (choix == 4) {
            cout << "Retour au menu principal..." << endl;
            break;
        } else {
            cout << "Choix invalide. Veuillez réessayer." << endl;
        }
    }
}

int main() {
    string fichier = "utilisateurs.csv"; // Nom du fichier CSV
    string nom, prenom, motDePasse, solde;
    int choix;

    while (true) {
        // Affichage du menu principal
        cout << "\n--- MENU PRINCIPAL ---" << endl;
        cout << "1. S'inscrire" << endl;
        cout << "2. Se connecter" << endl;
        cout << "3. Quitter" << endl;
        cout << "Votre choix : ";
        cin >> choix;

        if (choix == 1) { // Inscription
            cout << "\n--- INSCRIPTION ---" << endl;
            cout << "Entrez votre nom : ";
            cin >> nom;
            cout << "Entrez votre prénom : ";
            cin >> prenom;
            cout << "Entrez votre mot de passe : ";
            cin >> motDePasse;

            ajouterUtilisateur(fichier, nom, prenom, motDePasse);
            cout << "Inscription réussie !" << endl;

        } else if (choix == 2) { // Connexion
            cout << "\n--- CONNEXION ---" << endl;
            cout << "Entrez votre nom : ";
            cin >> nom;
            cout << "Entrez votre prénom : ";
            cin >> prenom;
            cout << "Entrez votre mot de passe : ";
            cin >> motDePasse;

            if (verifierUtilisateur(fichier, nom, prenom, motDePasse, solde)) {
                cout << "Connexion réussie !" << endl;
                afficherSousMenu(solde); // Afficher le sous-menu avec le solde
            } else {
                cout << "Vous n'avez pas de compte. Veuillez vous inscrire." << endl;
            }

        } else if (choix == 3) { // Quitter
            cout << "Au revoir !" << endl;
            break;
        } else {
            cout << "Choix invalide. Veuillez réessayer." << endl;
        }
    }

    return 0;
}
