#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Fonction pour vérifier si un utilisateur existe dans le fichier
bool verifierUtilisateur(const string& fichier, const string& nom, const string& prenom, const string& motDePasse) {
    ifstream file(fichier);
    if (!file.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier." << endl;
        return false;
    }

    string ligne;
    string combinaison = nom + "," + prenom + "," + motDePasse;

    while (getline(file, ligne)) {
        if (ligne == combinaison) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Fonction pour ajouter un utilisateur dans le fichier
void ajouterUtilisateur(const string& fichier, const string& nom, const string& prenom, const string& motDePasse) {
    ofstream file(fichier, ios::app);
    if (!file.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier." << endl;
        return;
    }

    file << nom << "," << prenom << "," << motDePasse << "\n";
    file.close();
}

// Fonction pour gérer le sous-menu après connexion
void afficherSousMenu() {
    int choix;

    while (true) {
        cout << "\n--- MENU APRÈS CONNEXION ---" << endl;
        cout << "1. Option 1 : Voir votre profil" << endl;
        cout << "2. Option 2 : Modifier vos informations" << endl;
        cout << "3. Retour au menu principal" << endl;
        cout << "Votre choix : ";
        cin >> choix;

        if (choix == 1) {
            cout << "Vous avez choisi de voir votre profil !" << endl;
        } else if (choix == 2) {
            cout << "Vous avez choisi de modifier vos informations !" << endl;
        } else if (choix == 3) {
            cout << "Retour au menu principal..." << endl;
            break;
        } else {
            cout << "Choix invalide. Veuillez réessayer." << endl;
        }
    }
}

int main() {
    string fichier = "utilisateurs.csv"; // Nom du fichier CSV
    string nom, prenom, motDePasse;
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

            if (verifierUtilisateur(fichier, nom, prenom, motDePasse)) {
                cout << "Connexion réussie !" << endl;
                afficherSousMenu(); // Afficher le sous-menu après connexion
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
