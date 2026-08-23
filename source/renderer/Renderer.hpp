

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer
{

public:
    Renderer() = default;
    ~Renderer() = default;

    void Render(){}
    static void GLDraw()
    {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

private:

};