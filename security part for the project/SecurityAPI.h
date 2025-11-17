#ifndef SECURITYAPI_H
#define SECURITYAPI_H

#include <string>
#include <unordered_map>

class SecurityAPI {
public:
    SecurityAPI(const std::string& filename = "users.txt");

    bool registerUser(const std::string& username, const std::string& password);
    bool loginUser(const std::string& username, const std::string& password, std::string &outToken);
    bool validateSession(const std::string& token);
    bool resetPassword(const std::string& username, const std::string& newPassword);

private:
    std::string dbFile;
    std::unordered_map<std::string, std::string> sessions;

    std::string generateRandomString(int length);
    std::string hashPassword(const std::string& pw, const std::string& salt);
    void saveUser(const std::string& username, const std::string& salt,
                  const std::string& hash);
    bool loadUser(const std::string& username,
                  std::string &saltOut, std::string &hashOut);
};

#endif
