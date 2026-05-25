#ifndef BEATBOX_61601_PREFERENCES_H
#define BEATBOX_61601_PREFERENCES_H
#include <array>
#include <string>


class Preferences {
public:
    static void save(const std::array<std::string, 4>& paths);
    static std::array<std::string, 4> load();
};

#endif //BEATBOX_61601_PREFERENCES_H
