#include "Cursor.h"

//#include "Rendering/Window.h"

#include <GLFW/glfw3.h>

void Cursor::SetCursorState(const CursorState& cursorState) 
{ 
    m_CursorState = cursorState; 

    switch (cursorState)
    {
        case CursorState::None:
            //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            break;
        case CursorState::Confined:
            // TODO: CursorState::Confined
            break;
        case CursorState::Locked:
            //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;     
        default:
            break;
    }
}