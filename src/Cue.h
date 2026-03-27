//
// Created by be on 3/27/26.
//

#ifndef TELP_T1_CUE_H
#define TELP_T1_CUE_H


class Cue {
    float m_pos_x{}, m_pos_y{};

public:
    static constexpr float width{10.0}, height{130.0};

    explicit Cue(const float x, const float y) : m_pos_x{x}, m_pos_y{y} {}
    ~Cue() = default;

    [[nodiscard]] float get_pos_x() const {
        return m_pos_x;
    }

    [[nodiscard]] float get_pos_y() const {
        return m_pos_y;
    }
};


#endif //TELP_T1_CUE_H