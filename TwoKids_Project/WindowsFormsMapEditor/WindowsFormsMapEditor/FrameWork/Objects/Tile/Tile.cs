using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

using Framework;
using Framework.Main;
using DxBasic;


public class Tile : GameObject
{
    private bool isSelectTile = false;
    private Point size = new Point(48, 48);

    public Point Size { get => size; set => size = value; }

    private List<TileSprite> tileSprites = new List<TileSprite>();
    private TileSprite tileCollider = null;

    override public void Init()
    {
        texture = ResourceManager.GetT.GetTexture("../../../Image/tile.png", MainGame.GetT.mainDX.Dx_device);
    }
    override public void Update()
    {
        if (isSelectTile == false)
        {
            if (IsCollision(size, GetMousePos()))
            {
                texture = ResourceManager.GetT.GetTexture("../../../Image/tileSelect.png", MainGame.GetT.mainDX.Dx_device);
                int x = GetMousePos().X;
                isSelectTile = true;
            }
        }
        else
        {
            if (IsCollision(size, GetMousePos()) == false)
            {
                texture = ResourceManager.GetT.GetTexture("../../../Image/tile.png", MainGame.GetT.mainDX.Dx_device);
                isSelectTile = false;
            }
        }
    }
    override public void Render()
    {
        Point _point = new Point((int)((transform.position.X + ScrollManager.GetT.MainScrollPoint.X) / (float)((float)size.X / 48.0f)),
            (int)((transform.position.Y + ScrollManager.GetT.MainScrollPoint.Y) / (float)((float)size.Y / 48.0f)));
        MainGame.GetT.mainDX.Dx_Sprite.Draw2D(texture, Rectangle.Empty, new Rectangle(0, 0, size.X, size.Y),
            transform.rotationCenter, 0, _point, color);

        foreach (var iter in tileSprites)
        {
            iter.Render(Rectangle.Empty, Rectangle.Empty, transform.rotationCenter, 0, transform.position, color);
        }
        if (tileCollider != null)
        {
            Point colliderPoint = new Point((int)((tileCollider.Position.X + ScrollManager.GetT.MainScrollPoint.X) / (float)((float)tileCollider.Size.X / 48.0f)),
               (int)((tileCollider.Position.Y + ScrollManager.GetT.MainScrollPoint.Y) / (float)((float)tileCollider.Size.Y / 48.0f)));

            MainGame.GetT.mainDX.Dx_Sprite.Draw2D(tileCollider.Texture, Rectangle.Empty, new Rectangle(0, 0, tileCollider.Size.X, tileCollider.Size.Y),
            transform.rotationCenter, 0, colliderPoint, color);
            //tileCollider.Render(Rectangle.Empty, new Rectangle(0, 0, tileCollider.Size.X, tileCollider.Size.Y),
            //    transform.rotationCenter, 0, colliderPoint, color);
        }
    }
    override public void Release()
    {

    }

    public TileSprite SetSpriteTile(string route, string name, string tileState)
    {
        for (int i = 0; i < tileSprites.Count; i++)
        {
            if (tileSprites[i].SpriteName == name)
                return tileCollider;
        }
        TileSprite tileSprite = new TileSprite();
        tileSprite.Texture = ResourceManager.GetT.GetTexture(route, MainGame.GetT.mainDX.Dx_device);
        tileSprite.SpriteName = name;
        tileSprite.SpriteState = tileState;
        Image image = new Bitmap(route);
        tileSprite.Size = new Point(image.Width, image.Height);
        if(name == "tileCollider.png")
        {
            tileSprite.Position = transform.position;
            tileCollider = tileSprite;
            tileCollider.Size = TileManager.GetT.ColliderSize;
            return tileSprite;
        }
        else
            tileSprites.Add(tileSprite);
        return null;
    }
    public void DestroySpriteTile()
    {
        tileCollider = null;
        tileSprites.Clear();
    }

    public void SaveSpriteTiles(string path, StreamWriter streamWriter)
    {
        foreach (var iter in tileSprites)
        {
            iter.InputFile(path, streamWriter);
        }
        if(tileCollider != null)
            tileCollider.ColliderInputFile(streamWriter);
    }
}