#include "include/TileMap.h"

TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet):Component(associated){

    Load(file);
    this->tileSet = tileSet;
}

void TileMap::Load(string file){
    ifstream map;

    //Open file, and verify if task was successful
    map.open(file);
    if(!map){
        cout<<"Couldn't open "<<file<<" file"<<endl;
    }

   string aux;

   //Read the first parameters of the file, giving the map width, height and depth
   getline(map, aux, ',');
   mapWidth = stoi(aux);
   getline(map, aux, ',');
   mapHeight = stoi(aux);
   getline(map, aux, ',');
   mapDepth = stoi(aux);

   //Read rest of the text file, storing each value in tileMatrix, in order
   for(int d=0;d<mapDepth;d++){
       for(int h=0;h<mapHeight;h++){
           for(int w=0;w<mapWidth;w++){
                getline(map, aux, ',');
                tileMatrix.push_back(stoi(aux)-1);
           }
       }
   }
}

void TileMap::SetTileSet(TileSet *tileSet){
    this->tileSet = tileSet;
}

int TileMap::GetIndex(int width, int height, int layer){
    return layer*mapHeight*mapWidth + height*mapWidth + width;
}

int& TileMap::At(int x, int y, int z){
    return tileMatrix[GetIndex(x, y, z)];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
    for(int h=0; h<mapHeight;h++){
        for(int w=0; w<mapWidth;w++){
            if(At(w, h, layer)!=-1){
                tileSet->RenderTile(At(w, h, layer), w*tileSet->GetTileWidth() - cameraX, h*tileSet->GetTileHeight() - cameraY, layer);
            }
        }
    }
}

void TileMap::Render(){
    /*for(int layer=0; layer<mapDepth;layer++){
        RenderLayer(layer);
    }*/
    RenderLayer(associated.layer);
    associated.layer = -1;
}

void TileMap::Update(float){}

bool TileMap::Is(string type){
    return (!type.compare("tilemap"));
}

int TileMap::GetWidth(){
    return mapWidth;
}

int TileMap::GetHeight(){
    return mapHeight;
}

int TileMap::GetDepth(){
    return mapDepth;
}
