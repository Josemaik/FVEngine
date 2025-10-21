#include "Mapa.h"

Mapa *Mapa::instance = nullptr;
Mapa* Mapa::getInstancia(){
    if(instance == 0){
        instance = new Mapa("resources/inicio.tmx");
    }
    return instance;
}
Mapa::Mapa(const std::string rutaMapa){
    //---------------------------------------------------------------------------------------------------------------------------------------------
    
    //Carga el archivo TMX.
    XMLDocument doc;
    if (doc.LoadFile(rutaMapa.c_str()) != XML_SUCCESS) {
        cout << "Error al cargar el TMX" << endl;
    }
    else {
        std::cout << "Archivo TMX cargado" << std::endl;
    }

    // Tamaño de mapa y tiles
    XMLElement* map = doc.FirstChildElement("map");
    mapWidth = map->IntAttribute("width");
    mapHeight = map->IntAttribute("height");
    tileWidth = map->IntAttribute("tilewidth");
    tileHeight = map->IntAttribute("tileheight");


    // Obtener capas
    XMLElement* capa = map->FirstChildElement("layer");
    numCapas = 1;


    mapSprite = new sf::Sprite***[numCapas];
    for(int l=0; l<numCapas; l++){
        mapSprite[l] = new sf::Sprite**[mapHeight];
    }

    for(int l=0; l<numCapas; l++){
        for(int y=0; y<mapHeight; y++){
            mapSprite[l][y] = new sf::Sprite*[mapWidth];
            for(int x=0; x<mapWidth; x++){
                mapSprite[l][y][x] = new sf::Sprite();
            }
        }
    }


    // Obtener la cantidad de tilesets y cargar cada tileset en textura
    XMLElement* tileset = map->FirstChildElement("tileset");
    XMLDocument doc2;
    doc2.LoadFile(tileset->Attribute("source"));

    XMLElement *tilesetElement = doc2.FirstChildElement("tileset");
    XMLElement *imageElement = tilesetElement->FirstChildElement("image");
    imgFILE = imageElement->Attribute("source");
    sf::Texture textTile;

    if(!textTile.loadFromFile(imgFILE)){
        std::cerr << "Error al cargar el archivo de textura "<< "\n";
    }
    
    int textureWidth = textTile.getSize().x / tileWidth;
    int textureHeight = textTile.getSize().y / tileHeight;
    int totalSprites = textureWidth*textureHeight;
    tilesSprites = new sf::Sprite[totalSprites];

    int n=0;
    for(int y=0; y<textureHeight; y++){
        for(int x=0; x<textureWidth; x++){
            tilesSprites[n] = sf::Sprite(textTile);
            tilesSprites[n].setTextureRect(sf::IntRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight));
            
            n++;
        }
    }

    XMLElement* layerELM = map->FirstChildElement("layer");
    for(int l = 0; l < numCapas; l++){
        XMLElement* tile = layerELM->FirstChildElement("data")->FirstChildElement("tile");
        for(int y = 0; y < mapHeight; y++){
            for(int x = 0; x < mapWidth; x++){
                int gid;
                tile->QueryIntAttribute("gid", &gid);

                if(gid>=mapWidth*mapHeight){
                    cout << "Error, gid at (l, x, y)= (" << l << "," << x << "," << y << ") :" << gid << "fuera del rango del tileset (" << mapWidth*mapHeight << ")" << endl;
                } else if(gid>0){
                    mapSprite[l][y][x] = new sf::Sprite(textTile, tilesSprites[gid-1].getTextureRect());
                    mapSprite[l][y][x]->setPosition(x*tileWidth, y*tileHeight);
                } else{
                    mapSprite[l][y][x] = NULL;
                }

                tile = tile->NextSiblingElement("tile");
            }
        }
    }

    //----------------------------------------------------------------------------------------------------------------------------------------------
    //Creamos matriz de colision
    sf::RectangleShape obstacles[MAP_ANCHO][MAP_ALTO];
    for (int i = 0; i < MAP_ANCHO; i++) {
        for (int j = 0; j < MAP_ALTO; j++) {
            if (i == 0 || i == MAP_ANCHO - 1 || j == 0 || j == MAP_ALTO - 1 || mapp[i][j] == 1) {
                obstacles[i][j] = sf::RectangleShape(sf::Vector2f(TILE_TAM, TILE_TAM));
                obstacles[i][j].setFillColor(sf::Color::Transparent);
                obstacles[i][j].setPosition(i * TILE_TAM, j * TILE_TAM);
            }
        }
    }
    
    obstaclesArray = new sf::RectangleShape*[MAP_ANCHO];
    for (int i = 0; i < MAP_ANCHO; i++) {
        obstaclesArray[i] = new sf::RectangleShape[MAP_ALTO];
    }

    // Copiar los valores de la matriz obstacles a la nueva matriz dinámica
    for (int i = 0; i < MAP_ANCHO; i++) {
        for (int j = 0; j < MAP_ALTO; j++) {
            obstaclesArray[i][j] = obstacles[i][j];
        }
    }
}

Mapa::~Mapa(){
    if (mapSprite) {
        for (int l = 0; l < numCapas; ++l) {
            if (mapSprite[l]) {
                for (int y = 0; y < mapHeight; ++y) {
                    if (mapSprite[l][y]) {
                        delete[] mapSprite[l][y];
                    }
                }
                delete[] mapSprite[l];
            }
        }
        delete[] mapSprite;
        mapSprite = nullptr;
    }
}




sf::Sprite**** Mapa::getMapa(){
    return mapSprite;
}
int Mapa::getNumCapas(){
    return numCapas;
}
int Mapa::getMap_Width(){
    return mapWidth;
}
int Mapa::getMap_Height(){
    return mapHeight;
}
sf::RectangleShape** Mapa::getObstacles(){
    return obstaclesArray;
}

sf::Sprite* Mapa::getVectorImagen(){
    return tilesSprites;
}

std::string Mapa::getRuta(){
    return imgFILE;
}