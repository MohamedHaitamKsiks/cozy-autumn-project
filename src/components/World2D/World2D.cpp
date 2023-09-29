#include "World2D.h"

EXPORT(World2D, Name, TilesetName)

World2D* World2D::Instance = nullptr;

void World2D::OnCreate()
{
    Instance = this;

    // cache scene ids
    ResourceID solidTileSceneID = ResourceManager<Scene>::GetResourceId(UniqueString("scenes/solidtile.scene.json"));

    // load tileset material
    Image tilesetImage;
    tilesetImage.Load(TilesetName);
    
    Texture tilesetTexture = Texture::LoadFromImage(tilesetImage);
    TilesetTexture = tilesetTexture;

    ResourceID defaultShaderID = ResourceManager<Shader>::GetResourceId(UniqueString("shaders/default.glsl"));
    TilesetMaterialID = ResourceManager<Material>::Add();
    auto& tilesetMaterial = ResourceManager<Material>::Get(TilesetMaterialID);

    tilesetMaterial.Create(defaultShaderID);
    tilesetMaterial.SetShaderParam(UniqueString("u_Texture"), tilesetTexture);
    
    // load world file
    File worldFile;
    worldFile.Open(Name, FileOpenMode::READ);

    std::string worldFileContent = worldFile.ReadText();

    worldFile.Close();

    // parse to json
    Json world = Json::parse(worldFileContent);

    // get levels
    auto levels = world["levels"];
    for (auto level: levels)
    {
        // add level
        Level2D level2D;
        level2D.Position.x = level["worldX"];
        level2D.Position.y = level["worldY"];
        level2D.Size.x = level["pxWid"];
        level2D.Size.y = level["pxHei"];

        Levels.Push(level2D);

        int LevelID = Levels.GetSize() - 1;

        // create tilemap2D
        TileMap2D tilemap2D;
        tilemap2D.LevelID = LevelID;

        // tilemap transform
        Transform2D tilemapTransform2D;
        tilemapTransform2D.Position = level2D.Position;

        // add layers
        auto layers = level["layerInstances"];
        for (auto layer: layers)
        {
            std::string layerIdentifier = layer["__identifier"];
            

            if (layerIdentifier == "Entities")
            {
                // spawn entities
                auto entityInstances = layer["entityInstances"];
                for (auto instance: entityInstances)
                {
                    // get scene
                    std::string sceneName = instance["fieldInstances"][0]["__value"];
                    ResourceID sceneID = ResourceManager<Scene>::GetResourceId(UniqueString(sceneName));
                    auto& scene = ResourceManager<Scene>::Get(sceneID);

                    // set transform
                    Transform2D transform2D;
                    transform2D.Position.x = instance["__worldX"];
                    transform2D.Position.y = instance["__worldY"];

                    SpawningSystem2D::SpawnSceneAt(scene, transform2D);
                }
            }
            else if (layerIdentifier == "SolidGrid")
            {
                auto grid = layer["intGridCsv"];
                int gridSize = layer["__gridSize"];
                int cellWidth = layer["__cWid"];
                int cellHeight = layer["__cHei"];

                for (int i = 0; i < grid.size(); i++)
                {
                    if (grid[i] == 0) continue;

                    // set transform
                    Transform2D solidTileTransform2D;
                    solidTileTransform2D.Position.x = (float) ( i % cellWidth) * gridSize + level2D.Position.x;
                    solidTileTransform2D.Position.y = (float) (i / cellWidth) * gridSize + level2D.Position.y;

                    // spawn scene at transform
                    auto& solidTileScene = ResourceManager<Scene>::Get(solidTileSceneID);
                    SpawningSystem2D::SpawnSceneAt(solidTileScene, solidTileTransform2D);
                }
            }
            else 
            {
                // create tilelayer
                TileMapLayer2D tilemapLayer2D;

                // set grid size
                tilemap2D.TileSize = layer["__gridSize"];
                
                // add tiles
                for (auto tile: layer["gridTiles"])
                {
                    Tile2D tile2D;

                    tile2D.Position.x = tile["px"][0];
                    tile2D.Position.y = tile["px"][1];

                    tile2D.Source.x = tile["src"][0];
                    tile2D.Source.y = tile["src"][1];

                    tilemapLayer2D.Tiles.Push(tile2D);
                }

                // add tile layer
                tilemap2D.Layers.Push(tilemapLayer2D);
            }

            // create entity
            EntityBuilder tileMapBuilder;
            tileMapBuilder.AddComponents(tilemap2D, tilemapTransform2D);
            World::Create(tileMapBuilder);
            
        }
    }

}

void World2D::OnDestroy()
{
    Instance = nullptr;

    ResourceManager<Material>::Remove(TilesetMaterialID);
}
