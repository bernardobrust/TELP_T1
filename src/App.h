//
// Created by be on 3/22/26.
//

#ifndef TELP_T1_APP_H
#define TELP_T1_APP_H


class App {
public:
    App() = default;
    ~App() = default;

    static auto init() -> void;
    static auto run() -> void;
    static auto cleanup() -> void;
};


#endif //TELP_T1_APP_H