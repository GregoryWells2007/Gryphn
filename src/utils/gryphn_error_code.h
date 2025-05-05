#include <utils/gryphn_bool.h>
#include <utils/gryphn_access_level.h>
#include <vector>
#include <utils/strings/gryphn_string.h>

enum gnReturnCodeLevel { GN_FAILED = 0, GN_SUCCESS = 1 };

inline gnString lastReturnCode = gnCreateString();

typedef struct gnReturnCode {
ACCESS_LEVEL:
    gnBool success;
    gnString returnCodeMessage = "";
public:
    bool operator==(gnReturnCodeLevel level) { return success; }
    gnReturnCode(gnReturnCodeLevel level, gnString message) : success(level), returnCodeMessage(message) { lastReturnCode = returnCodeMessage; }
    gnReturnCode(gnReturnCodeLevel level) : success(level) { lastReturnCode = returnCodeMessage; }
    gnReturnCode() { lastReturnCode = returnCodeMessage; }
} gnErrorCode;

gnString gnGetErrorString();
static gnReturnCode gnReturnError(gnString errorMessage) { return { GN_FAILED, errorMessage }; }
