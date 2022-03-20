#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <string>

#include "transform2D.h"
#include "Shapes/Primitives/Circle.h"
#include "Shapes/Entities/Player.h"
#include "Shapes/Entities/MapEdges.h"
#include "Shapes/Entities/Obstacles.h"
#include "EnemyManager.h"

using namespace std;
using namespace m1;

int Tema1::score = 0;

Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = 4;   // logic width
    logicSpace.height = 4;  // logic height

    glm::vec3 corner = glm::vec3(0.001, 0.001, 0);
    length = 0.99f;

    Primitive::meshes = &meshes;

    insertInEntityMap("mapEdges", new MapEdges());
    insertInEntityMap("mapObstacles", new Obstacles());
    player = new Player(2, 2, 0.3f, 0, this);
    insertInEntityMap("enemyManager", new EnemyManager(this));
}

void Tema1::insertInEntityMap(std::string key, Entity* e)
{
    entities[key] = e;
    orderedEntities.push_back(e);
}


// 2D visualization matrix
glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}


// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    sx < sy ? smin = sx : smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}


void Tema1::renderAllEntities(glm::mat3 visMatrix)
{
    for (const auto& primitive : player->orderedPrimitives)
    {
        RenderMesh2D(primitive->getMesh(), shaders["VertexColor"], visMatrix * primitive->getModelMatrix());
    }

    for (auto entity = orderedEntities.rbegin(); entity != orderedEntities.rend(); ++entity)
    {
        if ((*entity)->getIsHUD())
        {
            for (const auto& primitive : (*entity)->orderedPrimitives)
            {
                RenderMesh2D(primitive->getMesh(), shaders["VertexColor"], visMatrix * primitive->getModelMatrix());
            }
        }
    }

    for (auto entity = orderedEntities.rbegin(); entity != orderedEntities.rend(); ++entity)
    {
        if (!(*entity)->getIsHUD())
        {
            for (const auto& primitive : (*entity)->orderedPrimitives)
            {
                RenderMesh2D(primitive->getMesh(), shaders["VertexColor"], visMatrix * primitive->getModelMatrix());
            }
        }
    }
}


void Tema1::updateAllInTime(float deltaTime)
{
    for (auto& entity : entities)
    {
        ITimeDependant* tDepEntity = dynamic_cast<ITimeDependant*>(entity.second);
        if (tDepEntity != NULL)
        {
            tDepEntity->changeInTime(deltaTime);
        }
    }
}


void Tema1::translateHUD(float tx, float ty)
{
    logicSpace.x += tx;
    logicSpace.y += ty;

    player->translate(tx, ty);
    for (auto& entity : entities)
    {
        if (!entity.second->getIsHUD()) continue;
        entity.second->translate(tx, ty);
    }
}


void Tema1::processPlayerCollisions()
{
    for (auto& entity : entities)
    {
        ICollidable* collidableEntity = dynamic_cast<ICollidable*> (entity.second);
        if (collidableEntity != NULL) {
            if (player->doesCollide(collidableEntity) || collidableEntity->doesCollide(player))
            {
                collidableEntity->ProcessCollision(player);
                player->ProcessCollision(collidableEntity);
            }
        }
    }
}


void Tema1::processCollisions()
{
    processPlayerCollisions();
    for (auto entity1 = entities.begin(); entity1 != entities.end(); ++entity1)
    {
        for (auto& primitive1 : entity1->second->orderedPrimitives)
        {
            ICollidable* collidableEntity1 = dynamic_cast<ICollidable*>(primitive1);
            if (collidableEntity1 == NULL) continue;
            for (auto entity2 = std::next(entity1); entity2 != entities.end(); ++entity2)
            {
                for (auto& primitive2 : entity2->second->orderedPrimitives)
                {
                    ICollidable* collidableEntity2 = dynamic_cast<ICollidable*>(primitive2);
                    if (collidableEntity2 == NULL) continue;
                    if (collidableEntity1->doesCollide(collidableEntity2) || collidableEntity2->doesCollide(collidableEntity1))
                    {
                        collidableEntity1->ProcessCollision(collidableEntity2);
                        collidableEntity2->ProcessCollision(collidableEntity1);
                    }
                }

                ICollidable* collidableEntity2 = dynamic_cast<ICollidable*>(entity2->second);
                if (collidableEntity2 != NULL) {
                    if (collidableEntity1->doesCollide(collidableEntity2) || collidableEntity2->doesCollide(collidableEntity1))
                    {
                        collidableEntity1->ProcessCollision(collidableEntity2);
                        collidableEntity2->ProcessCollision(collidableEntity1);
                    }
                }

            }
        }

        ICollidable* collidableEntity1 = dynamic_cast<ICollidable*>(entity1->second);
        if (collidableEntity1 == NULL) continue;

        for (auto entity2 = std::next(entity1); entity2 != entities.end(); ++entity2)
        {
            for (auto& primitive2 : entity2->second->orderedPrimitives)
            {
                ICollidable* collidableEntity2 = dynamic_cast<ICollidable*>(primitive2);
                if (collidableEntity2 == NULL) continue;
                if (collidableEntity1->doesCollide(collidableEntity2) || collidableEntity2->doesCollide(collidableEntity1))
                {
                    collidableEntity1->ProcessCollision(collidableEntity2);
                    collidableEntity2->ProcessCollision(collidableEntity1);
                }
            }

            ICollidable* collidableEntity2 = dynamic_cast<ICollidable*>(entity2->second);
            if (collidableEntity2 != NULL) {
                if (collidableEntity1->doesCollide(collidableEntity2) || collidableEntity2->doesCollide(collidableEntity1))
                {
                    collidableEntity1->ProcessCollision(collidableEntity2);
                    collidableEntity2->ProcessCollision(collidableEntity1);
                }
            }
        }
    }
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Tema1::Update(float deltaTimeSeconds)
{
    if (deltaTimeSeconds > 0.02f) deltaTimeSeconds = 0.02f;
    glm::ivec2 resolution = window->GetResolution();
    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, backgroundColor, true);

    // Compute uniform 2D visualization matrix
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);

    processCollisions();
    updateAllInTime(deltaTimeSeconds);
    DrawScene(visMatrix);
}


void Tema1::FrameEnd()
{
}


void Tema1::DrawScene(glm::mat3 visMatrix)
{
    renderAllEntities(visMatrix);
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    if (deltaTime > 0.02f) deltaTime = 0.02f;

    if (window->KeyHold(GLFW_KEY_W)) {
        translateHUD(0, deltaTime);
        processPlayerCollisions();
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        translateHUD(-deltaTime, 0);
        processPlayerCollisions();
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        translateHUD(0, -deltaTime);
        processPlayerCollisions();
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        translateHUD(deltaTime, 0);
        processPlayerCollisions();
    }

    if (window->KeyHold(GLFW_KEY_Z)) {
        logicSpace.x += deltaTime / 2;
        logicSpace.y += deltaTime / 2;
        logicSpace.height -= deltaTime;
        logicSpace.width -= deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_X)) {
        logicSpace.x -= deltaTime / 2;
        logicSpace.y -= deltaTime / 2;
        logicSpace.height += deltaTime;
        logicSpace.width += deltaTime;
    }

    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
    {
        player->shoot(BulletStream::shotPattern::STRAIGHT);
    }

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        player->shoot(BulletStream::shotPattern::SHOTGUN);
    }

}


void Tema1::OnKeyPress(int key, int mods)
{
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    glm::ivec2 resolution = window->GetResolution();
    float mX = mouseX - resolution[0] / 2.0;
    float mY = -mouseY + resolution[1] / 2.0;
    player->placeAt(player->xc, player->yc, player->sizeX, player->sizeY, glm::atan2(mY, mX));
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}
