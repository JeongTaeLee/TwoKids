using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

using Framework;
using Framework.Main;

namespace WindowsFormsMapEditor.FrameWork.Objects.Tile
{
    class SelectTile : GameObject
    {
        private string route = null;
        private string name = null;
        private Point size = new Point(0, 0);
        private string spriteState = null;
        public Point GetSize { get => size; }

        public string Route { get => route; set => route = value; }
        public string Name { get => name; set => name = value; }
        public string SpriteState { get => spriteState; set => spriteState = value; }

        public override void Init()
        {
            base.Init();
        }
        public override void Update()
        {
            base.Update();
        }
        public override void Render()
        {
            Point _point = new Point(transform.position.X + ScrollManager.GetT.SubScrollPoint.X,
                transform.position.Y + ScrollManager.GetT.SubScrollPoint.Y);
            MainGame.GetT.tileDX.Dx_Sprite.Draw2D(texture, transform.rotationCenter, transform.angle, _point, color);
            base.Render();
        }
        public override void Release()
        {
            base.Release();
        }
        public void ChangeSize()
        {
            Image image = new Bitmap(route);
            size.X = image.Width;
            size.Y = image.Height;
        }
    }
}
