class Vector2 {
public:
    float x;
    float y;

    Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 operator/(float scalar) const {
        // Assuming scalar is not zero for simplicity
        return Vector2(x / scalar, y / scalar);
    }

    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2& operator/=(float scalar) {
        // Assuming scalar is not zero for simplicity
        x /= scalar;
        y /= scalar;
        return *this;
    }

    bool operator==(const Vector2& other) const {
        return (x == other.x) && (y == other.y);
    }

    bool operator!=(const Vector2& other) const {
        return !(*this == other);
    }

};