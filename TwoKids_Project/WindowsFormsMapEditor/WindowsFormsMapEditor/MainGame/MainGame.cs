using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using WindowsFormsMapEditor;
using DxBasic;

namespace Framework.Main
{
    public class MainGame : Singleton<MainGame>
    {
        private Point formPosition = new Point(0, 0);
        public Point FormPosition { get => formPosition; set => formPosition = value; }
        public DXInform mainDX = null;
        public DXInform tileDX = null;

        public void Init()
        {
            TileManager.GetT.SideInit();
            TileManager.GetT.Init();
        }

        public void Update()
        {
            TileManager.GetT.SideUpdate();
            TileManager.GetT.Update();
        }

        public void Render()
        {
            tileDX.BeginDraw();
            TileManager.GetT.SideRender();
            tileDX.EndDraw();
            mainDX.BeginDraw();
            TileManager.GetT.Render();
            mainDX.EndDraw();
        }

        public void Release()
        {

        }
    }
}