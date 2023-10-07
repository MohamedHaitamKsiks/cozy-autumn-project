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
                    std::string identifier = instance["__identifier"];

                    // get scene
                    std::string sceneName = instance["fieldInstances"][0]["__value"];
                    ResourceID sceneID = ResourceManager<Scene>::GetResourceId(UniqueString(sceneName));
                    Scene scene = ResourceManager<Scene>::Get(sceneID);

                    // set transform
                    Transform2D transform2D;
                    transform2D.Position.x = instance["__worldX"];
                    transform2D.Position.y = instance["__worldY"];
                    SpawningSystem2D::AddComponentToScene(scene, transform2D);

                    // if grass area add collision and grass
                    if (identifier == "GrassArea")
                    {
                        // add collision box
                        CollisionBox2D collisionBox2D;
                        collisionBox2D.Size.x = instance["width"];
                        collisionBox2D.Size.y = instance["height"];
                        collisionBox2D.Offset.y = -collisionBox2D.Size.y;
                        collisionBox2D.CollisionLayers = 1;
                        collisionBox2D.DrawDebug = false;

                        SpawningSystem2D::AddComponentToScene(scene, collisionBox2D);
                    
                        // add grass 
                        GrassParticles2D grassParticles2D;
                        grassParticles2D.Width = collisionBox2D.Size.x;

                        SpawningSystem2D::AddComponentToScene(scene, grassParticles2D);
                    }

                    scene.Instantiate();
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

                    int cellX = i % cellWidth;
                    int cellY = i / cellWidth;

                    // check if cell is surrounded by other cells
                    bool cellTopFilled = cellY - 1 < 0 || grid[cellX + (cellY - 1) * cellWidth] == 1;
                    bool cellBottomFilled = cellY + 1 > cellHeight - 1 || grid[cellX + (cellY + 1) * cellWidth] == 1;
                    bool cellLeftFilled = cellX - 1 < 0 || grid[cellX - 1 + cellY * cellWidth] == 1;
                    bool cellRightFilled = cellX + 1 > cellWidth - 1 || grid[cellX + 1 + cellY * cellWidth] == 1;

                    if (cellTopFilled && cellBottomFilled && cellLeftFilled && cellRightFilled) continue;

                    // set transform
                    Transform2D solidTileTransform2D;
                    solidTileTransform2D.Position.x = (float) cellX * gridSize + level2D.Position.x;
                    solidTileTransform2D.Position.y = (float) cellY * gridSize + level2D.Position.y;

                    // spawn scene at transform
                    Scene solidTileScene = ResourceManager<Scene>::Get(solidTileSceneID);
                    SpawningSystem2D::AddComponentToScene(solidTileScene, solidTileTransform2D);
                    solidTileScene.Instantiate();
                }
            }
            else 
            {
                // create tilelayer
                TileMapLayer2D tilemapLayer2D;


                // set grid size
                tilemap2D.TileSize = layer["__gridSize"];
                
                Json layerTiles;
                if (layerIdentifier == "AutoLayer")
                {
                    layerTiles = layer["autoLayerTiles"];
                    tilemapLayer2D.Layer = DrawLayer::Tilemap;
                }
                else if (layerIdentifier == "BackgroundLayer")
                {
                    layerTiles = layer["autoLayerTiles"];
                    tilemapLayer2D.Layer = DrawLayer::BackgroundTilemap;
                }
                else
                {
                    layerTiles = layer["gridTiles"];
                    tilemapLayer2D.Layer = DrawLayer::BackgroundTilemap;
                }


                // add tiles
                for (auto tile: layerTiles)
                {
                    Tile2D tile2D;

                    tile2D.Position.x = tile["px"][0];
                    tile2D.Position.y = tile["px"][1];
                    tile2D.Position = tile2D.Position + level2D.Position;

                    tile2D.Source.x = tile["src"][0];
                    tile2D.Source.y = tile["src"][1];

                    // create tile quad
                    mat3 tileTransformMatrix = mat3::Translate(tile2D.Position);
                    vec2 tileSize2D = vec2::ONE() * tilemap2D.TileSize;
                   
                    tile2D.Quad = Quad2D(tileSize2D, tileTransformMatrix, Color::WHITE(), tile2D.Source.x / tilemap2D.TileSize, TilesetTexture.GetWidth() / tilemap2D.TileSize, tile2D.Source.y / tilemap2D.TileSize, TilesetTexture.GetHeight() / tilemap2D.TileSize);
                    
                    tileTransformMatrix = tileTransformMatrix * mat3::Translate(vec2{-1.0f, 1.0f} * 2.0f);
                    tile2D.ShadowQuad = Quad2D(tileSize2D, tileTransformMatrix, Color::BLACK(), tile2D.Source.x / tilemap2D.TileSize, TilesetTexture.GetWidth() / tilemap2D.TileSize, tile2D.Source.y / tilemap2D.TileSize, TilesetTexture.GetHeight() / tilemap2D.TileSize);

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
