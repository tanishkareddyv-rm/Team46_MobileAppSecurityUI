#include "SecurityAPI.h"
#include "sha256.h"
#include <fstream>
#include <random>
#include <sstream>

SecurityAPI::SecurityAPI(const std::string& filename) : dbFile(filename) {}

std::string SecurityAPI::generateRandomString(int length) {
    static const char chars[] =
            "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, sizeof(chars)-2);

    std::string s;
    for (int i = 0; i < length; i++)
        s += chars[dist(gen)];

    return s;
}

std::string SecurityAPI::hashPassword(const std::string& pw, const std::string& salt) {
    return SHA256::hash(pw + salt);
}

void SecurityAPI::saveUser(const std::string& username,
                           const std::string& salt,
                           const std::string& hash) {

    std::ofstream out(dbFile, std::ios::app);
    out << username << ";" << salt << ";" << hash << "\n";
}

bool SecurityAPI::loadUser(const std::string& username,
                           std::string &saltOut, std::string &hashOut) {

    std::ifstream in(dbFile);
    std::string line;

    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string user, salt, hash;

        std::getline(ss, user, ';');
        std::getline(ss, salt, ';');
        std::getline(ss, hash, ';');

        if (user == username) {
            saltOut = salt;
            hashOut = hash;
            return true;
        }
    }
    return false;
}

bool SecurityAPI::registerUser(const std::string& username,
                               const std::string& password) {

    std::string s, h;
    if (loadUser(username, s, h))
        return false; // already exists

    std::string salt = generateRandomString(16);
    std::string hash = hashPassword(password, salt);

    saveUser(username, salt, hash);
    return true;
}

bool SecurityAPI::loginUser(const std::string& username,
                            const std::string& password,
                            std::string &outToken) {

    std::string salt, storedHash;
    if (!loadUser(username, salt, storedHash))
        return false;

    if (hashPassword(password, salt) != storedHash)
        return false;

    outToken = generateRandomString(32);
    sessions[outToken] = username;
    return true;
}

bool SecurityAPI::validateSession(const std::string& token) {
    return sessions.find(token) != sessions.end();
}

bool SecurityAPI::resetPassword(const std::string& username,
                                const std::string& newPassword) {

    std::ifstream in(dbFile);
    std::ofstream out("temp.txt");

    std::string line;
    bool updated = false;

    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string user, salt, hash;

        std::getline(ss, user, ';');
        std::getline(ss, salt, ';');
        std::getline(ss, hash, ';');

        if (user == username) {
            std::string newSalt = generateRandomString(16);
            std::string newHash = hashPassword(newPassword, newSalt);
            out << user << ";" << newSalt << ";" << newHash << "\n";
            updated = true;
        } else {
            out << line << "\n";
        }
    }

    in.close();
    out.close();

    std::remove(dbFile.c_str());
    std::rename("temp.txt", dbFile.c_str());

    return updated;
}
