//
// Created by be on 3/27/26.
//

#ifndef TELP_T1_BALL_H
#define TELP_T1_BALL_H

class Ball {
    float m_pos_x{}, m_pos_y{}, m_vel_x{}, m_vel_y{};

public:
    static constexpr float radius{6.0};

    explicit Ball(const float x, const float y, const float vel_x, const float vel_y) : m_pos_x{x}, m_pos_y{y},
        m_vel_x{vel_x},
        m_vel_y{vel_y} {
    }

    ~Ball() = default;

    [[nodiscard]] float get_pos_x() const {
        return m_pos_x;
    }

    [[nodiscard]] float get_pos_y() const {
        return m_pos_y;
    }
};


#endif //TELP_T1_BALL_H
