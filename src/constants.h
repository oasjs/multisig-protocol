#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <libcryptosec/MessageDigest.h>

// Default key size for the application.
const int KEY_SIZE = 2048;

// Default hash algorithm for the application.
const MessageDigest::Algorithm HASH_ALGORITHM = MessageDigest::SHA256;

// Default path for the folder containing the PDF files, starting from the root
// of the project.
const string PDF_PATH = "pdf/";

// Default path for the folder containing the temporary files, starting from the
// root of the project.
const string TMP_PATH = "tmp/";

// Default path for the folder containing the certificates, starting from the
// root of the project.
const string CERT_AUTH_PATH = "data/certauth/";

// Default path for the folder containing the users' certificates, starting from
// the root of the project.
const string USERS_PATH = "data/users/";

#endif // !CONSTANTS_H