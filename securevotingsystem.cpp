#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include<chrono>
#include<thread>
using namespace std;
void starline() {
    for (int i = 0; i < 120; i++) {
        cout << "*";
    }
    cout << endl;
}
string encrypt_caesar(string& text, int shift) {
    string encrypted = text;
    for (char& ch : encrypted) {
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            ch = (ch - base + shift) % 26 + base;
        }
    }
    return encrypted;
}


string decrypt_caesar(string& encrypted_text, int shift) {
    string decrypted = encrypted_text;
    for (char& ch : decrypted) {
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            ch = (ch - base - shift + 26) % 26 + base;
        }
    }
    return decrypted;
}

// Voter class
class voter {
public:
    string name;
    string cnic;


    void get_data() {
        cin.ignore();
        cout << "ENTER YOUR NAME :- ";
        getline(cin, name);
    cnic_again:
        cout << "ENTER CNIC(WITHOUT DASHES) --> ";
        getline(cin, cnic);
        if (cnic.length() != 13) {
            cout << "INVALID CNIC! " << endl;
            goto cnic_again;
        }
    }

    void display_voter() {
        cout << name << " having CNIC " << cnic << endl;
    }

    string returncnic()
    {
        return cnic;
    }
};

// Admin class
class admin {
public:
    string political_party;

    void display_candidate() {
        cout << "PTI" << endl;
        cout << "PMLN" << endl;
        cout << "PPP" << endl;
    }


    void save_vote_count(int pti, int pmln, int ppp) {
        ofstream file("vote_count.txt");
        if (file) {
            file << "PTI Votes: " << pti << endl;
            file << "PMLN Votes: " << pmln << endl;
            file << "PPP Votes: " << ppp << endl;
        }
        else {
            cout << "Error saving vote count." << endl;
        }
        file.close();
    }


    void load_vote_count(int& pti, int& pmln, int& ppp) {
        ifstream file("vote_count.txt");
        if (file) {
            string line;
            while (getline(file, line)) {
                if (line.find("PTI") != string::npos) {
                    pti = stoi(line.substr(line.find(":") + 2));
                }
                else if (line.find("PMLN") != string::npos) {
                    pmln = stoi(line.substr(line.find(":") + 2));
                }
                else if (line.find("PPP") != string::npos) {
                    ppp = stoi(line.substr(line.find(":") + 2));
                }
            }
        }
        else {
            pti = 0;
            pmln = 0;
            ppp = 0;
        }
        file.close();
    }
};
void instruction()
{
    starline();
    cout << "\t\t\t\t\t\tPROJECT MADE BY " << endl;
    starline();
    cout << "\n\t\t\t\tSTUDENT ID\t\t\t\tSTUDENT NAME\n" << endl;
    cout << "\t\t\t\tXXXX\t\t\t\tXXXXX\n" << endl;
    cout << "\t\t\t\tXXXX\t\t\t\tXXXXX\n" << endl;
    cout << "\t\t\t\tXXXX\t\t\t\tXXXXX\n" << endl;
    cout << "\t\t\t\tXXXX\t\t\t\tXXXXX\n" << endl;
    starline();
    system("pause");
    system("cls");
}
void features()
{
    starline();
    cout << "\t\t\t\t\tElection Commission Voting System FEATURES" << endl;
    starline();
    cout << "\n1. Admin Login: Use username and password to access the admin panel." << endl;
    cout << "   - Admin Username: admin" << endl;
    cout << "   - Admin Password: admin123" << endl;
    cout << "2. Display Voter Records: Admins can view the list of voters and their votes (with encrypted names)." << endl;
    cout << "3. View Results: Admins can see the total votes for each party and the current winner." << endl;
    cout << "4. Display Political Parties: Admins can display the list of participating political parties." << endl;
    cout << "5. Public Voting: Allows voters to cast their votes by entering their name, CNIC, and choosing a party." << endl;
    cout << "6. Secure Voting: Prevents duplicate voting using CNIC validation and encrypts voter data for privacy." << endl;
    cout << "7. Data Encryption: Voter names are encrypted using a Caesar cipher for enhanced privacy and security." << endl;
    cout << "8. Save and Load Votes: Automatically saves votes to a file and retrieves them for consistency across sessions." << endl;
    cout << "9. Prevent Multiple Admin Login Attempts: Limits incorrect login attempts to 3 for security." << endl;
    cout << "10. Real-Time Vote Counting: Updates and displays the vote count dynamically as votes are cast." << endl;
    cout << "11. Exit: Allows users to exit the system gracefully.\n" << endl;
    starline();
    cout << "Note: Follow the on-screen instructions for a smooth experience." << endl;
    starline();
    system("pause");
    system("cls");
}
bool instruction_display = 0;
// Main function
int main() {
    if (!instruction_display)
    {
        instruction();
        features();
        instruction_display = 1;
    }
    voter v1;
    admin a1;

    string user_name, password;
    int pti_count = 0, pmln_count = 0, ppp_count = 0;

    a1.load_vote_count(pti_count, pmln_count, ppp_count);


    ifstream checkFile("vote_count.txt");
    if (!checkFile) {
        ofstream initFile("vote_count.txt");
        initFile << "PTI Votes: 0\nPMLN Votes: 0\nPPP Votes: 0\n";
        initFile.close();
    }
    checkFile.close();
again:
    starline();
    cout << "\t\t\t\t\t\t WELCOME TO Election Commission " << endl;
    starline();
    cout << "Press 1 for Admin Panel" << endl;
    cout << "Press 2 for Voting" << endl;
    cout << "Press 3 to see Features" << endl;
    cout << "Press 0 to Exit" << endl;
    cout << "Enter your choice :- ";

    int choice;
    cin >> choice;

    system("cls");


    string winner = "No Winner Yet";

    switch (choice) {
    case 0:
        starline();
        cout << "\t\t\t\t\t\t Thanks for visiting!" << endl;
        starline();
        exit(0);

    case 1: {
        pass_again:
        starline();
        cout << "\t\t\t\t\t\t ADMIN LOGIN PAGE" << endl;
        starline();
        cout << "Enter Username :- ";
        cin >> user_name;
        cout << "Enter Password :- ";
        cin>>password;

        if ((user_name == "Admin" || user_name == "admin") && password == "admin123") {
            system("cls");
            starline();
            cout << "\t\t\t\t\t\tLOGIN SUCESSFULLY" << endl;
            starline();
            this_thread::sleep_for(chrono::seconds(1));
            system("cls");
        admin_again:
            starline();
            cout << "\t\t\t\t\t\t WELCOME TO Admin Panel" << endl;
            starline();
            cout << "Press 1 to Display Voter Records" << endl;
            cout << "Press 2 to View Results" << endl;
            cout << "Press 3 to Display Political Parties" << endl;
            cout << "Press 0 to Exit" << endl;
            cout << "Enter your choice :- ";

            int choice4;
            cin >> choice4;

            system("cls");

            switch (choice4) {
            case 0:
                starline();
                cout << "\t\t\t\t\t\t LOGGING OUT" << endl;
                starline();
                this_thread::sleep_for(chrono::seconds(1));
                system("cls");
                goto again;
                break;

            case 1: {
                starline();
                cout << "\t\t\t\t\t\t VOTERS RECORD" << endl;
                starline();
                ifstream read("voters1.txt");
                if (!read) {
                    cout << "No voter records available!" << endl;
                    system("pause");
                    system("cls");
                    goto admin_again;
                    break;
                }
                string line;
                while (getline(read, line)) {
                    size_t delimiter_pos = line.find(", Voted for: ");
                    if (delimiter_pos != string::npos) {
                        string encrypted_name = line.substr(17, delimiter_pos - 17);
                        string decrypted_name = decrypt_caesar(encrypted_name, 5);
                        string party_name = line.substr(delimiter_pos + 13);
                        cout << " Voter: " << decrypted_name
                            << ", Voted for: " << party_name << endl;
                    }
                }
                read.close();
                system("pause");
                system("cls");
                goto admin_again;
                break;
            }

            case 2:
                starline();
                cout << "\t\t\t\t\t\t RESULT PANEL" << endl;
                starline();
                cout << "Voting Results:" << endl;
                // Display current votes
                cout << "PTI Votes: " << pti_count << endl;
                cout << "PMLN Votes: " << pmln_count << endl;
                cout << "PPP Votes: " << ppp_count << endl;

                if (pti_count > pmln_count && pti_count > ppp_count) {
                    winner = "PTI";
                }
                else if (pmln_count > pti_count && pmln_count > ppp_count) {
                    winner = "PMLN";
                }
                else if (ppp_count > pti_count && ppp_count > pmln_count) {
                    winner = "PPP";
                }
                else {
                    winner = "It's a tie!";
                }



                a1.save_vote_count(pti_count, pmln_count, ppp_count);

                char exitChoice;
                cout << "Do you want to Exit polling (Y/N)? ";
                cin >> exitChoice;
                if (exitChoice == 'Y' || exitChoice == 'y') {

                    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
                    cout << "Winner:-\t\t\t\t" << winner << " leads with people's trust!" << endl;
                    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

                }
                else {
                    system("pause");
                    system("cls");
                    goto admin_again;
                }
                system("pause");
                system("cls");
                goto admin_again;
                break;

            case 3:
                starline();
                cout << "\t\t\t\t\t\t ELECTED PARTIES FOR ELECTIONS" << endl;
                starline();
                cout << endl;
                a1.display_candidate();
                system("pause");
                system("cls");
                goto admin_again;
                break;

            default:
                starline();
                cout << "\t\t\t\t\t\t INVALID OPERATION" << endl;
                starline();
                cout << "Please choose from the given options!" << endl;
                system("pause");
                system("cls");
                goto admin_again;
            }
        }
        else {
            cout << "\t\t\t\t\t\t Incorrect Credentials!" << endl;
            static int pass_count = 0;
            pass_count++;
            cout << "You have done " << pass_count << " wrong attemps out of 3." << endl;
            system("pause");
            system("cls");
            if (pass_count == 3) {
                starline();
                cout << "\t\t\t\t\t\t ATTEMPT BLOCKED" << endl;
                starline();
                cout << "Password attempts exceeded!" << endl;
                system("pause");
                system("cls");
                pass_count = 0;
                goto again;
            }
            else {
                goto pass_again;
            }
        }
    }
    case 2: {
        voting:
        starline();
        cout << "\t\t\t\t\t\t WELCOME TO Public Panel" << endl;
        starline();
        cout << "Press 1 to Cast Vote" << endl;
        cout << "Press 0 to Exit" << endl;
        cout << "Enter your choice :- ";

        int choice1;
        cin >> choice1;
        system("cls");
        switch (choice1) {
        case 1: {
            starline();
            cout << "\t\t\t\t\t\t MOVINT TO Voting Panel" << endl;
            starline();
            this_thread::sleep_for(chrono::seconds(1));
            system("cls");
            starline();
            cout << "\t\t\t\t\t\t WELCOME TO Voting Panel" << endl;
            starline();
            v1.get_data();
            system("cls");
            starline();
            cout << "\t\t\t\t\t\t SELECTION PANEL" << endl;
            starline();
            bool alreadyVoted = false;
            ifstream cnicFile("voters_registered1.txt");
            string cnic_line;
            while (getline(cnicFile, cnic_line)) {
                if (cnic_line == v1.cnic) {
                    alreadyVoted = true;
                    break;
                }
            }
            cnicFile.close();

            if (alreadyVoted) {
                cout << "Sorry, you have already voted!" << endl;
                break;
            }

            string encrypted_name = encrypt_caesar(v1.name, 5);
            a1.display_candidate();
            cout << "Enter the Name of the Political Party You Want to Vote For: ";
            string party_name;
            getline(cin, party_name);

            if (party_name == "PTI") {
                pti_count++;
            }
            else if (party_name == "PMLN") {
                pmln_count++;
            }
            else if (party_name == "PPP") {
                ppp_count++;
            }
            else {
                cout << "Invalid party name!" << endl;
                break;
            }

            cout << "\n---------------------------------------------------------------------------------------------------" << endl;
            cout << "Dear " << v1.name << ", we highly welcome and appreciate your participation in the voting process!" << endl;
            cout << "---------------------------------------------------------------------------------------------------" << endl;


            a1.save_vote_count(pti_count, pmln_count, ppp_count);

            ofstream file1("voters1.txt", ios::app);
            file1 << "Encrypted Voter: " << encrypted_name << " , " << v1.returncnic() << ", Voted for: " << party_name << endl;
            file1.close();

            ofstream regFile("voters_registered1.txt", ios::app);
            regFile << v1.cnic << endl;
            regFile.close();
            break;
        }

        case 0:
        {
            system("cls");
            starline();
            cout << "\t\t\t\t\t\t MOVING TO Home Page" << endl;
            starline();
            this_thread::sleep_for(chrono::seconds(1));
            system("cls");
            goto again;
            break;
        }
        default:
            starline();
            cout << "\t\t\t\t\t\t INVALID OPERATION" << endl;
            starline();
            cout << "\n\n\t\t\t\t\t Please choose from the given options!" << endl;
            system("pause");
            system("cls");
            goto voting;
        }
        break;
    }
    case 3:
    {
        features();
        goto again;
    }
    break;
    default:
        starline();
        cout << "\t\t\t\t\t\t INVALID OPERATION" << endl;
        starline();
        cout << "\n\n\t\t\t\t\tPlease choose from the given options!" << endl;
    }
    system("pause");
    system("cls");
    goto again;
}