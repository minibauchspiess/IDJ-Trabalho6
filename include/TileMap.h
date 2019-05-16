#ifndef TILEMAP_H
#define TILEMAP_H

#include "Gameobject.h"
#include "TileSet.h"
#include "Camera.h"
#include <fstream>

using namespace std;

class TileMap : public Component
{
public:
    TileMap(GameObject& associated, string file, TileSet* tileSet);

    void Load(string file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z = 0);
    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

    void Render();
    void Update(float);
    bool Is(string);

    int GetWidth();
    int GetHeight();
    int GetDepth();
    int GetIndex(int layer, int height, int width);

private:
    vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;
};

#endif // TILEMAP_H
