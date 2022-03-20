#pragma once

#include "components/simple_scene.h"
#include "Shapes/Entities/Entity.h"
#include "Shapes/Primitives/Rectangle.h"

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
        friend class Player;


    public:
        static int score;

        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

    public:
        Tema1();
        ~Tema1();

        void Init() override;
        Player* player;
           
        void insertInEntityMap(std::string key, Entity* e);
        std::vector<Entity*> orderedEntities;
        std::unordered_map<std::string, Entity*> entities;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawScene(glm::mat3 visMatrix);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

        // Sets the logic space and view space
        // logicSpace: { x, y, width, height }
        // viewSpace: { x, y, width, height }
        glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);

        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);
        void renderAllEntities(glm::mat3 visMatrix);
        void updateAllInTime(float deltaTime);
        void translateHUD(float tx, float ty);
        void processPlayerCollisions();
        void processCollisions();

    protected:
        float length;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 modelMatrix, visMatrix;

        Rectangle* rectangle;
        glm::vec3 backgroundColor = glm::vec3(184.0 / 255, 255.0 / 255, 145.0 / 255);
    };
}   // namespace m1
