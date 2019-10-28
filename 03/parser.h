#include <functional>
#include <vector>


using baseCallback = std::function<void()>;
using stringTokenCallback = std::function<void(const std::string &token)>;
using intTokenCallback = std::function<void(const int &token)>;
using isStringToken = std::function<bool(const std::string &token)>;
using isIntToken = std::function<bool(const int &token)>;


class Parser {
public:
    void addOnStartCallback(const baseCallback &handler);
    void addOnEndCallback(const baseCallback &handler);
    void addOnTokenCallback(const isStringToken &is_token, const stringTokenCallback &handler);
    void addOnTokenCallback(const isIntToken &is_token, const intTokenCallback &handler);
    std::vector<std::string> parse(const std::string &str);

private:
    void triggerTokenCallbacks(const bool is_number, const std::string &token);
    std::vector<baseCallback> on_start_callbacks;
    std::vector<baseCallback> on_end_callbacks;
    std::vector<std::pair<isStringToken, stringTokenCallback>> on_string_token_callbacks;
    std::vector<std::pair<isIntToken, intTokenCallback>> on_int_token_callbacks;
};
