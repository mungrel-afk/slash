#include <cstdint>
#include <cmath>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

struct vector2f
{
    float x = 0.0f;
    float y = 0.0f;

    // Constructors
    vector2f() = default;
    vector2f(float x_value, float y_value) : x(x_value), y(y_value) {}
    vector2f(const Vector2& raylibVector) : x(raylibVector.x), y(raylibVector.y) {}

    vector2f operator+(const vector2f& other) const { return vector2f(x + other.x, y + other.y); }
    vector2f operator*(const vector2f& other) const { return vector2f(x * other.x, y * other.y); }
    vector2f operator-(const vector2f& other) const { return vector2f(x - other.x, y - other.y); }
    vector2f operator-(const Vector2& other) const { return vector2f(x - other.x, y - other.y); }
    bool operator<(float other) const { return (x + y < other); }

    // Scalar Multiplication
    vector2f operator*(float scalar) const { return vector2f(x * scalar, y * scalar); }
    // Scalar Division
    vector2f operator/(float scalar) const { return vector2f(x / scalar, y / scalar); }
    // Dot Product
    float dot(const vector2f& other) const { return (x * other.x) + (y * other.y); }
    // Magnitude / Length
    float magnitude() const { return sqrt((x * x) + (y * y)); }

    // Normalized
    void normalize()
    {
        float mag = magnitude();
        if (mag > 0)
        {
            x /= mag;
            y /= mag;
        }
    }
    vector2f normalized() const { return vector2f((*this) / magnitude()); }
};
