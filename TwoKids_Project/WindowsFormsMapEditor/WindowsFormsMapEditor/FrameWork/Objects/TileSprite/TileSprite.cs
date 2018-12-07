using System.Text;
using System.Drawing;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

using Framework;
using Framework.Main;
using DxBasic;
using System.IO;

public class TileSprite : GameObject
{
    private string spriteName = null;
    private string spriteState = null;

    public string SpriteName { get => spriteName; set => spriteName = value; }
    private Point size = new Point(48, 48);

    public Point Size { get => size; set => size = value; }
    public string SpriteState { get => spriteState; set => spriteState = value; }

    public override void Update()
    {

        base.Update();
    }
    public void Render(Rectangle rectangle, Rectangle size, Point rotationCenter, float angle, Point point, Color color)
    {
        Point _point = new Point(point.X + ScrollManager.GetT.MainScrollPoint.X, point.Y + ScrollManager.GetT.MainScrollPoint.Y);
        MainGame.GetT.mainDX.Dx_Sprite.Draw2D(texture, rectangle, size, rotationCenter, angle, _point, color);
        transform.position = point;

        base.Render();
    }

    public void InputFile(string path, StreamWriter sw)
    {
        sw.WriteLine(spriteState + " " + SpriteName.ToString() + " " + transform.position.X + " " + transform.position.Y);
    }
    public void ColliderInputFile(StreamWriter sw)
    {
        sw.WriteLine(spriteState + " " + transform.position.X + " " + transform.position.Y + " " + Size.X + " " +  Size.Y);
    }
}