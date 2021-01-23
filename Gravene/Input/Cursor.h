#ifndef CURSOR_H
#define CURSOR_H

enum class CursorState {
    None,
    Confined,
    Locked
};

class Cursor {
    private:
        CursorState m_CursorState;
        bool m_IsVisible;
    public:
        const bool GetVisible() const { return m_IsVisible; }
        void SetVisible(const bool visible) { m_IsVisible = visible; }

        const CursorState& GetCursorState() const { return m_CursorState; };
        void SetCursorState(const CursorState& cursorState);
};

#endif