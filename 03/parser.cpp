#include "parser.h"

using namespace std;

void Parser::triggerTokenCallbacks(const bool is_number, const string &token) {
    if (is_number) {
        try {
            int number = stoi(token);
            for (auto &pair : on_int_token_callbacks) {
                if (pair.first(number)) {
                    pair.second(number);
                }
            }
        } catch (std::out_of_range &error_msg) {
            throw std::invalid_argument("Value " + token + " is too large for int");
        }
    } else {
        for (auto &pair : on_string_token_callbacks) {
            if (pair.first(token)) {
                pair.second(token);
            }
        }
    }
}

void Parser::addOnStartCallback(const baseCallback &handler) {
    on_start_callbacks.push_back(handler);
}

void Parser::addOnEndCallback(const baseCallback &handler) {
    on_end_callbacks.push_back(handler);
}

void Parser::addOnTokenCallback(const isStringToken &is_token, const stringTokenCallback &handler) {
    pair<isStringToken, stringTokenCallback> callback{is_token, handler};
    on_string_token_callbacks.push_back(callback);
}

void Parser::addOnTokenCallback(const isIntToken &is_token, const intTokenCallback &handler) {
    pair<isIntToken, intTokenCallback> callback{is_token, handler};
    on_int_token_callbacks.emplace_back(callback);
}

vector<string> Parser::parse(const string &str) {
    vector<string> parsed_str;
    string current_str;
    bool is_number = true;

    for (auto &func: on_start_callbacks) {
        func();
    }

    for (const auto ch : str) {
        if (isspace(ch)) {
            if (!current_str.empty()) {
                triggerTokenCallbacks(is_number, current_str);
                parsed_str.emplace_back(current_str);
                current_str = "";
                is_number = true;
            }
        } else {
            if (is_number && !isdigit(ch)) {
                is_number = false;
            }
            current_str += ch;
        }
    }

    if (!current_str.empty()) {
        triggerTokenCallbacks(is_number, current_str);
        parsed_str.emplace_back(current_str);
    }

    for (auto &func : on_end_callbacks) {
        func();
    }
    return parsed_str;
}
