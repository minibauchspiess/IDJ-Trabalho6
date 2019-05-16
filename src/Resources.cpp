#include "include/Resources.h"

unordered_map<string, SDL_Texture*> 	Resources::imageTable;
unordered_map<string, Mix_Music*> 	Resources::musicTable;
unordered_map<string, Mix_Chunk*> 	Resources::soundTable;

Resources::Resources()
{

}

SDL_Texture* Resources::GetImage(string file){

    unordered_map<string, SDL_Texture*>::iterator i;
    SDL_Texture* texture;
    Game& instance = Game::GetInstance();


    i = imageTable.find(file);
    //If the file has already been opened, return its corresponding texture
    if(i!=imageTable.end()){
        return i->second;
    }

    //Or else, open file, create texture and alocate in imageTable
    texture = IMG_LoadTexture(instance.GetRenderer(), file.c_str());
    if (texture == nullptr){
        cout<<"Error loading image"<<endl;
        cout<<SDL_GetError()<<endl;
    }
    else{
        imageTable[file] = texture;
    }

    return texture;
}

void Resources::ClearImages(){
    unordered_map<string, SDL_Texture*>::iterator i;

    //Goes through the table, destroying its textures
    for(i = imageTable.begin(); i != imageTable.end(); i++){
        SDL_DestroyTexture(i->second);
    }

    //Clear table
    imageTable.clear();
}

Mix_Music* Resources::GetMusic(string file){
    unordered_map<string, Mix_Music*>::iterator i;
    Mix_Music* music;

    i = musicTable.find(file);
    //If the file has already been opened, return its corresponding texture
    if(i!=musicTable.end()){
        return i->second;
    }

    //Or else, open file, create texture and alocate in imageTable
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr){
        cout<<"No music was loaded"<<endl;
    }
    else{
        musicTable[file] = music;
    }

    return music;
}

void Resources::ClearMusics(){
    unordered_map<string, Mix_Music*>::iterator i;

    //Goes through the table, destroying its components
    for(i = musicTable.begin(); i != musicTable.end(); i++){
        Mix_FreeMusic(i->second);
    }

    //Clear table
    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(string file){
    unordered_map<string, Mix_Chunk*>::iterator i;
    Mix_Chunk* chunk;

    i = soundTable.find(file);
    //If the file has already been opened, return its corresponding texture
    if(i!=soundTable.end()){
        return i->second;
    }

    //Or else, open file, create texture and alocate in imageTable
    chunk = Mix_LoadWAV(file.c_str());
    if (chunk == nullptr){
        cout<<"Sound file "<<file<<" failed to open"<<endl;
    }
    else{
        soundTable[file] = chunk;
    }

    return chunk;
}

void Resources::ClearSounds(){
    unordered_map<string, Mix_Chunk*>::iterator i;

    //Goes through the table, destroying its components
    for(i = soundTable.begin(); i != soundTable.end(); i++){
        Mix_FreeChunk(i->second);
    }

    //Clear table
    soundTable.clear();
}


















