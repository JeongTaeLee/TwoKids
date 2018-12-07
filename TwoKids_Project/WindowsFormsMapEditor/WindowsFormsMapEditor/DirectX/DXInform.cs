using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;
using WindowsFormsMapEditor;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

using Framework;


namespace DxBasic
{
    public class DXInform
    {
        private Sprite sprite = null;
        //private Texture texture= null;

        private Device dx_device = null;

        public Device Dx_device { get => dx_device; set => dx_device = value; }
        public Sprite Dx_Sprite { get => sprite; set => sprite = value; }

        public void MakeDevice(Panel panel)
        {
            PresentParameters pp = new PresentParameters();
            pp.Windowed = true;
            pp.SwapEffect = SwapEffect.Discard;

            dx_device = new Device(0,
                                DeviceType.Hardware,
                                panel,
                                CreateFlags.SoftwareVertexProcessing,
                                pp);

            sprite = new Sprite(dx_device);
            //texture = TextureLoader.FromFile(dx_device, "../../../Image/test.png", 
            //    640, 480, 0, Usage.None, Format.A8R8G8B8,
            //    Pool.Managed, Filter.None, Filter.None, 0);
        }

        public void BeginDraw()
        {
            dx_device.Clear(ClearFlags.Target, Color.Blue, 1.0f, 0);
            dx_device.BeginScene();

            sprite.Begin(SpriteFlags.AlphaBlend);
            //sprite.Draw2D(texture, new Point(0, 0), 0.0f, new Point(0, 0), Color.White);
        }
        public void EndDraw()
        {
            sprite.End();
            dx_device.EndScene();
            dx_device.Present();
        }

        public DXInform()
        {

        }
    }
}