#ifndef TIME_H
#define TIME_H

class Time {
    private:
        static float m_DeltaTime;
    public:

        static void Update();

        static const float GetDeltaTime() { return m_DeltaTime; }
};

#endif