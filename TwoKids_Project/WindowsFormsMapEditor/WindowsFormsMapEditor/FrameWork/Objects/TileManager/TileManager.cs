using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Drawing;

using Framework;
using WindowsFormsMapEditor.FrameWork.Objects.Tile;
using Microsoft.DirectX.Direct3D;
using WindowsFormsMapEditor;

public class TileManager : Singleton<TileManager>
{
    private List<Tile> l_tiles = new List<Tile>();
    private List<SelectTile> s_tiles = new List<SelectTile>();
    private string nowSelectTile = null;
    private string nowSelectTileName = null;
    private string nowSelectTileState = null;
    private int size = 0;

    private TileSprite nowTileCollider = null;

    private Point colliderPos = new Point(0, 0);
    private Point colliderSize = new Point(48, 48);

    public Point ColliderPos { get => colliderPos; set => colliderPos = value; }
    public Point ColliderSize { get => colliderSize; set => colliderSize = value; }

    public void Init()
    {
        for(int i = 0; i < 405; i++)
        {
            Tile tile = new Tile();
            tile.Position = new Point((i % 27) * 48, (i / 27) * 48); 
            l_tiles.Add(tile);
        }
        foreach (var iter in l_tiles)
        {
            iter.Init();
        }
    }
    #region Factory Function
    public void SideInit()
    {
        foreach (var iter in s_tiles)
        {
            iter.Init();
        }
    }
    public void Update()
    {
        foreach (var iter in l_tiles)
        {
            iter.Update();
        }
    }
    public void SideUpdate()
    {
        foreach (var iter in s_tiles)
        {
            iter.Update();
        }
    }
    public void Render()
    {
        foreach (var iter in l_tiles)
        {
            iter.Render();
        }
    }
    public void SideRender()
    {
        foreach (var iter in s_tiles)
        {
            iter.Render();
        }
    }
    public void Release()
    {
        foreach (var iter in l_tiles)
        {
            iter.Release();
        }
    }
    #endregion

    public void ChageMapSize(Point mapSize, Point size)
    {
        l_tiles.Clear();
        for(int i = 0; i < mapSize.X * mapSize.Y; i++)
        {
            Tile tile = new Tile();
            tile.Position = new Point((i % mapSize.X) * size.X, (i / mapSize.X) * size.Y);
            l_tiles.Add(tile);
        }
        foreach (var iter in l_tiles)
        {
            iter.Init();
        }
    }
    public void SetTileScale(Point mapSize, Point size)
    {
        foreach (var iter in l_tiles)
        {
            iter.Size = size;
        }
        for (int i = 0; i < mapSize.X * mapSize.Y; i++)
        {
            l_tiles[i].Position = new Point((i % mapSize.X) * size.X, (i / mapSize.X) * size.Y);
        }
    }
    public void AddSelectTile(string tileState, Texture tex, string str, string name)
    {
        SelectTile _tile = new SelectTile();
        _tile.Texture = tex;
        _tile.Route = str;
        _tile.Name = name;
        _tile.ChangeSize();
        _tile.SpriteState = tileState;
        if (size != 0)
        {
            Point point = s_tiles[size - 1].Position;
            point.Y += s_tiles[size - 1].GetSize.Y;
            _tile.Position = point;
        }
        s_tiles.Add(_tile);
        size++;
    }
    public void SelectTileClick()
    {
        foreach (var iter in s_tiles)
        {
            if (iter.IsCollision(iter.GetSize, iter.GetSubMousePos()))
            {
                nowSelectTile = iter.Route;
                nowSelectTileName = iter.Name;
                nowSelectTileState = iter.SpriteState;
            }
        }
    }
    public void TileClick()
    {
        foreach(var iter in l_tiles)
        {
            if (iter.IsCollision(iter.Size, iter.GetMousePos()) && nowSelectTile != null)
                nowTileCollider = iter.SetSpriteTile(nowSelectTile, nowSelectTileName, nowSelectTileState);
        }
    }
    public void AddTile(Point position, string tileName, string tileState)
    {
        foreach (var iter in l_tiles)
        {
            if (iter.Position == position)
                iter.SetSpriteTile("../../../Image/Tiles/" + tileName, tileName, tileState);
        }
    }
    public void DestroyClick()
    {
        foreach (var iter in l_tiles)
        {
            if (iter.IsCollision(iter.Size, iter.GetMousePos()))
                iter.DestroySpriteTile();
        }
    }
    public void SaveFile(string path, StreamWriter streamWriter)
    {
        foreach (var iter in l_tiles)
        {
            iter.SaveSpriteTiles(path, streamWriter);
        }
    }

    public void ChangeColliderTransform(Point pos, Point size)
    {
        if (nowTileCollider != null)
        {
            Point tempPos = nowTileCollider.Position;
            tempPos.X += pos.X;
            tempPos.Y += pos.Y;
            nowTileCollider.Position = tempPos;
            nowTileCollider.Size = size;
            ColliderPos = tempPos;
            ColliderSize = size;
        }
    }

    public void AddTileToState(StreamReader sw, string route)
    {
        Point point = new Point(0, 0);
        string line = sw.ReadLine();
        string[] result = line.Split(' ');

        if(result[0] == "Collider")
        {
            int x, y, width, height;
            Point size = new Point(0, 0);
            Int32.TryParse(result[1], out x);
            Int32.TryParse(result[2], out y);
            Int32.TryParse(result[3], out width);
            Int32.TryParse(result[4], out height);
            point.X = x; point.Y = y;
            size.X = width; size.Y = height;
            foreach (var iter in l_tiles)
            {
                if (iter.Position == point)
                {
                    nowTileCollider = iter.SetSpriteTile("../../../Image/" + "tileCollider.png", "tileCollider.png", "Collider");
                    nowTileCollider.Size = size;
                }
            }
        }
        else if(result[0] == "Monster")
        {
            int x, y;
            string tileState = result[0];
            string tileName = result[1];
            Int32.TryParse(result[2], out x);
            Int32.TryParse(result[3], out y);
            point.X = x; point.Y = y;
            foreach (var iter in l_tiles)
            {
                if (iter.Position == point)
                    iter.SetSpriteTile("../../../Image/Monster/" + tileName, tileName, tileState);
            }
        }
        else
        {
            int x, y;
            string tileState = result[0];
            string tileName = result[1];
            Int32.TryParse(result[2], out x);
            Int32.TryParse(result[3], out y);
            point.X = x; point.Y = y;
            foreach (var iter in l_tiles)
            {
                if (iter.Position == point)
                    iter.SetSpriteTile(route + tileName, tileName, tileState);
            }
        }
    }
}